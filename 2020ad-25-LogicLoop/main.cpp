#include <iostream>
#include <vector>
#include <set>
#include <stack>

using namespace std;

class Vertex{

public:
    int key; //该节点的键值
    bool activated;
    set<Vertex *> in; //到该节点的入
    set<Vertex *> out; //从该节点的出

    explicit Vertex(int _key =0):key(_key),activated(false){}
    explicit Vertex(Vertex * v):key(v->key),activated(v->activated){}
    ~Vertex(){
        in.clear();
        out.clear();
    }
    bool operator < (const Vertex & v){
        return this->key < v.key;
    }
    int inDegree(){
       return in.size();
    }

    void activate(){
        this->activated = true;
    }
    static void connect(Vertex * a,Vertex * b){
        //from a to b
        a->out.insert(b);
        b->in.insert(a);
    }
    static Vertex ** makeCopy(Vertex ** g, int n);
    static bool hasRing(Vertex ** g,int n);
};

Vertex ** Vertex::makeCopy(Vertex ** g, int n){
    auto ** graph = new Vertex*[n];
    for(int i=0;i<n;i++){
        graph[i] = new Vertex(g[i]);
    }
    for(int i=0;i<n;i++){
        if(g[i]->activated){
            for(auto it : g[i]->out){
                Vertex::connect(graph[i],graph[it->key]);
            }
        }
    }
    return graph;
}
bool Vertex::hasRing(Vertex ** g,int n){
    stack<Vertex *> s;
    int activateCount = 0;
    for(int i=0;i<n;i++){
        if(g[i]->activated){
            activateCount++;
            if(!g[i]->inDegree()){ //入度为零
                activateCount --;
                s.push(g[i]);
            }
        }
    }
    while(!s.empty()){
        Vertex * v= s.top();
        s.pop();
        for( auto it : v->out){
            it->in.erase(v);
            if(!it->inDegree()){
                activateCount--;
                s.push(it);
            }
        }
    }
    bool result = false;
    for(int i=0;i<n;i++){
        if(activateCount != 0){ //图中还有点 则一定有环
            result = true;
            break;
        }
    }
    //gc
    for(int i=0;i<n;i++){
        delete g[i];
    }
    delete[] g;
    return result;
}
int main() {
    std::ios::sync_with_stdio(false);
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int n,m;
    cin >> n >> m; //n个顶点，m条有向边
    auto ** graph = new Vertex*[n];
    for(int i=0;i<n;i++){
        graph[i] = new Vertex(i);
    }
    int s,e,t=-1,i=0;
    for(;i<m;i++){
        cin >> s >> e;
        if(t==-1){
            Vertex::connect(graph[s-1],graph[e-1]);
            graph[s-1]->activate();
            graph[e-1]->activate();
            auto tmpGraph = Vertex::makeCopy(graph,n);
            //这样检测数据量3000约需5s，即使内存不RE也一定过不了
            if(Vertex::hasRing(tmpGraph,n)){
                t=i+1;
            }
        }
    }

    cout << t <<endl;
    return 0;
}