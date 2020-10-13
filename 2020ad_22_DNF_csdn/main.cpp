#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e2 + 5;
const int INF = 0x3f3f3f3f;
const int dx[] = {1, 0, -1, 0};
const int dy[] = {0, 1, 0, -1};

struct node{
    int x, y, step;
    node(int _x = 0, int _y = 0, int _step = 0){
        x = _x;
        y = _y;
        step = _step;
    }
};

queue<node> q;
char mp[maxn][maxn];
bool vis[maxn][maxn][52];

int main() {
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int n, m, k, sx, sy, T, i, j;
    scanf("%d", &T);
    while(T--){
        scanf("%d%d%d", &n, &m, &k);
        getchar();
        for(i=1;i<=n;i++){
            for(j=1;j<=m;j++){
                mp[i][j] = getchar();
                if(mp[i][j]=='S')
                    sx = i, sy = j;
            }
            getchar();
        }

        int ans = INF;
        memset(vis, 0, sizeof(vis));
        while(!q.empty()) q.pop();
        q.push(node(sx, sy, 0));
        vis[sx][sy][0] = 1;
        while(!q.empty()){
            node tmp = q.front(); q.pop();
            if(mp[tmp.x][tmp.y]=='E'){
                ans = tmp.step;
                break;
            }
            for(i=0;i<4;i++){
                int x = tmp.x + dx[i], y = tmp.y + dy[i], stp = tmp.step+1;
                if(x<1 || x>n || y<1 || y>m || mp[x][y]=='#' || vis[x][y][stp%k]) continue;
                if(mp[x][y]=='*' && (stp%k)) continue;

                q.push(node(x, y, stp));
                vis[x][y][stp%k] = 1;
            }
        }

        if(ans==INF) printf("-1\n");
        else printf("%d\n", ans);
    }
    return 0;
}