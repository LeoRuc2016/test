/*
**	该部分代码实现了函数操作。支持用户使用关键词定义运行自己的函数
**	主要使用链式结构，定义了数据类型fNode 详细请见calc.h文件
**	函数操作主要包括输入函数，判断操作，提取函数，构造存贮链表等操作
**	其中运算部分调用了表达式求值得函数，convert由表达式求值函数转化而来，在主函数中操作， 详细见主函数和文件expression.cpp
*/
#ifndef FUNC
#define FUNC 1
#include "calc.h"
void deleteOpCode(char m[], int i){		//确定函数操作之后，删除操作码，方便后续的提取函数
	
	char temp[1024];
	strcpy(temp, m);
	memset(m, 0, sizeof(m));
	strcpy(m, temp + i);
}

int judgeOperation(char m[]){    //	函数支持5种操作，定义，运行，查看历史函数，退出和查看帮助手册。
	
	char *p = strupr(m);

	if(strstr(p, "DEF") == p){		//输入会被转化成大写方便此处的查找，所以程序对大小写不敏感

		deleteOpCode(m,3);
		return 1;
	}else if(strstr(p, "RUN") == p){
				
		deleteOpCode(m,3);	
		return 2;
	}else if(strstr(p, "QUIT") == p){
			
		deleteOpCode(m,4);
		return 3; 
	}else if(strstr(p, "HISTORY") == p){
		
		deleteOpCode(m,7);
		return 4;
	}else if(strstr(p, "HELP") == p){
		
		return 5;
	}else return 6;
	
} 

int funcInput(char m[]){		//输入函数
	
	scanf("%c", &m[0]);
	int i = 0;
	while(m[i] != '\n'){
		
		if(m[i] == ' '){		//处理空格使得函数对空格不敏感
			
			scanf("%c", &m[i]);
			continue;
		}
		
		i++;
		scanf("%c", &m[i]);
	}
	m[i] = '\0';
	
	return i;
}

double func_get_name(char m[]){		//run 得到函数名  同时得到括号里的参数
	
	char temp[1024];
	double num1;
	int i = 0;
	while(m[i] != '('){
	
		temp[i] = m[i];
		i++;
	}
	temp[i] = '\0';
	i++;
	char num[64];

	int j = 0;
	while(m[i] != ')'){
		
		num[j++] = m[i++];
	}
	
	num1 = atof(num);
	memset(m,0,sizeof(m));
	strcpy(m,temp);
	return num1;
}

int func_get(char m[], FuncList &list){	//得到函数表达式和未知数的符号 并保存在
	
	int i = 0;
	while(m[i] != '\0'){
		
		if(m[i] == '=')break;
		i++;
	}
	
	char funcName[64];
	
	int j = 0;
	while(m[j] != '('){
		
		funcName[j] = m[j];
		j++;
	}
	funcName[j] = '\0';
	
	char temp[1024];
	strcpy(temp, m);
	memset(m,0,sizeof(m));
	strcpy(m, temp + i + 1);
	
	if(list == NULL){ //存函数的链表为空 
		
		FuncList newlist = (FuncList)malloc(sizeof(fNode));
		strcpy(newlist->func, m);
		strcpy(newlist->name, funcName);
		list = newlist;	
		list->next = NULL;
		return 1;
	}else {//存函数链表不空 
		
		FuncList cur = list;	
		while(cur != NULL && strcmp(funcName, cur->name) != 0){
			
			cur = cur->next;
		}
		if(cur != NULL){     //有重复结束 
			
			printf("This function already exits\n");
			return 0;
			
		}else{      //无重复建立新节点 
			
			FuncList newlist = (FuncList)malloc(sizeof(fNode)); 
			strcpy(newlist->func, m);
			strcpy(newlist->name, funcName);
			newlist->next = list;
			list = newlist; 
			return 1;
		}
			
		
	}

	
}

int convert(char a[], char b[]){ //将表达式转化为表达式求值中函数可以处理的形式
	
	b[0] = '#';//开头加#号
	int i = 0;
	int j = 1;
	int t = 0;
	memset(unknow, 0, sizeof(unknow));   //保存未知数的数组
	while(a[i] != '\0'){
		
		if(a[i] == '-' && (a[i-1] == '#' || a[i-1] == '(')){ // 讨论 - 为正负号和运算减号的情况， 负号时前面是#或（时加个0。 
	
			b[j++] = '0';	
			b[j] = '-';
		}
		else if((a[i] < '0' || a[i] > '9' )&& a[i] != '+' && a[i] != '-' && a[i] != '*' && a[i] != '/' && a[i] != '(' && a[i] != ')' && a[i] != '\n' && a[i] != '^'){
			//出现位置数的情况
			int m = 0;
			unknow[0] = a[i++];
			while(/*(u < '0' || u > '9' )&&*/ a[i] != '+' && a[i] != '-' && a[i] != '*' && a[i] != '/' && a[i] != '(' && a[i] != ')' && a[i] != '\n' && a[i] != '^'){
				
				unknow[++m] = a[i];
				i++;
			}//表达式中压缩未知数为一位，未知数原式保存到unknow数组中
			b[j] = '?';	//未知数的位置用？代表
			t++;
			unknow[m] = '\0';
			j++;
			b[j] = a[i];
		}else{
			
			b[j] = a[i];
			
		}
		i++;
		j++;
	}	
	b[j] = '#';//末尾加#号
	return t;
}
#endif