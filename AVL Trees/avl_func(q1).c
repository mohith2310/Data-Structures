#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define new (node*)malloc(sizeof(node))

typedef struct Node{
    int data;
    struct Node *left,*right;
    int height;
}node;

int max(int a,int b)
{
	return a>b?a:b;
}

int height(node *T)
{
	if(T==NULL)
		return 0;
	else
		return T->height;
}

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
        return T;
    }
    else if(T->data>ele)
        T->left=insert(T->left,ele);
    else if(T->data<=ele)
        T->right=insert(T->right,ele);

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
        return 0;
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
    if(T==NULL)
        return T;

    T->height=1+max(height(T->left),height(T->right));
    int bf= getBalance(T);
    if(bf>1 && getBalance(T->left)>=0)
        return  rightRotate(T);
    else if(bf<-1 && getBalance(T->right)<=0)
        return  leftRotate(T);
    else if(bf >1 && getBalance(T->left)<0)
    {
        T->left=leftRotate(T->left);
        return rightRotate(T);
    }
    else if(bf<-1 && getBalance(T->right)>0)
    {
        T->right=rightRotate(T->right);
        return leftRotate(T);
    }
    return T;
}

void printTree(node *T)
{
    if(T==NULL)
    {
        printf("( )");
        return;
    }
    else
    {
        printf("( ");
        printf("%d ",T->data);
        printTree(T->left);
        printTree(T->right);
        printf(") ");
    }
}

int isAVL(node *T)
{
    if(T==NULL)
        return 1;

    int bf=abs(height(T->left)-height(T->right));

    if(bf<2 && isAVL(T->right) && isAVL(T->right))
        return 1;
    return 0;
}

int main()
{
    node *T=NULL;
    node* temp=NULL;
    char choice[6];
    int k,ele;
    while(1)
    {
        scanf("%s",choice);
        if(!strcmp(choice,"insr"))
        {
            scanf("%d",&ele);
                T=insert(T,ele);
        }
        if(!strcmp(choice,"delt"))
        {
            scanf("%d",&ele);
            if(T=delete(T,ele));
            else
                printf("Delete Impossible\n");
        }
        if(!strcmp(choice,"pbal"))
        {
            scanf("%d",&ele);
            temp=search(T,ele);
            k=getBalance(temp);
            printf("%d\n",k);
        }
        if(!strcmp(choice,"disp"))
        {
            printTree(T);
            printf("\n");
        }
        if(!strcmp(choice,"avlc"))
        {
            if(isAVL(T))
                printf("1\n");
            else
                printf("0\n");
        }
        if(!strcmp(choice,"srch"))
        {
            scanf("%d",&ele);
            if(search(T,ele))
                printf("TRUE\n");
            else
                printf("FALSE\n");
        }
        if(!strcmp(choice,"stop"))
            break;
    }
}
