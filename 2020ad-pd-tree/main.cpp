#include <iostream>
#include <vector>
#include <set>
#include <string>

using namespace std;

int main() {
    int n;
    cin >> n;
    int val[n];
    bool isOrdered[n];

    vector<vector<int>> p(n);
    for(int i=0;i<n;i++){
        cin >> val[i];
    }
    for(int i=0;i<n;i++){
        cin >> isOrdered[i];
    }
    int tmpa,tmpb;
    for(int i=0;i<n-1;i++){
        cin >> tmpa >> tmpb;
        p[tmpa-1].push_back(tmpb-1);
        p[tmpb-1].push_back(tmpa-1);
    }


    std::cout << "Hello, World!" << std::endl;
    return 0;
}