#include <iostream>
#include <string>
#include <map>

using namespace std;

int main() {
    string tmp;
    int n,m;
    map<string,bool> isAppear;
    for(cin >> n >> m; n>0;n--){
        cin >> tmp;
        isAppear[tmp]=true;
    }
    while(m>0){
        cin >> tmp;
        if(isAppear.count(tmp)==0){
            cout << "NO" << endl;
        }else{
            cout << "YES" << endl;
        }
        m--;
    }
    return 0;
}