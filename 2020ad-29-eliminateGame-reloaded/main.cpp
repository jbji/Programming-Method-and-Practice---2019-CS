#include <iostream>
#include <cstring>
#include <queue>

int pos_enum[4][2] = {{1,  0},
                      {0, 1},
                      {-1,0},
                      {0,-1}};
int pos_enum_1[2][2] = {{1,  0},
                        {0, 1}};
bool ** count_vis;

bool dfs_solve(int **map, int &to_eli, int n, int m, int t);

int countConnect(int i, int j, int **map, int m, int n);

void markConnect(int i, int j, int **map, int m, int n, int t);

bool isIsolated(int **map, int i, int j, int n, int m);

using namespace std;

void print(int ** in,int m,int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cout << in[i][j] << " ";
        }
        cout << endl;
    }
}
void print(bool ** in,int m,int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cout << in[i][j] << " ";
        }
        cout << endl;
    }
}

vector<pair<pair<int,int>,pair<int,int>>> ans;

int main() {
    ios::sync_with_stdio(false);
//    freopen("input.txt","r",stdin);
//    freopen("output.txt","w",stdout);
    int n,m;
    cin >> n >> m;
    int ** map = new int *[n];//0,1,2...
    int to_eli = 0;
    for(int i=0;i<n;i++){
        map[i] = new int[m];
        for(int j=0;j<m;j++) {
            cin >> map[i][j];
            if(map[i][j]) to_eli++;
        }
    }
    count_vis = new bool *[n];
    for(int k=0;k<n;k++){
        count_vis[k] = new bool[m];
    }
    dfs_solve(map, to_eli, n, m, 30);
    cout << ans.size() << endl;
    for(auto it:ans){
        cout << it.first.first+1 << " " << it.first.second+1 << " " << it.second.first+1 << " " << it.second.second+1 << endl;
    }
    return 0;
}



bool isValidPos(int i, int j, int n, int m) {
    return (i >= 0 && i < n && j >= 0 && j< m);
}

bool dfs_solve(int **map, int &to_eli, int n, int m, int t) {
//    cout << "to_eli:" << to_eli << endl <<"map:" <<endl;
//    print(map,m,n);
    for(int i = 0; i < n ; i++){
        for(int j = 0; j < m ; j++){
            if(map[i][j]>0 && isIsolated(map, i, j, n, m)){
                return false;
            }
            if(map[i][j]>0){
//                cout << "checking "<< endl;
                for (auto & k : pos_enum_1) {
                    //if the "enum_ed" case is valid
                    int di = k[0];
                    int dj = k[1];
                    if (isValidPos(i+di,j+dj, n, m) && map[i + di][j + dj] > 0 && map[i][j] != map[i + di][j + dj]) {
                        swap(map[i][j], map[i + di][j + dj]);
                        ans.emplace_back(make_pair(i, j), make_pair(i + di, j + dj));
                        int a = countConnect(i, j, map, m, n);
                        int b = countConnect(i + di, j + dj, map, m, n);
                        if (a >= 3) {
                            markConnect(i, j, map, m, n, t);
                            to_eli -= a;
                        }
                        if (b >= 3) {
                            markConnect(i + di, j + dj, map, m, n, t);
                            to_eli -= b;
                        }
//                        cout << "afterswitch:" << endl;
//                        print(map,m,n);
//                        cout << endl;
                        if (a >= 3 || b >= 3) {
                            if (dfs_solve(map, to_eli, n, m, t+10)) return true;
                        }
                        if (a >= 3) {
                            markConnect(i, j, map, m, n, t);
                            to_eli += a;
                        }
                        if (b >= 3) {
                            markConnect(i + di, j + dj, map, m, n, t);
                            to_eli += b;
                        }
                        ans.pop_back();
                        swap(map[i][j], map[i + di][j + dj]);
                    }
                }
            }
        }
    }
    return to_eli == 0;
}

bool isIsolated(int **map, int i, int j, int n, int m) {
    int isolateCount = 0;
    for(auto & k : pos_enum){
        int di = k[0];
        int dj = k[1];
        if(isValidPos(i+di,j+dj,n,m)){
            if(map[i+di][j+dj] <= 0){
                isolateCount++;
            }
        }else{
            isolateCount++;
        }
    }
    return isolateCount == 4;
}

int countConnect(int i, int j, int **map, int m, int n) {
    for(int k=0;k<n;k++){memset(count_vis[k] , 0, sizeof(bool)*m);}
    int source = map[i][j];
    int result = 0;
    queue<pair<int,int>> q;
    q.push(make_pair(i,j));
    while(!q.empty()){
        pair<int,int> tmp = q.front();
        i = tmp.first;
        j = tmp.second;
        result++;
        count_vis[i][j] = true;
        q.pop();
        for(auto & k : pos_enum){
            int di = k[0];
            int dj = k[1];
            if(isValidPos(i+di,j+dj,n,m) && !count_vis[i+di][j+dj] && map[i+di][j+dj] == source){
                q.push(make_pair(i+di,j+dj));
            }
        }
    }
    return result;
}
void markConnect(int i, int j, int **map, int m, int n, int t) {
    for(int k=0;k<n;k++){memset(count_vis[k] , 0, sizeof(bool)*m);}
    int source = map[i][j];
    queue<pair<int,int>> q;
    q.push(make_pair(i,j));
    while(!q.empty()){
        pair<int,int> tmp = q.front();
        i = tmp.first;
        j = tmp.second;
        map[i][j] = - map[i][j] - t;
        count_vis[i][j] = true;
        q.pop();
        for(auto & k : pos_enum){
            int di = k[0];
            int dj = k[1];
            if(isValidPos(i+di,j+dj,n,m) && !count_vis[i+di][j+dj] && map[i+di][j+dj] == source){
                q.push(make_pair(i+di,j+dj));
            }
        }
    }
}