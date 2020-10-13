#include <iostream>

using namespace std;
int main() {
    freopen("input.txt","w",stdout);
    int n=200000;
    cout << n <<endl;
    for(int i=1;i<n;i++){
        cout << i << " " << i+1<<endl;
    }

    return 0;
}