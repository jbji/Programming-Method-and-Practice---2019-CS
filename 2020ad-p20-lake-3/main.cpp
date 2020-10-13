#include <iostream>
#include <stack>

bool readOddNum();

using namespace std;

int readNum();

int main() {
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int n;
    stack<int> s;
    while(cin >> n){
        int tmp;
        int last_pop=0;
        for(int i=0;i<n;i++){
            tmp = readNum();
            if(!s.empty() && s.top()==tmp){
                s.pop();
                if(!s.empty() && s.top() < tmp){
                    s.push(tmp);
                    s.push(tmp);
                }else{
                    last_pop = last_pop > tmp ? last_pop : tmp;
                }
            }else{
                s.push(tmp);
            }
        }
        if(s.size()==1 &&last_pop <= s.top()  || s.size() == 0){
            cout << "YES" <<endl;
        }else{
            cout << "NO" << endl;
        }
        while(!s.empty()){
            s.pop();
        }
    }
    return 0;
}

int readNum(){
    int tmpChar = getchar();
    int tmpNum=0;
    while(tmpChar < '0' || tmpChar > '9' || tmpChar == ' ' || tmpChar == '\n') tmpChar=getchar();
    while(tmpChar >= '0' && tmpChar <= '9'){
        tmpNum = tmpNum*10 + tmpChar - '0';
        tmpChar=getchar();
    }
    return tmpNum;
}