#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
//����ջ�ڵ�
typedef struct OperandNode {
    double data;//����double��������
    struct OperandNode*next;
} OperandNode;

typedef struct {//ջ��ָ�룬���ڷ���ջ�����ݣ��ں���������ջ��ջ�ŷ���
    OperandNode*top;
} OperandStack;

//�����ջ�ڵ�
typedef struct OperatorNode {
    char data;
    struct OperatorNode*next;
} OperatorNode;

typedef struct {//ͬ��ɵ�
    OperatorNode*top;
} OperatorStack;

//������ջ���г�ʼ��
void operand_stack_init(OperandStack* s) {
    s->top=NULL;
}

//������ջ
void operand_push(OperandStack* s,double data) {
    OperandNode* node = (OperandNode*)malloc(sizeof(OperandNode));
    node->data=data;
    node->next=s->top;
    s->top=node;
}

//���ֳ�ջ
double operand_pop(OperandStack* s) {
    if (s->top == NULL) {
        fprintf(stderr, "ָ���������ջ�Ѿ��ǿյ���\n");
        exit(EXIT_FAILURE);
    }
    OperandNode*temp = s->top;//������ʱָ���滻��top����top����ֵΪnext�ͷŵ���ʱָ��
    double data=temp->data;
    s->top =temp->next;
    free(temp);
    return data;
}

//�������ջ�Ƿ�Ϊ��
int operand_is_empty(OperandStack* s) {
    return s->top==NULL;
}


//�����ջ��ʼ��
void operator_stack_init(OperatorStack* s) {
    s->top = NULL;
}

//�������ջ
void operator_push(OperatorStack* s, char data) {
    OperatorNode* node = (OperatorNode*)malloc(sizeof(OperatorNode));
    node->data=data;
    node->next=s->top;
    s->top=node;
}

//�������ջ
char operator_pop(OperatorStack* s) {
    if (s->top == NULL) {
        fprintf(stderr, "ָ����������ջ�Ѿ��ǿյ���\n");
        exit(EXIT_FAILURE);
    }
    OperatorNode*temp=s->top;
    char data=temp->data;
    s->top=temp->next;
    free(temp);
    return data;
}

//�鿴ջ�������
char operator_peek(OperatorStack* s) {
    if (s->top == NULL) return '\0';
    return s->top->data;
}

//��������ջ�Ƿ�Ϊ��
int operator_is_empty(OperatorStack* s) {
    return s->top==NULL;
}


typedef enum {
    NUMBER,//����
    OPERATOR,//�����
    LEFT_PAREN,//������
    RIGHT_PAREN//������
} TokenType;

typedef struct {
    TokenType type;
    union {//����������
        double num;
        char op;
    } value;//valueֻ���Դ���һ������������ݣ��ﵽ�ֱ������ֻ��������������
} Token;

//ȷ������������ȼ�
int get_priority(char op) {
    switch (op) {
        //�˳����ȼ���ߣ�����Ϊ2���Ӽ���Ϊ1������Ĭ��Ϊ0
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 2;
        default:  return 0;
    }
}

//�ѱ��ʽΪToken����
Token* parse_expression(const char*expr, int*token_count, int*error) {//����������ı��ʽ�ַ�����Token���������޴�����
    *token_count = 0;//�õ���Token����������
    *error = 0;//������޴���
    Token* tokens = NULL;
    int capacity = 0;
    int len = strlen(expr);//��ȡ�ַ�������
    int i = 0;//��ʼ���±�

    while (i<len) {
        if (isspace(expr[i])) {//���Կհ��ַ�
            i++;
            continue;
        }

        //��������
        if (isdigit(expr[i])  ||   expr[i] == '.') {
            int has_point = 0;//�ж��Ƿ���С����
            double num = 0.0, fraction = 0.1;//�ֱ𴢴�������С��
            while (i < len && (isdigit(expr[i]) || expr[i]=='.'))
                {
                if (expr[i]=='.')
                    {//С�����ظ����������֣����д�����
                    if (has_point) {
                        *error = 1;
                        free(tokens);
                        return NULL;
                    }
                    has_point = 1;
                    i++;
                    continue;
                }
                if (!has_point) {//��û������С����
                    num=num*10+(expr[i]-'0');//������������,����ASCII��
                }
                else{
                    num+=(expr[i]-'0') * fraction;
                    fraction *= 0.1;
                }
                i++;
            }

            if (*token_count >= capacity){//����
                capacity=capacity?capacity*2:4;//capacity>0˫��������==0��ʼ��Ϊ4
                Token* new_tokens=realloc(tokens, capacity * sizeof(Token));
                if (!new_tokens) {//����ʧ�����
                    *error = 1;
                    free(tokens);
                    return NULL;
                }
                tokens = new_tokens;//����ָ��ָ���µ��ڴ�����
            }
            tokens[*token_count].type = NUMBER;//���õ�ǰToken����Ϊ����
            tokens[*token_count].value.num = num;//���õ�ǰToken��ֵΪ�����õ�������
            (*token_count)++;//��������
        }
        //���������������
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
            if (expr[i]=='(' || expr[i]==')') {//������ĶԺ�����
                tokens[*token_count].type=(expr[i]=='(') ? LEFT_PAREN : RIGHT_PAREN;
            } else {
                tokens[*token_count].type = OPERATOR;
            }
            tokens[*token_count].value.op = expr[i];
            (*token_count)++;
            i++;
        }
        else {//�Ƿ��ַ�
            *error = 1;
            free(tokens);
            return NULL;
        }
    }
    return tokens;
}

//��׺ת��׺
Token* infix_to_postfix(Token* infix, int infix_len, int* postfix_len, int* error) {//��׺���ʽ����׺���ȣ���׺���ȣ�������
    OperatorStack op_stack;//�ݴ������
    operator_stack_init(&op_stack);
    Token* postfix = malloc(infix_len * sizeof(Token));//�����ڴ�洢��׺���ʽ
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
                while (!operator_is_empty(&op_stack) && operator_peek(&op_stack) != '(') {//���ջ��Ԫ���Ƿ�Ϊ������
                    postfix[(*postfix_len)].type = OPERATOR;//������ǣ���ջ������������������׺���ʽ
                    postfix[(*postfix_len)++].value.op = operator_pop(&op_stack);
                }
                if (operator_is_empty(&op_stack)) {//���ջΪ�յ�ʱ����δ�ҵ������ţ�˵�����Ų�ƥ�䣬�˳�
                    *error = 1;
                    free(postfix);
                    return NULL;
                }
                operator_pop(&op_stack); //����������
                break;
            }
            case OPERATOR: {
                while (!operator_is_empty(&op_stack)&&  get_priority(operator_peek(&op_stack))>=get_priority(token.value.op))
                    {//���ջ������������ȼ����ڻ���ڵ�ǰ���������ջ������������������׺���ʽ,�����������ȼ����ڵ�ǰ��������������������
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

    //����ʣ��������
    while (!operator_is_empty(&op_stack)) {
        char op = operator_pop(&op_stack);
        if (op == '(') {//����δƥ���������(����˵�����Ų�ƥ�䣬�˳�
            *error = 1;
            free(postfix);
            return NULL;
        }
        //�������ջ��ʣ�����������ε����������׺���ʽ
        postfix[(*postfix_len)].type = OPERATOR;
        postfix[(*postfix_len)++].value.op = op;
    }
    return postfix;
}

//Finally,�����׺���ʽ
double evaluate_postfix(Token* postfix, int postfix_len, int* error) {
    OperandStack stack;
    operand_stack_init(&stack);

    for (int i=0; i<postfix_len;i++)
        {
        Token token=postfix[i];
        if (token.type==NUMBER) {
            operand_push(&stack, token.value.num);//ѹ������ջ
        }
        else if (token.type==OPERATOR) {
            if (operand_is_empty(&stack)) {//����Ƿ�Ϊ��
                *error = 1;
                return 0;
            }
            double b = operand_pop(&stack);//����ջ������
            if (operand_is_empty(&stack)) {//���Ϊ�գ�˵����������һ�����֣�����
                *error = 1;
                return 0;
            }
            double a = operand_pop(&stack);
            switch (token.value.op) {//����
                case '+':operand_push(&stack, a + b);
                break;
                case '-':operand_push(&stack, a - b);
                break;
                case '*':operand_push(&stack, a * b);
                break;
                case '/':
                    if (b == 0) {//�����Գ�0
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
//������ս��
    if (operand_is_empty(&stack)) {
        *error = 1;
        return 0;
    }
    //������ս��
    double result = operand_pop(&stack);
    if (!operand_is_empty(&stack)) {//���ʽ���Ƿ��Ѿ�ȫ��������
        *error = 1;
        return 0;
    }
    *error = 0;
    return result;
}

int main() {
    char input[1000];//������ʽ��1000���ַ������ܲ���������
    printf("��ӭ���������������磡������q�˳���\n");

    while (1) {
        printf("������ʽ����������=�����룺");
        if (!fgets(input, sizeof(input), stdin))
            break;

        input[strcspn(input, "\n")] = '\0'; // ȥ�����з�
        if(strcmp(input, "q")==0)
            break;

        int parse_error = 0, token_count = 0;//��¼�����Token����
        Token* infix=parse_expression(input, &token_count, &parse_error);//����������ַ���ΪToken��������
        if (parse_error || !infix) {
            printf("�������ʽ�Ǵ���ģ������һ���\n");
            free(infix);
            continue;
        }

        int postfix_len=0,conversion_error=0;//������ĺ�׺�ַ������ȣ���Ǵ���
        Token* postfix = infix_to_postfix(infix, token_count, &postfix_len, &conversion_error);//��׺ת��Ϊ��׺
        free(infix);
        if (conversion_error||!postfix) {
            printf("���ʽת������\n");
            free(postfix);
            continue;
        }

        int eval_error=0;
        double result=evaluate_postfix(postfix, postfix_len, &eval_error);//��׺��ֵ
        free(postfix);
        if (eval_error) {
        printf("��������ˣ�������һ����ʽ�ɣ�\n");
        }
        else {
           printf("���: %g\n", result);
         }
    }

    printf("����������Ĵ����Ѿ��رգ���ӭ�´�������\n");
    return 0;
}