#include <stdio.h>
#include <stdlib.h>
//���е���ʽ�ṹ

typedef int ElemType;

typedef struct QueueNode
{
    ElemType data;
    struct QueueNode *next;
}QueueNode;

typedef struct //ָ��ͷ��β�ڵ��ָ��
{
    QueueNode *front;
    QueueNode *rear;
}Queue;

//��ʼ��
Queue* initQueue()
{
    Queue *q = (Queue*)malloc(sizeof(Queue));
    QueueNode *node = (QueueNode*)malloc(sizeof(QueueNode));//�൱����һ��ͷ�ڵ�
    node->data = 0;
    node->next = NULL;
    q->front = node;//��ͷָ��
    q->rear = node;//��βָ��
    return q;
}

//�ж϶����Ƿ�Ϊ��
int isEmpty(Queue *q)
{
    if (q->front == q->rear)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//��������
void display(Queue* q) {
    QueueNode *node =q->front->next;
    while (node != NULL) {
        printf("%d ",node->data);
        node = node->next;

    }
printf("\n");
}
//���
void equeue(Queue *q, ElemType e)
{
    QueueNode *node = (QueueNode*)malloc(sizeof(QueueNode));
    node->data = e;
    node->next = NULL;
    q->rear->next = node;//��β�ڵ�ǰһ���ڵ㣨ԭ����β�ͽڵ㣩��ָ��ָ��β�ͽڵ�
    q->rear = node;//����βָ��
}

//����
int dequeue(Queue *q, ElemType *e)
{
    if (isEmpty(q))
    {
        printf("�����ǿյ�\n");
        return 0;
    }

    QueueNode *node = q->front->next;/*q�Ƕ��У�q��frontָ��ͷ�ڵ㣬
 q��front��next���ǵ�һ���������ݵĽڵ�
 ��������൱�ڰѵ�һ�����ݽڵ��Ϊnode���ٰ�node�ͷŵ�
 */
    *e = node->data;
    q->front->next = node->next;//�ѵڶ����ڵ㸳��ͷ�ڵ��ָ��
    if (q->rear == node)//���Ҫɾ��������ڵ㱾�����β�ͽڵ�
    {
        q->rear = q->front;//��rear�����ͷ�ڵ������NULL����free��ͳ�Ϊ��һ��ͷ�ڵ㣬front 0��rear NULL;
    }
    free(node);
    return 1;
}

//��ȡ��ͷԪ��
ElemType getFront(Queue *q)
{
    if (isEmpty(q))
    {
        printf("�յ�\n");
        return 0;
    }
    return q->front->next->data;
}


int main(int argc, char const *argv[])
{
    Queue *q = initQueue();
    equeue(q, 10);
    equeue(q, 20);
    equeue(q, 30);
    equeue(q, 40);
    equeue(q, 50);
    display(q);
    ElemType e;
    dequeue(q, &e);
    printf("����%d\n", e);
    display(q);
    dequeue(q, &e);
    printf("����%d\n", e);
    display(q);
    printf("���е�һ��Ԫ��Ϊ%d\n", getFront(q));
    return 0;
}