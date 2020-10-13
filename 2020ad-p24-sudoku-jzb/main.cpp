#include <stdio.h>
#include <string.h>

char map[20][20], map1[20][20], fuzhu[5][5], fuzhu2[5][5];//num记录每个位置的大块旋转了几次
int flag1 = 0, flag2 = 0, flag = 0, jilu1[17] = {0}, jilu2[17] = {0}, num[5][5] = {0}, num2[5][5] = {0};

//旋转函数
void xuanzhuan(int n, int x, int y) {
    for (int k = 0; k < n; k++)//k代表旋转的次数
    {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                fuzhu[3 - j][i] = map[i + (x - 1) * 4][j + (y - 1) * 4];
            }
        }
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                map[i + (x - 1) * 4][j + (y - 1) * 4] = fuzhu[i][j];
            }
        }
    }
    //记录块旋转了几次
    num[x - 1][y - 1] = n;
}

void xuanzhuan_lie(int n, int x, int y) {
    for (int k = 0; k < n; k++)//k代表旋转的次数
    {
        for (int r = 0; r < 4; r++) {
            for (int l = 0; l < 4; l++) {
                fuzhu2[3 - l][r] = map[r + (x - 1) * 4][l + (y - 1) * 4];
            }
        }
        for (int r = 0; r < 4; r++) {
            for (int l = 0; l < 4; l++) {
                map[r + (x - 1) * 4][l + (y - 1) * 4] = fuzhu2[r][l];
            }
        }
    }
    //记录块旋转了几次
    for (int p = 0; p < 4; p++) {
        num2[x - 1][p] = (num[x - 1][p] + n) % 4;
    }
}

//判断函数
int panduan(int a) {
    //判断第一行
    memset(jilu1, 0, sizeof(jilu1));
    for (int i = 0; i < 16; i++) {
        char s = map[a][i];
        int k;
        if (s <= '9' && s >= '0') k = s - '0';
        else k = s - 'A' + 10;
        if (jilu1[k] == 0) {
            jilu1[k]++;
        } else {
            return 0;
        }
    }
    return 1;
}

int panduan_lie(int b) {
    //判断第一列
    memset(jilu2, 0, sizeof(jilu2));
    for (int r = 0; r < 16; r++) {
        char s2 = map[r][b];
        int z;
        if (s <= '9' && s >= '0') z = s2 - '0';
        else z = s2 - 'A' + 10;
        if (jilu2[z] == 0) {
            jilu2[z]++;
        } else {
            return 0;
        }
    }
    return 1;
}

//dfs
//dfs
int dfs(int x, int y) {
    if (flag1 == 1) {
        return 0;
    }
    if (y == 4) {
        for (int i = 0; i < 4; i++) {
            xuanzhuan(i, x, y);
            int a = (x - 1) * 4;
            /*int b=(y-1)*4;*/
            int q = panduan(a);
            if (q == 1) {
                flag1 = 1;
                return 0;
            } else {
                //如果行任一有重复，则恢复原图
                for (int k = 0; k < 4; k++) {
                    for (int j = 0; j < 4; j++) {
                        map[k + (x - 1) * 4][j + (y - 1) * 4] = map1[k + (x - 1) * 4][j + (y - 1) * 4];
                    }
                }
                num[x - 1][y - 1] = 0;
            }
        }
    } else if (y != 4) {
        int i;
        for (i = 0; i < 4; i++) {
            xuanzhuan(i, x, y);
            dfs(x, y + 1);
            int a = (x - 1) * 4;
            /*int b=(y-1)*4;*/
            int q = panduan(a);
            if (q == 1) {
                flag1 = 1;
                return 0;
            } else {
                //如果行任一有重复，则恢复原图
                for (int k = 0; k < 4; k++) {
                    for (int j = 0; j < 4; j++) {
                        map[k + (x - 1) * 4][j + (y - 1) * 4] = map1[k + (x - 1) * 4][j + (y - 1) * 4];
                    }
                    num[x - 1][y - 1] = 0;
                }
            }
        }
    }
    return 0;
}

int dfs_lie(int dx, int dy) {
    if (flag2 == 1) {
        return 0;
    }
    if (dx == 4) {
        for (int i1 = 0; i1 < 2; i1++) {
            xuanzhuan_lie(i1 * 2, dx, dy);
            int b = (dy - 1) * 4;
            int w = panduan_lie(b);
            if (w == 1) {
                flag2 = 1;
                return 0;
            } else {
                //如果行任一有重复，则恢复原图
                for (int r = 0; r < 4; r++) {
                    for (int l = 0; l < 4; l++) {
                        map[r + (dx - 1) * 4][l + (dy - 1) * 4] = map1[r + (dx - 1) * 4][l + (dy - 1) * 4];
                    }
                }
                for (int p = 0; p < 4; p++) {
                    num2[dx - 1][p] = num[dx - 1][p];
                }
            }
        }
    } else if (dx != 4) {
        for (int i1 = 0; i1 < 2; i1++) {
            xuanzhuan_lie(i1 * 2, dx, dy);
            dfs_lie(dx + 1, dy);
            int b = (dy - 1) * 4;
            int w = panduan_lie(b);
            if (w == 1) {
                flag2 = 1;
                return 0;
            } else {
                //如果行任一有重复，则恢复原图
                for (int r = 0; r < 4; r++) {
                    for (int l = 0; l < 4; l++) {
                        map[r + (dx - 1) * 4][l + (dy - 1) * 4] = map1[r + (dx - 1) * 4][l + (dy - 1) * 4];
                    }
                }
                for (int p = 0; p < 4; p++) {
                    num2[dx - 1][p] = num[dx - 1][p];
                }
            }
        }
    }
    return 0;
}

int main() {
    long long int i, j, T, k, e, a;
    long long int count = 0, count1 = 0;
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    scanf("%lld\n", &T);
    for (k = 0; k < T; k++) {
        memset(map, 0, sizeof(map));
        memset(map1, 0, sizeof(map1));
        memset(num, 0, sizeof(num));
        memset(fuzhu, 0, sizeof(fuzhu));
        memset(jilu2, 0, sizeof(jilu2));
        memset(jilu1, 0, sizeof(jilu1));
        //输入数独map 并保存副本map1
        for (i = 0; i < 16; i++) {
            for (j = 0; j < 16; j++) {
                scanf("%c", &map[i][j]);
                map1[i][j] = map[i][j];
            }
            getchar();
        }
        for (i = 1; i < 5; i++) {//此时i代表大行的行数(从1开始)
            flag1 = 0;
            dfs(i, 1);
        }
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                num2[i][j] = num[i][j];
            }
        }
        //反转列
        for (i = 1; i < 5; i++) {//此时i代表大行的行数(从1开始)
            flag2 = 0;
            dfs_lie(1, i);
        }
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                count += num2[i][j];
                count1 += (num2[i][j] + 2) % 4;
            }
        }
        if (count < count1) {
            printf("%lld\n", count);
            for (i = 0; i < 4; i++) {
                for (j = 0; j < 4; j++) {
                    a = num2[i][j];
                    for (e = 0; e < a; e++) {
                        printf("%d %d\n", i + 1, j + 1);
                    }
                }
            }
        } else if (count >= count1) {
            printf("%lld\n", count1);
            for (i = 0; i < 4; i++) {
                for (j = 0; j < 4; j++) {
                    num2[i][j] = (num2[i][j] + 2) % 4;
                    a = num2[i][j];
                    for (e = 0; e < a; e++) {
                        printf("%d %d\n", i + 1, j + 1);
                    }
                }
            }
        }
        count = 0;
        count1 = 0;
        flag1 = 0;
        flag2 = 0;
        flag = 0, a = 0;
    }
    return 0;
}
/*E42F5A0C43E936AC
B9C54B628C1F0148
37A073EFA26D5E9D
D186D189507B7F2B
39FAED5628C10B74
D120C4B795A6EF38
7EC829A0FB346D51
B56438F17ED09C2A
26A5BC4E3D08719F
90EC1673BF42A58D
4D87AF25619C30BE
13BF90D8EA57264C
C7D1F29406835EAB
AF5287CD19BE4306
8B360E1AD425F7C9
E409653BC7FA18D2*/
/*681D981DB70536AC
0A73FE37D62A0148
5C9B26B4F1C85E9D
F24EC0A59E347F2B
39FAED5628C10B74
D120C4B795A6EF38
7EC829A0FB346D51
B56438F17ED09C2A
26A5BC4E3D08719F
90EC1673BF42A58D
4D87AF25619C30BE
13BF90D8EA57264C
C7D1F29406835EAB
AF5287CD19BE4306
8B360E1AD425F7C9
E409653BC7FA18D2*/
/*681D981DB70536AC
0A73FE37D62A0148
5C9B26B4F1C85E9D
F24EC0A59E347F2B
39FA1F830DE7A2C9
D1200A9243BF15D6
7EC87B4C6A5983FE
B56465DE1C8247B0
26A58D0975AEC462
90EC52FAC916EB03
4D87376124FBD85A
13BFE4CB80D3F917
C7D1F29406835EAB
AF5287CD19BE4306
8B360E1AD425F7C9
E409653BC7FA18D2*/
/*681D5A0C43E9B2F7
0A734B628C1FD9E5
5C9B73EFA26D8410
F24ED189507BCA63
39FAED5628C10B74
D120C4B795A6EF38
7EC829A0FB346D51
B56438F17ED09C2A
26A5BC4E3D08719F
90EC1673BF42A58D
4D87AF25619C30BE
13BF90D8EA57264C
C7D1F29406835EAB
AF5287CD19BE4306
8B360E1AD425F7C9
E409653BC7FA18D2*/
/*2D81AF7CF294904E
9C7F524D87CD63B8
6034EB910E1A25FA
BAE53860653B1D7C
C46275AE8D091492
EB03C91652FA3D06
D85A24FB3761B8EA
F91780D3E4CBF7C5
A2C97F921F83465B
15D6EB580A928CE7
83FED3AC7B4C021D
47B0046165DEAF93
36AC5A84981DE42F
014802C3FE37B9C5
5E9D761E26B437A0
7F2BBDF9C0A5D186*/
/*681D5A0C9FDBB2F7
0A734B62E167D9E5
5C9B73EF3C208410
F24ED18948A5CA63
39FAED5616400B74
D120C4B7CA3DEF38
7EC829A085BE6D51
B56438F129F79C2A
5C7FBC4E3D08719F
AE8B1673BF42A58D
60D3AF25619C30BE
294190D8EA57264C
C7D1B35606835EAB
AF52A1E019BE4306
8B36DC78D425F7C9
E409492FC7FA18D2*/
/*D3BE5A0C43E9B2F7
17944B628C1FD9E5
8AC273EFA26D8410
605FD189507BCA63
39FAED5628C10B74
D120C4B795A6EF38
7EC829A0FB346D51
B56438F17ED09C2A
26A5BC4E3D08719F
90EC1673BF42A58D
4D87AF25619C30BE
13BF90D8EA57264C
C7D1F29406835EAB
AF5287CD19BE4306
8B360E1AD425F7C9
E409653BC7FA18D2*/
/*D3BE5A0C43E9B2F7
17944B628C1FD9E5
8AC273EFA26D8410
605FD189507BCA63
39FAED5628C10B74
D120C4B795A6EF38
7EC829A0FB346D51
B56438F17ED09C2A
26A5BC4E3D08719F
90EC1673BF42A58D
4D87AF25619C30BE
13BF90D8EA57264C
C7D1F29406835EAB
AF5287CD19BE4306
8B360E1AD425F7C9
E409653BC7FA18D2*/
/*2D81AF7CF294904E
9C7F524D87CD63B8
6034EB910E1A25FA
BAE53860653B1D7C
C46275AE8D091492
EB03C91652FA3D06
D85A24FB3761B8EA
F91780D3E4CBF7C5
A2C97F921F83465B
15D6EB580A928CE7
83FED3AC7B4C021D
47B0046165DEAF93
36AC5A84981DE42F
014802C3FE37B9C5
5E9D761E26B437A0
7F2BBDF9C0A5D186*/


