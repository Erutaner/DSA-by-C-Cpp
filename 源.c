#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
/*
	关于递归的几条个人理解：
	1. 递归函数的思路是将某轮函数调用时处理的情况进行分类讨论，将情况分为“边值类”和“递归类”两种
	2. 边值类是接近最底层的问题最简形态，递归类可以向边值类逐级靠近
	3. 边值类写在前，递归类写在后
	4. 返回值分为边值返回值和弹出返回值，前者意味着问题最简化后解决最底层问题，后者放在递归类之后，用于“弹出”递归过程
	5. 递归类和边值类都可以为多种情况，一个递归类可以有多个递归入口，也可以有多个递归类进行选择执行（见下面的clearNode和insertNode）
	6. 递归入口和弹出返回值之间可以有操作，该操作为结束本轮之前最后要完成的任务（如删除节点）
*/
typedef struct Node
{
	int val;
	struct Node* lchild, * rchild;
}Node;//节点类型负责具体存放数据与指针

typedef struct Tree
{
	Node* root;//根节点地址，注意树的地址不同于根节点的地址
	int n;//当前二叉树节点数目
}Tree;//树类型本身存放根节点地址，与树的一些宏观数学特征，双结构定义分工与链表极为相似，体现出本质的同一性

Node* getNewNode(int val)//创建节点，初始化节点，返回节点地址
{
	Node* p = (Node*)malloc(sizeof(Node));//获取一个节点
	if (!p)return p;//判空
	p->val = val;//数据域赋值
	p->lchild = p->rchild = NULL;//指针域赋值，初值为空，有待后续添加
	return p;//传出节点地址
}

Tree* getNewTree()//创建树，初始化树，传出树的地址
{
	Tree* tree = (Tree*)malloc(sizeof(Tree));//创建一棵树，获取树的地址
	if (!tree)return tree;//判空
	tree->n = 0;//初始化树特征：节点数为零
	tree->root = NULL;//初始化根节点
	return tree;//将树的地址传出
}

Node* insertNode(Node* root, int val,int* ret)//分类讨论，边值类、递归类均可有多个，边值类放前面
{
	if (root == NULL)//第一个边值类：节点不存在，只要本轮节点存在就不会执行这一块。
	{
		*ret = 1;//给ret赋值为1
		return getNewNode(val);//调用getNewNode，返回getNewNode的返回值，即一个新节点地址
	}//对于第一个边值类，创建一个新的节点，让它由不存在变为存在，返回新建节点的地址
	if (root->val == val)return root;//第二个边值类：传入节点的数据域取值与待插入数据相同，则直接返回传入节点的地址，不创建新节点
	if (root->val > val)root->lchild = insertNode(root->lchild, val,ret);//第一递归类：本轮节点的数据域取值大于待插入数据，递归调用本函数，将返回值赋值给左指针，即确定本次插入在左子树的某个位置
	else root->rchild = insertNode(root->rchild, val,ret);//第二递归类：若本轮节点的数据域取值小于待插入数据，递归调用本函数，将返回值赋值给右指针，即确定本次插入在右子树的某个位置
	return root;//返回本轮节点的地址给前一轮，由于“弹出返回值”（与边值返回值对应）与递归类之间没有其余运算，则会逐级快速结束整个递归过程
}//小的往左插，大的往右插，排序二叉树

void insert(Tree* tree, int val)
{
	int flag = 0;
	tree->root = insertNode(tree->root, val,&flag);//传入的是这棵树的根节点的地址
	tree->n += flag;//函数向外传递信息可以通过返回值或传址，若新建了节点，则在函数内部flag会被赋值为1
	return;
}
void clearNode(Node* node)
{
	if (!node)return;//子节点也是节点，也是子子节点的父节点，意识到子是子子的父  第一边值类：节点不存在
	clearNode(node->lchild);//递归前后都有return，前面的边值条件用来中止深入，后面的用于逐级返回，你希望这个函数返回值是什么，这两个return的返回值一般就是什么
	clearNode(node->rchild);//双递归入口，考虑某节点没有左子树但有右子树的情况
	free(node);//设计在递归入口与逐级返回之间的操作，从下到上逐级清理
	return;
}//此函数中有两个递归入口，但只有一个递归类

void clearTree(Tree* tree)
{
	clearNode(tree->root);
	free(tree);
	return;
}

void outputNode(Node* root)
{
	if (root == NULL)return;//第一边值类：节点不存在，结束本轮
	printf("%d", root->val);//节点存在，则输出数据域中数据
	if (root->lchild == NULL && root->rchild == NULL)return;//第二边值类，节点为最下面的节点，由于上面已经输出了本节点数据，则直接结束
	printf("(");//节点为父节点，则打印左括号作输出子树准备
	outputNode(root->lchild);//递归类：有子节点，但不确定是左还是右，此入口负责输出左节点
	printf(",");
	outputNode(root->rchild);//此入口负责输出右节点
	printf(")");
	return;
}

void outputTree(Tree* tree)
{
	printf("tree(%d) = ", tree->n);
	outputNode(tree->root);
	printf("\n\n"); 
	return;
}

void preorderNode(Node* node)
{
	if (!node)return;
	printf(" %d", node->val);
	preorderNode(node->lchild);
	preorderNode(node->rchild);
	return;
}

void preorder(Tree* tree)
{
	printf("Preorder : ");
	preorderNode(tree->root);
	printf("\n\n");
	return;
}

void inorderNode(Node* node)
{
	if (!node)return;
	inorderNode(node->lchild);
	printf(" %d", node->val);
	inorderNode(node->rchild);
	return;
}

void inorder(Tree* tree)
{
	printf("Inorder : ");
	inorderNode(tree->root);
	printf("\n\n");
	return;
}

void postorderNode(Node* node)
{
	if (!node)return;
	postorderNode(node->lchild);
	postorderNode(node->rchild);
	printf(" %d", node->val);
	return;
}

void postorder(Tree* tree)
{
	printf("Postorder : ");
	postorderNode(tree->root);
	printf("\n\n");
	return;
}

int main(void)
{
	srand(time(0));
	Tree* tree = getNewTree();
	for (int i = 0;i < 10;i++)
	{
		int val = rand() % 100;
		insert(tree, val);
		outputTree(tree);
	}
	preorder(tree);
	inorder(tree);
	postorder(tree);
	clearTree(tree);

	return 0;
}