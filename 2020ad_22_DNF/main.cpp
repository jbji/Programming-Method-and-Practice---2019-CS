#include <iostream>
#include <queue>
#include <vector>
#include <cstring>

#define START 'S'
#define END 'E'
#define MOB '*'
#define WALL '#'
#define ROAD '.'

using namespace std;
class Pos{
public:
    int x; //行
    int y; //列
    int t; //已用时间
    explicit Pos(int _x=0,int _y=0,int _times=0):x(_x),y(_y),t(_times){}
    bool operator == (Pos pos){
        return pos.x == this->x && pos.y == this->y;
    }
    Pos operator + (Pos pos){
        return Pos(x+pos.x ,y+pos.y,t+pos.t);
    }
};
class Map{
public:
    char ** map;
    bool *** isWalked;
    int n_row;
    int m_col;
    int k_interval;
    explicit Map(int n = 1,int m = 1,int k = 1):n_row(n),m_col(m),k_interval(k){
        std::ios::sync_with_stdio(false);
        //The map Initialize
        map = new char*[n_row];
        for(int i=0;i<n;i++){
            map[i] = new char[m_col+1];
            cin >> map[i];
        }
        //Set the Utility for Storage.
        isWalked = new bool**[n_row];
        for(int i=0;i<n;i++){
            isWalked[i] = new bool*[m_col+1];
            for(int j=0;j<m;j++){
                isWalked[i][j] = new bool[k_interval+1];
                memset(isWalked[i][j],0, sizeof(bool)*(k_interval+1));
            }
        }
    }
    ~Map(){
        for(int i=0;i<n_row;i++){
            delete[] map[i];
            for(int j=0;j<m_col;j++){
                delete[] isWalked[i][j];
            }
        }
        delete[] map;
        for(int i=0;i<n_row;i++){
            delete[] isWalked[i];
        }
        delete[] isWalked;
    }
    Pos locateStart(){
        for(int i=0;i<n_row;i++){
            for(int j=0;j<m_col;j++){
                if(map[i][j] == START){
                    return Pos(i,j,0);
                }
            }
        }
        return Pos(-1,-1);
    }
    Pos locateEnd(){
        for(int i=0;i<n_row;i++){
            for(int j=0;j<m_col;j++){
                if(map[i][j] == END){
                    return Pos(i,j);
                }
            }
        }
        return Pos(-1,-1);
    }

    void mark(Pos p){
        isWalked[p.x][p.y][p.t%k_interval] = true;
    }
    bool isLocationValid(Pos p){
        if (p.x>=0 && p.x<n_row && p.y>=0 && p.y<m_col && !isWalked[p.x][p.y][p.t%k_interval]){
            return map[p.x][p.y] == ROAD || map[p.x][p.y] == START || map[p.x][p.y] == END
                   || (map[p.x][p.y] == MOB && p.t%k_interval == 0);
        }else{
            return false;
        }
    }
};

Pos itr[4]={Pos(0,1,1),Pos(0,-1,1),Pos(-1,0,1),Pos(1,0,1)};

vector<Pos> getAllChildren(Map * map, Pos start){
    vector<Pos> v;
    for(int i=0;i<4;i++){
        Pos tmp = start + itr[i];
        if(map->isLocationValid(tmp)){
            v.push_back(tmp);
            map -> mark(tmp);
        }
    }
    return v;
}

int bfs(Map * map){
    if(map->m_col == 1 && map->n_row == 1){
        return 0;
    }
    queue<Pos> q;
    q.push(map->locateStart());
    Pos s,e = map->locateEnd();
    while(!q.empty()){
        s = q.front();
        q.pop();
        if(s == e){
            return s.t;
        }
        vector<Pos> v = getAllChildren(map,s);
        for(auto it = v.begin() ; it != v.end() ; it++){
            q.push(*it);
        }
    }
    return -1;
}

int main() {
    std::ios::sync_with_stdio(false);
//    freopen("input.txt","r",stdin);
//    freopen("output.txt","w",stdout);
    int T, n, m, k, ans;
    for(cin >> T; T>0;T--){
        cin >> n >> m >> k;
        Map * map = new Map(n,m,k);
        ans = bfs(map);
        cout << ans << endl;
        delete map;
    }
    return 0;
}