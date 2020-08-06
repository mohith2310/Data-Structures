#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct heap{
        int data,deg;
        struct heap *sib,*child,*par;
}*node;
node create()
{
        node temp = (node)malloc(sizeof(struct heap));
        temp->par = NULL;
        temp->child = NULL;
        temp->sib = NULL;
        temp->deg = 0;
        return temp;
}

node make_heap()
{
        node h = NULL;
        return h;
}

node binomial_link(node x,node y)
{
        x->sib = y->child;
        y->child = x;
        x->par = y;
        y->deg += 1;
        return y;
}

node merge(node p,node q)
{
        if(p==NULL)
                return q;
        else if(q==NULL)
                return p;                                                                                                                                                                                                  else if(p->deg <= q->deg)
        {                                                                                                                                                                                                                          p->sib = merge(p->sib,q);                                                                                                                                                                                          return p;                                                                                                                                                                                                  }                                                                                                                                                                                                                  else
        {
                q->sib = merge(q->sib,p);
                return q;
        }
}

node consolidate(node p)
{
        if(p==NULL)
                return NULL;
        else if(p->sib == NULL)
                return p;
        else if(p->sib->deg > p->deg)
        {
                p->sib = consolidate(p->sib);
                return p;
        }
        else
        {
                if((p->sib->sib!=NULL)&&(p->sib->sib->deg==p->deg))
                {
                        p->sib = consolidate(p->sib);
                        return p;
                }
                else
                {
                        node z = p->sib->sib;
                        if(p->data < p->sib->data)
                                p = binomial_link(p->sib,p);
                        else
                                p = binomial_link(p,p->sib);
                        p->sib = z;
                        p = consolidate(p);
                        return p;
                }
        }
}

node Union(node h1,node h2)
{
        if(h1==NULL)
                return h2;
        else if(h2==NULL)
                return h1;
        else
        {
                node H = make_heap();
                node p = h1;
                node q = h2;
        //      free(h1);
        //      free(h2);
                H = merge(p,q);
                H = consolidate(H);
                return H;
        }
}


node insert(node H,node x)
{
        node h = make_heap();
        h = x;
        H = Union(H,h);
        return H;
}

node reverse(node x)
{
        node current=x,next=NULL,prev=NULL;
        while(current != NULL)
        {
                current->par = NULL;
                next = current->sib;
                current->sib = prev;
                prev = current;
                current = next;
        }
        x = prev;
        return x;
}

node extract_min(node H)
{
        node m=create(),curr=H,prev=NULL,pre=NULL;
        m->data = 9999;
        while(curr != NULL)
        {
                if(m->data > curr->data)
                {
                        m = curr;
                        pre = prev;
                }
                prev = curr;
                curr = curr->sib;
        }
        node x = m->child;
        if(pre!=NULL)
                pre->sib = m->sib;
        else
                H = m->sib;
        //free(m);
        node h = make_heap();
        h = reverse(x);
        H = Union(H,h);
        //printtree(H);
        return H;
}

node decrease_data(node H,node x,int k,int j,node A[])
{
        x->data -= k;
        int t=x->data;
        while(x->par!=NULL&&x->par->data > x->data)
        {
                //x->data = x->par->data;
                //x->par->data = t;
                //x = x->par;
                int i=0;
                while(A[i] != x->par)
                        i++;
                node temp;
                temp = A[j];
                A[j] = A[i];
                A[i] = temp;
                k = x->data;
                x->data = x->par->data;
                x->par->data = k;
                x = x->par;
        }
        //printf("heap after decreasing is\n");
        //printtree(H);
        return H;
}

node delete(node H,node x,int j,node A[])
{
        decrease_data(H,x,-9999,j,A);
        extract_min(H);
        return H;
}

int printtree(node H)
{
        node p = H;
        int count=0;
        while(p!=NULL)
        {
                count++;
                p = p->sib;
        }
        printf("%d\n",count);
}

int main()
{
        int n;
        scanf("%d",&n);
        node A[n];
        node H = make_heap();
        node min = create();
        min->data = 9999;
        for(int i=0;i<n;i++)
                A[i] = NULL;
        int j,k;
        char c[4];
        while(1)
        {
                scanf("%s",c);
                if(!strcmp(c,"insr"))
                {
                        scanf("%d %d",&j,&k);
                        node new = create();
                        new->data = k;
                        H = insert(H,new);
                        A[j] = new;
                        if(min->data>k)
                                min = new;
                }
                if(!strcmp(c,"min"))
                        printf("%d\n",min->data);
                if(!strcmp(c,"extr"))
                {
                        printf("%d\n",min->data);
                        H = extract_min(H);
                        node p=H;
                        min->data = 9999;
                        while( p != NULL)
                        {
                                if(p->data < min->data)
                                        min = p;
                                p = p->sib;
                        }
                }
                if(!strcmp(c,"decr"))
                {
                        scanf("%d %d",&j,&k);
                        if(A[j]->data<k)
                                printf("-1\n");
                        else
                                H = decrease_data(H,A[j],k,j,A);
                        node p = H;
                        while(p!=NULL)
                        {
                                if(p->data < min->data)
                                        min = p;
                                p = p->sib;
                        }
                }
                if(!strcmp(c,"del"))
                {
                        scanf("%d",&j);
                        if(A[j]==NULL)
                        {
                                printf("-1\n");
                                continue;
                        }
                        printf("%d\n",A[j]->data);
                        H = delete(H,A[j],j,A);
                        node p=H;
                        if(min->data==A[j]->data)
                                min->data = 9999;
                        while(p!=NULL)
                        {
                                if(p->data < min->data)
                                        min = p;
                                p = p->sib;
                        }
                        A[j] = NULL;
                }
                if(!strcmp(c,"tc"))
                        printtree(H);
                if(!strcmp(c,"stop"))
                          return 0;
        }
}
