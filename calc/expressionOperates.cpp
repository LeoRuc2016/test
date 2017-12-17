/*
**	该部分代码实现了一元多项式的输入，转化为链表，排序和按多项式形式输出的功能
**	最后有顺序表的代码可以忽略。
*/
#ifndef EXPRESSIONOPERATE
#define EXPRESSIONOPERATE 1
#include "calc.h"
int input(char a[]){	//输入多项式

	
	printf("请输入多项式\n");
	scanf("%c",&a[0]);
	int lena = 0;
	while(a[lena] != '\n'){
		
		lena++;
		scanf("%c", &a[lena]);
		
	}

	return lena;
}


int initialList(char a[], int len, List &list){  //将输入的多项式转化为链表
//	printf("1\n");
	int t = 0;
	List cur;	
	list = (struct Node*)malloc(sizeof(struct Node));
	if(!list)exit(OVERFLOW); 
	
	list->next = NULL;
	list->coe=0;
	list->exp=0;
	
	cur = list;

	for(int i = 0; i < len;){
		int index = 0;
		if(a[i] == ' ' || a[i] == '+'){
			
			i++;
			continue; 
		} 
		
		char num[16];
		memset(num,0,sizeof(num));
		List node = (List)malloc(sizeof(struct Node));
		if(!node)exit(OVERFLOW);
		node->coe = 1;

		if((a[i] <= '9' && a[i] >= '0') || a[i] == '-'){			//遇到数字或-吸收系数

			int j = 0; 
			while(i < len && ((a[i] <= '9' && a[i] >= '0') || a[i] == '-' || a[i] == ' ')){//可以吸收空格，当还是数字或者-时说明系数没有完全提取
				if(a[i] == ' '){
					
					i++;
					continue;
				}
				num[j] = a[i];
				i++;
				j++;
			}	
			if(j == 1 && num[0] == '-')node->coe = -1;
			else node->coe = atof(num);							//转化字符串为系数
			node->exp = 0;
		}
		
		if(i<len)while(a[i] == 'X' || a[i] == 'x' || a[i] == '^' || a[i] == ' '){		//取x和^
			
			if(a[i] == 'X' || a[i] == 'x')node->exp = 1;	
			if(a[i] == '^')index =1;						//取到后标志位置为1
			i++;
		}
		
		memset(num,0,sizeof(num));	
		if(index == 1 && i < len && ((a[i] <= '9' && a[i] >= '0') || a[i] == '-')){			//标志位为0，说明没有指数 否则提取指数
			 
			int j = 0; 
			while(a[i] == '-' || a[i] == ' '){
				
				if(a[i] == ' '){
					
					i++;
					continue;
				}			
				num[j] = a[i];
				i++;
				j++;
			}
			while(i < len && (a[i] <= '9' && a[i] >= '0') ){

				num[j] = a[i];
				i++;
				j++;
			}	
			node->exp = atof(num);

		}
		t++;
		node->next = cur->next;			//插入节点
		cur->next = node;
		cur = node;
	}
	
	return t;
}




void sort(List &list){
	
	List a = list->next;		//保留list的开头
	List p = list;					
	List end = (List)malloc(sizeof(struct Node));//创建表尾方便插入


	end->exp  = -1;			// 表尾设置为特殊情况-1
	list->next = end;			
	List cur;
	while(a != NULL){	//将a的节点一个个插回list
		
		p = list;				
		while(p->next != NULL){
			
			if(a->exp - p->next->exp > 0){
			
				cur = a;
				a = a->next;
				cur->next = p->next;
				p->next = cur;
				break;
			}	
			else p = p->next;
		}
	}


	p = list;				
	while(p->next->exp != -1){		//找到表尾
		
		p = p->next;
	}
	p->next = NULL;
	
//	printf("1\n");
	free(end);			//删除表尾 
	end = NULL;
}

void outputList(List &list){//按照表达式形式输出一元多项式
	
	
	List cur = list->next;
	if(cur==NULL){
		printf("0\n");
		return;
	}	
	
	if(cur->coe != 1 && cur->coe > 0)printf("%lf", cur->coe);		//第一项处理
	else if(cur->coe < 0 && cur->coe != -1)printf("-%lf", (-1)*(cur->coe));	//负系数输出负数
	else if(abs(cur->coe + 1) < 1e-10)printf("-");					//负一直接输出负号
		
	if(abs(abs(cur->coe) - 1) < 1e-10 && abs(cur->exp) < 1e-10) printf("1");	//如果系数为1指数为0则输出一，与前面的正负号符号配合
	else if(cur->exp != 1 && cur->exp != 0)printf("x^%lf", cur->exp);			//指数为不为0或1则输出x^n 
	else if(abs(cur->exp - 1) <1e-10)printf("x");								//如果指数为1输出x

	cur = cur->next;
	
	
	while(cur!=NULL){				//其余项
		
		if(cur->coe != 1 && cur->coe > 0)printf(" + %lf", cur->coe);		//如果系数不为1，且正数 输出+m
		else if(abs(cur->coe - 1) < 1e-10)printf(" + ");					//如果系数为1   只输出+号
		else if(cur->coe < 0 && cur->coe != -1) printf(" - %lf", (-1)*(cur->coe));//如果为负数，且不为-1，输出-m
		else if(abs(cur->coe + 1) < 1e-10)printf(" - ");						//如果-1输出-
	
		if(abs(abs(cur->coe) - 1) < 1e-10 && abs(cur->exp) < 1e-10) printf("1");	//如果指数为0输出1
		else if(cur->exp != 1 && cur->exp != 0)printf("x^%lf", cur->exp);			//如果指数不为1且不为0，输出x^n
		else if(abs(cur->exp - 1) < 1e-10)printf("x");								//如果指数为1输出x
	
		cur = cur->next;
	}


	printf("\n");
	
}

void DelectList(List list){  // 释放链表
	
	List cur;
	List a;
	cur = list;
	
	while(cur!=NULL){
		
		a = cur;
		cur = cur->next;
		free(a);
	}
	
}






/***************************以下顺序表的表达式，可忽略*****************************/



int format(char a[], int len, struct Node list[]){
	
	int t = 0;
	
	for(int i = 0; i < len;){
		int index = 0;
		if(a[i] == ' ' || a[i] == '+'){
			
			i++;
			continue; 
		} 
		
		char num[16];
		memset(num,0,sizeof(num));
	
		list[t].coe = 1;
	//	printf("\n%c\n\n",a[i]);
		if((a[i] <= '9' && a[i] >= '0') || a[i] == '-'){
	//		printf("%c\n",a[i]);
			int j = 0; 
			while(i < len && ((a[i] <= '9' && a[i] >= '0') || a[i] == '-' || a[i] == ' ')){
				if(a[i] == ' '){
					
					i++;
					continue;
				}
				num[j] = a[i];
				i++;
				j++;
			}	
	//		printf("%lf\n",t);
	//		printf("j %lf num%c\n", j,num[0]);
			if(j == 1 && num[0] == '-')list[t].coe = -1;
			else list[t].coe = atoi(num);
	//		printf("j %lf num%s coe%lf\n\n", j,num, list[t].coe);
			list[t].exp = 0;
		}
		
		if(i<len)while(a[i] == 'X' || a[i] == 'x' || a[i] == '^' || a[i] == ' '){
			
			if(a[i] == 'X' || a[i] == 'x')list[t].exp = 1;
			if(a[i] == '^')index =1;
			i++;
		}
		
		memset(num,0,sizeof(num));	
		if(index == 1 && i < len && ((a[i] <= '9' && a[i] >= '0') || a[i] == '-')){
			 
			int j = 0; 
			while(a[i] == '-' || a[i] == ' '){
				
				if(a[i] == ' '){
					
					i++;
					continue;
				}			
				num[j] = a[i];
				i++;
				j++;
			}
			while(i < len && (a[i] <= '9' && a[i] >= '0') ){

				num[j] = a[i];
				i++;
				j++;
			}	
			list[t].exp = atoi(num);

		}
		t++;
	}
	
	return t;
}

void output(struct Node list[], int t){
	
	if(t==0){
		printf("0\n");
		return ;
	}
	if(abs(list[0].coe - 1) > 1e-10 && list[0].coe > 0)printf("%lf", list[0].coe);
	else if(list[0].coe < 0 && list[0].coe != -1) printf("-%lf", (-1)*list[0].coe);
	else if(abs(list[0].coe + 1) < 1e-10)printf("-");
	
	if(abs(abs(list[0].coe) - 1) < 1e-10 && abs(list[0].exp) < 1e-10) printf("1");
	else if(list[0].exp != 1 && list[0].exp != 0)printf("x^%lf", list[0].exp);
	else if(abs(list[0].coe - 1) < 1e-10)printf("x");
	
	for(int i = 1; i < t; i++){
		
		if(list[i].coe != 1 && list[i].coe > 0)printf(" + %lf", list[i].coe);
		else if(abs(list[i].coe - 1) < 1e-10)printf(" + ");
		else if(list[i].coe < 0 && list[i].coe != -1) printf(" - %lf", (-1)*list[i].coe);
		else if(abs(list[i].coe + 1) < 1e-10)printf(" - ");
		
		if(abs(abs(list[i].coe) - 1) < 1e-10 && abs(list[i].exp) < 1e-10) printf("1");
		else if(list[i].exp != 1 && list[i].exp != 0)printf("x^%lf", list[i].exp);
		else if(abs(list[i].exp - 1) < 1e-10)printf("x");
	}
	printf("\n");
	
}

#endif

