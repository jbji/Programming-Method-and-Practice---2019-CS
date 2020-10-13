#include <iostream>

using namespace std;
int main() {
    int lakeWidth,maxHeight;
    long counter=0;
    int newHeight;
    cin >> lakeWidth >> maxHeight;
    for(int tmpH=maxHeight; lakeWidth > 0; lakeWidth--, tmpH = newHeight){
        cin >> newHeight;
        if(newHeight < tmpH){
            counter += tmpH - newHeight;
        }
    }
    cout << counter << endl;
    return 0;
}