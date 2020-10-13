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

void printdp(int *dp, int len) {
    for (int i = 0; i < len; i++) {
        cout << dp[i] << " ";
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
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        p[i] %= V;
        if(p[i] == 0) p[i] = V;
    }
    int * dp = new int[2*V+2];
    memset(dp,0, sizeof(int) * (2*V+2));
    dp[0] = 1;
    for(int i=1;i<=n;i++){
        for(int j = 2 * V ; j>=p[i-1] ;j--){
            dp[j] = (dp[j] + dp[j-p[i-1]]) % mod;
        }
        for(int j = 2 * V ; j>V ;j--){
            dp[j-V] = (dp[j-V] + dp[j]) % mod;
            dp[j] = 0;
        }
    }

    std::cout << dp[V]%mod << std::endl;
    return 0;
}