#include <iostream>
#include <vector>
#include <cstring>

using namespace std;


long long int dfs_sigma_dist(vector<vector<int>> *tree, long long n);

long long int dfs_dist(vector<vector<int>> *tree, long long root, bool *isVisited, long long *vertexSize,  long long &depth, long long &odd_cnt);

int main() {
    ios::sync_with_stdio(false);
//    freopen("input.txt","r",stdin);
//    freopen("output.txt","w",stdout);
    long long n, a, b;
    cin >> n;
    vector<vector<int>> g(n);
    for (long long i = 0; i < n - 1; i++) {
        cin >> a >> b;
        g[a - 1].push_back(b - 1);
        g[b - 1].push_back(a - 1);
    }
    long long ans = dfs_sigma_dist(&g, n);
    cout << ans << endl;
    return 0;
}

long long int dfs_sigma_dist(vector<vector<int>> *tree, long long n) {
    //initialize
    bool *isVisited = new bool[n];
    auto *vertexSize = new long long[n];
    for(long long i=0;i<n;i++){
        vertexSize[i] = 1;
    }
    memset(isVisited, 0, sizeof(bool)*n);
    isVisited[0] = true;
    //dfs
    long long  depth = 0, odd_cnt = 0;
    dfs_dist(tree, 0, isVisited, vertexSize, depth, odd_cnt);
    //ans calc
    long long ans = 0;
    for (long long i = 0; i < n; i++) {
//        cout <<"vertex: "<<i <<"; size: " <<vertexSize[i]<< endl;
        ans += vertexSize[i] * (n - vertexSize[i]);
    }
    delete[] isVisited;
    delete[] vertexSize;
//    return ans;
    return (ans + odd_cnt * (n - odd_cnt)) / 2;
}

long long int dfs_dist(vector<vector<int>> *tree, long long root, bool *isVisited, long long *vertexSize, long long &depth, long long &odd_cnt) {
    long long ans = 1;
    if (depth % 2 == 1) odd_cnt++;
    for (auto child : (*tree)[root]) {
        if (!isVisited[child]) {
            isVisited[child] = true;
            depth++;
            ans += dfs_dist(tree, child, isVisited, vertexSize, depth, odd_cnt);
            vertexSize[root] += vertexSize[child];
            depth--;
        }
    }
    return ans;
}
