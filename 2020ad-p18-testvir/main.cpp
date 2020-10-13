#include <iostream>

using namespace std;
int main() {
    freopen("input.txt","w",stdout);
    cout << "1" << endl << "1000000" << endl;

    for(int i=1000000;i>0;i--){
        cout << i;
        if(i!=1){
            cout <<" ";
        }else{
            cout << endl;
        }
    }
    for(int i=1000000;i>0;i--){
        cout << i;
        if(i!=1){
            cout <<" ";
        }else{
            cout << endl;
        }
    }
    return 0;
}