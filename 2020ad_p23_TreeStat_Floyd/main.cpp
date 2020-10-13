#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>

using namespace std;

int sigma_dist_floyd(vector<vector<int>> *graph);
int sigma_dist_floyd_array(vector<vector<int>> *g);

int gdist[200000][200000];
bool gnewEdge[200000][200000];

int main() {
    ios::sync_with_stdio(false);
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int n , a, b;
    cin >> n;
    vector<vector<int>> g(n);
    for(int i=0;i<n-1;i++){
        cin >> a >> b;
        g[a-1].push_back(b-1);
        g[b-1].push_back(a-1);
    }
    int ans = sigma_dist_floyd_array(&g);
    cout << ans << endl;
    return 0;
}

int sigma_dist_floyd(vector<vector<int>> *g) {
    int n = g->size();
    vector< unordered_map<int,int> > g_dist(n);
    vector< unordered_map<int,bool> > g_newEdge(n);
    //convert;
    for(int i=0;i<n;i++){
        for(auto it: (*g)[i]){
            g_dist[i][it] = 1;
        }
        g_dist[i][i]=0;
    }
    //add new edge
    for(int k=0;k<n;k++){
        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                if(g_dist[i].count(j)==0 && g_dist[i].count(k)!=0 && g_dist[k].count(j)!=0){
                    g_newEdge[i][j] = true;
                }
            }
        }
    }
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(g_newEdge[i].count(j)){
                g_dist[i][j]=1;
            }
        }
    }
    //floyd;
    for(int k=0;k<n;k++){
        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                if(g_dist[i].count(j)!=0 && g_dist[i].count(k)!=0 && g_dist[k].count(j)!=0){
                    if(g_dist[i][j] > g_dist[i][k] + g_dist[k][j]){
                        g_dist[i][j] = g_dist[i][k] + g_dist[k][j];
                    }
                }
            }
        }
    }
    long long ans = 0;
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(g_dist[i].count(j)!= 0){
                ans += g_dist[i][j];
            }
        }
    }
    return ans;
}
int sigma_dist_floyd_array(vector<vector<int>> *g) {
    int n = g->size();
    int sup = INT32_MAX/3;

    //convert;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            gdist[i][j] = sup;
            gnewEdge[i][j] = false;
        }
        gdist[i][i] = 0;
    }
    for(int i=0;i<n;i++){
        for(auto it: (*g)[i]){
            gdist[i][it] = 1;
        }
    }
    //add new edge
    for(int k=0;k<n;k++){
        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                if(gdist[i][j] == sup && gdist[i][k] + gdist[k][j] < sup){
                    gnewEdge[i][j] = true;
                }
            }
        }
    }
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(gnewEdge[i][j]){
                gdist[i][j]=1;
            }
        }
    }
    //floyd;
    for(int k=0;k<n;k++){
        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                if(gdist[i][j] > gdist[i][k] + gdist[k][j]){
                    gdist[i][j] = gdist[i][k] + gdist[k][j];
                }
            }
        }
    }
    long long ans = 0;
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(gdist[i][j] < sup/2){
                ans += gdist[i][j];
            }
        }
    }
    return ans;
}