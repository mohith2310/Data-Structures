#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

#define in(a) scanf("%d",&a);
#define loop(i,a,b) for(int i=a;i<b;i++)

int main()
{
  int v,e;in(v);in(e);

  int edges[e][3];

  loop(i,0,e){
    in(edges[i][0]);
    in(edges[i][1]);
    in(edges[i][2]);
  }

  int dis[v];
  loop(i,0,v)
    (dis[i]=0);

  loop(i,0,v-1)
    loop(j,0,e)
    {
      int x=edges[j][0],y=edges[j][1],z=edges[j][2];
      if(dis[y]>dis[x]+z  &&  dis[x]!=INT_MAX)
        dis[y]=dis[x]+z;
    }

    loop(j,0,e)
    {
      int x=edges[j][0],y=edges[j][1],z=edges[j][2];
      if(dis[y]>dis[x]+z  &&  dis[x]!=INT_MAX)
      {
        printf("1\n" );
        return 0;
      }
    }
    printf("-1\n" );

  return 0;
}
