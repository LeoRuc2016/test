/**
	该段代码描述了计算器所用的数据类型和操作和
*/
#ifndef CALC
#define CALC 1

#include <stdio.h>
#include <iostream> 
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define Length 1024

struct Node{
	
	double exp;	//指数
	double coe;	//系数
	struct Node * next;
	
};			//多项式结构

typedef struct Node * List;

struct VNode{
	
	double n;	//第n维
};				//向量数据类型
typedef struct VNode * VList;

struct ENode{
	
	double opnd;	//运算数
	char optr;  	//运算符
	int isnum;      //标志位，判断运算数还是运算符
	struct ENode * next;
};			//表达式数据类型
typedef struct ENode* EList;

struct fNode{
	
	char func[Length];	//函数式
	char name[64];		//函数名
	struct fNode * next;
};			//函数数据类型
typedef struct fNode * FuncList;

extern char precede[10][10]; //运算符优先级矩阵

extern int divideZero;   //判断是否有除0的错误
extern char unknow[64];   //未知数 


int input(char a[]);//输入多项式
int initialList(char a[], int len, List &list);//初始化链表
void AddList(List list1, List list2, List &list3);//一元多项式加法
void SubList(List list1, List list2, List &list3);//一元多项式减法
void multiply(List list1, List list2, List & list3);//一元多项式乘法	
void diff(List list1, List & list2);//求导
void DelectList(List list);//释放多项式
void outputList(List &list);//输出多项式
void sort(List &list);//链式排序函数

void output(struct Node list[], int t);	//顺序表的四个个函数，可忽略
int Sub(struct Node list1[], struct Node list2[], struct Node list3[], int t1, int t2);
int Add(struct Node list1[], struct Node list2[], struct Node list3[], int t1, int t2);
int format(char a[], int len, struct Node list[]);

int judgeOperation(char m[]); //判断函数操作
int funcInput(char m[]);		//输入函数
int func_get(char m[], FuncList &list);//提取函数表达式
int convert(char a[], char b[]);		//将函数表达式变为表达式求值函数可以处理的形式
void deleteOpCode(char m[], int i);		//删除操作码， 方便后续函数式的处理
double func_get_name(char m[]);			//得到函数名

int compare(char a, char b);			//比较运算符之间的优先级
int inputExpression(char a[]);			//输入表达式
int initialExpression(char s[], EList & list);	//初始化表达式或者函数式
double evalute(double a, double b, char m);		//具体计算
double EvaluateExpression(EList list);			//计算函数式或表达式

void initialVector(int n, VList & list);		//初始化向量
void vectorsum(VList list1, VList list2, VList & list3, int n);	//向量加法	
void vectorsub(VList list1, VList list2, VList & list3, int n);	//向量减法
void outputVector(VList list, int n);							//输出向量
void cosine(VList list1, VList list2, int n);					//求cos

#endif