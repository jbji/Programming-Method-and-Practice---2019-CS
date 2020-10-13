#include <iostream>
#include <vector>
#include <set>
#include <queue>
using namespace std;
class Node{
public:
    int id;
    int weight;
    bool ordered;
    Node * father;
    multiset<Node *> children;
    explicit Node(int _id,int _weight = 0,int isOrdered = false,Node * _father = nullptr):id(_id),weight(_weight),ordered(isOrdered),father(_father){}
    bool operator()(const Node &lhs,const Node &rhs) const
    {
        return rhs.id < lhs.id;
    }
};

Node * locateFather(Node** Nodes){
    Node * p = Nodes[0];
    while(p->father){
        p = p->father;
    }
    return p;
}

vector<int> ans;
void dfs_generate(Node * root){
    if(root->children.empty()){
        ans.push_back(root->weight);
    }else{
        if(root->ordered){
            multiset<int> sub_ans;
            queue<Node *> q;
            q.push(root);
            while(!q.empty()){
                Node * tmp = q.front();
                sub_ans.insert(tmp->weight);
                q.pop();
                for(auto child: tmp->children){
                    q.push(child);
                }
            }
            for(auto it:sub_ans){
//                cout <<"sub:" << it << "; ";
                ans.push_back(it);
            }
        }else{
            ans.push_back(root->weight);
            for(auto child:root->children){
//                cout <<"subchild:" << child->weight << "; ";
                dfs_generate(child);
            }
        }
    }
}
int main() {
    ios::sync_with_stdio(false);
//    freopen("input.txt","r",stdin);
//    freopen("output.txt","w",stdout);
    int n,tmp;
    cin >> n;
    Node **Nodes = new Node*[n];
    for(int i=0;i<n;i++){
        cin >> tmp;
        Nodes[i] = new Node(i+1,tmp);
    }
    for(int i=0;i<n;i++){
        cin >> tmp;
        Nodes[i]->ordered = tmp;
    }
    int from,to;
    for(int i=0;i<n-1;i++){
        cin >> from >> to;
        Nodes[from-1]->children.insert(Nodes[to-1]);
        Nodes[to-1]->father = Nodes[from-1];
    }
    Node * root = locateFather(Nodes);
    dfs_generate(root);
    //众所周知，大家都会输出
    for(auto it=ans.begin();it<ans.end();it++){
        if(it==ans.begin()){
            cout <<"["<< *it <<",";
            continue;
        }
        if(it==ans.end()-1){
            cout << *it <<"]";
            continue;
        }
        cout << *it <<",";
    }
    cout << endl;
    return 0;
}