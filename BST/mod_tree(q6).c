#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define new (node *)malloc(sizeof(node))

typedef struct Node{
        int data,sum;
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
            temp->sum=ele;
            temp->left=temp->right=NULL;
            insert(&(temp->left));
            insert(&(temp->right));
            *T=temp;
        }
        else *T=NULL;
    }
}

int paren(node* T)
{
    if(T==NULL)
        return;
    printf("%d",T->sum);

    printf("(");
    paren(T->left);
    printf(")");

    printf("(");
    paren(T->right);
    printf(")");
}

node* search(node *T,int x)
{
    if(T==NULL)
        return T;
    else if(T->data==x)
        return T;
    else if(T->data>x)
        return search(T->left,x);
    else if(T->data<x)
        return search(T->right,x);
}

int findMin(node* T)
{

    node *temp=new;
    temp=T;
    if(temp==NULL)
        return;
    while(temp->left!=NULL)
        temp=temp->left;
    return temp->data;
}

node* delete(node* T,int ele)
{
    node *z=search(T,ele);
    node *x=T;
    if(x==NULL)
        return x;
    if(z->data<x->data)
        x->left=delete(x->left,z->data);
    else if(z->data>x->data)
        x->right=delete(x->right,z->data);
    else
    {
        if(x->left==NULL)
        {
            x=x->right;
            return x;
        }
        if(x->right==NULL)
        {
            x=x->left;
            return x;
        }
        int temp=findMin(T->right);
        node* y=search(T->right,temp);
        x->right=delete(x->right,y->data);
        y->right=x->right;
        y->left=x->left;
        return y;
    }
}

int mod_tree(node **T)
{
    if(*T==NULL)
        return 0;
    int a=mod_tree(&((*T)->left));
    int b=mod_tree(&((*T)->right));
    (*T)->sum=a+b+(*T)->data;
    return (*T)->sum;
}

int main()
{
    node* T=NULL;
    insert(&T);
    mod_tree(&T);
    printf("(");
    paren(T);
    printf(")\n");
}
