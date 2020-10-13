#include <iostream>
#include <vector>

using namespace std;

class Edge{
public:
    int vertex; //targrtVertex
    int join_time;
    explicit Edge(int v=0,int t=0):vertex(v),join_time(t){}
};

bool dfs(vector<vector<Edge>> *g, int init_vertex, int * color,int maxTime);
bool isLoop(vector<vector<Edge>> *g, int n,int maxTime);

int locateLoop(vector<vector<Edge>> * graph_t, int vertex_num, int edge_num);


int main() {
    std::ios::sync_with_stdio(false);
//    freopen("input.txt","r",stdin);
//    freopen("output.txt","w",stdout);
    int n,m;
    cin >> n >> m; //n个顶点，m条有向边
    int tmpS,tmpE;
    vector<vector<Edge>> g(n); //the graph
    for(int i=0;i<m;i++){
        cin >> tmpS >> tmpE;
        g[tmpS-1].push_back(Edge(tmpE-1,i));
    }
    int t = locateLoop(&g,n,m);
    cout << t << endl;
    return 0;
}

int locateLoop(vector<vector<Edge>> *graph_t, int vertex_num, int edge_num) {
    int ans = -1;
    int left = 0;
    int right = edge_num*2;
    int mid;
    while(left < right - 1){
        mid = (left + right)/2;
//        cout << "beginLocate" << endl;
        bool flag =isLoop(graph_t, vertex_num, mid);
//        cout << "Left: " << left<< "; mid: " << mid << "; isLoop? "<< flag << endl;
        if(!flag && mid == edge_num) return -1;
        if(flag){
            right = mid;
        }else{
            left = mid;
        }
        if(left >= right - 1){
            ans = right;
        }
//        cout << "Left: " << left<< "; Right: " << right << ";" << endl;
    }
    return ans;
}

bool dfs(vector<vector<Edge>> *g, int init_vertex, int * color,int maxTime){
    color[init_vertex] = 0; //gray
    for(int target_vertex=0; target_vertex < (*g)[init_vertex].size() ; target_vertex++){ //get all targets
        if((*g)[init_vertex][target_vertex].join_time>=maxTime) continue;
        if(color[(*g)[init_vertex][target_vertex].vertex] == 0) return true;
        if(color[(*g)[init_vertex][target_vertex].vertex] == -1){
            if(dfs(g, (*g)[init_vertex][target_vertex].vertex , color, maxTime)){
                return true;
            }
        }
    }
    color[init_vertex] = 1; // black
    return false;
}
bool isLoop(vector<vector<Edge>> *g, int n, int maxTime){
    int * color = new int[n];
    for(int i=0;i<n;i++) color[i] = -1; //white
    for(int i=0;i<n;i++){
        if(color[i] == -1){
            if(dfs(g,i,color,maxTime)){
                delete[] color;
                return true;
            }
        }
    }
    delete[] color;
    return false;
}