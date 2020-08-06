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

node* create(node* T){
	char input[200];
	scanf("%[^\n]s", input);
	int ele = 0;
	int i=0;
	char *str = input;

	while (sscanf(str, "%*[^0-9]%d%n", &ele, &i)==1){
		T = insert(T, ele);
		str+=i;
		create(T->left);
		create(T->right);
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

node* mirror(node* T)
{
    if(T==NULL)
        return;
    printf("%d ",T->data);

    printf("( ");
    mirror(T->right);
    printf(") ");

    printf("( ");
    mirror(T->left);
    printf(") ");
}


int main()
{
    node *T=NULL;
    T=create(T);
    printf("( ");
    mirror(T);
    printf(") ");
}
