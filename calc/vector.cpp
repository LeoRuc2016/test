/*	
**  该部分代码主要实现了向量部分的操作
**	主要分为三个部分，输入，计算和输出
**	计算的部分分为 加法减法和求cosine的值
**	主要使用顺序表，删除动态分配内存的操作比较简单没有封装，在主函数里直接调用了free（）
**	定义数据结构 VNode 具体见 calc.h文件
*/

#ifndef VECTOR 
#define VECTOR 1
#include "calc.h"
void initialVector(int n, VList & list){    //生成并输入vector
	
	list = (VList)malloc(n*sizeof(struct VNode));	//生成新向量
	double index;
	for(int i = 0; i < n; i++){						//按位输入
		
		printf("请输入第%d维分量：\n", i + 1);	
		scanf("%lf", &index);
		(list+i)->n = index;
	}
	
}

void vectorsum(VList list1, VList list2, VList & list3, int n){   //向量加法
	
	list3 = (VList)malloc(n*sizeof(struct VNode));                //生成新向量，保留原始向量

	for(int i = 0; i < n; i++){
		
		(list3+i)->n = (list1+i)->n + (list2+i)->n;               //按位相加
	}
	
}

void vectorsub(VList list1, VList list2, VList & list3, int n){   //向量减法
	
	list3 = (VList)malloc(n*sizeof(struct VNode));				

	for(int i = 0; i < n; i++){
		
		(list3+i)->n = (list1+i)->n - (list2+i)->n;					//按位相减保存在新向量中
	}
	
}

void outputVector(VList list, int n){                              //输出向量
	 
	for(int i = 0; i < n; i++){
		
		printf("%lf ", (list+i)->n);	
	}
	printf("\n");
	
}

void cosine(VList list1, VList list2, int n){                       //求cos的值并输出
	
	double suma = 0;
	double sumb = 0;
	double sum = 0;
	
	for(int i = 0; i < n; i++){
		
		suma += (list1+i)->n * (list1+i)->n;						 //求平方和
		sumb += (list2+i)->n * (list2+i)->n;			
		sum  += (list1+i)->n * (list2+i)->n;						//求积的和
	}

	double m = sum/(sqrt(suma)*sqrt(sumb));								//计算

	if(suma ==0 || sumb == 0)printf("cosine is not exist.\n");			//输出cos
	else printf("cosine = %lf\n", m);	
}

#endif