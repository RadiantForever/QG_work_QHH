#include <stdio.h>
#include <stdlib.h>
//队列的链式结构

typedef int ElemType;

typedef struct QueueNode
{
    ElemType data;
    struct QueueNode *next;
}QueueNode;

typedef struct //指向头和尾节点的指针
{
    QueueNode *front;
    QueueNode *rear;
}Queue;

//初始化
Queue* initQueue()
{
    Queue *q = (Queue*)malloc(sizeof(Queue));
    QueueNode *node = (QueueNode*)malloc(sizeof(QueueNode));//相当于做一个头节点
    node->data = 0;
    node->next = NULL;
    q->front = node;//队头指针
    q->rear = node;//队尾指针
    return q;
}

//判断队列是否为空
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

//遍历队列
void display(Queue* q) {
    QueueNode *node =q->front->next;
    while (node != NULL) {
        printf("%d ",node->data);
        node = node->next;

    }
printf("\n");
}
//入队
void equeue(Queue *q, ElemType e)
{
    QueueNode *node = (QueueNode*)malloc(sizeof(QueueNode));
    node->data = e;
    node->next = NULL;
    q->rear->next = node;//让尾节点前一个节点（原来的尾巴节点）的指针指向尾巴节点
    q->rear = node;//更新尾指针
}

//出队
int dequeue(Queue *q, ElemType *e)
{
    if (isEmpty(q))
    {
        printf("队列是空的\n");
        return 0;
    }

    QueueNode *node = q->front->next;/*q是队列，q的front指向头节点，
 q的front的next就是第一个含有数据的节点
 这里就是相当于把第一个数据节点变为node，再把node释放掉
 */
    *e = node->data;
    q->front->next = node->next;//把第二个节点赋给头节点的指向
    if (q->rear == node)//如果要删除的这个节点本身就是尾巴节点
    {
        q->rear = q->front;//让rear变成了头节点那里的NULL，在free后就成为了一个头节点，front 0；rear NULL;
    }
    free(node);
    return 1;
}

//获取队头元素
ElemType getFront(Queue *q)
{
    if (isEmpty(q))
    {
        printf("空的\n");
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
    printf("出队%d\n", e);
    display(q);
    dequeue(q, &e);
    printf("出队%d\n", e);
    display(q);
    printf("队列第一个元素为%d\n", getFront(q));
    return 0;
}