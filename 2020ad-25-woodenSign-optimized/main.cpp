#include <iostream>
#include <cstring>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    const int mod = INT32_MAX;
    long long dp[n+2]; //wooden sign <i>, tail at <j>
    long long pre[n+2]; //wooden sign <i>, tail at <j>
    int arrow[n + 1];
    memset(dp,0,sizeof(long long) * (n+2));
    memset(pre,0,sizeof(long long) * (n+2));
    for(int i=0;i<n+1;i++){
        cin >> arrow[i];
    }
    pre[arrow[0]] = 1; //arrow zero is a tail, and pre here for sign<1>
    for(int i=2;i<=n;i++){ //begin from sign <2>
        memset(dp,0,sizeof(long long) * (n+2));
        for(int j=1;j<=n+1;j++){
            int l = min(j, arrow[i - 1]) , r = max(j, arrow[i - 1]);
            if(arrow[i] > l){
                dp[l] += pre[j];
                dp[l] %= mod;
            }
            if(arrow[i] < r){
                dp[r] += pre[j];
                dp[r] %= mod;
            }
        }
        for(int j=1;j<=n+1;j++){
            pre[j] = dp[j];
        }
    }
    long long ans = 0;
    for(int j=1;j<=n+1;j++){
        ans += pre[j];
        ans %= mod;
    }
    cout << ans << endl;
    return 0;
}