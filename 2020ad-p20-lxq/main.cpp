#include <iostream>
//#include <stdio.h>
long long int a[200000]={0};
int main()
{
    int j, flag, i, n;
    long long int max=0, k;
    while(scanf("%d", &n)!=EOF)
    {
        if(n!=0)scanf("%lld", &a[0]);
        j=0;
        flag=1;
        max=0;
        //k=1;
        for(i=1; i<n; i++)
        {
            scanf("%lld", &k);
            if(flag){
                if(a[j]!=k){
                    if(k<a[j]) {  //新的数小于栈底，存入栈中
                        j++;
                        a[j]=k;
                    }else {
                        flag=0;  //新的数比栈底大，break
                    }
                }else{   //新取的数等于栈底
                    if(a[j]>max)max=a[j];  //找到最高的，并且会被消除的数
                    if(j>0)j--;      //新放入的数等于栈底，推出
                    else{      //栈中数为0
                        if(i<n-1){     //存入的数不是最后一个
                            scanf("%lld", &a[0]);
                        }
                        else break;  //存入的数是最后一个
                        j=0;
                        i++;    //上面新存了一个a[0]，要+1
                        if(i==n-1 && a[0]<max)flag=0;  //如果上面新存入的是最后一个，如果比最高的高YES；否则NO
                    }
                }
            }
        }
        if(j==0 && flag)printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}