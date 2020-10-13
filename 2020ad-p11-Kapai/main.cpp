#include <iostream>
#include <set>
#include <deque>
#include <cstring>
using namespace std;

bool check(set<int> hand, deque<int> q);
void continualInsert(set<int> & hand, deque<int> & q ,int & cnt);
void valInsert(set<int> & hand, deque<int> & q ,int & cnt,int val);
int main() {
    set<int> hand;//默认做升序排序
    deque<int> q;
    int cnt=0;
    int n; //所有牌的数量
    cin >> n;
    //用于快读
    char tmpChar=getchar();
    int tmpNum=0;
    //快读读入手中的牌
    while(!((tmpChar >= '0' && tmpChar <= '9') || tmpChar == ' ')) tmpChar=getchar();
    while((tmpChar >= '0' && tmpChar <= '9') || tmpChar == ' '){
        if(tmpChar != ' '){
            tmpNum = 0;
            while(tmpChar >= '0' && tmpChar <= '9'){
                tmpNum = tmpNum*10 + tmpChar-'0';
                tmpChar=getchar();
            }
            if(tmpNum) hand.insert(tmpNum);
            continue;
        }
        tmpChar=getchar();
    }
    //快读读入牌堆中的牌，进入队列
    while(!((tmpChar >= '0' && tmpChar <= '9') || tmpChar == ' ')) tmpChar=getchar();
    while((tmpChar >= '0' && tmpChar <= '9') || tmpChar == ' '){
        if(tmpChar != ' '){
            tmpNum = 0;
            while(tmpChar >= '0' && tmpChar <= '9'){
                tmpNum = tmpNum*10 + tmpChar-'0';
                tmpChar=getchar();
            }
            q.push_back(tmpNum);
            continue;
        }
        tmpChar=getchar();
    }
    if(hand.empty()){ // you need to check if it's ordered
        int j=1;
        for(deque<int>::iterator it = q.begin();it<q.end();it++){
            if(*it != j){
                valInsert(hand,q,cnt,0);
                break;
            }
            j++;
        }
    }
    while(!hand.empty()){
        if(q.back() == 0){
            if(*hand.begin() != 1){
                valInsert(hand,q,cnt,0);
            }else{//手中有1
                //计算次数即可。
                int calc[n+10],i=1;
                memset(calc,0,sizeof(calc));
                for(deque<int>::iterator it = q.begin();it < q.end();it++){
                    calc[*it] = i;
                    i++;
                }
                int max=-1;
                for(int j = 1 ; j<=n;j++){
                    max = max > calc[j] - (j - 1)? max : calc[j] - (j - 1);
                }
                cnt+= n+max;
                break;
            }
        }else{
            if(hand.count(q.back()+1)){
                if(check(hand,q)){
                    continualInsert(hand,q,cnt);
                }else{
                    valInsert(hand,q,cnt,0);
                }
            }else{
                valInsert(hand,q,cnt,0);
            }
        }
    }
    std::cout << cnt << std::endl;
    return 0;
}
bool check(set<int> hand, deque<int> q){
    int cnt=0;
    while(!hand.empty()){
        if(hand.count(q.back()+1)){
            valInsert(hand,q,cnt,q.back()+1);
            continue;
        }
        if(!hand.empty()){
            return false;
        }
    }
    return (q.front()==1);
}

void continualInsert(set<int> & hand, deque<int> &q, int & cnt){
    while(!hand.empty()){
        if(hand.count(q.back()+1)){
            valInsert(hand,q,cnt,q.back()+1);
        }
    }
}

void valInsert(set<int> & hand, deque<int> & q ,int & cnt,int val){
    q.push_back(val);
    if(val != 0) hand.erase(val);
    if(q.front()!=0) hand.insert(q.front());
    q.pop_front();
    cnt++;
}