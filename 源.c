#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct Stack
{
	int* data;
	int top, size;
}Stack;

Stack* init(int n)
{
	Stack* s = (Stack*)malloc(sizeof(Stack));
	if (!s)return s;
	s->data = (int*)malloc(sizeof(int) * n);
	s->size = n;
	s->top = -1;
	return s;
}

int top(Stack* s)
{
	if (empty(s))return 0;
	return s->data[s->top];
}

int push(Stack* s,int val)
{
	if (!s)return 0;
	if (s->top + 1 == s->size)return 0;
	s->top += 1;
	s->data[s->top] = val;
	return 1;
}

int pop(Stack* s)
{
	if (!s)return 0;
	if (empty(s))return 0;
	s->top -= 1;
	return 1;
}

int empty(Stack* s)
{
	if (!s)return 2;
	return s->top == -1;
}

void clear(Stack* s)
{
	if (!s)return;
	free(s->data);
	free(s);
	return;
}

void output(Stack* s)
{
	printf("Stack(%d) = [", s->top + 1);
	for (int i = s->top;i >= 0;i--)
	{
		if (i == s->top)
			printf("%d", s->data[i]);
		else
			printf(" %d", s->data[i]);
	}
	printf("]\n");
	return;
}
int main(void)
{
	srand(time(0));
	#define MAX_OP 20
	Stack* s = init(MAX_OP);
	for (int i = 0;i < MAX_OP;i++)
	{
		int op = rand() % 3, val = rand() % 100;
		switch (op)
		{
			case 0:
			{
				printf("Push %d to stack = %d\n", val, push(s, val));
				break;
			}
			case 1:
			{
				if (empty(s))
					printf("The stack is empty, pop from stack = %d\n", pop(s));
				else if (empty(s) == 2)
					printf("NULL!\n");
				else
				{
					int fir = top(s);
					printf("Pop %d from stack = %d\n", fir, pop(s));
				}
				break;
			}
			case 2:
			{
				printf("Push %d to stack = %d\n", val, push(s, val));
				break;
			}
		}
		output(s);
	}

	return 0;
}