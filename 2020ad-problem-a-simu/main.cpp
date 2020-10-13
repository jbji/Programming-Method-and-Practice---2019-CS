#include <iostream>

using namespace std;

int main() {
//    ios::sync_with_stdio(false);
    int T;
    int A,B,t,k,i;
    for(cin >> T;T>0;T--){
        cin >> A >> B >> t >> k;
        int t_now=0;
        for(int i=0;i<k;i++){
            t_now += t;
            if(t_now>=B){
                t_now %= B;
                if(t_now >= A && i!= k-1){
                    t_now = 0;
                }
                continue;
            }
            if(t_now >= A && i!= k-1){
                t_now = 0;
            }
        }
        cout << t_now <<endl;
    }
    return 0;
}