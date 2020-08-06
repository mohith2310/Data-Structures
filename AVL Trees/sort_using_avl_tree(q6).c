#include <stdio.h>
#include <stdlib.h>

#define new (node*)malloc(sizeof(node))

typedef struct Node{
    int data;
    struct Node *left,*right;
    int height;
    int count;
}node;

node* rightRotate(node *x)
{
    node *y=x->left;
    node *temp=y->right;

    y->right=x;
    x->left=temp;

    x->height=max(height(x->left),height(x->right))+1;
    y->height=max(height(y->left),height(y->right))+1;
    return y;
}

node* leftRotate(node *x)
{
    node *y=x->right;
    node *temp=y->left;
    y->left=x;
    x->right=temp;
    x->height=max(height(x->left),height(x->right))+1;
    y->height=max(height(y->left),height(y->right))+1;
    return y;
}

int max(int a,int b)
{
    return a>=b?a:b;
}

int height(node *T)
{
    if(T==NULL)
        return 0;
    else
        return T->height;
}

int getBalance(node *T)
{
    if(T==NULL)
        return 0;
    else
        return height(T->left)-height(T->right);
}

node* insert(node *T,int ele)
{
    if(T==NULL)
    {
        T=new;
        T->data=ele;
        T->left=T->right=NULL;
        T->height=1;
        T->count=1;
        return T;
    }
    else if(T->data>ele)
        T->left=insert(T->left,ele);
    else if(T->data<ele)
        T->right=insert(T->right,ele);
    else
        T->count++;

    T->height=1+max(height(T->left),height(T->right));
    int bf= getBalance(T);
    if(bf>1 && ele<T->left->data)
        return  rightRotate(T);
    if(bf<-1 && ele>T->right->data)
        return  leftRotate(T);
    if(bf >1 && ele>T->left->data)
    {
        T->left=leftRotate(T->left);
        return rightRotate(T);
    }
    if(bf<-1 && ele<T->right->data)
    {
        T->right=rightRotate(T->right);
        return leftRotate(T);
    }
    return T;
}


inorder(node *T)
{
    if(T==NULL)
        return;
    inorder(T->left);
    for(int i=0;i<T->count;i++)
        printf("%d ",T->data);
    inorder(T->right);
}

int main()
{
    int n;
    scanf("%d",&n);

    node *T=NULL;

    int a[n];
    for(int i=0;i<n;i++)
        scanf("%d",&a[i]);
    for(int i=0;i<n;i++)
    {
        T=insert(T,a[i]);
    }
    inorder(T);
}
