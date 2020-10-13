#include<iostream>
#include<algorithm>
#include<stack>
#include<cstring>
#include<cstdio>

using namespace std;
struct houselist {
    long int c, h;
};

int main() {
    long long color[100005];
    long int p, i, n, cnt, ans;
    scanf("%ld", &p);
    for (ans = 0; ans < p; ans++) {
        scanf("%ld", &n);
        struct houselist house[n];
        memset(color, 0, sizeof(color));
        stack<struct houselist> s;
        for (i = 0; i < n; i++) {
            scanf("%ld", &house[i].c);
        }
        for (i = 0; i < n; i++) {
            scanf("%ld", &house[i].h);
        }
        s.push(house[0]);
        color[house[0].c] = 1;
        cnt = 1;
        printf("%ld ", cnt);
        for (i = 1; i < n; i++) {
            while (!s.empty() && house[i].h >= s.top().h) {
                color[s.top().c] -= 1;
                if (color[s.top().c] == 0) {
                    cnt--;
                }
                s.pop();
            }
            if (color[house[i].c] == 0)
                cnt++;
            color[house[i].c] += 1;
            s.push(house[i]);
            if (i == n - 1)
                printf("%ld\n", cnt);
            else printf("%ld ", cnt);
        }
    }
}
