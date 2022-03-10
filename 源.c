#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
typedef struct Queue
{
	int* data;
	int head, tail;
	int length, cnt;//cnt代表当前队列中存储的元素总数量
}Queue;

Queue* init(int n)
{
	Queue* q = (Queue*)malloc(sizeof(Queue));
	if (!q)return (q);//申请完内存之后第一件事就是判定
	q->data = (int*)malloc(sizeof(int) * n);
	q->head = q->tail = q->cnt = 0;//全新赋值方式
	q->length = n;//length表示的是数据域的总长度
	return (q);
}

int empty(Queue* q)//Judge whether the queue is empty
{
	if (!q)return 0;
	return q->cnt == 0;//若总元素个数为零则返回1
}

int front(Queue* q)
{
	if (!q)return 0;
	return (q->data[q->head]);
}

int push(Queue* q, int val)//队列入队操作
{
	if (!q)return 0;
	if (q->cnt == q->length)return 0;//tail和head 都是下标，tail并不是最后一个元素的下标，而是比这个元素的下标大一
	q->data[q->tail++] = val;//tail的位置可以理解为“总为空”，它可以指示插入时插在哪，每次插入完之后tail向后移动一位
	if (q->tail == q->length) q->tail -= q->length;//若移动完之后下标溢出了，则将之置为零
	q->cnt += 1;
	return 1;
}

int pop(Queue* q)//队列出队操作
{
	if (!q)return 0;
	if (empty(q))return 0;
	q->head++;
	if (q->head == q->length) q->head -= q->length;
	q->cnt -= 1;
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
	printf("queue = [");
	for (int i = q->head,j = 0;j < q->cnt;j++)//全新循环方式，同时声明两个变量时第二个前面不能加int
	{
		int ind = (i + j) % q->length;//非常神奇的一种下标设置方法，可以从head位置开始向后走，遍历完后，从整块内存的头部继续遍历，直到队列中的最后一个元素
		if (ind == q->head)
		{
			printf("%d",q->data[ind]);
			continue;
		}
		printf(" %d", q->data[ind]);
	}
	printf("]\n");
	return;
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
	printf("Head: %d                            Tail:%d                      Count:%d\n", q->head, q->tail, q->cnt);
	for (int i = 0;i < MAX_OP;i++)
	{
		int val = rand() % 100;
		printf("Push %d to queue = %d\n", val, push(q, val));
		output(q);
	}
	clear(q);
	return 0;
}