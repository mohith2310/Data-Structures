#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

#define new (node*)malloc(sizeof(node))

typedef struct Node
{
        int data;
        char clr;
        struct Node *left, *right;
}node;

void insert(node **T)
{
        int d;
        char bfr;
        scanf("%c",&bfr);
        while(bfr == ')' || bfr==' ')
                scanf("%c",&bfr);
        if(bfr=='(')
        {
                if(scanf("%d",&d))
                {
                        *T = new;
                        (*T)->data = d;
                        (*T)->left = (*T)->right = NULL;
                        scanf("%c",&bfr);
                        scanf("%c",&bfr);
                        (*T)->clr = bfr;
                        insert(&((*T)->left));
                        insert(&((*T)->right));
                }
        }
}

int isRb(node *T,int min,int max,int *h)
{
        if(T==NULL)
        {
                *h = 1;
                return 1;
        }
        if(T->clr=='R')
        {
                if(T->left!=NULL)
                  if(T->left->clr=='R')
                        return 0;
                if(T->right!=NULL)
                  if(T->right->clr=='R')
                        return 0;
        }
        if(T->data<min || T->data>max)
                return 0;

        int lh=0 , rh = 0;

        int l = isRb(T->left,min,T->data-1,&lh) ;
        int r = isRb(T->right,T->data+1,max,&rh);

        (T->clr=='B') ? (*h = 1 + lh) : (*h = lh);

        if(lh!=rh) 
		return 0;
       	return l&&r ;
}

int main()
{
        node *T;
        insert(&T);
        int res=0;
        int h=0;
        if(T)
          if(T->clr=='R')
          {
            printf("0\n");
            return 0;
          }
        res=isRb(T,INT_MIN,INT_MAX,&h);
        printf("%d\n",res);
}
