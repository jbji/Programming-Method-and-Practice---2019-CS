#include <iostream>
#include <stack>

bool readOddNum();

using namespace std;

int main() {
//    freopen("input.txt","r",stdin);
//    freopen("output.txt","w",stdout);
    int n;
    stack<bool> s;
    while(cin >> n){
        bool tmp;
        for(int i=0;i<n;i++){
            tmp = readOddNum();
            if(!s.empty() && s.top()==tmp){
                s.pop();
            }else{
                s.push(tmp);
            }
        }
        if(s.size()<=1){
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

bool readOddNum(){
    int tmpChar = getchar();
    bool ans = 0;
    while(tmpChar < '0' || tmpChar > '9' || tmpChar == ' ' || tmpChar == '\n') tmpChar=getchar();
    while(tmpChar >= '0' && tmpChar <= '9'){
        ans = (tmpChar-'0')%2;
        tmpChar=getchar();
    }
    return ans;
}