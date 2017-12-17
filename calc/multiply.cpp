/*
**	该部分代码实现了一元多项式的乘法
**	使用链表结构 定义了数据类型 Node 具体见文件 calc.h
**	乘法结果可以保存在新建的表中，也可以保存在输入的表中。
**  支持负系数和浮点系数 不支持负系数和浮点系数，该函数与输入函数独立
*/

#ifndef MULTIPLY
#define MULTIPLY 1
#include "calc.h"
void multiply(List list1, List list2, List & list3){
	
	int freea = 0;						//	保存在list3中时为0 保存在list1中时为1
	int freeb = 0;						
	if(list1 == list3)freea = 1;		//  判断保存位置，list1 == list3 说明保存在list1，否则保存在list3
	if(list2 == list3)freeb =1;

	List a = list1->next;				//  指针指向不为空的位置
	List b = list2->next;
	
	list3 = (List)malloc(sizeof(struct Node));    // 建立新表， 生成表头

	List end = (List)malloc(sizeof(struct Node));  // 建立尾节点，方便插入末尾，消除对特殊情况的讨论。
	end->next = NULL;
	end->exp = -1;									//计算器不支持负数幂的运算。取-1代表极端情况
	list3->next = end;
	List cur = list3;								//cur指向当前节点的指针

	while(a != NULL){   
		
		b = list2->next;							// list1中的一个节点与list2中的所有节点相乘后，b指回list2的第一个非空节点，与list1中的下一个节点继续运算。
		while(b!=NULL){								
			
			double newexp = a->exp + b->exp;		//	计算指数
				
				cur = list3;
				while(cur->next != NULL){			//  计算好的节点插入结果链中，按降序方式，因为尾节点的存在，省去了插入最后的讨论
						
					if(newexp == cur->next->exp){	
						
						cur->next->coe = cur->next->coe + (a->coe * b->coe);
						if(abs(cur->next->coe) < 1e-10){						// 指数相等且系数和为0并到链中，删除该节点
							
							List m = cur->next;
							cur->next = cur->next->next;
							free(m);
						}
						break;
						
					}else if(newexp - cur->next->exp > 0){						
						
						List m = (List)malloc(sizeof(struct Node));	          //指数不等，插到第一个指数比自己小的节点之前
						m->coe = a->coe*b->coe;
						m->exp = newexp;
						m->next = cur->next;
						cur->next = m;
						break;
					}
					
					cur = cur->next;
				}	
			
			
			b = b->next;													
		}
		
		a = a->next;
	}

	cur = list3;
	while(cur->next->exp != -1){			//	找到并删除作为标志位的尾节点
		
		cur = cur->next;
	}
	cur->next = NULL;
	free(end);
	end = NULL;
	
	
	if(freea == 1){							//	如果存在list1处，则释放原有list1，指向生成的list3
		
		while(a != NULL){
		
			cur = a;
			a = a->next;
			free(cur);
		}
	}
	if(freeb == 1){							//	如果存在list2处，则释放原有list2，指向生成的list3
		
		while(b != NULL){
		
			cur = b;
			b = b->next;
			free(cur);
		}
	}
}
#endif