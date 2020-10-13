#include <iostream>
#include <map>
#include <unordered_map>
#include <queue>
#include <vector>

using namespace std;

class SetPhrase;
typedef int NodeType;
class Node{
public:
    NodeType data;
    Node * next;
    bool isVisited;
    Node(){
        this -> data = 0;
        this -> next = nullptr;
        isVisited = false;
    }
    Node(NodeType _data){
        this -> data = _data;
        this -> next = nullptr;
        isVisited = false;
    }
    void setData(NodeType t){
        this->data = t;
    }
};

class SetPhrase{ //成语的邻接链表
public:
    int keyNum;
    Node * nexts;
    explicit SetPhrase(int k=0):keyNum(k){
        this-> nexts = nullptr;
    }
    void addNext(int key){
        if(this->nexts){
            Node* p = nexts;
            while(p->next) p = p->next;
            p->next = new Node(key);
        }else{
            this -> nexts = new Node(key);
        }
    }
    bool isEqual(int newNum){
        return this->keyNum == newNum;
    }
};

void getInput(int &head,int& tail){
    cin >> head;
    for(int i=0;i<3;i++){
        cin >> tail;
    }
}
vector<int> getAllChildren(unordered_map<int,SetPhrase * > *lib,int key){
    vector<int> v;
    if(lib->count(key)){
        Node * tmp = (*lib)[key] -> nexts;
        for(Node * p = tmp; p ;p=p->next){
            if(!p->isVisited){
                p->isVisited = true;
                v.push_back(p->data);
            }
        }
    }
    return v;
};
int bfs(unordered_map<int,SetPhrase * > *lib, int start,int end){
    int key,times=2;
    queue<int> q; //存储搜索起点
    queue<int> depth;
    q.push(start);
    depth.push(times);
    while(!q.empty()){
        key = q.front();
        times = depth.front();
        q.pop();
        depth.pop();
        if(key == end){
            return times;
        }
        vector<int> v = getAllChildren(lib,key);
        times++;
        for(auto it = v.begin() ; it!=v.end() ; it++){
            q.push(*it);
            depth.push(times);
        }
    }
    return -1;
}


int main() {
    std::ios::sync_with_stdio(false);
    auto *lib = new unordered_map<int,SetPhrase * >;
    int m=0,head=0,tail=0;
    for(cin >> m; m>0;m--){
        getInput(head,tail);
//        if(lib->count(tail)==0)  (*lib)[tail] = new SetPhrase(tail);
        if(lib->count(head)==0)  (*lib)[head] = new SetPhrase(head);
        (*lib)[head] -> addNext(tail);
    }
    getInput(head,tail); //tail as the START
    int _head,_tail;
    getInput(_head,_tail);
    if(head == _head && tail == _tail){
        cout << 1 << endl;
        return 0;
    }
    int times = bfs(lib,tail,_head);
    cout << times << endl;
    return 0;
}