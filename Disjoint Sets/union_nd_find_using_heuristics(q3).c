#include<stdio.h>
#include<stdlib.h>

#define N 10001

typedef struct node
{
        int parent[N];
        int rank[N];
        int type;
}Node;

int g[4];

Node *initial(Node *ds,int i)
{
        ds = (Node*)malloc(sizeof(Node));
        for(int i=0;i<N;i++)
                ds->parent[i]=-1;
        ds->type = i;
        return ds;
}

Node *make_set(Node *ds,int d)
{
        if(ds->parent[d]!=-1)
        {
                if(ds->type==0)
                        printf("PRESENT\n");
                return ds;
        }
        else
        {
                if(ds->type==0)
                        printf("%d\n",d);
                ds->parent[d] = d;
                ds->rank[d] = 0;
                return ds;
        }
}

int find(Node *ds,int x)
{
        g[ds->type]++;
        if(ds->parent[x]==-1)
                return -1;
        if(ds->type==0 || ds->type==1)
        {
                if(ds->parent[x]==x)
                        return x;
                return find(ds,ds->parent[x]);
        }
        if(ds->type==2 || ds->type==3)
        {
                if(ds->parent[x]==x)
                        return x;
                return ds->parent[x] = find(ds,ds->parent[x]);
        }
}

Node *unin(Node *ds,int x,int y)
{
        int px = ds->parent[x];
        int py = ds->parent[y];
        if(px==-1 || py==-1)
        {
                if(ds->type==0)
                printf("ERROR\n");
                return ds;
        }
        px = find(ds,x);
        py = find(ds,y);
        if(ds->type==0 || ds->type==2)
        {
                ds->parent[py] = px;
                printf("%d ",px);
                return ds;
        }
        if(ds->type==1 || ds->type==3)
        {
                if(ds->rank[px]>ds->rank[py])
                {ds->parent[py] = px;
                        printf("%d ",px);
                }
                else if(ds->rank[px]<ds->rank[py])
                {       ds->parent[px] = py;
                        printf("%d ",py);
                }
                else
                {
                        ds->parent[py] = px;
                        ds->rank[px]++;
                        printf("%d ",px);
                }
                return ds;
        }
}

int main()
{

        char c;
        int d;
        int x,y;
        Node *ds[4];
        for(int i=0;i<4;i++)
        {
                g[i] = 0;
                ds[i] = initial(ds[i],i);
        }
        while(1)
        {
                scanf("%c",&c);
                if(c=='m')
                {
                      scanf("%d",&d);
                     for(int i=0;i<4;i++)
                       ds[i] = make_set(ds[i],d);
                }
                if(c=='m')
                {
                      scanf("%d",&x);
                      scanf("%d",&y);
                      for(int i=0;i<4;i++)
                        ds[i] = unin(ds[i],x,y);
                      printf("\n");
                }
                if(c=='m')
                {
                      scanf("%d",&d);
                      for(int i=0;i<4;i++)
                      {
                         x = find(ds[i],d);
                         if(x==-1)
                         {
                           printf("NOT FOUND\n");
                           break;
                         }
                          printf("%d ",x);
                       }
                      printf("\n");
                  }
                  if(c=='m')
                  {
                      printf("%d %d %d %d\n",g[0],g[1],g[2],g[3]);
                      return 0;
                  }
        }
}
