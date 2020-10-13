#include<iostream>
#include<cstring>
#include<cstdlib>
typedef struct line{
    char name[30];
    struct line *link;
}node;
void leave(node *head,char a[])
{
    node *p;
    if(head->link!=NULL)
    {
        p=head->link;
        head->link=p->link;
    }
}
void arrive(node *head,char a[])
{
    node *p,*q;
    q=head;
    while(q->link!=NULL)
    {
        q=q->link;
    }
    p=(node*)malloc(sizeof(node));
    strcpy(p->name,a);
    p->link=NULL;
    q->link=p;
}
void lookhead(node *head)
{
    node *p;
    if(head->link==NULL)
    {
        printf("Empty queue\n");
    }
    else{
        p=head->link;
        printf("%s\n",p->name+7);
    }
}
void looktail(node *head)
{
    node *p;
    if(head->link==NULL)
    {
        printf("Empty queue\n");
    }
    else{
        p=head->link;
        while(p->link!=NULL)
        {
            p=p->link;
        }
        printf("%s\n",p->name+7);
    }
}
int main()
{
    node *head,*p;
    p=(node*)malloc(sizeof(node));
    p->link=NULL;
    head=p;
    long long int n,i;
    char a[30];
    scanf("%lld",&n);
    getchar();
//    fflush(stdin);
    for(i=0;i<n;i++)
    {
//        memset(a,'\0',sizeof(a));
        gets(a);
//        fflush(stdin);
        if(a[0]=='A')
        {
            arrive(head,a);
        }
        else if(a[0]=='L')
        {
            leave(head,a);
        }
        else if(a[5]=='H')
        {
            lookhead(head);
        }
        else{
            looktail(head);
        }
    }
}