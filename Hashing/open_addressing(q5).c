#include <stdio.h>
#include <stdlib.h>
#include<limits.h>

int prime(int m)
{

    for(int i=m-1;i>1;i--)
    {
        int flag=0;
        for(int j=2;j*j<=(i);j++)
        {
            if(i%j==0)
            {
                flag=1;break;
            }
        }
        if(flag==0)
            return i;
    }
}

int hash_func(int a[],int m,char choice,int ele,int c1,int c2)
{
    int hash_value;
    if(choice=='a')
    {
        int i=0;
        while(i!=m)
        {
            hash_value=((ele%m)+i)%m;
            i++;
            if(a[hash_value]==INT_MIN)
                break;
        }
        return hash_value;
    }
    if(choice=='b')
    {
        int i=0;
        while(i<m)
        {
            hash_value=(ele%m+(c1*i)+(c2*i*i))%m;
            if(a[hash_value]==INT_MIN)
                break;
            else i++;
        }
        return hash_value;
    }
    if(choice=='c')
    {
        int i=0;
        int r = prime(m);
        printf("%d\n",r);
        while(i<m)
        {
            hash_value=((ele%m)+(i*(r-(ele%r))))%m;
            if(a[hash_value]==INT_MIN)
                break;
            else i++;
        }
        return hash_value;
    }
    return 0;
}

int search(int a[],int m,char choice,int ele,int c1,int c2)
{
    if(choice=='a')
    {
        int i=ele%m;
        while(i<m || a[i]!=INT_MIN)
        {
            if(a[i]==ele)
                return i;
        }
        return -1;
    }
    if(choice=='b')
    {
        int i=0;
        int idx=((ele%m)+(c1*i)+(c2*i*i))%m;
        while(i<m || a[i]!=INT_MIN)
        {
            idx=((ele%m)+(c1*i)+(c2*i*i))%m;
            i++;
            if(a[idx]==ele)
                return idx;
        }
        return -1;
    }
    if(choice=='c')
    {
        int i=0;
        int r=prime(m);
        int idx=((ele%m)+(i*(r-(ele%r))))%m;
        while(i<m || a[i]!=INT_MIN)
        {
            idx=((ele%m)+(i*(r-(ele%r))))%m;
            i++;
            if(a[idx]==ele)
                return idx;
        }
        return -1;
    }
    return 0;
}

void delete(int a[],int m,int choice,int ele,int c1,int c2)
{
    int idx=search(a,m,choice,ele,c1,c2);
    if(idx!=-1)
        a[idx]=0;
}

void print(int a[],int m)
{
    for(int i=0;i<m;i++)
    {
        if(a[i]==INT_MIN)
            printf("%d()\n",i);
        else
            printf("%d(%d)\n",i,a[i]);
    }
}

int main()
{
    int m,c2,c1;
    char choice;
    scanf("%c",&choice);
    scanf("%d",&m);
    if(choice=='b')
        scanf("%d %d",&c1,&c2);
    int a[m];
    for(int i=0;i<m;i++)
        a[i]=INT_MIN;
    char ope;
    int ele,idx;
    while(1)
    {
        scanf("%c",&ope);
        if(ope=='i')
        {
            scanf("%d",&ele);
            idx = hash_func(a,m,choice,ele,c1,c2);
            a[idx]=ele;
        }
        else if(ope=='s')
        {
            scanf("%d",&ele);
            int res=search(a,m,choice,ele,c1,c2);
            if(res!=-1)
                printf("1\n");
            else
                printf("-1\n");
        }
        else if(ope=='d')
        {
            scanf("%d",&ele);
            delete(a,m,choice,ele,c1,c2);
        }
        else if(ope=='p')
            print(a,m);
        else if(ope=='t')
            break;
    }
}
/*
#include<stdio.h>
#include<stdlib.h>
int *hash(int m)
{
	int *A=(int*)malloc(m*sizeof(int));
	for(int i=0;i<m;i++)
		A[i]=0;
	return A;
}
int hashfunc(int key,int m,int i,char ch,int c1,int c2,int R)
{
	if(ch=='a')
		return ((int)key%m+i)%m;
	else if(ch=='b')
		return ((int)key%m+i*c1+i*i*c2)%m;
	else if(ch=='c')
		return ((int)key%m+i*(R-(int)key%R))%m;

}
int prime(int m)
{
	int i, prime,n;int j=0;
	int P[m];
	for(n=1; n<m; n++)
	{
		prime = 1;
		for(i=2; i<n; i++)
			if(n%i == 0)
			{
				prime = 0;
				break;
			}
			if(prime)
			{
			P[j]=n;
			j++;
			}

	}
	return P[j-1];
}

int insert(int A[],int key,int m,char ch,int c1,int c2)
{
	int R=prime(m);
	int i=0;
	while(i!=m)
	{
		int n=hashfunc(key,m,i,ch,c1,c2,R);
		if(A[n]==0)
		{
			A[n]=key;
			return 0;
		}
		else
			i=i+1;
	}
}

void print(int A[],int m)
{
	int i=0;
	while(i<m)
	{
		printf("%d(%d)\n",i,A[i]);
		i++;
	}
}
int search(int A[],int m,int k,char ch,int c1,int c2)
{
	int R=prime(m);
	int i=0;
	while(i!=m)
	{
		int n=hashfunc(k,m,i,ch,c1,c2,R);
		if(A[n]==k)
			return 1;
		i+=1;


	}
	return 0;
}
int delete(int A[],int m,int k,char ch,int c1,int c2)
{
	int R=prime(m);
	int i=0;
	while(i!=m)
	{
		int n=hashfunc(k,m,i,ch,c1,c2,R);
		if(A[n]==k)
			{
				A[n]=0;
				return 0;
			}
		i+=1;
		if(A[n]==0)
			break;

	}
	return 0;
}

int main()
{
	char ch;int m,c1,c2,ele;
	scanf("%c",&ch);
	if(ch=='a')
	{
		scanf("%d",&m);
	}
	else if(ch=='b')
	{
		scanf("%d",&m);
		scanf("%d %d",&c1,&c2);
	}
	else if(ch=='c')
		scanf("%d",&m);
	char c,b;
	int *A=hash(m);
	while(1)
	{
		scanf("%c",&b);
		scanf("%c",&c);

		if(c=='i')
		{
			scanf("%c",&b);
			scanf("%d",&ele);
			insert(A,ele,m,ch,c1,c2);
		}
		else if(c=='p')
			print(A,m);
		else if(c=='s')
		{
			int k;
			scanf("%d",&k);
			if(search(A,m,k,ch,c1,c2))
				printf("1\n");
			else
				printf("-1\n");
		}
		else if(c=='d')
		{
			int d;
			scanf("%d",&d);
			if(search(A,m,d,ch,c1,c2))
			delete(A,m,d,ch,c1,c2);
			else
				printf("unimpossible\n");
		}
		else if(c=='t'||c=='T')
			exit(0);
	}

}
*/
