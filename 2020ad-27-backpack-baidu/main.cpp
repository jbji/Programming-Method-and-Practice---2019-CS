#include <iostream>
#include <cstring>

using namespace std;

const int INF = 0x3f3f3f3f;
const int NINF = -INF - 1;

int main() {
    int n = 5;
    int sum = 12;


    int p[5] = {12, 3, 10, 3, 6};

    int dp[6][13];

    int i, v;

    memset(dp, NINF, sizeof(dp));
    dp[0][0] = 0;

    for (i = 1; i <= n; i++) {
        dp[i][0] = 0;

        for (v = 1; v <= sum; v++) {
            dp[i][v] = dp[i - 1][v];
        }
    }

    for (i = 1; i <= n; i++) {
        for (v = 0; v <= sum; v++) {
            if (dp[i][v] < 0)
                printf("X  ");
            else
                printf("%d  ", dp[i][v]);
        }
        printf("\n");
    }
    return 0;
}