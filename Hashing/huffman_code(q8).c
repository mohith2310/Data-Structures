#include<stdio.h>
#include<stdlib.h>

#define mem (Node*)malloc(sizeof(Node))
typedef struct node
{
        int data;
        struct node *left;
        struct node *right;
}Node;

typedef struct ch
{
  char k;
  int m;
} C;

Node *newnode(int i)
{
    Node *temp = mem;
    temp->data = i;
    temp->left = temp->right = NULL;
    return temp;
}

Node* insert(Node *T, int ele) {
	if(T == NULL) {
        T = (Node*) malloc(sizeof(Node));
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


Node* search(Node *T,int x)
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

int findMin(Node* T)
{

    Node *temp=mem;
    temp=T;
    if(temp==NULL)
        return;
    while(temp->left!=NULL)
        temp=temp->left;
    return temp->data;
}

Node* delete(Node* T,int ele)
{
    Node *z=search(T,ele);
    Node *x=T;
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
        Node* y=search(T->right,temp);
        x->right=delete(x->right,y->data);
        y->right=x->right;
        y->left=x->left;
        return y;
    }
}

Node *huffman_code(int frq[],int n)
{
    int a;
    char c;
    if(n==0)
    {
        Node *head = newnode(0);
	      return head;
    }
    if(n==1)
    {
    	Node *temp = newnode(frq[0]);
	Node *head = newnode(frq[0]-1);
	head->left = temp;
	return head;
    }
    for (int i = 0; i < n; ++i)
        {

            for (int j = i + 1; j < n; ++j)
            {

                if (frq[i] > frq[j])
                {

                    a =  frq[i];
                    frq[i] = frq[j];
                    frq[j] = a;

                  //  c =  arr[i];
                    //arr[i] = arr[j];
                    //arr[j] = c;

                }

            }

        }
        a = 0;
    Node *t1 = newnode(frq[a++]);
    Node *t2 = newnode(frq[a++]);
    Node *t3 = newnode(t1->data + t2->data);
    if(t1->data>t2->data)
    {t3->left = t2;
    t3->right = t1;}
    else{
        t3->left = t1;
        t3->right = t2;
    }
    while(a<n)
    {
        Node *t1 = newnode(frq[a++]);
        Node *t4 = newnode(t1->data + t3->data);
        if(t1->data>t3->data)
        {t4->left = t3;
        t4->right = t1;}
        else{
        t4->left = t1;
        t4->right = t3;
    }
    t3 = t4;
    }
    return t3;
}

int length(Node *temp,int j)
{
    if(!temp->left && !temp->right)
        return (temp->data)*j;
    return length(temp->left,j+1) + length(temp->right,j+1);
}

int check(char g, C a[])
{
  int flag = 0;
  for(int i=0;C[i].k!='%';i++)
  {
    if(C[i].k==g)
    {flag = 1;
      break;}
  }
  return flag;
}

int main()
{
	char s[100];
  while(1)
  {
  scanf("%s",s);
  if(!strcmp(s,"0"))
      break;
	/*int freq[26];
	for(int i=0;i<26;i++)
        freq[i] = 0;
    for(int i=0;s[i]!='\0';i++)
    {
        freq[s[i]-'a']++;
    }
    int j=0;
    for(int i=0;i<26;i++)
    {
        if(freq[i]!=0)
            j++;
    }
    char arr[j];
    int frq[j];
    j=0;
    for(int i=0;i<26;i++)
    {
        if(freq[i])
        {
            arr[j] = 'a'+i;
            frq[j] = freq[i];
            j++;
        }
    }*/
    C a[100];
    for(int i=0;i<100;i++)
    {a[i].m = 0;
      a[i].k = '%';
    }
    char c;
    int j=0;
    for(int i=0;s[i]!='\0';i++)
    {
      if(check(s[i],a))
      {
        a[i].m += 1;
      }
      else {int j=0;
      for(j=0;s[j].k!='%';j++);
      a[i].k = s[i];
      a[i].m = 1;
    }
    }
    int z=0;
    for(z=0;a[z].m!=0;z++);
    int frq[z];
    for(int i=0;i<z;i++)
    frq[i] = a[i].m;
    Node *head = NULL;
    head = huffman_code(frq,z);
    printf("%d\n",length(head,0));
  }
}
