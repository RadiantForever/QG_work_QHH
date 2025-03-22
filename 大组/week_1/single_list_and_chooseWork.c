#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct node{
	ElemType data;
	struct node *next;
}Node;

//��������
Node* initList()
{
	Node *head = (Node*)malloc(sizeof(Node));
	head->data = 0;
	head->next = NULL;
	return head;
}

//��ʼ���ڵ�
Node* initListWithElem(ElemType e)
{
	Node *node = (Node*)malloc(sizeof(Node));
	node->data = e;
	node->next = NULL;
	return node;
}

//ͷ�巨����
int insertHead(Node* L, ElemType e)
{
	Node *p = (Node*)malloc(sizeof(Node));
	p->data = e;
	p->next = L->next;
	L->next = p;
	return 1;
}

//��������
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

//��ȡβ�����
Node*  get_tail(Node  *L)
{
	Node *p = L;
	while(p->next != NULL)
	{
		p = p->next;
	}
	return p;
}

//β�巨����
Node* insertTail(Node *tail, ElemType e)
{
	Node *p = (Node*)malloc(sizeof(Node));
	p->data = e;
	tail->next = p;
	p->next = NULL;
	return p;
}

//β�巨���ڵ㣩
Node* insertTailWithNode(Node *tail, Node *node)
{
	tail->next = node;
	node->next = NULL;
	return node;
}

//ָ��λ�ò���
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
	q->next = p->next;
	p->next = q;
	return 1;
}

//ɾ���ڵ�
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
		printf("�����ɾ����λ�ó�����\n");
		return 0;
	}

	Node *q = p->next;
	p->next = q->next;
	free(q);
	return 1;
}

//��ȡ�����Ⱥ���
int listLength(Node *L)
{
	Node *p = L;
	int len = 0;
	while(p != NULL)
	{
		p = p->next;
		len++;
	}
	return len;
}

//�ͷ�����
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

//���ҵ�����k���ڵ�
int findNodeFS(Node *L, int k)
{
	Node *fast = L->next;
	Node *slow = L->next;

	for (int i = 0; i < k; i++)
	{
		fast = fast->next;
	}

	while(fast != NULL)
	{
		fast = fast->next;
		slow = slow->next;
	}

	printf("������%d���ڵ�ֵΪ��%d\n", k, slow->data);
	return 1;
}

// ��������ż��������
void swapPairs(Node* head) {
	if (head == NULL || head->next == NULL)
		return ;

	Node* prev = head;
	Node* curr = head->next;

	while (curr != NULL && curr->next != NULL) {
		// ������ǰ�ڵ����һ���ڵ�
		Node* nextNode = curr->next;
		curr->next = nextNode->next;
		nextNode->next = curr;
		prev->next = nextNode;

		// �ƶ�ָ��
		prev = curr;
		curr = curr->next;
	}
}

//���������ڵ㹲ͬ��׺����ʼλ��
Node* findIntersectionNode(Node *headA, Node *headB)
{
	if(headA == NULL || headB == NULL)
	{
		return NULL;
	}

	Node *p = headA;
	int lenA = 0;
	int lenB = 0;
	while(p != NULL)
	{
		p = p->next;
		lenA++;
	}

	p = headB;
	while(p != NULL)
	{
		p = p->next;
		lenB++;
	}

	Node *m;
	Node *n;
	int step;
	if (lenA > lenB)
	{
		step = lenA - lenB;
		m = headA;
		n = headB;
	}
	else
	{
		step = lenB - lenA;
		m = headB;
		n = headA;
	}

	for (int i = 0; i < step; i++)
	{
		m = m->next;
	}

	while(m != n)
	{
		m = m->next;
		n = n->next;
	}
	return m;
}

//ɾ������ֵ��ͬ�Ľڵ�
void removeNode(Node *L, int n)
{
	Node *p = L;
	int index;
	int *q = (int*)malloc(sizeof(int)*(n+1));

	for (int i = 0; i < n+1; i++)
	{
		*(q + i) = 0;
	}

	while(p->next != NULL)
	{

		index = abs(p->next->data);
		if(*(q+index) == 0)
		{
			*(q + index) = 1;
			p = p->next;
		}
		else
		{
			Node *temp = p->next;
			p->next = temp->next;
			free(temp);
		}

	}
	free(q);
}

//��ת����                 ������ҵѡ�����ݵ������ת����
Node* reverseList(Node* head)
{
	Node *first = NULL;
	Node *second = head->next;
	Node *third;

	while(second != NULL)
	{
		third = second->next;
		second->next = first;
		first = second;
		second = third;
	}
	Node *hd = initList();
	hd->next = first;

	return hd;
}

//ɾ���м�ڵ㺯��
int delMiddleNode(Node *head)
{
	Node *fast = head->next;
	Node *slow = head;

	while(fast != NULL && fast->next != NULL)
	{
		fast = fast->next->next;
		slow = slow->next;
	}
	Node *q = slow->next;
	slow->next = q->next;
	free(q);
	return 1;
}

//Ѱ���м�ڵ㺯��            ������ҵѡ�����ݵڶ��Ѱ���м�ڵ�
Node* findMiddleNode(Node *head)
{
	Node *fast = head;
	Node *slow = head;

	while(fast != NULL && fast->next != NULL)
	{
		fast = fast->next->next;
		slow = slow->next;
	}
	return slow;
}
//������������
void reOrderList(Node *head)
{
	Node *fast = head;
	Node *slow = head;
	while(fast != NULL && fast->next != NULL)
	{
		fast = fast->next->next;
		slow = slow->next;
	}

	Node *first = NULL;
	Node *second = slow->next;
	slow->next = NULL;
	Node *third = NULL;

	while(second !=NULL)
	{
		third = second->next;
		second->next = first;
		first = second;
		second = third;
	}

	Node *p1 = head->next;
	Node *q1 = first;
	Node *p2, *q2;
	while(p1 != NULL && q1 != NULL)
	{
		p2 = p1->next;
		q2 = q1->next;

		p1->next = q1;
		q1->next = p2;

		p1 = p2;
		q1 = q2;
	}
}

//�ж������Ƿ��л�����                        ������ҵѡ�����ݵ�����Ƿ��л�
int isCycle(Node *head)
{
	Node *fast = head;
	Node *slow = head;

	while(fast != NULL && fast->next != NULL)
	{
		fast = fast->next->next;
		slow = slow->next;
		if (fast == slow)
		{
			return 1;
		}
	}

	return 0;
}

//�ҵ���������ں���
Node* findBegin(Node *head)
{
	Node *fast = head;
	Node *slow = head;

	while(fast != NULL && fast->next != NULL)
	{
		fast = fast->next->next;
		slow = slow->next;
		if (fast == slow)
		{
			Node *p = fast;
			int count = 1;
			while(p->next != slow)
			{
				count++;
				p = p->next;
			}

			fast = head;
			slow = head;

			for (int i = 0; i < count; i++)
			{
				fast = fast->next;
			}

			while(fast != slow)
			{
				fast = fast->next;
				slow = slow->next;
			}
			return slow;
		}
	}
	return NULL;
}
int main(int argc, char const *argv[])
{
	Node *list = initList();

	Node *tail = get_tail(list);

	tail = insertTail(tail, 1);
	tail = insertTail(tail, 2);
	tail = insertTail(tail, 3);
	tail = insertTail(tail, 4);
	tail = insertTail(tail, 5);
	tail = insertTail(tail, 6);
	tail = insertTail(tail, 7);
	tail = insertTail(tail, 8);
	int mid=findMiddleNode(list)->data;//ѡ�������
	printf("�м�ڵ�ֵΪ%d\n", mid);





	swapPairs(list);//ѡ������һ
	printf("��ż�Ի�:\n");
	listNode(list);



	//ѡ��������
	list=reverseList(list);
	printf("reverseList:\n");
	listNode(list);



	// ��������
	Node*newtail=get_tail(list);
	Node *cycleStart = list->next->next->next;
	printf("cycleStart is %d\n", cycleStart->data);
	newtail->next = cycleStart;

	//ѡ��������
	int yes1_or_no0 = isCycle(list);
	if (yes1_or_no0)
		printf("�л�\n");
	else
		printf("�޻�\n");


	Node *p = findBegin(list);
	printf("��ֵ%dΪ����㴦����ֵ\n", p->data);

	return 0;
}