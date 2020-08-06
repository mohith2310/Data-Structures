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

node *LeftRotate(node *y)
{
        node *x = y->right;
        y->right = x->left;
        x->left = y;

        char c = y->clr;
        y->clr = x->clr;
        x->clr = c;

        return x;
}

node *RightRotate(node *y)
{
        node *x = y->left;
        y->left = x->right;
        x->right = y;

        char c = y->clr;
        y->clr = x->clr;
        x->clr = c;

        return x;
}

node *insertRb(node *T,int ele)
{
        if(T == NULL)
        {
                T = new;
                T->data = ele;
                T->clr = 'R';
                T->left = T->right = NULL;
                return T;
        }
        if(ele<T->data)
                T->left = insertRb(T->left,ele);
        else
                T->right = insertRb(T->right,ele);
        if(T->left!=NULL && T->left->clr=='R')
        {
                if(T->left->left!=NULL && T->left->left->clr=='R')
                {
                        if(T->right!=NULL && T->right->clr=='R')
                        {
                                T->clr = 'R';
                                T->left->clr = 'B';
                                T->right->clr = 'B';
                        }
                        else
                                T = RightRotate(T);
                        return T;
                }
                if(T->left->right!=NULL && T->left->right->clr=='R')
                {
                        if(T->right!=NULL && T->right->clr=='R')
                        {
                                T->left->clr = 'B';
                                T->right->clr = 'B';
                                T->clr = 'R';
                        }
                        else
                        {
                                T->left = LeftRotate(T->left);
                                T = RightRotate(T);
                        }
                        return T;
                }
        }

        if(T->right!=NULL && T->right->clr=='R')
        {
                if(T->right->left!=NULL && T->right->left->clr=='R')
                {
                        if(T->left!=NULL && T->left->clr=='R')
                        {
                                T->clr = 'R';
                                T->left->clr = 'B';
                                T->right->clr = 'B';
                        }
                        else
                        {
                                T->right = RightRotate(T->right);
                                T = LeftRotate(T);
                        }
                        return T;
                }
                if(T->right->right!=NULL && T->right->right->clr=='R')
                {
                        if(T->left!=NULL && T->left->clr=='R')
                        {
                                T->clr = 'R';
                                T->left->clr = 'B';
                                T->right->clr = 'B';
                        }
                        else
                                T = LeftRotate(T);
                        return T;
                }
        }
        return T;
}

void print(node *T)
{
        printf("( ");
        if(T!=NULL)
        {
                printf("%d %c ",T->data,T->clr);
                print(T->left);
                print(T->right);
        }
        printf(") ");
}

int main()
{
        node *T = NULL;
        int ele;
        while(scanf("%d",&ele))
        {
                T = insertRb(T,ele);
                T->clr = 'B';
                print(T);
                printf("\n");
        }
}
