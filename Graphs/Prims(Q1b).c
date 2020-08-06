#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

#define in(a) scanf("%d",&a);
#define inc(a) scanf("%c",&a);
#define new (Ver*)malloc(sizeof(Ver))
#define loop(i,a,b) for(int i=a;i<b;i++)

typedef struct vertex{
  int data,weight;
  struct vertex* next;
}Ver;

void Graph_list(int v,Ver* V[v])
{
  Ver *temp;
  int i=0,k=0;
  char c;
  while(i<v)
  {
    int ele;in(ele);
    if(k==0)
    {
      V[i]=new;
      temp=V[i];
      k++;
    }
    else
    {
      temp->next=new;
      temp=temp->next;
    }
    temp->data=ele;
    temp->next=NULL;
    inc(c);
    if(c=='\n')
    {
      i++;
      k=0;
    }
  }
}

void adding_weight(int v,Ver *V[v])
{
    Ver *temp;
    loop(i,0,v)
    {
      temp=V[i];
      while(temp!=NULL)
      {
        int w;in(w);
        temp->weight=w;
        temp=temp->next;
      }
    }
}

int extractMin(int v,Ver *V[v],int key[],int flag[])
{
  int min_idx,min=INT_MAX;
  loop(i,0,v)
  {
    if(flag[i]==0 && key[i]<min)
    {
      min=key[i];
      min_idx=i;
    }
  }
  return min_idx;

}

int prim(int v,Ver *V[v])
{
  int key[v],flag[v];
  loop(i,0,v)
  {
    flag[i]=0;
    key[i]=INT_MAX;
  }
  key[0]=0;
  Ver *temp;
  loop(i,0,v-1)
  {
    int ele=extractMin(v,V,key,flag);
    flag[ele]=1;
    temp=V[ele];
    while(temp!=NULL)
    {
      if( flag[temp->data]==0 && temp->weight<key[temp->data] )
        key[temp->data]=temp->weight;
      temp=temp->next;
    }
  }
  int ans=0;
  loop(i,0,v)
    ans+=key[i];
  return ans;
}

int main()
{
  int v;in(v);
  Ver* V[v];
  Graph_list(v,V);
  adding_weight(v,V);
  int res=prim(v,V);
  printf("%d\n",res);
}
