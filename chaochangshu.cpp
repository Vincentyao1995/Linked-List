#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "math.h"

typedef struct number
{
	int a;							///系数
	int b;							///幂数
	struct number *next;
}list;
void main()
{
	list *creat(int);//创建链表,存储超长数字
	list* plus(list*,list*,int,int);//实现相加,传入两个链表,和分别的长度,遗迹正负
	void output(list*,list*);//输出随机数字到文件
	void output1(list*);//输出运算结果到文件,且注意数字正负
	list* multiply(list*,list*,int,int);//实现相乘
	void output2(list*);
	list *head1,*head2,*head3,*head4;
	
	printf("请输入数字长度(将随机产生):\n");
	int N1;
	scanf("%d",&N1);
	head1=creat(N1);


	printf("请输入数字长度(将随机产生):\n");
	int N2;
	scanf("%d",&N2);
	head2=creat(N2);

	output(head1,head2);////输出随机数字到文件
	
	head3=plus(head1,head2,N1,N2);////数字加法
	
	output1(head3);//输出加法运算结果到文件

	head3=multiply(head1,head2,N1,N2);//实现相乘
	output2(head3);//输出乘法运算结果到文件
	
}

list *creat(int N)
{
	
	
	srand ((unsigned)time(NULL));
	
	list *head,*p,*pre;
	int count=0;
	do
	{	
	p=new list;
	p->next=NULL;
	p->b=count;
	++count;
	if(count==1)
	{
		head=p;
		p->a=rand()%(9-0)+0;
		pre=p;
	}
	else
	{
		p->a=rand()%(9-0)+0;("%d",&p->a);
		if(count==N)p->a=rand()%(9-0)+1;("%d",&p->a);
		pre->next=p;
		pre=p;
	}

}while(count<N);
	return head;	
}



list* multiply(list *head1,list *head2,int N1,int N2)//乘法运算:
													//	将一个链中的各个数与另一个链相乘,得到新链
													//  各个新链相加,即为得数.
{
	void selfplus(list* head3,list* head4,int,int);
	list *p1,*p2,*p3,*p4,*head3,*head4,*temp;
	
	p2=head2;
	p1=head1;

	int temp_int;
	if(N2>N1){
		temp_int=N1;
		N1=N2;
		N1=temp_int;//N1变成较大数
		temp=p1;
		p1=p2;
		p2=temp;}//判断较长链,p1短的话交换.p1一定是较长链
	
	int count=0;
		list *pre;
		for(int x=0;x<N1+N2+1;x++)//创建新的链表p3,存储各个位相加的结果
		{
			p3=new list;
			p3->a=0;
			p3->b=x;
			p3->next=NULL;
			++count;
			if(count==1)
				head3=p3;
			else
				pre->next=p3;
			pre=p3;
		}
		count=0;
		for(x=0;x<N1+N2+1;x++)//创建新的链表p4,存储各个位相乘的结果
		{
			p4=new list;
			p4->a=0;
			p4->b=x;
			p4->next=NULL;
			++count;
			if(count==1)
				head4=p4;
			else
				pre->next=p4;
			pre=p4;
		}
	p3=head3;
	p4=head4;
	p1=head1;
	p2=head2;
	for(int i=0;i<N2;i++)
	{

			//运算给值部分(生成N2条相乘得数链):		
		int answer_mul=0;
		int next_plus=0;//  要进位的数.4*9=36,3即为此数.
		int pre_next_plus=0;
	for(int u=0;u<N1+N2;)
	{
			if(p1==NULL&&pre_next_plus!=0)
			{
				p4->next->a=pre_next_plus;
				break;	
			}
			int judge_p4_b;
			
			if(p1!=NULL)
				judge_p4_b=p2->b+p1->b;
			if(p4==NULL)break;
		if(p4->b==judge_p4_b&&p1!=NULL)
		{
			answer_mul=p1->a*p2->a;			
			next_plus=(int(answer_mul/10));
			p4->a=answer_mul-10*next_plus+pre_next_plus;//乘后此位变成的数字
			if(p4->b==0)head4->a=p4->a;
			if((p4->a)>=10)
			{
			p4->a-=10;
			next_plus=next_plus+1;
			}
			pre_next_plus=next_plus;
			p1=p1->next;
			u++;
		}
		else
			p4=p4->next;
		

	}
		p2=p2->next;
		p1=head1;
		p4=head4;
	
		selfplus(head3,head4,N1,N2);
	}
	
	return head3;
}

void selfplus(list* head3,list* head4,int N1,int N2)
{
	list *p3,*p4,*temp;
	p3=head3;
	p4=head4;
	for(int i=0;i<N1+N2;)        //共同位的运算			
	{
		if(p3->b==p4->b)
		{
			int judgeplus;
			judgeplus=(p3->a)+(p4->a);
			if(p3->b==0)
				head3->a=p3->a;
			if(judgeplus>=10)
			{
				p3->a=judgeplus-10;
				p3->next->a+=1;
			}
			else 
				p3->a=judgeplus;	
				
			p3=p3->next;
			p4=p4->next;
			i++;
		}
		else
		{
			p4=p4->next;
		}
	}
	p4=head4;
	while(p4!=NULL)
	{
		p4->a=0;
		p4=p4->next;
	}
	p4=head4;
		
}
list* plus(list *head1,list *head2,int N1,int N2)
{
	list *p1,*p2,*temp,*head3,*p3;
	p1=head1;
	p2=head2;
	if(N2>N1){temp=p1;p1=p2;p2=temp;}//判断较长链,p1短的话交换.p1一定是较长链
	
	int count=0;
		list *pre;
		for(int x=0;x<N1+N2+1;x++)
		{
			p3=new list;
			p3->a=0;
			p3->b=x;
			p3->next=NULL;
			++count;
			if(count==1)
				head3=p3;
			else
				pre->next=p3;
			pre=p3;
		
		}
		p3=head3;
		while(p1!=NULL&&p2!=NULL)        //共同位的运算			
		{
			
			int judgeplus;
			judgeplus=(p1->a)+(p2->a);
			
			if(judgeplus>=10)
			{
				p3->next->a+=1;
				p3->a=judgeplus-10+p3->a;
				
			}
			else p3->a=judgeplus+p3->a;	
				
			p1=p1->next;
			p2=p2->next;
			p3=p3->next;
		}
		while(p1!=NULL&&p2==NULL)
		{
			p3->a=p1->a;
			p1=p1->next;
			p3=p3->next;
		}
		return head3;


}

void output(list*head1,list*head2)
{
	list *p1=head1;
	FILE *fp1=fopen("infile1.txt","w+");
	if(fp1==NULL)exit(0);
	
	

/*	p1=head1;
	p1->a=1;
	p1=p1->next;
	p1->a=4;
	p1=p1->next;
	p1->a=1;
	p1=p1->next;
	p1->a=0;
	p1=p1->next;
	p1->a=4;
	p1=head1;*/	

	printf("随即产生的第一数为:\n");
	while(p1!=NULL)                
	{
	printf("%d",p1->a);
	fprintf(fp1,"%d ",p1->a);
	p1=p1->next;
	}
	printf("\n");
	fclose(fp1);
	
	list *p2=head2;
	FILE *fp2=fopen("infile2.txt","w+");
	if(fp2==NULL)exit(0);
	printf("随即产生的第二数为:\n");
	while(p2!=NULL)                
	{
	printf("%d",p2->a);
	fprintf(fp2,"%d ",p2->a);
	p2=p2->next;
	}
	printf("\n");
	fclose(fp2);
}

void output1(list* head)
{
	list *p=head;	
	FILE *fp=fopen("outfile.txt","w+");
	if (fp==NULL)exit(0);
	fprintf(fp,"加法的结果为:\n");
	printf("加法的结果为:\n");

	int shanchu0(list* head);
	int answer;
	answer=shanchu0(head);


	int j=0;
	while(j<answer&&p!=NULL) 
	{
	printf("%d",p->a);
	fprintf(fp,"%d ",p->a);
	p=p->next;
	++j;
	}
	printf("\n");
	fclose(fp);
}


void output2(list* head)
{
	list *p1=head;
	FILE *fp1=fopen("outfile.txt","a");
	if(fp1==NULL)exit(0);
	fprintf(fp1,"\n");
	fprintf(fp1,"乘法的结果为:\n");
	printf("乘法的结果为:\n");

	int shanchu0(list* head);
	int answer;
	answer=shanchu0(head);
	int j=0;

	while(j<answer&&p1!=NULL)
	{
	printf("%d",p1->a);
	fprintf(fp1,"%d ",p1->a);
	p1=p1->next;
	++j;
	}
	printf("\n");
	fclose(fp1);
}
int shanchu0(list* head1)
{
	list *p1=head1;
	int cur_pos,temp,answer;
	for(int i=1;p1!=NULL;++i,p1=p1->next)
	{
		cur_pos=i;
		if(p1->a==0)
		{
			for(int w=cur_pos;p1!=NULL;p1=p1->next,w++)
			{
				if(p1->a!=0)
				{
					temp=-1;
					p1=head1;
					for(int j=1;j<cur_pos;j++)//huan yuan zhizhen
					{	
						
						p1=p1->next;
					}
					break;
				}
				if(p1->next==NULL&&p1->a==0)
					temp=1;
			}
		}
		if(temp==1)
		{
			answer=cur_pos-1;
			break;
		}
		else 
			answer=cur_pos;
	}

	return answer;

}