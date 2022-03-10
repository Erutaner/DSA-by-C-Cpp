#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
typedef struct Queue
{
	int* data;
	int head, tail;
	int length;
}Queue;

Queue* init(int n)
{
	Queue* q = (Queue*)malloc(sizeof(Queue));
	if (!q)return (q);//申请完内存之后第一件事就是判定
	q->data = (int*)malloc(sizeof(int) * n);
	q->head = q->tail = 0;//全新赋值方式
	q->length = n;//length表示的是数据域的总长度
	return (q);
}

int empty(Queue* q)//Judge whether the queue is empty
{
	if (!q)return 0;
	return(q->head == q->tail);//若队列为空返回一
}

int front(Queue* q)
{
	if (!q)return 0;
	return (q->data[q->head]);
}

int push(Queue* q, int val)
{
	if (!q)return 0;
	if (q->tail == q->length)return 0;//tail和head 都是下标，tail并不是最后一个元素的下标，而是比这个元素的下标大一
	q->data[q->tail++] = val;
	return 1;
}

int pop(Queue* q)
{
	if (!q)return 0;
	if (empty(q))return 0;
	q->head++;
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
	printf("[");
	for (int i = q->head;i < q->tail;i++)
	{
		if (i == q->head)
		{
			printf("%d",q->data[q->head]);
			continue;
		}
		printf(" %d", q->data[i]);
	}
	printf("]\n");
}
int main(void)
{
	srand(time(0));
	#define MAX_OP 20
	Queue* q = init(MAX_OP);
	for (int i = 0;i < MAX_OP;i++)
	{
		int val = rand() % 100, op = rand() % 2;
		switch (op)
		{
			case 0:
			{
				printf("Push %d to queue = %d\n", val, push(q, val));
			}break;
			case 1:
			{
				int head = front(q);
				int ret = pop(q);
				if (!ret)
				{
					printf("The queue is empty, pop from queue = %d\n",ret);
					break;
				}
				printf("Pop %d from queue = %d\n", head, ret);
				break;

			}
		}
		output(q);
	}

	return 0;
}