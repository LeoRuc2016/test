/*
	计算器的主函数，略长
*/
#include "calc.h"
// #include "Add.cpp"
// #include "Sub.cpp"
// #include "Diff.cpp"
// #include "func.cpp"
// #include "expression.cpp"
// #include "vector.cpp"
// #include "multiply.cpp"
// #include "expressionOperates.cpp"
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


int main(){
	
	char a[Length];				
	char b[Length];				//输入字串保存
	
	memset(a, 0, sizeof(a));
	memset(b, 0, sizeof(b));
	
	struct Node list1[Length];	//顺序表实现的情况，可忽略
	struct Node list2[Length];	
	struct Node list3[Length];
	struct Node list4[Length];	
	
	List list5;					//保存输入的多项式一
	List list6;					//保存输入的多项式二
	List list7;					//加法保存
	List list8;					//减法保存
	List list9;					//乘法保存
	List list10;				//
	List list11;				//导数保存
	
	VList vlist1;				//输入的向量
	VList vlist2;				//输入的向量
	VList vlist3;				//向量加减法保存
	
	EList elist1;				//表达式生成链表
	FuncList flist = NULL; 		//保存函数链
	
	
	int choose;
	while(1){
		
		printf("1.一元多项式求和\n");//交互界面
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
		
			
		if(choose == 1){		//多项式加法
			
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
		
		}else if(choose == 2){		//   多项式减法
		
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
