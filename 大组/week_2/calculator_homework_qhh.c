#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
//数字栈节点
typedef struct OperandNode {
    double data;//采用double数字类型
    struct OperandNode*next;
} OperandNode;

typedef struct {//栈顶指针，用于访问栈顶内容，在后面用来进栈入栈才方便
    OperandNode*top;
} OperandStack;

//运算符栈节点
typedef struct OperatorNode {
    char data;
    struct OperatorNode*next;
} OperatorNode;

typedef struct {//同理可得
    OperatorNode*top;
} OperatorStack;

//对数字栈进行初始化
void operand_stack_init(OperandStack* s) {
    s->top=NULL;
}

//数字入栈
void operand_push(OperandStack* s,double data) {
    OperandNode* node = (OperandNode*)malloc(sizeof(OperandNode));
    node->data=data;
    node->next=s->top;
    s->top=node;
}

//数字出栈
double operand_pop(OperandStack* s) {
    if (s->top == NULL) {
        fprintf(stderr, "指令错误，数字栈已经是空的了\n");
        exit(EXIT_FAILURE);
    }
    OperandNode*temp = s->top;//利用临时指针替换掉top，在top被赋值为next释放掉临时指针
    double data=temp->data;
    s->top =temp->next;
    free(temp);
    return data;
}

//检查数字栈是否为空
int operand_is_empty(OperandStack* s) {
    return s->top==NULL;
}


//运算符栈初始化
void operator_stack_init(OperatorStack* s) {
    s->top = NULL;
}

//运算符入栈
void operator_push(OperatorStack* s, char data) {
    OperatorNode* node = (OperatorNode*)malloc(sizeof(OperatorNode));
    node->data=data;
    node->next=s->top;
    s->top=node;
}

//运算符出栈
char operator_pop(OperatorStack* s) {
    if (s->top == NULL) {
        fprintf(stderr, "指令错误，运算符栈已经是空的了\n");
        exit(EXIT_FAILURE);
    }
    OperatorNode*temp=s->top;
    char data=temp->data;
    s->top=temp->next;
    free(temp);
    return data;
}

//查看栈顶运算符
char operator_peek(OperatorStack* s) {
    if (s->top == NULL) return '\0';
    return s->top->data;
}

//检查运算符栈是否为空
int operator_is_empty(OperatorStack* s) {
    return s->top==NULL;
}


typedef enum {
    NUMBER,//数字
    OPERATOR,//运算符
    LEFT_PAREN,//左括号
    RIGHT_PAREN//右括号
} TokenType;

typedef struct {
    TokenType type;
    union {//采用联合体
        double num;
        char op;
    } value;//value只可以储存一个联合体的数据，达到分辨是数字还是运算符的作用
} Token;

//确定运算符的优先级
int get_priority(char op) {
    switch (op) {
        //乘除优先级最高，设置为2，加减法为1，其他默认为0
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 2;
        default:  return 0;
    }
}

//把表达式为Token数组
Token* parse_expression(const char*expr, int*token_count, int*error) {//参数：输入的表达式字符串，Token数量，有无错误标记
    *token_count = 0;//得到的Token变量的数量
    *error = 0;//标记有无错误
    Token* tokens = NULL;
    int capacity = 0;
    int len = strlen(expr);//获取字符串长度
    int i = 0;//初始化下标

    while (i<len) {
        if (isspace(expr[i])) {//忽略空白字符
            i++;
            continue;
        }

        //处理数字
        if (isdigit(expr[i])  ||   expr[i] == '.') {
            int has_point = 0;//判断是否有小数点
            double num = 0.0, fraction = 0.1;//分别储存整数和小数
            while (i < len && (isdigit(expr[i]) || expr[i]=='.'))
                {
                if (expr[i]=='.')
                    {//小数点重复，错误数字，进行错误标记
                    if (has_point) {
                        *error = 1;
                        free(tokens);
                        return NULL;
                    }
                    has_point = 1;
                    i++;
                    continue;
                }
                if (!has_point) {//还没有遇到小数点
                    num=num*10+(expr[i]-'0');//计算整数部分,利用ASCII码
                }
                else{
                    num+=(expr[i]-'0') * fraction;
                    fraction *= 0.1;
                }
                i++;
            }

            if (*token_count >= capacity){//扩容
                capacity=capacity?capacity*2:4;//capacity>0双倍增长或==0初始化为4
                Token* new_tokens=realloc(tokens, capacity * sizeof(Token));
                if (!new_tokens) {//扩容失败情况
                    *error = 1;
                    free(tokens);
                    return NULL;
                }
                tokens = new_tokens;//更新指针指向新的内存区域
            }
            tokens[*token_count].type = NUMBER;//设置当前Token类型为数字
            tokens[*token_count].value.num = num;//设置当前Token的值为解析得到的数字
            (*token_count)++;//计数增加
        }
        //处理运算符和括号
        else if (expr[i]=='+' || expr[i]=='-' || expr[i]=='*' || expr[i]=='/' ||
                 expr[i]=='(' || expr[i]==')') {
            if (*token_count>=capacity) {
                capacity=capacity?capacity*2:4;
                Token* new_tokens = realloc(tokens, capacity * sizeof(Token));
                if (!new_tokens) {
                    *error = 1;
                    free(tokens);
                    return NULL;
                }
                tokens = new_tokens;
            }
            if (expr[i]=='(' || expr[i]==')') {//运算符的对号入座
                tokens[*token_count].type=(expr[i]=='(') ? LEFT_PAREN : RIGHT_PAREN;
            } else {
                tokens[*token_count].type = OPERATOR;
            }
            tokens[*token_count].value.op = expr[i];
            (*token_count)++;
            i++;
        }
        else {//非法字符
            *error = 1;
            free(tokens);
            return NULL;
        }
    }
    return tokens;
}

//中缀转后缀
Token* infix_to_postfix(Token* infix, int infix_len, int* postfix_len, int* error) {//中缀表达式，中缀长度，后缀长度，错误标记
    OperatorStack op_stack;//暂存运算符
    operator_stack_init(&op_stack);
    Token* postfix = malloc(infix_len * sizeof(Token));//分配内存存储后缀表达式
    *postfix_len = 0;
    *error = 0;

    for (int i=0;i<infix_len;i++) {
        Token token = infix[i];
        switch (token.type){
            case NUMBER:
                postfix[*postfix_len] = token;
                (*postfix_len)++;
                break;
            case LEFT_PAREN:
                operator_push(&op_stack, '(');
                break;
            case RIGHT_PAREN: {
                while (!operator_is_empty(&op_stack) && operator_peek(&op_stack) != '(') {//检查栈顶元素是否为左括号
                    postfix[(*postfix_len)].type = OPERATOR;//如果不是，将栈顶运算符弹出并放入后缀表达式
                    postfix[(*postfix_len)++].value.op = operator_pop(&op_stack);
                }
                if (operator_is_empty(&op_stack)) {//如果栈为空的时候仍未找到左括号，说明括号不匹配，退出
                    *error = 1;
                    free(postfix);
                    return NULL;
                }
                operator_pop(&op_stack); //弹出左括号
                break;
            }
            case OPERATOR: {
                while (!operator_is_empty(&op_stack)&&  get_priority(operator_peek(&op_stack))>=get_priority(token.value.op))
                    {//如果栈顶运算符的优先级高于或等于当前运算符，则将栈顶运算符弹出并放入后缀表达式,除非遇到优先级低于当前运算符的运算符或左括号
                    if (operator_peek(&op_stack)=='(')
                        break;
                    postfix[(*postfix_len)].type = OPERATOR;
                    postfix[(*postfix_len)++].value.op = operator_pop(&op_stack);
                }
                operator_push(&op_stack, token.value.op);
                break;
            }
            default:
                *error = 1;
                free(postfix);
                return NULL;
        }
    }

    //处理剩余的运算符
    while (!operator_is_empty(&op_stack)) {
        char op = operator_pop(&op_stack);
        if (op == '(') {//仍有未匹配的左括号(，则说明括号不匹配，退出
            *error = 1;
            free(postfix);
            return NULL;
        }
        //将运算符栈中剩余的运算符依次弹出并放入后缀表达式
        postfix[(*postfix_len)].type = OPERATOR;
        postfix[(*postfix_len)++].value.op = op;
    }
    return postfix;
}

//Finally,计算后缀表达式
double evaluate_postfix(Token* postfix, int postfix_len, int* error) {
    OperandStack stack;
    operand_stack_init(&stack);

    for (int i=0; i<postfix_len;i++)
        {
        Token token=postfix[i];
        if (token.type==NUMBER) {
            operand_push(&stack, token.value.num);//压入数字栈
        }
        else if (token.type==OPERATOR) {
            if (operand_is_empty(&stack)) {//检查是否为空
                *error = 1;
                return 0;
            }
            double b = operand_pop(&stack);//弹出栈顶数字
            if (operand_is_empty(&stack)) {//如果为空，说明少了另外一个数字，错误
                *error = 1;
                return 0;
            }
            double a = operand_pop(&stack);
            switch (token.value.op) {//运算
                case '+':operand_push(&stack, a + b);
                break;
                case '-':operand_push(&stack, a - b);
                break;
                case '*':operand_push(&stack, a * b);
                break;
                case '/':
                    if (b == 0) {//不可以除0
                        *error = 1;
                        return 0;
                    }
                    operand_push(&stack, a / b);
                    break;
                default:
                    *error = 1;
                    return 0;
            }
        }
    }
//检查最终结果
    if (operand_is_empty(&stack)) {
        *error = 1;
        return 0;
    }
    //输出最终结果
    double result = operand_pop(&stack);
    if (!operand_is_empty(&stack)) {//检查式子是否已经全部计算完
        *error = 1;
        return 0;
    }
    *error = 0;
    return result;
}

int main() {
    char input[1000];//储存表达式，1000个字符不可能不够输入了
    printf("欢迎来到计算器的世界！（输入q退出）\n");

    while (1) {
        printf("输入算式（无需输入=），请：");
        if (!fgets(input, sizeof(input), stdin))
            break;

        input[strcspn(input, "\n")] = '\0'; // 去除换行符
        if(strcmp(input, "q")==0)
            break;

        int parse_error = 0, token_count = 0;//记录错误和Token数量
        Token* infix=parse_expression(input, &token_count, &parse_error);//解析输入的字符串为Token类型数组
        if (parse_error || !infix) {
            printf("输入的算式是错误的，再输出一遍吧\n");
            free(infix);
            continue;
        }

        int postfix_len=0,conversion_error=0;//传唤后的后缀字符串长度，标记错误
        Token* postfix = infix_to_postfix(infix, token_count, &postfix_len, &conversion_error);//中缀转换为后缀
        free(infix);
        if (conversion_error||!postfix) {
            printf("表达式转换错误\n");
            free(postfix);
            continue;
        }

        int eval_error=0;
        double result=evaluate_postfix(postfix, postfix_len, &eval_error);//后缀求值
        free(postfix);
        if (eval_error) {
        printf("计算出错了，重新输一遍算式吧！\n");
        }
        else {
           printf("结果: %g\n", result);
         }
    }

    printf("计算器世界的大门已经关闭，欢迎下次再来！\n");
    return 0;
}