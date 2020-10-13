#include<bits/stdc++.h>
/*
 * 题目：给定n，m，求长度为n的数列的m个不相交子列的最大和。

视状态为dp[i][j]为分成i组以j结尾的最大子列和，状态转移方程为：

dp[i][j]=max{ A： dp[i][j-1]  , B： max(dp[i-1][i~j-1])   } + a[j];

A: a[j]与a[j-1]相连组成第i个子列   B：a[j]不与任何子列相连，独自形成第i个子列

i的移动需要m次循环，j的移动需要n次循环，B中max项的确认需要j-i+1次循环

时间复杂度可达 n^3，n最大为1000000,dp[i][j]会mle

优化： dp只与i，i-1状态有关，可以只开一维数组，优化空间

            用premx[j-1]记录上一次外层循环的max(dp[i-1][i~j-1]) 可以免去第三次循环 时间降为n^2

            */
using namespace std;
#define MAXN 1000000
const int inf = 0x3f3f3f3f;

int data[MAXN + 10];
long long dp[MAXN + 10], premx[MAXN + 10];

int main() {
    int m, n;
    //求解m组最大不相交子段和
    for (int i = 1; i <= n; i++) {
        scanf("%d", &data[i]);
        dp[i] = 0;
        premx[i] = 0;
    }
    long long mx;
    dp[0] = 0;
    premx[0] = 0;

    for (int i = 1; i <= m; i++) {
        mx = -inf;
        for (int j = i; j <= n; j++) {
            dp[j] = max(dp[j - 1], premx[j - 1]) + data[j];
            premx[j - 1] = mx;
            mx = max(mx, dp[j]);
        }
    }

    printf("%lld\n", mx);

    return 0;
}