#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
typedef struct Queue
{
	int* data;
	int head, tail;
	int length, cnt;
}Queue;

Queue* init(int n)
{
	Queue* q = (Queue*)malloc(sizeof(Queue));
	if (!q)return q;
	q->data = (int*)malloc(sizeof(int) * n);
	if (!(q->data))return q;
	q->head = q->tail = q->cnt = 0;
	q->length = n;//忘记设置length长度
	return q;//忘记返回值类型为指针
}

int empty(Queue* q)
{
	if (!q)return 0;
	return q->cnt==0;//我写为了  q->head == q->tail, 若head与tail重合，有可能是head在最前面，队列刚刚放满，tail回到第一个元素的位置，此时队列是满的
}

int front(Queue* q)
{
	if (!q)return 0;
	if (!q->cnt)return 0;
	return (q->data[q->head]);
}

int push(Queue* q, int val)
{
	if (!q)return 0;
	if (q->cnt == q->length)return 0;
	q->data[q->tail++] = val;
	if (q->tail == q->length)q->tail -= q->length;//我将这一行放在了上一行上面，则会导致函数调用结束后 tail“指针”越界的现象，
	q->cnt++;
	return 1;
}

int pop(Queue* q)
{
	if (!q)return 0;
	if (empty(q))return 0;
	q->head++;
	if (q->head == q->length)
		q->head -= q->length;
	q->cnt--;
	return 1;
}

void clear(Queue* q)
{
	if (!q)return;
	free(q->data);
	free(q);
	return;
}

void output(Queue* q)
{
	if (!q)return;
	int ind = 0;
	printf("Queue = [");
	for (int i = q->head, j = 0;j < q->cnt;j++)
	{
		ind = (i + j) % q->length;//我模成了cnt
		if (ind == q->head)
		{
			printf("%d", q->data[ind]);
		}
		else
		{
			printf(" %d", q->data[ind]);
		}
	}
	printf("]\n");
	return;
}

int main(void)
{
	#define MAX_OP 20
	srand(time(0));
	Queue* q = init(MAX_OP);
	for (int i = 0;i < MAX_OP;i++)
	{
		int val = rand() % 100;
		int op = rand() % 2;
		switch (op)
		{
			case 0:
			{
				printf("Push %d to queue = %d\n", val, push(q, val));
			}break;
			case 1:
			{
				if (empty(q))
				{
					printf("The queue is empty, pop from queue = %d\n", pop(q));
					break;
				}
				else
				{
					int fir = front(q);
					printf("Pop %d from queue = %d\n", fir, pop(q));
					break;
				}
			}
		}
		output(q);
	}
	printf("Queue head = %d               Queue tail = %d                Queue count = %d\n",
		q->head,
		q->tail,
		q->cnt);
	for (int i = 0;i < MAX_OP;i++)
	{
		int val = rand() % 100;
		printf("Push %d to queue = %d\n", val, push(q, val));
		output(q);
	}
	clear(q);

	return 0;
}