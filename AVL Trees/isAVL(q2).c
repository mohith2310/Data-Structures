#include <stdio.h>
#include <stdlib.h>
#include<limits.h>

#define new (node *)malloc(sizeof(node))
#define unc  z->p->p
typedef struct Node{
    int data;
    char clr;
    struct Node *left,*right,*p;
}node;

void leftRotate(node **T,node *x)
{
  node *y=x->right;
  x->right=y->left;
  if(y->left!=NULL)
    y->left->p=x;
  y->p=x->p;
  if(x->p==NULL)
  {
    T->data=y->data;
    T->clr=y->clr;
    T->left=y->left;
    T->right=y->right;
    T->p=NULL;
  }
  else if(x==x->p->left)
    x->p->left=y;
  else
    x->p->right=y;
  y->left=x;
  x->p=y;
}

void rightRotate(node **T,node *x)
{
  node *y=x->left;
  x->left=y->right;
  if(y->right!=NULL)
    y->right->p=x;
  y->p=x->p;
  if(x->p==NULL)
  {
    T->data=y->data;
    T->clr=y->clr;
    T->left=y->left;
    T->right=y->right;
    T->p=NULL;
  }
  else if(x==x->p->left)
    x->p->left=y;
  else
    x->p->right=y;
  y->right=x;
  x->p=y;
}

void fix(node **T,node *z)
{
  while(z->p->clr=='R')
  {
    if(z->p==unc->left)
    {
      node *y=unc->right;
      if(y->clr=='R')
      {
        z->p->clr='B';
        y->clr='B';
        unc->clr='R';
        z=unc;
      }
      else if(z==z->p->right)
      {
        z=z->p;
        leftRotate(T,z);
        z->p->clr='B';
        unc->clr='R';
        rightRotate(T,unc);
      }
    }
    else
    {
      if(z->p==unc->right)
      {
        node *y=unc->left;
        if(y->clr=='R')
        {
          z->p->clr='B';
          y->clr='B';
          unc->clr='R';
          z=unc;
        }
        else if(z==z->p->left)
        {
          z=z->p;
          rightRotate(T,z);
          z->p->clr='B';
          unc->clr='R';
          leftRotate(T,unc);
        }
    }
  }

}

void insert(node **T,node *z)
{
  node *y=NULL;
  node *x=T;
  while(x!=NULL)
  {
    y=x;
    if(z->data<x->data)
      x=x->left;
    else
      x=x->right;
  }
  z->p=y;
  if(y==NULL)
    T=z;
  else if(z->data<y->data)
    y->left=z;
  else
    y->right=z;
  z->left=NULL;
  z->right=NULL;
  x->clr=R;
  fix(T,z);
}

void printTree(node *T)
{
  if(T==NULL)
  {
    printf("( )");
  }
  else
  {
    printf("(");
    printf("%d %c",T->data,T->clr);
    printTree(T->left);
    printTree(T->right);
    printf(")");
  }
}

int main()
{
    node *T=NULL;
    int key;
    while(scanf("%d",&key))
    {
      node *z=(node  *)malloc(sizeof(node));
      z->data=key;
      z->clr=R;
      z->left=z->right=z->p=NULL;
      insert(&T,z);
      printTree(T);
    }

}
