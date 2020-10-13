#include<stdio.h>
#include<string.h>

struct House {
    long long color;
    long long height;
} house[1100000];
long long int color[1100000];
long long n0, i, j, n, k, count;

int main() {

    scanf("%lld", &n0);
    for (i = 0; i < n0; i++) {
        scanf("%lld", &n);
        for (j = 0; j < n; j++) scanf("%lld", &house[j].color);
        for (j = 0; j < n; j++) scanf("%lld", &house[j].height);
        memset(color, 0, sizeof(color));
        count = 1;
        color[house[0].color] = 1;
        printf("1 ");
        for (j = 1; j < n; j++) {
            if (color[house[j].color] == 0) count++;
            color[house[j].color]++;
            if (house[j].height >= house[j - 1].height) {
                k = j - 1;
                while (house[k].height <= house[j].height && k >= 0) {
                    color[house[k].color]--;
                    if (color[house[k].color] == 0) count--;
                    k--;
                }
            }
            if (j < n - 1) printf("%lld ", count);
            else printf("%lld\n", count);
        }
    }
}
