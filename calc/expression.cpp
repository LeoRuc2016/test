/*
**	该部分代码实现了
**
*/

#ifndef Expression
#define Expression 1
#include "calc.h"
int compare(char a, char b){		//运算符优先级比较函数
	
	
	int i, j; 
	switch(a){
		
		case '+': i = 0; break;
		case '-': i = 1; break;
		case '*': i = 2; break;
		case '/': i = 3; break;
		case '(': i = 4; break;
		case ')': i = 5; break;
		case '#': i = 6; break;
		case '^': i = 7; break;
		default:;
	}

	switch(b){
			
		case '+': j = 0; break;
		case '-': j = 1; break;
		case '*': j = 2; break;
		case '/': j = 3; break;
		case '(': j = 4; break;
		case ')': j = 5; break;
		case '#': j = 6; break;
		case '^': j = 7; break;	
		default:;
	}	
	
	return precede[i][j];
	
	
}

int inputExpression(char a[]){		//输入表达式转化为便于计算的形式
	
	a[0] = '#';
	int i = 0;
	int t = 0;
	memset(unknow, 0, sizeof(unknow));
	while(a[i] != '\n'){
		
		i++;	
		scanf("%c",&a[i]);	 
		if(a[i] == ' '){
			
			i--;	
			continue;//使表达式对空格不敏感。
		}
		if(a[i] == '-' && (a[i-1] == '#' || a[i-1] == '(')){ // 讨论 - 为正负号和运算减号的情况。 
	
			a[i++] = '0';	
			a[i] = '-';
		}
		if((a[i] < '0' || a[i] > '9' )&& a[i] != '+' && a[i] != '-' && a[i] != '*' && a[i] != '/' && a[i] != '(' && a[i] != ')' && a[i] != '\n' && a[i] != '^'){
			//替换未知数串为？
			int j = 0;
			char u = a[i];
			unknow[0] = u;
			while(/*(u < '0' || u > '9' )&&*/ u != '+' && u != '-' && u != '*' && u != '/' && u != '(' && u != ')' && u != '\n' && u != '^'){
				
				scanf("%c",&u);
				unknow[++j] = u;
			}
			a[i] = '?';
			unknow[j] = 0;
			t++;
			i++;
			a[i] = u;
		}
		
	}	
	a[i] = '#';
	return t;
}

int initialExpression(char s[], EList & list){   //初始化表达式链
	
	int len = strlen(s);
	int i = 0;
	
	list = (EList)malloc(sizeof(struct ENode));
	list->optr = '@';
	list->next = NULL; 
	EList cur = list;
	
	while(i < len){
		
		EList node = (EList)malloc(sizeof(struct ENode));  
		node->optr = '@';
		
		if(s[i] <= '9' && s[i] >= '0'){		//如果是数字，则提取系数
			
			char decimal[32];			
			memset(decimal, 0, sizeof(decimal));
			int j = 0;
			while( (s[i] <= '9' && s[i] >= '0') || s[i] == '.'){
			
				decimal[j++] = s[i++];
			}
			
			node->opnd = atof(decimal);
			node->isnum = 1;
		
			
		}else{
			
			node->optr = s[i++];		//如果是运算符则置标志位为0
			node->isnum = 0;
		}
		
		node->next = cur->next;
		cur->next = node;
		cur = cur->next;
		
	}
	
}

double evalute(double a, double b, char m){ //具体计算
	
	if(m == '+')return a + b;
	else if(m == '-')return a - b;
	else if(m == '*')return a * b;
	else if(m == '/'){
	
		if(b != 0){
			
			divideZero = 0; 
			return a / b;
		}else divideZero = 1;
	}	
	else if(m == '^')return pow(a,b);
	
}


double EvaluateExpression(EList list){ //运用栈计算表达式
	
	EList opnd, optr;
	opnd = (EList)malloc(sizeof(struct ENode));
	optr = (EList)malloc(sizeof(struct ENode));
	opnd->next = NULL;
	optr->next = NULL;
	
	EList top1 = opnd;
	EList top2 = optr;
	
	EList cur = list->next;
	top2->optr = cur->optr;
	cur = cur->next;
	EList m; 
	
	while(((cur->isnum == 0 && cur->optr != '#') || cur->isnum == 1) || top2->optr != '#'){
		
		if(cur->isnum == 1){
			
			m = cur->next;
			cur->next = top1;
			top1 = cur;
			cur = m;		
					
		}else{
			
			char compc = compare(top2->optr, cur->optr);
			if(compc == '<'){
				
				m = cur->next;
				cur->next = top2;
				top2 = cur;
				cur = m;
				
			}else if(compc == '='){
			
				m = cur;
				cur =cur->next;	
				free(m);
				m = top2;
				top2 = top2->next;
				free(m);
				 
			}else if(compc == '>'){
				
				EList a, b;	
			
				a = top1;
				top1 = top1->next;
				b = top1;
				top1 = top1->next;
				
				m = top2;
				top2 = top2->next;
				
				a->opnd = evalute(b->opnd, a->opnd, m->optr);
				a->next = top1;
				top1 = a;
			
				free(b);
				free(m);
		
			
			} 
			else if(compc == '!'){
				
				printf("输入表达式有语法错误，请重新输入。\n");
				return 0;
			}		
		}
		

	}

	double result = top1->opnd;

	while(top1 != NULL){
		
		m  =top1;
		top1 = top1->next;
		free(m);
	}
	while(top2 != NULL){
		
		m = top2;
		top2 = top2->next;
		free(m);
	}
	
	return result;
	
}

#endif