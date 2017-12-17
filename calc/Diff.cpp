/*
**	该部分代码实现了一元多项式的求导
**	使用链表结构 定义了数据类型 Node 具体见文件 calc.h
**	求导法结果可以保存在新建的表中，也可以保存在输入的表中。
**  支持负系数和浮点系数 不支持负系数和浮点系数，该函数与输入函数独立
*/
#ifndef DIFF
#define DIFF 1
#include "calc.h"



void diff(List list1, List & list2){
	
	int free1 = 0;//	保存在list3中时为0 保存在list1中时为1
	if(list1 == list2)free1 = 1;//  判断保存位置，list1 == list2 说明保存在list1，否则保存在list2

	List a;
	List cur;
	list2 = (List)malloc(sizeof(struct Node));	//生成新链
	list2->next = NULL;
	
	cur = list2;
	a = list1->next;
	
	while(a!=NULL){
		
		List node = (List)malloc(sizeof(struct Node));
		if(abs(a->exp)<1e-8){			//指数为0则跳过
			 
			a = a->next;
			continue;
		}
		
		node->coe = a->coe * a->exp;
		node->exp = a->exp - 1;
		node->next = cur->next;
		cur->next = node;
		cur = cur->next;
		a = a->next;
	}
	
	cur = list1;
	if(free1){						//	如果存在list1中则释放原链，将结果保存在list中
		
		while(cur!=NULL){
			
			a = cur;
			cur = cur->next;
			free(a);
		}	
	}
	
}
#endif