#include<stdio.h>

int main() {//½öÊÊÓÃÓÚ1900.3.1--2100.2.28
    int a, b, d, e;
    long int c;
    scanf("%d%d%ld", &a, &b, &c);
    if (b > 12 || b < 1) {
        printf("month is error.\n");
        goto k;
    }
    else if (a % 4 == 0) {
        if (b == 1 || b == 3 || b == 5 || b == 7 || b == 8 || b == 10 || b == 12) {
            if (c > 31 || c < 1) {
                printf("day is error.\n");
                goto k;
            }
            else goto m;
        } else if (b == 2) {
            if (c > 29 || c < 1) {
                printf("day is error.\n");
                goto k;
            }
            else goto m;
        } else {
            if (c > 30 || c < 1) {
                printf("day is error.\n");
                goto k;
            }
            else goto m;
        }
    } else {
        if (b == 1 || b == 3 || b == 5 || b == 7 || b == 8 || b == 10 || b == 12) {
            if (c > 31 || c < 1) {
                printf("day is error.\n");
                goto k;
            }
            else goto m;
        } else if (b == 2) {
            if (c > 28 || c < 1) {
                printf("day is error.\n");
                goto k;
            }
            else goto m;
        } else {
            if (c > 30 || c < 1) {
                printf("day is error.\n");
                goto k;
            }
            else goto m;
        }
    }
    m:
    c = c + 70000;
    if (a >= 2013) {
        e = (a - 2013) * 365 + (a - 2012) / 4;
        if (b == 1) c = c - 28 - 31 + e - (a - 2012) / 4 + (a - 1 - 2012) / 4;
        else if (b == 2) c = c - 28 + e - (a - 2012) / 4 + (a - 1 - 2012) / 4;
        else if (b == 3) c = c + e;
        else if (b == 4) c = c + 31 + e;
        else if (b == 5) c = c + 31 + 30 + e;
        else if (b == 6) c = c + 31 + 30 + 31 + e;
        else if (b == 7) c = c + 31 + 30 + 31 + 30 + e;
        else if (b == 8) c = c + 31 + 30 + 31 + 30 + 31 + e;
        else if (b == 9) c = c + 31 + 30 + 31 + 30 + 31 + 31 + e;
        else if (b == 10) c = c + 31 + 30 + 31 + 30 + 31 + 31 + 30 + e;
        else if (b == 11) c = c + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + e;
        else if (b == 12) c = c + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30 + e;
    } else {
        e = (a - 2013) * 365 - (2016 - a) / 4;
        if (b == 1) c = c - 28 - 31 + e;
        else if (b == 2) c = c - 28 + e;
        else if (b == 3) c = c + e + (2016 - a) / 4 - (2016 - 1 - a) / 4;
        else if (b == 4) c = c + 31 + e + (2016 - a) / 4 - (2016 - 1 - a) / 4;
        else if (b == 5) c = c + 31 + 30 + e + (2016 - a) / 4 - (2016 - 1 - a) / 4;
        else if (b == 6) c = c + 31 + 30 + 31 + e + (2016 - a) / 4 - (2016 - 1 - a) / 4;
        else if (b == 7) c = c + 31 + 30 + 31 + 30 + e + (2016 - a) / 4 - (2016 - 1 - a) / 4;
        else if (b == 8) c = c + 31 + 30 + 31 + 30 + 31 + e + (2016 - a) / 4 - (2016 - 1 - a) / 4;
        else if (b == 9) c = c + 31 + 30 + 31 + 30 + 31 + 31 + e + (2016 - a) / 4 - (2016 - 1 - a) / 4;
        else if (b == 10) c = c + 31 + 30 + 31 + 30 + 31 + 31 + 30 + e + (2016 - a) / 4 - (2016 - 1 - a) / 4;
        else if (b == 11) c = c + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + e + (2016 - a) / 4 - (2016 - 1 - a) / 4;
        else if (b == 12) c = c + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30 + e + (2016 - a) / 4 - (2016 - 1 - a) / 4;
    }
    d = (c - 10) % 7;
    printf("%d\n", d);
    k:
    return (0);
}
