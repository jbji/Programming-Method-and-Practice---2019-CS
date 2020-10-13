#include <iostream>
#include <cstring>

using namespace std;

long long int mergeSort(int *,int m,int n);
long long int mergeCalc(int *,int,int,int);

int main() {
    int n;
    cin >> n;
    int a[n];
    memset(a,0,sizeof(a));
    char tmpChar=getchar();
    int tmpNum=0,symbol,index=0;
    long long int ans=0;
    while(!((tmpChar >= '0' && tmpChar <= '9') || tmpChar == ' ' || tmpChar == '-'))  tmpChar=getchar();
    while((tmpChar >= '0' && tmpChar <= '9') || tmpChar == ' ' || tmpChar == '-'){
        if(tmpChar != ' '){
            symbol = 1;
            if(tmpChar == '-'){
                symbol = -1;
                tmpChar = getchar();
            }
            tmpNum = 0;
            while(tmpChar >= '0' && tmpChar <= '9'){
                tmpNum = tmpNum*10 + tmpChar-'0';
                tmpChar=getchar();
            }
            //here we can process;
            a[index++]=tmpNum*symbol;
            continue;
        }
        tmpChar=getchar();
    }
    //换个思路 不妨求解逆序数
    ans = mergeSort(a,0,n-1);
    cout << ans << endl;
    return 0;
}

long long int mergeSort(int *a,int m,int n){
    if( m < n ){
        int mid = ( m + n ) / 2;
        return  mergeSort(a,m,mid) + mergeSort(a,mid+1,n) + mergeCalc(a,m,mid,n);
    }else{
        return 0;
    }
}

long long int mergeCalc(int * a,int m,int mid,int n){
    long long int ans=0;
    int ll = mid-m+1;//左半边元素个数
    int rl = n-(mid+1)+1;//右半边元素个数
    int *l = new int[ll]; //实际需要的长度
    int *r = new int[rl+1]; //防止出现长度为0的数组 [0,0,1] [2,2,2]
    for(int i=0;i<ll;i++){
        l[i]=a[m+i];
    }
    for(int i=0;i<rl;i++){
        r[i]=a[mid+1+i];
    }
    int i=0,j=0,k=m;
    for(;k<=n && i<ll && j<rl; k++){ //用k扫描数组a的区间[m,n]
        if(l[i] <= r[j]){
            a[k] = l[i++];
        }else{
            a[k] = r[j++];
            ans +=  ll-i;//这是因为，包括第i个元素在内，i后面的元素一定都比i要大，当前的r[j]元素相对于l[i]及后面的元素也就构成了这么多个逆序。
        }
    }
    //将左边剩余元素继续加入a数组
    while( i < ll && k<=n ){
        a[k++] = l[i++];
    }
    delete[] l;
    delete[] r;
    return ans;
}