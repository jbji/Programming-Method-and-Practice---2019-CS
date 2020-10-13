#include <iostream>
#include <stack>
#include <cstring>
#include <map>
#define MIN(x,y) (x<y?x:y)
using namespace std;

int main() {
    int T;
    char c;
    int counter=0;
    cin >> T;
    map<int,int> indexMap;
    int index=0;
    int lAmount[T],rAmount[T],midAmount=0;
    memset(lAmount,0, sizeof(lAmount));
    memset(rAmount,0, sizeof(rAmount));
    for(int i=0; i<T;i++){
        stack<char> s;
        c=getchar();
        while(c!='(' && c!=')'){
            c=getchar();
        }
        while(c=='('||c==')'){
            if(c==')'){
                if(!s.empty() && s.top()=='('){
                    s.pop();
                }else{
                    s.push(c);
                }
            }else{
                s.push(c);
            }
            c=getchar();
        }
        int size=s.size();

        //此时，所有的括号会被化简成最简形式，并被存储起来供匹配。
        if(indexMap.count(size) == 0){
            indexMap[size]=index++;
        }
        if(!s.empty()){
            char top = s.top(),tail = top;
            while(!s.empty()){
                tail=s.top();
                s.pop();
            }
            if(top==tail){
                if( tail=='('){
                    lAmount[(indexMap[size])]++;
                }else{
                    rAmount[(indexMap[size])]++;
                }
            }
        }else{
            midAmount++;
        }
    }
    for(int i=0;i<T;i++){
        counter += MIN(lAmount[i],rAmount[i]);
    }
    counter += midAmount/2;

    cout << counter << endl;
    return 0;
}