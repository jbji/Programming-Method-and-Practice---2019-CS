#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

int sigma_dist(vector<vector<int>> *g);
int bfs_dist(vector<vector<int>> *g, int i, int j);

void all_connect(vector<vector<int>> *g);
void bfs_connect(vector<vector<int>> *g, int i, int j,queue<pair<int,int>> *);

long long int dfs_sigma_dist(vector<vector<int>> *tree, int n);

long long int dfs_dist(vector<vector<int>> *tree, int root, bool *isVisited, int *depth, int *odd_cnt);

int main() {
    ios::sync_with_stdio(false);
    freopen("input-1.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int n , a, b;
    cin >> n;
    vector<vector<int>> g(n);
    for(int i=0;i<n-1;i++){
        cin >> a >> b;
        g[a-1].push_back(b-1);
        g[b-1].push_back(a-1);
    }
//    all_connect(&g);
//    int ans = sigma_dist(&g);
    long long ans = dfs_sigma_dist(&g, n);
    cout << ans << endl;
    return 0;
}

long long int dfs_sigma_dist(vector<vector<int>> *tree, int n) {
    long long ans = 0, tmp;
    int depth = 0,odd_cnt = 0;
    bool * cutVisit = new bool[n]; //防止双向边访问两次
    bool * isVisited = new bool[n];
    memset(cutVisit, 0, sizeof(cutVisit));
    for (int i = 0 ; i< n ;i++){
        cutVisit[i] = true;
        for(auto child_as_root : (*tree)[i]){
            if(!cutVisit[child_as_root]){
                memset(isVisited,0, sizeof(isVisited));
                isVisited[i] = true;
                isVisited[child_as_root] = true;
                cutVisit[child_as_root] = true;
                tmp = dfs_dist(tree, child_as_root, isVisited, &depth, &odd_cnt);
                ans += (n-tmp) * tmp;
            }
        }
    }
    memset(isVisited,0, sizeof(isVisited));
    isVisited[0] = true;
    odd_cnt = 0; depth = 0;
    dfs_dist(tree, 0, isVisited, &depth, &odd_cnt);
    delete[] isVisited;
    return (ans+ odd_cnt*(n-odd_cnt))/2;
}

long long int dfs_dist(vector<vector<int>> *tree, int root, bool *isVisited, int *depth, int *odd_cnt) {
    long long ans = 1;
    if(*depth % 2 == 1) (*odd_cnt)++;
    for (auto it : (*tree)[root]) {
        if (!isVisited[it]) {
            isVisited[it] = true;
            (*depth)++;
            ans += dfs_dist(tree, it, isVisited, depth, odd_cnt);
            (*depth)--;
        }
    }
    return ans;
}


int sigma_dist(vector<vector<int>> *g) {
    int dist = 0;
    int n = g->size();
    for(int i=0;i< n;i++){
        for(int j=i+1;j< n;j++){
            dist += bfs_dist(g,i,j);
        }
    }
    return dist;
}

int bfs_dist(vector<vector<int>> *g, int i, int j) {
    queue<pair<int,int>> q; //two arguments stands for vertex & walkTime;
    q.push(make_pair(i,0));
    while(!q.empty()){
        pair<int,int> tmp = q.front();
        q.pop();
        if(tmp.first == j){
            return tmp.second;
        }
        for (auto target : (*g)[tmp.first]){
            q.push(make_pair(target,tmp.second+1));
        }
    }
    return -1;
}
void all_connect(vector<vector<int>> *g){
    queue<pair<int,int>> vertex_q; //two arguments stands for vertex & vertex;
    int n = g->size();
    for(int i=0;i< n;i++){
        for(int j=i+1;j< n;j++){
            bfs_connect(g,i,j,&vertex_q);
        }
    }
    while(!vertex_q.empty()){
        pair<int,int> tmp = vertex_q.front();
        vertex_q.pop();
        (*g)[tmp.first].push_back(tmp.second);
        (*g)[tmp.second].push_back(tmp.first);
    }
}
void bfs_connect(vector<vector<int>> *g, int i, int j,queue<pair<int,int>> * vertex_queue) {
    bool vertex_visit[g->size()];
    memset(vertex_visit,0, sizeof(vertex_visit));
    queue<pair<int,int>> q; //two arguments stands for vertex & walkTime;
    q.push(make_pair(i,0));
    vertex_visit[i] = true;
    while(!q.empty()){
        pair<int,int> tmp = q.front();
        q.pop();
        if(tmp.first == j){
            if(tmp.second == 2){
                vertex_queue->push(make_pair(i,j));
            }
            break;
        }
        for (auto target : (*g)[tmp.first]){
            if(!vertex_visit[target]){
                vertex_visit[target] = true;
                q.push(make_pair(target, tmp.second + 1));
            }
        }
    }
}