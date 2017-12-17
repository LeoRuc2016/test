/*
**	该部分代码实现了一元多项式的加法, 包括顺序表和链表两部分，顺序表部分弃之不用，可以忽略
**	使用链表结构 定义了数据类型 Node 具体见文件 calc.h
**	加法结果可以保存在新建的表中，也可以保存在输入的表中。
**  支持负系数和浮点系数 不支持负系数和浮点系数，该函数与输入函数独立
**  传入的一元多项式必须是按照指数降序排序 排序函数在主函数调用， 详见expressionOperates.cpp文件
*/

#ifndef ADD
#define ADD 1
#include "calc.h"
void AddList(List list1, List list2, List &list3){

	int freea = 0;			//	保存在list3中时为0 保存在list1中时为1
	int freeb = 0;			
	
	if(list1 == list3)freea = 1;	//  判断保存位置，list1 == list3 说明保存在list1，否则保存在list3
	if(list2 == list3)freeb = 1;

	List a = list1->next;			//  指针指向不为空的位置
	List b = list2->next;
	list3 = (List)malloc(sizeof(struct Node)); // 建立新表， 生成表头
	list3->next = NULL;
	List cur;
	cur = list3;
	while(a != NULL && b != NULL){			//合并两表的操作
		
		List node = (List)malloc(sizeof(struct Node));     // 生成新节点
		
		if(a->exp - b->exp > 1e-10){			//	指数不同，在新表上插入指数较大的。指针后移
			
			node->coe = a->coe;
			node->exp = a->exp;
			a = a->next;
			node->next = cur->next;
			cur->next = node;
			cur = cur->next;
			
		}else if(abs(a->exp - b->exp) < 1e-10){		//	指数相同 看系数和，和为零删除节点，否则插入节点。
			
			if( abs(a->coe + b->coe) < 1e-10){
			
				a = a->next;
				b = b->next; 
				continue;
			}
			
			node->exp = a->exp;
			node->coe = a->coe + b->coe; 
			
			a = a->next;
			b = b->next;
			node->next = cur->next;
			cur->next = node;
			cur = cur->next;
			
		}else if(a->exp - b->exp < -1*1e-8){
			
			node->coe = b->coe;
			node->exp = b->exp;
			b=b->next;
			node->next = cur->next;
			cur->next = node;
			cur = cur->next;
		}		
			
	}
	
	while(a!=NULL){			// 当一条链空式把另一条链的结尾接到后面，为了保留原链，每次新建节点
		
		List node = (List)malloc(sizeof(struct Node));
		node->coe = a->coe;
		node->exp = a->exp;
		node->next = cur->next;
		cur->next = node;
		cur = cur->next;
		a = a->next; 
	}
	
	while(b!=NULL){			// 当一条链空式把另一条链的结尾接到后面，为了保留原链，每次新建节点
		
		List node = (List)malloc(sizeof(struct Node));
		node->coe = b->coe;
		node->exp = b->exp;
		node->next = cur->next;
		cur->next = node;
		cur = cur->next;
		b = b->next; 
	}
	
	
	
	if(freea == 1){				//	如果存在list1处，则释放原有list1，指向生成的list3
		
		while(a != NULL){
		
			cur = a;
			a = a->next;
			free(cur);
		}
	}
	if(freeb == 1){				//	如果存在list2处，则释放原有list2，指向生成的list3
		
		while(b != NULL){
		
			cur = b;
			b = b->next;
			free(cur);
		}
	}

}


/**********************以下是动态顺序表数组实现的代码，可以忽略***********************/



int Add(struct Node list1[], struct Node list2[], struct Node list3[], int t1, int t2){
	
	int t = 0;
	int i = 0;
	int j = 0;
	
	while(i < t1 && j < t2){
		
		if(list1[i].exp - list2[j].exp > 0){
			
			list3[t] = list1[i];
			i++;
			t++;
	
		}else if(abs(list1[i].exp - list2[j].exp) < 1e-10){
			
			if( abs(list1[i].coe + list2[j].coe) < 1e-10){
			
				i++;
				j++;
				continue;
			}
			
			list3[t].exp = list1[i].exp;
			list3[t].coe = list1[i].coe + list2[j].coe; 
			
			i++;
			j++;
			t++;
			
		}else if(list1[i].exp - list2[j].exp < 0){
			
			list3[t] = list2[j];
			j++;
			t++;
		}		
			
	}
	while(i<t1){
		
		list3[t].exp = list1[i].exp;
		list3[t].coe = list1[i].coe;
		i++;
		t++;
	}
	while(j<t2){
		
		list3[t].exp = list2[j].exp;
		list3[t].coe = list2[j].coe;
		j++;
		t++;
	}
	
	
	return t;
}

#endif