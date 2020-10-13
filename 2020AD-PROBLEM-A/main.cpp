#include <iostream>

using namespace std;

int main() {
//    ios::sync_with_stdio(false);
    int T;
    int A,B,t,k,i;
    for(cin >> T;T>0;T--){
        cin >> A >> B >> t >> k;
        if(t>B) {
            t = (t - 1) % B + 1;
        }
        //i表示，第几次将会被滞留
        for(i=1;t*i<A;i++);
        //将k变到不大于i的范围
        cout << t * ((k - 1) % i + 1) % B << endl;
    }
//    std::cout << "Hello, World!" << std::endl;
    return 0;
}