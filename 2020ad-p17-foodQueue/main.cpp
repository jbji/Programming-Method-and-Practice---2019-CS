#include <iostream>
#include <deque>

using namespace std;

int getRead(char * str);

int main() {
    deque<char *> q;
    int n;
    char * tmpStr;
    for(cin >> n;n>0;n--){
        tmpStr = new char[35];
        switch(getRead(tmpStr)){
            case 0:
                q.push_back(tmpStr);
                break;
            case 1:
                if(!q.empty()) q.pop_front();
                break;
            case 2:
                if(q.empty()){
                    printf("Empty queue\n");
                }else{
                    printf("%s\n",q.front()+7);
                }
                break;
            case 3:
                if(q.empty()){
                    printf("Empty queue\n");
                }else{
                    printf("%s\n",q.back()+7);
                }
                break;
        }
    }
    return 0;
}

int getRead(char * str){
    char * tmpstr=str;
    char tmpChar = getchar();
    while(tmpChar == '\n') tmpChar=getchar();
    for(;tmpChar!='\n';tmpChar=getchar()){
        *(str++) = tmpChar;
    }
    *str='\0';
    str=tmpstr;
    if(str[0]=='A'){
        return 0;
    }
    if(str[0]=='L'){
        delete[] str;
        return 1;
    }
    if(str[5] =='H'){
        delete[] str;
        return 2;
    }
    if(str[5] =='T'){
        delete[] str;
        return 3;
    }
    return 4;
};