#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define new (node *)malloc(sizeof(node))

typedef struct Node{
        int data;
        struct Node *right,*left;
}node;

node* insert(node *T, int ele) {
	if(T == NULL) {
        T = (node*) malloc(sizeof(node));
        T->data = ele;
        T->left = NULL;
        T->right = NULL;
	}
	else if(ele <= T->data)
		T->left = insert(T->left, ele);
	else
		T->right = insert(T->right, ele);
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
        return;
    while(temp->left!=NULL)
        temp=temp->left;
    return temp->data;
}

int findMax(node *T)
{
    node *temp=new;
    temp=T;
    if(temp==NULL)
        return ;
    while(temp->right!=NULL)
        temp=temp->right;
    return temp->data;
}

int pred(node *T,int ele)
{
    node *temp=T;
    node *x=search(T,ele);
    if(temp==NULL || x==NULL)
    {
        printf("NULL\n");
        return 0;
    }
    if(x->data==findMin(T))
    {
        printf("-1\n");
        return;
    }
    if(x->left!=NULL)
        return findMax(x->left);
    else
    {
        node *pred=NULL;
        node *ans=T;
        while(ans!=x)
        {
            if(x->data>ans->data)
            {
                pred=ans;
                ans=ans->left;
            }
            else
            ans=ans->right;
        }
        printf("%d\n",pred->data);
    }
}

int succ(node *T,int ele)
{
    node *temp=T;
    node *x=search(T,ele);
    if(temp==NULL || x==NULL)
    {
        printf("NULL\n");
        return 0;
    }
    if(x->data==findMax(T))
    {
        printf("-1\n");
        return;
    }
    if(x->right!=NULL)
        return findMin(x->right);
    else
    {
        node *succ=NULL;
        node *ans=T;
        while(ans!=x)
        {
            if(x->data<ans->data)
            {
                succ=ans;
                ans=ans->left;
            }
            else
            ans=ans->right;
        }
        printf("%d\n",succ->data);
    }
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

inorder(node *T)
{
    if(T==NULL)
        return;
    inorder(T->left);
    printf("%d ",T->data);
    inorder(T->right);
}

preorder(node *T)
{
    if(T==NULL)
        return;
    printf("%d ",T->data);
    preorder(T->left);
    preorder(T->right);
}

postorder(node* T)
{
    if(T==NULL)
            return;
    postorder(T->left);
    postorder(T->right);
    printf("%d ",T->data);
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

int main()
{
    node* T=NULL;
    char choice[6];
    int ele,x,i,count;
    count=0;
    while(1)
    {
        scanf("%s",choice);
        if(!strcmp(choice,"insr"))
        {
            scanf("%d",&ele);
            if(count==0)
            {
                T=insert(T,ele);
                count++;
            }
            else
                insert(T,ele);
        }
        if(!strcmp(choice,"srch"))
        {
            scanf("%d",&x);
            if(search(T,x))
                printf("FOUND\n");
            else
                printf("NOT FOUND\n");
        }
        if(!strcmp(choice,"minm"))
        {
            if(findMin(T))
                printf("%d\n",findMin(T));
            else
                printf("NIL\n");
        }
        if(!strcmp(choice,"maxm"))
        {
            if(findMax(T))
                printf("%d\n",findMax(T));
            else
                printf("NIL\n");
        }
        if(!strcmp(choice,"pred"))
        {
            scanf("%d",&i);
            pred(T,i);
        }
        if(!strcmp(choice,"succ"))
        {
            scanf("%d",&i);
            succ(T,i);
        }
        if(!strcmp(choice,"delt"))
        {
            scanf("%d",&ele);
            if(delete(T,ele));
            else printf("NOT FOUND\n");
        }
        if(!strcmp(choice,"inor"))
        {
            inorder(T);
            printf("\n");
        }
        if(!strcmp(choice,"prer"))
        {
            preorder(T);
            printf("\n");
        }
        if(!strcmp(choice,"post"))
        {
            postorder(T);
            printf("\n");
        }
        if(!strcmp(choice,"prep"))
        {
            printf("( ");
            paren(T);
            printf(")\n");
        }
        if(!strcmp(choice,"stop"))
            exit(0);
    }
}
