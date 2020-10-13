#include <iostream>
#include <cctype>

using namespace std;

int main() {
    char c = getchar();
    bool toggleUpper = true;
    while(c!=EOF){
        if(isalpha(c) && toggleUpper){
            printf("%c",toupper(c));
            toggleUpper = false;
        }else{
            if(isalpha(c)){
                printf("%c",tolower(c));
            }else{
                cout << c;
            }
        }
        if(c == '.'||c=='?' || c=='!') toggleUpper=true;
        c=getchar();
    }

    return 0;
}