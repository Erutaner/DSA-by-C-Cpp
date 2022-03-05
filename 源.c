#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
typedef struct ListNode
{
	int data;//数据域
	struct ListNode* next;
}ListNode;//链表的节点与链表本身穿起来是两个结构
typedef struct LinkList
{
	ListNode head;//虚拟头结点，可以想象成第负一个节点，其本身也是一个节点类型
	int length;//链表的总长度
}LinkList;//链表的结构定义分为两部分，所以有两种初始化
ListNode* init_listnode(int val)//传进去一个值，传出来一个指向该节点的指针
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	if (!p)return p;
	p->data = val;
	p->next = NULL;//初始化一个节点之后next指针为空
	return p;
}
LinkList* init_linklist()
{
	LinkList* l = (LinkList*)malloc(sizeof(LinkList));
	if (!l)return l;
	l->head.next= NULL;//虚拟头节点的下一位才算是第零位，注意链表里也有第零位的说法
	l->length = 0;
	return l;
}//有两个初始化就有两个销毁操作
void clear_listnode(ListNode* node)
{
	if (!node)return;
	free(node);//如果链表节点的数据域是malloc出来的，那得先销毁数据域再销毁节点本身
	return;
}
void clear_linklist(LinkList* l)
{
	if (!l)return;
	ListNode* p = l->head.next, * q;
	while (p)//顺着链表去销毁每一个节点
	{
		q = p->next;
		clear_listnode(p);//函数里调用的函数必须在其上面定义好了
		p = q;
	}
	free(l);
	return;
}
int insert(LinkList* l, int ind, int val)//返回值代表成功或失败
{
	if (!l)return 0;
	if (ind<0 || ind>l->length)return 0;
	ListNode* p = &(l->head), * node = init_listnode(val);
	while (ind--)//从虚拟头节点开始，向后走ind步，注意虚拟头节点也是个节点类型的结构体
	{
		p = p->next;//从循环出来后p指向待插入位置的前一个位置
	}
	node->next = p->next;//这种指针作为右值存在的时候理解为某一结点的地址，第一次给链表添加值时，这一句是把NULL给NULL
	p->next = node;//作为左值存在的时候理解为某一节点内指针域存放的值
	l->length += 1;
	return 1;
}
int erase(LinkList* l, int ind)
{
	if (!l)return 0;
	if (ind < 0 || ind >= l->length)return 0;
	ListNode* p = &(l->head), * q;
	while (ind--)
	{
		p = p->next;
	}
	q = p->next->next;//p指向待删除节点的前一个位置，两个->next指向待删除节点的下一个位置，先把该位置保存
	clear_listnode(p->next);//删除待删除节点
	p->next = q;//将p中指针域赋值为它本来下一个节点的下一个节点的地址
	l->length -= 1;//增添和删除都要把记录长度的length自减
	return 1;
}
void output(LinkList* l)//输出链表也是结构操作
{
	printf("LinkList(%d) : ", l->length);
	for (ListNode* p = l->head.next;p;p = p->next)//第一个条件声明并初始化一个变量，指向第零个节点，第二个判断p是否为空指针，第三个移位p
	{
		printf("%d -> ", p->data);
	}
	printf("NULL\n");
	return;
}
#define MAX_OP 30
int main(void)
{
	srand(time(0));
	LinkList* l = init_linklist();
	for (int i = 0;i < MAX_OP;i++)
	{
		int op = rand() % 3;
		int ind = rand() % (l->length + 1);
		int val = rand() % 100;
		switch (op)
		{
		case 0:
		case 1:
		{
			printf("Inserted %d at %d to LinkList = %d\n",//注意逗号打到末尾可以换行继续输入
				val, ind, insert(l, ind, val));//最后一个%d表征是否成功
		}break;
		case 2:
		{
			printf("Erased item at %d from LinkList = %d\n",
				ind, erase(l, ind));
		}break;
		}
		output(l);
		printf("\n");
	}
	clear_linklist(l);
	return 0;
}