#include <iostream>
#include <cstring>
/*
 * dp function:
 * dp[i][j] = MAX{ dp[i][j-1] + e[j] , MAX{ dp[i-1][i~j-1] + e[j] } }
 * element j is either into <part i>, or be as the head of <part i>
 *
 *
 *
 *
 * */
using namespace std;

void print(long long *dp,int n){
    for(int i=0;i<n;i++){
        cout << dp[i] << " ";
    }
    cout << endl;
}
int main() {
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    int *data = new int[n];
    auto *dp_1 = new long long[n];
    auto *dp_2 = new long long[n];
    auto *dp_3 = new long long[n];
    memset(dp_1, 0, sizeof(long long) * (n));
    memset(dp_2, 0, sizeof(long long) * (n));
    memset(dp_3, 0, sizeof(long long) * (n));
    for (int i = 0; i < n; i++) {
        cin >> data[i];
    }

    dp_1[0] = data[0];
    for (int j = 1; j < n; j++) {
        dp_1[j] = max(dp_1[j - 1] , 0LL) + data[j];
    }
//    print(dp_1,n);
    dp_2[0] = dp_1[0];
    for (int j = 1; j < n; j++) {
        dp_2[j] = max(dp_2[j - 1], dp_1[j - 1]) + data[j];
        dp_1[j] = max(dp_1[j], dp_1[j-1]);
    }
//    print(dp_2,n);
    dp_3[0] = dp_2[0];
    dp_3[1] = dp_2[1];
    for (int j = 2; j < n; j++) {
        dp_3[j] = max(dp_3[j - 1], dp_2[j - 1]) + data[j];
        dp_2[j] = max(dp_2[j], dp_2[j-1]);
    }
//    print(dp_3,n);
    //find the answer
    for (int j = 3; j < n; j++) {
        dp_3[j] = max(dp_3[j], dp_3[j-1]);
    }
//    print(dp_3,n);
    cout << dp_3[n-1] << endl;
    return 0;
}