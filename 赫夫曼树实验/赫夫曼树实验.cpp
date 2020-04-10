#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#define len 10000
//--------------�շ������ͺշ��������ʾ------------
typedef struct
{
	char data;
	unsigned int weight;
	unsigned int parent, lchild, rchild;
}HTNode, *HuffmanTree;
typedef char* *HuffmanCode;
int minweight(HuffmanTree &T, int n);
int select(HuffmanTree &T, int i, int &s1, int &s2);         //Ƶ��ͳ�ƺ���
int CreatHuffmanTree(HuffmanTree &T, int n);                 //����շ�����
int HuffmanTree_BianMa(HuffmanTree &T, HuffmanCode &TC, int n);      //��ÿ����ĸ���б���
int HuffmanTree_BianYi(HuffmanTree T, HuffmanCode TC, char BianYi[], char a[], int n, int x);      //�����ݽ��б���
int HuffmanTree_YiMa(HuffmanTree T, char BianYi[], int n);         //����
int HuffmanTree_chucunjiegou(HuffmanTree T, int n);              //����⹹
int main()
{
	HuffmanTree T;
	HuffmanCode TC;
	char a[len];
	char bian_yi_a[3*len];
	printf("�����ַ�����");
	gets(a);
	char ch;
	int count[26];
	for(ch='a'; ch<='z'; ch++)
	{	
		count[ch]=0;
		for(int i=0; a[i]!='\0'; i++)
		{
			if(a[i]>='A'&&a[i]<='Z')
			{
			    a[i]=a[i]+32;
			}
			if(ch==a[i])
			{
				count[ch]++;
			}
		}
	}

	int i=0;
	for(ch='a'; ch<='z'; ch++)
	{
	
		if(count[ch]>0)
		{	
			i++;
		}
	}
    T=(HuffmanTree)malloc((2*i)*sizeof(HTNode));
	if(!T)
	{
		printf("�ռ�����ʧ�ܣ�\n");
		return 0;
	}
	int x=1;
	for(ch='a'; ch<='z'; ch++)
	{
	
		if(count[ch]>0)
		{	
			
			T[x].weight=count[ch];
			T[x].data=ch;
			T[x].parent=0;
			T[x].lchild=0;
			T[x].rchild=0;
            printf("�ַ�%c�ĸ���->%d\n", T[x].data, T[x].weight);
			x++;
		}
	}
	CreatHuffmanTree(T, x-1);
    HuffmanTree_BianMa(T ,TC, x-1);
    HuffmanTree_BianYi(T, TC, bian_yi_a, a ,strlen(a), x-1);
	HuffmanTree_YiMa(T, bian_yi_a, x-1);
	HuffmanTree_chucunjiegou(T, x-1);
	return 0;

}
int minweight(HuffmanTree &T, int n)
{
	int min=UINT_MAX, a=0, i;
	for(i=1; i<=n; i++)
	{	
		if((T[i].weight<min)&&(T[i].parent==0))
		{
			min=T[i].weight;
			a=i;
		}

	}
	
	T[a].parent=1;
	return a;

}
int select(HuffmanTree &T, int i, int &s1, int &s2)
{
	s1=minweight(T, i);
	s2=minweight(T, i);
	return 1;

}
int CreatHuffmanTree(HuffmanTree &T, int n)       //�����շ�����
{
    int i, x, s1, s2;
	for(x=n+1; x<=2*n-1; x++)
	{
		T[x].weight=0;
		T[x].data=0;
		T[x].parent=0;
		T[x].lchild=0;
		T[x].rchild=0;

	}
	for(i=n+1; i<=2*n-1; i++)
	{
		select(T, i-1, s1, s2);
//		printf("s1=%d s2=%d \n", s1, s2);
//		printf("s1.weight=%d s2.weight=%d\n", T[s1].weight, T[s2].weight);
		T[s1].parent=i;
		T[s2].parent=i;
		T[i].lchild=s1;
		T[i].rchild=s2;
		T[i].weight=T[s1].weight+T[s2].weight;
/*		for(int k=1; k<=i; k++)
		{
			if(T[k].parent==1)
			{
		         printf("T[%d].parent=%d \n", k, T[k].parent);
			}
		}
		printf("%d->weight=%d\n", i,T[i].weight);*/
	}
	return 1;
}
int HuffmanTree_BianMa(HuffmanTree &T, HuffmanCode &TC, int n)          //��ÿ����ĸ���б���
{
	int j;
	TC=(HuffmanCode)malloc((n+1)*sizeof(char*)); //����ÿ����ĸ
	char *cd=(char*)malloc(n*sizeof(char)); //����ÿ���ַ�
	cd[n-1]='\0'; //����n���ռ丳ֵ
	for(j=1; j<=n; j++)
	{
		int c, f, start=n-1;
		for(c=j, f=T[j].parent; f!=0; c=f, f=T[f].parent)
		{
			if(T[f].lchild==c)
			{
				cd[--start]='0';
			}
			else
			{
				cd[--start]='1';
			}
		}
		TC[j]=(char*)malloc((n-start+1)*sizeof(char));
		strcpy(TC[j], &cd[start]);
	}
	free(cd);
	printf("ÿ���ַ��ı��룺\n");
	for(j=1; j<=n; j++)
	{
		printf("%c�ı���:%s\n",T[j].data, TC[j]);
	}
    
	return 1;
}
int HuffmanTree_BianYi(HuffmanTree T, HuffmanCode TC, char BianYi[], char a[], int n, int x)    //����
{
	char *k=BianYi;
	for(int i=0; i<n; i++)
	{
         for(int j=1; j<=x; j++)
		 {
			 if(a[i]==T[j].data)
			 {
				 strcpy(k, TC[j]);
				 k=k+strlen(TC[j]);
			 }
		 }
	}
	*(k+1)='\0';
	printf("���͵ı���Ϊ:");
	puts(BianYi);
	return 1;
}
int HuffmanTree_YiMa(HuffmanTree T, char BianYi[], int n)        //����
{
	printf("�����:");
    int p;
	int x=2*n-1;
	for(p=0; p<strlen(BianYi); p++)
	{
        if(BianYi[p]=='0')
		{
             x=T[x].lchild;
		}
		if(BianYi[p]=='1')
		{
			x=T[x].rchild;
		}
		if(T[x].lchild==0||T[x].rchild==0)
		{
			printf("%c", T[x].data);
			x=2*n-1;
		}
	}
	printf("\n");
	return 0;
}

int HuffmanTree_chucunjiegou(HuffmanTree T, int n)
{
	printf("����ṹΪ:\ndata weight parent lchild rchild\n");
	for(int i=1; i<2*n; i++)
	{
		printf(" %c     %d     %d     %d     %d\n", T[i].data, T[i].weight, T[i].parent, T[i].lchild, T[i].rchild);

	}
	return 1;
}