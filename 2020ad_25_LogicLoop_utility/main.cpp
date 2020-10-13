#include <iostream>

using namespace std;
int main() {
    std::ios::sync_with_stdio(false);
    freopen("input.txt","w",stdout);
    int n=255;
    cout << n << " " << n<<endl;
    for(int i=1;i<n;i++){
        cout << i << " " << i+1<<endl;
    }
    cout << n << " " << 1<<endl;
    return 0;
}