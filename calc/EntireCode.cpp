#include<stdio.h>
#include<iostream> 
#include<string.h>
#include<stdlib.h>
#include<math.h>
#define Length 1024
struct Node{
	
	double exp;	
	double coe;	 
	struct Node * next;
	
};
typedef struct Node * List;

struct VNode{
	
	double n;
};
typedef struct VNode * VList;

struct ENode{
	
	double opnd;
	char optr;  
	int isnum;
	struct ENode * next;
};
typedef struct ENode* EList;

struct fNode{
	
	char func[Length];
	char name[64];
	struct fNode * next;
};
typedef struct fNode * FuncList;


char precede[10][10] = {    
//    +   -  *    /   (   )   #  ^
	{'>','>','<','<','<','>','>','<'},	 // +
    {'>','>','<','<','<','>','>','<'},   // -
    {'>','>','>','>','<','>','>','<'},   // *
    {'>','>','>','>','<','>','>','<'}, 	 // /		 	
	{'<','<','<','<','<','=','!','<'},	 // (	 
	{'>','>','>','>','!','>','>','>'},   // )  
	{'<','<','<','<','<','!','=','<'},	 // #
	{'>','>','>','>','<','>','>','<'}	 // ^ 
	
};
int divideZero;
char unknow[64];

int comp(const void* a, const void * b){
	
	struct Node * a1 = (Node *)a;
	struct Node * b1 = (Node *)b;
	
	return a1->exp - b1->exp > 0;
}


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

void AddList(List list1, List list2, List &list3){

	int freea = 0;
	int freeb = 0;
	
	if(list1 == list3)freea = 1;
	if(list2 == list3)freeb = 1;

	List a = list1->next;
	List b = list2->next;
	list3 = (List)malloc(sizeof(struct Node));
	list3->next = NULL;
	List cur;
	cur = list3;
	while(a != NULL && b != NULL){
		
		List node = (List)malloc(sizeof(struct Node));
		
		if(a->exp - b->exp > 1e-10){
			
			node->coe = a->coe;
			node->exp = a->exp;
			a = a->next;
			node->next = cur->next;
			cur->next = node;
			cur = cur->next;
			
		}else if(abs(a->exp - b->exp) < 1e-10){
			
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
	
	while(a!=NULL){
		
		List node = (List)malloc(sizeof(struct Node));
		node->coe = a->coe;
		node->exp = a->exp;
		node->next = cur->next;
		cur->next = node;
		cur = cur->next;
		a = a->next; 
	}
	
	while(b!=NULL){
		
		List node = (List)malloc(sizeof(struct Node));
		node->coe = b->coe;
		node->exp = b->exp;
		node->next = cur->next;
		cur->next = node;
		cur = cur->next;
		b = b->next; 
	}
	
	
	
	if(freea == 1){
		
		while(a != NULL){
		
			cur = a;
			a = a->next;
			free(cur);
		}
	}
	if(freeb == 1){
		
		while(b != NULL){
		
			cur = b;
			b = b->next;
			free(cur);
		}
	}

}

int Sub(struct Node list1[], struct Node list2[], struct Node list3[], int t1, int t2){
	
	int t = 0;
	int i = 0;
	int j = 0;
	
	while(i < t1 && j < t2){
		
		if(list1[i].exp - list2[j].exp > 1e-10){
			
			list3[t].exp = list1[i].exp;
			list3[t].coe = list1[i].coe;
			i++;
			t++;
		}else if(abs(list1[i].exp - list2[j].exp) < 1e-10){
			
			if( abs(list1[i].coe - list2[j].coe) < 1e-10){
			
				i++;
				j++;
				continue;
			}
			
			list3[t].exp = list1[i].exp;
			list3[t].coe = list1[i].coe - list2[j].coe; 
			
			i++;
			j++;
			t++;
			
		}else if(list1[i].exp - list2[j].exp < -1*1e-8){
			
			list3[t].exp = list2[j].exp;
			list3[t].coe = (-1)*list2[j].coe;
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
		list3[t].coe = (-1)*list2[j].coe;
		j++;
		t++;
	}
	
	
	return t;
}
void SubList(List list1, List list2, List &list3){
	
	int freea = 0;
	int freeb = 0;
	
	if(list1 == list3)freea = 1;
	if(list2 == list3)freeb = 1;
	
	List a = list1->next;
	List b = list2->next;
	list3 = (List)malloc(sizeof(struct Node));
	list3->next = NULL;
	List cur;
	cur = list3;
	while(a != NULL && b != NULL){
		
		List node = (List)malloc(sizeof(struct Node)); 
		if(a->exp - b->exp > 1e-8){
			
			node->coe = a->coe;
			node->exp = a->exp;
			a = a->next; 
			node->next = cur->next;
			cur->next = node;
			cur = cur->next;
		}else if(abs(a->exp - b->exp) < 1e-8){
			
			if( abs(a->coe - b->coe) < 1e-8){
			
				a = a->next;
				b = b->next;
				continue;
			}
			
			node->exp = a->exp;
			node->coe = a->coe - b->coe; 
			a = a->next;
			b = b->next;
			node->next = cur->next;
			cur->next = node;
			cur = cur->next;
			
		}else if(a->exp - b->exp < -1*1e-8){
			
			node->exp = b->exp;
			node->coe = (-1)*(b->coe);
			b=b->next;
			node->next = cur->next;
			cur->next = node;
			cur = cur->next;
		}		
			
	}
	while(a!=NULL){
		
		List node = (List)malloc(sizeof(struct Node));
		node->coe = a->coe;
		node->exp = a->exp;
		node->next = cur->next;
		cur->next = node;
		cur = cur->next;
		a = a->next; 
	}
	
	while(b!=NULL){
		
		List node = (List)malloc(sizeof(struct Node));
		node->coe = (-1)*b->coe;
		node->exp = b->exp;
		node->next = cur->next;
		cur->next = node;
		cur = cur->next;
		b = b->next; 
	}
	

	if(freea == 1){
		
		while(a != NULL){
		
			cur = a;
			a = a->next;
			free(cur);
		}
	}
	if(freeb == 1){
		
		while(b != NULL){
		
			cur = b;
			b = b->next;
			free(cur);
		}
	}
	
}

void diff(List list1, List & list2){
	
	int free1 = 0;
	if(list1 == list2)free1 = 1;

	List a;
	List cur;
	list2 = (List)malloc(sizeof(struct Node));
	list2->next = NULL;
	
	cur = list2;
	a = list1->next;
	
	while(a!=NULL){
		
		List node = (List)malloc(sizeof(struct Node));
		if(abs(a->exp)<1e-8){
			 
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
	if(free1){
		
		while(cur!=NULL){
			
			a = cur;
			cur = cur->next;
			free(a);
		}	
		
	}
	
}



int input(char a[]){

	
	printf("请输入多项式\n");
	scanf("%c",&a[0]);
	int lena = 0;
	while(a[lena] != '\n'){
		
		lena++;
		scanf("%c", &a[lena]);
		
	}

	return lena;
}



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


int initialList(char a[], int len, List &list){
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

		if((a[i] <= '9' && a[i] >= '0') || a[i] == '-'){

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
			if(j == 1 && num[0] == '-')node->coe = -1;
			else node->coe = atof(num);
			node->exp = 0;
		}
		
		if(i<len)while(a[i] == 'X' || a[i] == 'x' || a[i] == '^' || a[i] == ' '){
			
			if(a[i] == 'X' || a[i] == 'x')node->exp = 1;
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
			node->exp = atof(num);

		}
		t++;
		node->next = cur->next;
		cur->next = node;
		cur = node;
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


void sort(List &list){
	
	List a = list->next;
	List p = list;
	List end = (List)malloc(sizeof(struct Node));
	end->exp  = -1;
	list->next = end;
	List cur;
	while(a != NULL){
		
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
	while(p->next->exp != -1){
		
		p = p->next;
	}
	p->next = NULL;
	
//	printf("1\n");
	free(end);
	end = NULL;
}

void outputList(List &list){
	
	
	List cur = list->next;
	if(cur==NULL){
		printf("0\n");
		return;
	}	
	
	if(cur->coe != 1 && cur->coe > 0)printf("%lf", cur->coe);
	else if(cur->coe < 0 && cur->coe != -1)printf("-%lf", (-1)*(cur->coe));
	else if(abs(cur->coe + 1) < 1e-10)printf("-");
		
	if(abs(abs(cur->coe) - 1) < 1e-10 && abs(cur->exp) < 1e-10) printf("1");
	else if(cur->exp != 1 && cur->exp != 0)printf("x^%lf", cur->exp);
	else if(abs(cur->exp - 1) <1e-10)printf("x");

	cur = cur->next;
	
	
	while(cur!=NULL){
		
		if(cur->coe != 1 && cur->coe > 0)printf(" + %lf", cur->coe);
		else if(abs(cur->coe - 1) < 1e-10)printf(" + ");
		else if(cur->coe < 0 && cur->coe != -1) printf(" - %lf", (-1)*(cur->coe));
		else if(abs(cur->coe + 1) < 1e-10)printf(" - ");
	
		if(abs(abs(cur->coe) - 1) < 1e-10 && abs(cur->exp) < 1e-10) printf("1");
		else if(cur->exp != 1 && cur->exp != 0)printf("x^%lf", cur->exp);
		else if(abs(cur->exp - 1) < 1e-10)printf("x");
	
		cur = cur->next;
	}


	printf("\n");
	
}

void multiply(List list1, List list2, List & list3){
	
	int freea = 0;
	int freeb = 0;
	if(list1 == list3)freea = 1;
	if(list2 == list3)freeb =1;
	List a = list1->next;	
	List b = list2->next;
	
	list3 = (List)malloc(sizeof(struct Node));

	List end = (List)malloc(sizeof(struct Node));
	end->next = NULL;
	end->exp = -1;
	list3->next = end;
	List cur = list3;
	while(a != NULL){
		
		b = list2->next;
		while(b!=NULL){
			
			double newexp = a->exp + b->exp;
				
				cur = list3;
				while(cur->next != NULL){
					
					if(newexp == cur->next->exp){
						
						cur->next->coe = cur->next->coe + (a->coe * b->coe);
						if(abs(cur->next->coe) < 1e-10){
							
							List m = cur->next;
							cur->next = cur->next->next;
							free(m);
						}
						break;
						
					}else if(newexp - cur->next->exp > 0){
						
						List m = (List)malloc(sizeof(struct Node));	
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
	while(cur->next->exp != -1){
		
		cur = cur->next;
	}
	cur->next = NULL;
	free(end);
	end = NULL;
	
	
	if(freea == 1){
		
		while(a != NULL){
		
			cur = a;
			a = a->next;
			free(cur);
		}
	}
	if(freeb == 1){
		
		while(b != NULL){
		
			cur = b;
			b = b->next;
			free(cur);
		}
	}
}


void DelectList(List list){
	
	List cur;
	List a;
	cur = list;
	
	while(cur!=NULL){
		
		a = cur;
		cur = cur->next;
		free(a);
	}
	
}

void initialVector(int n, VList & list){
	
	list = (VList)malloc(n*sizeof(struct VNode));
	double index;
	for(int i = 0; i < n; i++){
		
		printf("请输入第%d维分量：\n", i + 1);	
		scanf("%lf", &index);
		(list+i)->n = index;
	}
	
}

void vectorsum(VList list1, VList list2, VList & list3, int n){
	
	list3 = (VList)malloc(n*sizeof(struct VNode));

	for(int i = 0; i < n; i++){
		
		(list3+i)->n = (list1+i)->n + (list2+i)->n;
	}
	
}

void vectorsub(VList list1, VList list2, VList & list3, int n){
	
	list3 = (VList)malloc(n*sizeof(struct VNode));

	for(int i = 0; i < n; i++){
		
		(list3+i)->n = (list1+i)->n - (list2+i)->n;
	}
	
}

void outputVector(VList list, int n){
	 
	for(int i = 0; i < n; i++){
		
		printf("%lf ", (list+i)->n);	
	}
	printf("\n");
	
}

void cosine(VList list1, VList list2, int n){
	
	double suma = 0;
	double sumb = 0;
	double sum = 0;
	
	for(int i = 0; i < n; i++){
		
		suma += (list1+i)->n * (list1+i)->n;
		sumb += (list2+i)->n * (list2+i)->n;
		sum  += (list1+i)->n * (list2+i)->n;
	}

	double m = sum/(sqrt(suma)*sqrt(sumb));

	if(suma ==0 || sumb == 0)printf("cosine is not exist.\n");
	else printf("cosine = %lf\n", m);
	
	
}

int compare(char a, char b){
	
	
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

int inputExpression(char a[]){
	
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

int initialExpression(char s[], EList & list){
	
	int len = strlen(s);
	int i = 0;
	
	list = (EList)malloc(sizeof(struct ENode));
	list->optr = '@';
	list->next = NULL; 
	EList cur = list;
	
	while(i < len){
		
		EList node = (EList)malloc(sizeof(struct ENode));  
		node->optr = '@';
		
		if(s[i] <= '9' && s[i] >= '0'){
			
			char decimal[32];			
			memset(decimal, 0, sizeof(decimal));
			int j = 0;
			while( (s[i] <= '9' && s[i] >= '0') || s[i] == '.'){
			
				decimal[j++] = s[i++];
			}
			
			node->opnd = atof(decimal);
			node->isnum = 1;
		
			
		}else{
			
			node->optr = s[i++];
			node->isnum = 0;
		}
		
		node->next = cur->next;
		cur->next = node;
		cur = cur->next;
		
	}
	
}

double evalute(double a, double b, char m){
	
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


double EvaluateExpression(EList list){
	
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

void deleteOpCode(char m[], int i){
	
	char temp[1024];
	strcpy(temp, m);
	memset(m, 0, sizeof(m));
	strcpy(m, temp + i);
}

int judgeOperation(char m[]){
	
	char *p = strupr(m);

	
	if(strstr(p, "DEF") == p){

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


int funcInput(char m[]){
	
	scanf("%c", &m[0]);
	int i = 0;
	while(m[i] != '\n'){
		
		if(m[i] == ' '){
			
			scanf("%c", &m[i]);
			continue;
		}
		
		i++;
		scanf("%c", &m[i]);
	}
	m[i] = '\0';
	
	return i;
}

double func_get_name(char m[]){
	
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

int func_get(char m[], FuncList &list){
	
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
	}else {//不空 
		
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

int convert(char a[], char b[]){
	
	b[0] = '#';
	int i = 0;
	int j = 1;
	int t = 0;
	memset(unknow, 0, sizeof(unknow));
	while(a[i] != '\0'){
		
		if(a[i] == '-' && (a[i-1] == '#' || a[i-1] == '(')){ // 讨论 - 为正负号和运算减号的情况。 
	
			b[j++] = '0';	
			b[j] = '-';
		}
		else if((a[i] < '0' || a[i] > '9' )&& a[i] != '+' && a[i] != '-' && a[i] != '*' && a[i] != '/' && a[i] != '(' && a[i] != ')' && a[i] != '\n' && a[i] != '^'){
			
			int m = 0;
			unknow[0] = a[i++];
			while(/*(u < '0' || u > '9' )&&*/ a[i] != '+' && a[i] != '-' && a[i] != '*' && a[i] != '/' && a[i] != '(' && a[i] != ')' && a[i] != '\n' && a[i] != '^'){
				
				unknow[++m] = a[i];
				i++;
			}
			b[j] = '?';
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
	b[j] = '#';
	return t;
}


int main(){
	
	char a[Length];		
	char b[Length];
	memset(a, 0, sizeof(a));
	memset(b, 0, sizeof(b));
	
	struct Node list1[Length];
	struct Node list2[Length];
	struct Node list3[Length];
	struct Node list4[Length];
	List list5;
	List list6;
	List list7;
	List list8;
	List list9;
	List list10;
	List list11;
	
	VList vlist1;
	VList vlist2;
	VList vlist3;
	
	EList elist1;
	FuncList flist = NULL; 
	
	
	int choose;
	while(1){
		
		printf("1.一元多项式求和\n");
		printf("2.一元多项式相减\n");
		printf("3.一元多项式乘法\n");
		printf("4.一元多项式\n");
		printf("5.向量加法\n"); 
		printf("6.向量减法\n");
		printf("7.求向量余弦值\n");
		printf("8.四则运算求值\n");
		printf("9.定义函数:\n"); 
		printf("10.quit\n");
		printf("请输入操作：");
	
		scanf("%d", &choose);
		int t1;
		int t2;
		int lena;
		int lenb;
		int n;
		
			
		if(choose == 1){
			
				 	getchar();
					lena = input(a);
					lenb = input(b);
					  
					t1 = initialList(a, lena, list5);	
					t2 = initialList(b, lenb, list6);
					
					sort(list5);
					sort(list6);
	
					AddList(list5,list6,list7);
				
					printf("sum:");outputList(list7);
					
					DelectList(list5);
					DelectList(list6);				
					DelectList(list7);
		
		}else if(choose == 2){
		
					getchar();			
					lena = input(a);
					lenb = input(b);  
					t1 = initialList(a, lena, list5);	
					t2 = initialList(b, lenb, list6);
	
					sort(list5);
					sort(list6);
						
					SubList(list5,list6,list8);	
					
					printf("sub:");outputList(list8);

					DelectList(list5);
					DelectList(list6);				
					DelectList(list8);
				
		}else if(choose == 3){
	
					getchar();
					lena = input(a);
					lenb = input(b);  
					t1 = initialList(a, lena, list5);	
					t2 = initialList(b, lenb, list6);
								
					sort(list5);
					sort(list6);
			
					multiply(list5,list6,list9);		
					
					printf("mutliply");outputList(list9);
					
					DelectList(list5);
					DelectList(list6);				
					DelectList(list9);
		
		}else if(choose == 4){
		
					getchar();
					lena = input(a);
					t1 = initialList(a, lena, list5);	
				
					sort(list5);		
					
					diff(list5,list11);
					
					printf("diff:"); outputList(list11);
					
					DelectList(list5);
					DelectList(list11);
		
		}else if(choose == 5){
				
					printf("请输入向量维数\n");
					scanf("%d",&n);
					
					initialVector(n, vlist1);	
					initialVector(n, vlist2);
					
					vectorsum(vlist1, vlist2, vlist3, n);			
					outputVector(vlist3, n);
					free(vlist1);
					free(vlist2);
					free(vlist3);
	
		}else if(choose == 6){
	
					printf("请输入向量维数\n");
					scanf("%d",&n);
					
					initialVector(n, vlist1);	
					initialVector(n, vlist2);
					
					vectorsub(vlist1, vlist2, vlist3, n);			
					outputVector(vlist3, n);
					free(vlist1);
					free(vlist2);
					free(vlist3);
		}else if(choose == 7){
		
					printf("请输入向量维数\n");
					scanf("%d",&n);
					
					initialVector(n, vlist1);	
					initialVector(n, vlist2);
					
					cosine(vlist1, vlist2, n);			
				
					free(vlist1);
					free(vlist2);
		
		}else if(choose == 8){
			
			printf("请输入四则表达式: \n");
			getchar();
			int t = inputExpression(a);		
			
//			printf("%s",a);
			initialExpression(a,elist1);
			
			EList m;
			if(t != 0){
				
				double u; 
				printf("请输入未知数%s的值：\n", unknow);	
				scanf("%lf", &u);
//				printf("%lf",u);
				m = elist1->next;

				while(m!=NULL){
					
					if(m->optr == '?'){
						
						m->isnum = 1;
						m->opnd = u;
					}
					
					m=m->next; 
				}
			} 


						
			double result = EvaluateExpression(elist1);
			
			if(divideZero == 0)printf("= %lf\n", result);
			else {
			
				divideZero = 0;	
				printf("Error: Divide 0\n");
			}
				
			while(elist1 != NULL){
				
 				m = elist1;
				elist1 = elist1->next;
				free(m);
			}
			
		}else if(choose == 9){

			getchar();
			while(1){
			
				printf("请输入函数操作(或输入HELP查帮助):\n");
					
				char instruction[Length]; 
				int lenfunc = funcInput(instruction);
		
				int  func_operate = judgeOperation(instruction);

				if(func_operate == 1){
				
					func_get(instruction, flist);
				
				}else if(func_operate == 2){
				
					FuncList cur = flist;
					double func_index = func_get_name(instruction);
				
					while(cur != NULL && strcmp(cur->name, instruction) != 0)cur= cur->next;
				
					int t = 0;

					if(cur == NULL){
					
						printf("No such a function\n");
						continue;
					}else{
				
						char temp[1024];
						memset(temp, 0, sizeof(temp));

						convert(cur->func,temp);					
						initialExpression(temp,elist1);
		 
						EList m;				
						m = elist1->next;
	
						while(m!=NULL){
					
							if(m->optr == '?'){
						
								m->isnum = 1;
								m->opnd = func_index;
							}
						
							m=m->next; 
						}
			 
						
						double result = EvaluateExpression(elist1);
					

						if(divideZero == 0)printf("= %lf\n", result);
						else {
						
							printf("Error: Divide 0\n");
							divideZero = 0;
						}
						
						while(elist1 != NULL){
				
 							m = elist1;
							elist1 = elist1->next;
							free(m);
						}
								
					}
				
				}else if(func_operate == 3){
				
					break;
				
				}else if(func_operate == 4){
				
					FuncList cur = flist;
					if(cur == NULL)printf("No function defined\n");
					else {
				
						int i = 1;	
						while(cur != NULL){
						
							printf("%d. %s()\n", i++ , cur->name);
							cur = cur->next;
						}
				
					}
				}
				else if(func_operate == 5){
				
					printf("样例： DEF f(x) = x*2-x\nOR:    RUN f(5)\n       20\nOR     HISTORY\nOR     QUIT\n对输入的大小写不敏感\n"); 	
					continue;		
				}
				else if(func_operate == 6){
				
					printf("输入有误\n");
					continue;
				}			
			}

		}else if(choose == 10){
		
			printf("Thanks for using\n"); 
			return 0;
		
		}else {
			
			printf("错误输入，请重新输入\n");
			
		}
		
	}

	
//	int lena = input(a);
//	int lenb = input(b);   // input two multinomials
	
//	int t1 = format(a, lena, list1);
//	int t2 = format(b, lenb, list2);

//	int t1 = initialList(a, lena, list5);	
//	int t2 = initialList(b, lenb, list6);

//	qsort(a, t1, sizeof(a[0]), comp);
//	qsort(b, t2, sizeof(b[0]), comp);
	
//	int t3 = Add(list1, list2, list3, t1, t2);
//	int t4 = Sub(list1, list2, list4, t1, t2);

//	sort(list5);
//	sort(list6);

//	AddList(list5,list6,list7);
//	SubList(list5,list6,list8);

//	multiply(list5,list6,list9);
//	diff(list9,list11);
//	output(list3,t3);
//	output(list4,t4);	
//	printf("sum:");outputList(list7);
//	printf("sub:");outputList(list8);
//	printf("mutliply");outputList(list9);
//	printf("test diff:"); outputList(list11);
	
	return 0;
}
