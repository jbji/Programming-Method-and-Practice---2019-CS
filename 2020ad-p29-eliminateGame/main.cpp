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

bool dfs_solve(int i, int j, int **map, int **pos_swap, int &to_eli, bool **vis, int &vis_remain, int n, int m);

int countConnect(int i, int j, int **map, int m, int n);

void markConnect(int i, int j, int **map, int m, int n, bool **vis, int &vis_remain);

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

int colorCounter[40]={};

int main() {
    ios::sync_with_stdio(false);
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int n,m;
    cin >> n >> m;
    int ** map = new int *[n];//0,1,2...
    int ** pos_swap = new int *[n];
    bool ** vis = new bool *[n];
    //num
    //<-1>eliminated,-2,-3... this records what exactly have we eliminated
    int to_eli = 0; //num of blocks remaining to be eliminated
    for(int i=0;i<n;i++){
        map[i] = new int[m];
        for(int j=0;j<m;j++) {
            cin >> map[i][j];
            colorCounter[map[i][j]]++;
            if(map[i][j]) to_eli++;
        }
        vis[i] = new bool[m];
        pos_swap[i] = new int[m];
        memset(vis[i],0, sizeof(bool)*m);
        memset(pos_swap[i], 0, sizeof(int) * m);
    }
//    print(map,m,n);
    int vis_remain = to_eli;
    count_vis = new bool *[n];
    for(int k=0;k<n;k++){
        count_vis[k] = new bool[m];
    }
    dfs_solve(0, 0, map, pos_swap, to_eli, vis, vis_remain, n, m);
//    cout << "outside:" <<  endl;
//    print(map,m,n);
//    print(vis,m,n);
//    print(pos_swap,m,n);
    cout << ans.size() << endl;
    for(auto it:ans){
        cout << it.first.first+1 << " " << it.first.second+1 << " " << it.second.first+1 << " " << it.second.second+1 << endl;
    }
    return 0;
}



bool isValidPos(int i, int j, int deltai, int deltaj, int n, int m) {
    return (i + deltai >= 0 && i + deltai < n && j + deltaj >= 0 && j + deltaj < m);
}

void markSingle(int i,int j,bool isVisited, bool**vis , int & vis_remain){
    if(vis[i][j] != isVisited){
        vis[i][j] = isVisited;
        if(isVisited){
            vis_remain --;
        }else{
            vis_remain ++;
        }
    }
}
bool dfs_solve(int i, int j, int **map, int **pos_swap, int &to_eli, bool **vis, int &vis_remain, int n, int m) {
//    cout <<endl <<  "begindp:" <<i+1 << " " << j+1 <<  endl;
//    cout << "vis_remain: " << vis_remain <<" ;to_eli:" << to_eli << endl <<"map:" <<endl;
//    print(map,m,n);
//    cout <<"vis:"<< endl;
//    print(vis,m,n);
//    cout <<"pos_swap"<< endl;
//    print(pos_swap,m,n);
    if(map[i][j] == 0){
        for(int ii = 0;ii<n;ii++){
            for(int jj = 0;jj<m;jj++){
                if(isValidPos(ii, jj, 0, 0, n, m) && !vis[ii][jj] && map[ii][jj]>0){
                    return dfs_solve(ii, jj, map, pos_swap, to_eli, vis, vis_remain, n, m);
                }
            }
        }
    }
    if(vis_remain==0){
        return (to_eli == 0);
    }
    int fails = 0;
    for (auto & k : pos_enum_1) {
        //if the "enum_ed" case is valid
        int di = k[0];
        int dj = k[1];
        if (isValidPos(i, j, di, dj, n, m) && !vis[i + di][j + dj] && map[i + di][j + dj] > 0) {
            if (map[i][j] != map[i + di][j + dj]) {
                swap(map[i][j], map[i + di][j + dj]);
                ans.emplace_back(make_pair(i, j), make_pair(i + di, j + dj));
                int c_num = countConnect(i, j, map, m, n);
                int n_num = countConnect(i + di, j + dj, map, m, n);
                int tmpc = colorCounter[map[i][j]] - c_num;
                int tmpn = colorCounter[map[i + di][j + dj]] - n_num;
//                if ( (c_num >= 3 || n_num >=3) && (tmpc == 1 || tmpc == 2) && (tmpn == 1 || tmpn == 2) ){
//                    ans.pop_back();
//                    swap(map[i][j], map[i + di][j + dj]);
//                    fails++;
//                    continue;
//                }
//                colorCounter[map[i][j]] -= c_num;
//                colorCounter[map[i + di][j + dj]] -= n_num;
                if (c_num >= 3) {
                    markConnect(i, j, map, m, n, vis, vis_remain);
                    to_eli -= c_num;
                }
                if (n_num >= 3) {
                    markConnect(i + di, j + dj, map, m, n, vis, vis_remain);
                    to_eli -= n_num;
                }
                if (c_num >= 3 || n_num >= 3) {
                    markSingle(i, j, true, vis, vis_remain);
                    if (dfs_solve(i + di, j + dj, map, pos_swap, to_eli, vis, vis_remain, n, m)) {
                        return true;
                    }
                    markSingle(i, j, false, vis, vis_remain);
                }
                if (c_num >= 3) {
                    markConnect(i, j, map, m, n, vis, vis_remain);
                    to_eli += c_num;
                }
                if (n_num >= 3) {
                    markConnect(i + di, j + dj, map, m, n, vis, vis_remain);
                    to_eli += n_num;
                }
//                colorCounter[map[i][j]] += c_num;
//                colorCounter[map[i + di][j + dj]] += n_num;
                ans.pop_back();
                swap(map[i][j], map[i + di][j + dj]);
            }
            markSingle(i,j,true,vis,vis_remain);
            if(dfs_solve(i + di, j + dj, map, pos_swap, to_eli, vis, vis_remain, n, m)) return true;
            markSingle(i,j,false,vis,vis_remain);
        }else{
            fails++;
        }
    }
//    cout << "fails:" << fails << endl;
    if(fails == 2 && to_eli>0 && vis_remain >0){
        for(int ii = 0;ii<n;ii++){
            for(int jj = 0;jj<m;jj++){
                if(isValidPos(ii, jj, 0, 0, n, m) && !vis[ii][jj] && map[ii][jj]>0){
                    markSingle(i,j,true,vis,vis_remain);
                    if(dfs_solve(ii, jj, map, pos_swap, to_eli, vis, vis_remain, n, m)) return true;
                    markSingle(i,j,false,vis,vis_remain);
                    return false;
                }
            }
        }
    }
    return false;
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
        count_vis[i][j] = true;
//        cout << "Counting: i:"<< i << " ;j:" << j << endl;
        result++;
        q.pop();
        for(auto & k : pos_enum){
            int di = k[0];
            int dj = k[1];
            if(isValidPos(i,j,di,dj,n,m) && !count_vis[i+di][j+dj] && map[i+di][j+dj] == source){
                q.push(make_pair(i+di,j+dj));
            }
        }
    }
    return result;
}
void markConnect(int i, int j, int **map, int m, int n, bool **vis, int &vis_remain) {
    for(int k=0;k<n;k++){memset(count_vis[k] , 0, sizeof(bool)*m);}
    int source = map[i][j];
    queue<pair<int,int>> q;
    q.push(make_pair(i,j));
    while(!q.empty()){
        pair<int,int> tmp = q.front();
        i = tmp.first;
        j = tmp.second;
        markSingle(i,j,source>0,vis,vis_remain);
        map[i][j] = -map[i][j];
        q.pop();
        count_vis[i][j] = true;
//        cout << "MarkingConnect: i:"<< i << " ;j:" << j << endl;
        for(auto & k : pos_enum){
            int di = k[0];
            int dj = k[1];
            if(isValidPos(i,j,di,dj,n,m) && !count_vis[i+di][j+dj] && map[i+di][j+dj] == source){
                q.push(make_pair(i+di,j+dj));
            }
        }
    }
}


