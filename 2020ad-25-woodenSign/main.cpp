#include <iostream>
#include <cstring>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    const int mod = INT32_MAX;

    long long *dp[n+1]; //wooden sign <i>, tail at <j>
    int arrow[n + 1];
    for(int i=0;i<n+1;i++){
        cin >> arrow[i];
        dp[i] = new long long [n+2];
        memset(dp[i],0,sizeof(long long) * (n+2));
    }
    dp[1][arrow[0]] = 1; //arrow zero is a tail
    for(int i=2;i<=n;i++){
        for(int j=1;j<=n+1;j++){
            int l = min(j, arrow[i - 1]) , r = max(j, arrow[i - 1]);
            if(arrow[i] > l){
                dp[i][l] += dp[i-1][j];
                dp[i][l] %= mod;
            }
            if(arrow[i] < r){
                dp[i][r] += dp[i-1][j];
                dp[i][r] %= mod;
            }
        }
    }
    long long ans = 0;
    for(int i=1;i<=n+1;i++){
        ans += dp[n][i];
        ans %= mod;
    }
    cout << ans << endl;
    return 0;
}