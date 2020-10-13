#include<iostream>
#include<algorithm>
#include<queue>
#include<cstring>
#include<cstdio>
using namespace std;
//long int flag;
int main()
{
    queue<char *> name;
    long int n,i=0;
    char *s,*p;
//    string s1;
//    scanf("%ld",&n);
//    getchar();
    cin >> n;
    for(i=0;i<n;i++)
    {
//        memset(s,'\0',sizeof(s));
        s = new char[30];
        gets(s);
//        fflush(stdin);
        if(s[0]=='A')
        {
            name.push(s);
//            flag=1;
        }
        if(s[0]=='L')
        {
            if(!name.empty()) name.pop();
            /*
            if(name.empty()==1)
            {
                flag=0;
            }
            else
            {
                name.pop();
                flag = !name.empty();
//                if(name.empty()==1)
//                {
//                    flag=0;
//                }
//                else
//                {
//                    flag=1;
//                }
            }
             */
        }
        if(s[5]=='H')
        {
//            if(flag==1)
//            {
//                cout<<name.front()<<endl;
//            }
//            if(flag==0)
//            {
//                printf("Empty queue\n");
//            }
            if(!name.empty()){
                printf("%s",name.front()+7);
//                cout<<name.front()<<endl;
            }else{
                printf("Empty queue\n");
            }
        }
        if(s[5]=='T')
        {
            if(!name.empty()){
                printf("%s",name.back()+7);
//                cout<<name.front()<<endl;
            }else{
                printf("Empty queue\n");
            }
//            if(flag==1)
//            {
//                cout<<name.back()<<endl;
//            }
//            if(flag==0)
//            {
//                printf("Empty queue\n");
//            }
        }
    }
}