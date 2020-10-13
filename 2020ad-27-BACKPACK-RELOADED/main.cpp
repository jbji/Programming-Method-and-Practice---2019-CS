#include <iostream>
#include <cstring>
/*
 * 对于 
 * %V==0 -> ++; 
 * dp[][v] 表示体积 
 * //when taking an extra object: 
 * dp[object_index][v] = dp[object_index - 1 ][v] // not taking this object 
 *                     = dp[object_index - 1][v - object_v] + 1 // taking this object 
 *  v%V == 0; -> ++; 
 *  dp[object_index][v] 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * */
using namespace std;
void printdp(int * dp,int len){
    for(int i=0;i<len;i++){
        cout << dp[i] <<" ";
    }
    cout << endl;
}
int main() {
    ios::sync_with_stdio(false);
    int n, V;
    const int mod = 10000000;
    const int inf = -1;
    cin >> n >> V;
    int p[n]; // p  stands for volume of every single object. 
    //objective : pick out some objects full-filling a backpack of volume k*V. 
    int sum = 0 ;
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        sum += p[i];
    }
    int maxIndex = sum/V *V;
    auto *dp = new int[maxIndex + 1];
    for(long long i=0;i< maxIndex+1;i++){
        dp[i] = inf;
    }
    dp[0] = 1;
    dp[p[0]] = 1; //represents for plan num. 
    for (int i = 1; i < n; i++) { //from the second object 
        for (int j = maxIndex; j >= p[i]; j--) {
            if(dp[j] < 0 && dp[j - p[i]]>0){
                dp[j] = dp[j - p[i]];
            }else if(dp[j] >0){
                dp[j] += dp[j - p[i]];
                dp[j] %= mod;
            }
        }
//        cout << "after putting p[i]: " << p[i] << endl;
        printdp(dp,maxIndex+1);
    }
    int ans = 0;
    for(int i=V;i<=maxIndex;i+=V){
        if(dp[i] >= 0){
            ans += dp[i];
            ans %= mod;
        }
    }
    std::cout << ans << std::endl;
    return 0;
}  