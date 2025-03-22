//双向链表
#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct node{
	ElemType data;
	struct node *next, *prev;
}Node;

//初始化链表函数
Node* initList()
{
	Node *head = (Node*)malloc(sizeof(Node));
	head->data = 0;
	head->next = NULL;
	head->prev = NULL;
	return head;
}

//头插法函数
int insertHead(Node* L, ElemType e)
{
	Node *p = (Node*)malloc(sizeof(Node));
	p->data = e;
	p->prev = L;
	p->next = L->next;
	if (L->next != NULL)
	{
		L->next->prev = p;
	}
	L->next = p;
	return 1;
}

//遍历双指针链表
void listNode(Node* L)
{
	Node *p = L->next;
	while(p != NULL)
	{
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}

//获取尾部结点
Node*  get_tail(Node  *L)
{
	Node *p = L;
	while(p->next != NULL)
	{
		p = p->next;
	}
	return p;
}

//尾插法
Node* insertTail(Node *tail, ElemType e)
{
	Node *p = (Node*)malloc(sizeof(Node));
	p->data = e;
	p->prev = tail;
	tail->next = p;
	p->next = NULL;
	return p;
}

//在特定位置插入函数
int insertNode(Node *L, int pos, ElemType e)
{
	Node *p = L;
	int i = 0;
	while(i < pos-1)
	{
		p = p->next;
		i++;
		if (p == NULL)
		{
			return 0;
		}
	}
	Node *q = (Node*)malloc(sizeof(Node));
	q->data = e;
	q->prev = p;
	q->next = p->next;
	p->next->prev = q;
	p->next = q;
	return 1;
}

//删除节点
int deleteNode(Node *L, int pos)
{
	Node *p = L;
	int i = 0;
	while(i < pos-1)
	{
		p = p->next;
		i++;
		if (p == NULL)
		{
			return 0;
		}
	}

	if(p->next == NULL)
	{
		printf("输入的删除的位置出错了\n");
		return 0;
	}
	Node *q = p->next;
	p->next = q->next;
	q->next->prev = p;
	free(q);
	return 1;
}

//释放链表函数
void freeList(Node *L)
{
	Node *p = L->next;
	Node *q;

	while(p != NULL)
	{
		q = p->next;
		free(p);
		p = q;
	}
	L->next = NULL;
}





int main(int argc, char const *argv[])
{
	Node *list = initList();//初始化链表

	insertHead(list, 1);//头插法
	insertHead(list, 2);
	insertHead(list, 3);
	listNode(list);//输出链表

	Node *tail = get_tail(list);
	tail = insertTail(tail, 10);//尾插法插入元素
	tail = insertTail(tail, 20);
	tail = insertTail(tail, 30);
	listNode(list);//输出链表

	insertNode(list, 2, 15);//指定位置插入
	listNode(list);


	deleteNode(list, 2);//删除指定位置的链表节点
	listNode(list);


	return 0;
}