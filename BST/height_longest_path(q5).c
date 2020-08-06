#include <stdio.h>
#include <stdlib.h>

#define new (node *)malloc(sizeof(node))

typedef struct Node{
    int data;
    struct Node *left,*right;
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

int max(int a,int b)
{
    return a>b?a:b;
}

int max2(int a,int b,int c)
{
    int max=a;
    if(b>=max)
        max=b;
    if(c>=max)
        max=c;
    return max;
}

int height(node *T,int h)
{
    if(T==NULL)
        return 0;
    else if(T->left==NULL && T->right==NULL)
        return h;
    return max(height(T->left,h+1),height(T->right,h+1));
}

int long_path(node *T)
{
    if(T==NULL)
        return 0;
    if(T->left && T->right)
        return max2(long_path(T->left),long_path(T->right),height(T->left,0)+height(T->right,0)+2);
    else if(T->left || T->right)
        return max2(long_path(T->left),long_path(T->right),height(T->left,0)+height(T->right,0)+1);
}

int main()
{
    node* T=NULL;
    insert(&T);
    printf("%d %d\n",height(T,0),long_path(T));
}
