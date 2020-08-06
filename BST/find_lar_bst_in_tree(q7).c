#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

#define new (node *)malloc(sizeof(node))

typedef struct Node{
        int data;
        struct Node *right,*left;
}node;

int insert(node **T)
{
    int ele;
    char bfr;
    scanf("%c",&bfr);
    while(bfr==' ' || bfr==')')
        scanf("%c",&bfr);
    if(bfr=='(')
    {
        if(scanf("%d",&ele))
        {
            node* temp=new;
            temp->data=ele;
            temp->left=temp->right=NULL;
            insert(&(temp->left));
            insert(&(temp->right));
            *T=temp;
        }
        else *T=NULL;
    }
}


node* paren(node* T)
{
    if(T==NULL)
        return;
    printf("%d ",T->data);

    printf("( ");
    paren(T->left);
    printf(") ");

    printf("( ");
    paren(T->right);
    printf(") ");
}

typedef struct Info
{
    int flag,size,min,max,res;
}info;

int max_(int a,int b)
{
    return a>b?a:b;
}

int min_(int a,int b)
{
    return a<b?a:b;
}

info maxBst(node *T)
{
    if(T==NULL)
    {
        info temp;
        temp.flag=1;
        temp.size=0;
        temp.min=INT_MIN;
        temp.max=INT_MAX;
        temp.res=0;
        return temp;
    }
    if(T->left==NULL && T->right==NULL)
    {
        info temp;
        temp.flag=1;
        temp.size=1;
        temp.min=T->data;
        temp.max=T->data;
        temp.res=1;
        return temp;
    }
    info l=maxBst(T->left);
    info r=maxBst(T->right);
    info retu;

    retu.size=(1+l.size+r.size);

    if(l.flag && r.flag && l.max<T->data && T->data<r.min)
    {
        retu.min=min_(l.min,min_(T->data,r.min));
        retu.max=max_(r.max,max_(T->data,l.max));
        retu.res=retu.size;
        retu.flag=1;

        return retu;
    }
    retu.res=max_(l.res,r.res);
    retu.flag=0;
    return retu;
}

/*
int maxBst(node* T)
{
    int a[1000];
    int size=0;
    inorder(T,a,&size);
    int count=1,max=0;
    //printf("%d",size);
    for(int i=0;i<size;i++)
    {
        //printf("%d",a[i]);
        if(a[i]<a[i+1])
        {
            count++;
            if(count>max)
                max=count;
        }
        else
            count=0;
    }
    return max;
}

int inorder(node *T,int a[],int* i)
{
    if(T==NULL)
        return;
    inorder(T->left,a,i);
    a[(*i)]=T->data;
    //printf("%d ",*i);
    (*i)++;
    inorder(T->right,a,i);
}*/

int main()
{
    node *T=NULL;
    insert(&T);
    printf("%d",maxBst(T).res);
}
