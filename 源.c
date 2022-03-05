#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define MAX_OP 40
typedef struct ListNode
{
	int data;
	struct ListNode* next;
}ListNode;

typedef struct LinkedList
{
	ListNode head;
	int length;
}LinkedList;

LinkedList* init_linkedlist()
{
	LinkedList* p = (LinkedList*)malloc(sizeof(LinkedList));
	if (!p)return p;
	p->head.next = NULL;
	p->length = 0;
	return p;
}

ListNode* init_listnode(int val)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	if (!p)return p;
	p->data = val;
	p->next = NULL;
	return p;
}

int insert(LinkedList* l, int ind, int val)
{
	if (!l)return 0;
	if (ind<0 || ind>l->length)return 0;
	ListNode* p = &(l->head),*q=init_listnode(val);
	while (ind--)
	{
		p = p->next;
	}
	q->next = p->next;
	p->next = q;
	l->length += 1;
	return 1;
}

void clear_listnode(ListNode* p)
{
	if (!p)return;
	free(p);
	return;
}

void clear_linkedlist(LinkedList* l)
{
	if (!l)return;
	ListNode* q;
	for (ListNode* p = l->head.next;p;p = p->next)
	{
		q = p->next;
		clear_listnode(p);//最好调用一下上面的函数，不要直接free
		p = q;
	}
	free(l);
	return;
}

int erase(LinkedList* l, int ind)
{
	if (!l)return 0;
	if (ind < 0 || ind >= l->length)return 0;
	ListNode* p = &(l->head),*q;
	while (ind--)
	{
		p = p->next;
	}
	q = p->next->next;
	clear_listnode(p->next);
	p->next = q;//若没有上面一行代码，这一步就会导致内存泄漏
	l->length--;
	return 1;
}


void output(LinkedList* l)
{
	if (!l)return;
	printf("LinkedList(%d): ", l->length);
	for (ListNode* p = l->head.next;p;p = p->next)
	{
		printf("%d -> ", p->data);
	}
	printf("NULL\n");
	return;
}
int main(void)
{
	srand(time(0));
	LinkedList* l = init_linkedlist();
	int op, val,ind;
	for (int i = 0;i < MAX_OP;i++)
	{
		op = rand() % 3;
		val = rand() % 100;
		ind = rand() % (l->length + 1);
		switch (op)
		{
		case 0:
		case 1:
		{
			printf("Inserted %d at %d to LinkedList = %d\n", 
				val, ind, insert(l, ind, val));
		}break;
		case 2:
		{
			printf("Erased item at %d in LinkedList = %d\n", 
				ind, erase(l, ind));
		}break;
		}
		output(l);
		printf("\n");
	}
	clear_linkedlist(l);//若没有这行，堆区内存没有归还也要内存泄漏
	return 0;
}