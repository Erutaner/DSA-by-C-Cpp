#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
typedef struct Vector
{
	int* data;//该指针类型决定了开辟数据的类型
	int size, length;
}Vector;
Vector* init(int n)
{
	Vector* vec = (Vector*)malloc(sizeof(Vector));//看到内存开辟函数首先想到失败会怎样
	if (vec == NULL)return vec;//若失败则直接返回空指针
	vec->data = (int*)malloc(sizeof(int) * n);//data负责维护存放数据的那一块堆区内存
	vec->size = n;
	vec->length = 0;
	return vec;//堆区空间在函数结束后不会自动释放，所以只要把指针传出去就可以在函数外维护
}//顺序表的初始化操作
int expand(Vector* vec)
{
	int new_size = 2 * vec->size;//不能直接vec->size*=2; 要确保内存扩展成功后再改变size的值
	int* ptr = (int*)realloc(vec->data, new_size*sizeof(int));
	if (!ptr)return 0;
	else
	{
		vec->size = new_size;
		vec->data = ptr;
		return 1;
	}
}

int insert(Vector* vec, int ind, int val)//ind 表示index   val表示value
{
	if (vec == NULL)return 0;//非法操作
	if (vec->size == vec->length)
	{
		if (!expand(vec))return 0;
		printf("Expand Vector size to %d succeeded\n", vec->size);
	}
	if (ind<0 || ind>vec->length)return 0;//下标小于零或下标大于当前元素的  下标等于length 的时候是合法的
	for (int i = vec->length;i > ind;i--)//将所有元素都后移一位，为待插入元素留出空位
	{
		vec->data[i] = vec->data[i-1];
	}
	vec->data[ind] = val;//用指针维护一个顺序表，使用方法与数组类似
	vec->length += 1;
	return 1;
}//实现插入操作
int erase(Vector* vec, int ind)
{
	if (vec == NULL)return 0;
	if (vec->length == 0)return 0;
	if (ind < 0 || ind >= vec->length)return 0;//先判断此次操作合法性
	for (int i = ind;i < vec->length-1;i++)
	{
		vec->data[i] = vec->data[i + 1];
	}
	vec->length-=1;
	return 1;
}//删除操作
void clear(Vector* vec)
{
	if (vec == NULL)return;
	free(vec->data);
	free(vec);
	return;
}//顺序表的销毁
void output(Vector* vec)
{
	if (!vec)return;
	printf("Vector(%d)=[", vec->length);
	for (int i = 0;i < vec->length;i++)
	{
		if (i)printf(", ");
		printf("%d", vec->data[i]);
	}
	printf("]\n\n");
	return;//即使返回空值，也要礼貌性的return一下
}
int main(void)
{
	srand(time(0));
	#define MAX_OP 20
	Vector* vec = init(1);
	int op, ind, val;
	for (int i = 0;i < MAX_OP;i++)
	{
		op = rand() % 2;
		ind = rand() % (vec->length + 1);//模零是非法的
		val = rand() % 100;
		switch (op)
		{
		case 0:
		{
			insert(vec, ind, val);
			printf("Inserted %d at %d to Vector, the length now is %d\n", val, ind, vec->length);
		}break;
		case 1:
		{
			if (ind == vec->length)continue;//switch case 语句放在循环内的
			erase(vec, ind);//erase确实不会改动下标为length的内存，但该分支结构仍会输出一遍，所以上一句语句是为了遇到此情况时不再输出下面的printf
			printf("Erased item at %d from Vector, the length now is %d\n", ind, vec->length);
		}break;
		}
		output(vec);
	}

	return 0;
}