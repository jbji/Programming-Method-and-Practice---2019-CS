#include <iostream>

using namespace std;

int main() {
    int n = rand()%10+5;
    char seed[10]={
            'I','I','I','I','.','.','.','.','*','*'
    };
    cout << n << endl;
    for(int i=0;i<n;i++){
        for(int i=0;i<n;i++){
            cout << seed[rand()%10];
        }
        cout << endl;
    }
    std::cout << "Hello, World!" << std::endl;
    return 0;
}