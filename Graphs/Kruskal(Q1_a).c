#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

#define lar 1001
#define in(a) scanf("%d",&a);
#define inc(a) scanf("%c",&a);
#define new (Ver*)malloc(sizeof(Ver))
#define loop(i,a,b) for(int i=a;i<b;i++)

int parent[lar],rank[lar];

typedef struct vertex{
  int data;
  struct vertex* next;
}Ver;

typedef struct edge{
  int src,dest,weight;
}Edge;

int Graph_list(int v,Ver* V[v])
{
  Ver *temp;
  int count=0,i=0,k=0;
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
    count++;
  }
  return count/2;
}

int making_edge_set(int v,Ver *V[v],Edge E[],int e)
{
  Ver *temp;
  int idx=0;
  loop(i,0,v)
  {
    temp=V[i];
    while(temp)
    {
      int w;in(w);
      if(i<temp->data)
      {
        E[idx].src=i;
        E[idx].dest=temp->data;
        E[idx++].weight=w;
      }
      temp=temp->next;
    }
  }
}

void Union(int a,int b)
{
  if(rank[a]<rank[b])
    parent[a]=b;
  else if(rank[a]>rank[b])
    parent[b]=a;
  else{
    parent[b]=a;
    rank[a]++;
  }
}

int find(int a)
{
  if(a==parent[a])
    return a;
  else
  {
    parent[a]=find(parent[a]);
    return parent[a];
  }
}

int cycle(Edge E)
{
  int a=find(E.src);
  int b=find(E.dest);
  if(b==a)
    return 1;
  Union(a,b);
  return 0;
}

int comparator(const void* a,const void* b)
{
  Edge* l=(Edge *)a;
  Edge* r=(Edge *)b;
  return (l->weight-r->weight);
}

int kruskal(int v,Ver *V[v],Edge E[],int e)
{
  int ans=0;
  qsort(E,e,sizeof(Edge),comparator);
  loop(i,0,e)
    if(!cycle(E[i]))
      ans+=E[i].weight;
  return ans;
}

int main()
{
  memset(rank,0,lar*sizeof(int));
  loop(i,0,lar)
    parent[i]=i;
  int v;in(v);
  Ver* V[v];
  int e=Graph_list(v,V);
  Edge E[e];
  making_edge_set(v,V,E,e);
  int res=kruskal(v,V,E,e);
  printf("%d\n",res);
}
