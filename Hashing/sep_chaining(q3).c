#include <stdio.h>
#include <stdlib.h>
#include<string.h>

typedef struct Node{
    char *word;
    struct Node *next;
}node;

int hashCode(char str[],int n)
{
    int i=0,j;
    int count=0;
    char temp[20];
    strcpy(temp,str);
    while(temp[i])
    {
        if((temp[i]>='a' && temp[i]<='z') || (temp[i]>='A' && temp[i]<='Z'))
            str[count++] = temp[i++];
        else
            i++;

    }
    str[count] = '\0';
    return count%n;
}

void groupWords(char str[],node* ht[],int n,int idx)
{
    node *temp=(node *)malloc(sizeof(node));
    node *head = ht[idx],*temp1;
    temp->word = str;
    temp->next=NULL;

    if(ht[idx]==NULL)
        ht[idx]=temp;
    else
    {
        while(head!=NULL){
          if(!strcmp(head->word,str))
                return;
            temp1 = head;
            head=head->next;
        }
        temp1->next=temp;
    }
}

void print(node* ht[],int n)
{
    for(int i=0;i<10;i++)
    {
        if(ht[i]==NULL)
            printf("NULL");
        else{
            while(ht[i]!=NULL)
            {
                printf("%s ",ht[i]->word);
                ht[i]=ht[i]->next;
            }
        }
        printf("\n");
    }
}

int main()
{
    int n,idx;
    scanf("%d",&n);
    char bfr;
    scanf("\n");
    char str[100000];
    node* ht[n];
    for(int i=0;i<n;i++)
        ht[i]=NULL;
    scanf("%[^\n]s",str);
    char *word=strtok(str," ");
    while(word!=NULL)
    {
        idx=hashCode(word,n);
        groupWords(word,ht,n,idx);
        word=strtok(NULL," ");
    }
    print(ht,n);
}
