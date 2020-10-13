#include <iostream>
#include <stack>
#include <algorithm>
#include <cstring>
using namespace std;

class Building{
public:
    int color;
    int height;
    Building(int _color=0, int _height=0): color(_color), height(_height){}
    static bool colorCmp(Building * i,Building * j){
        return i->color < j->color;
    }
};

int readNum();
int reAssignColor (Building *in, int len);

int main() {
    int n, T;
    for (cin >> T; T > 0; T--) {
        cin >> n;
        Building *b = new Building[n];
        stack<Building> s;
        for (int i = 0; i < n; i++) {
            b[i].color = readNum();
        }
        for (int i = 0; i < n; i++) {
            b[i].height = readNum();
        }
        int colorBucket[reAssignColor(b, n)+1];
        memset(colorBucket,0,sizeof(colorBucket));
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            while (!s.empty() && s.top().height < b[i].height) {
                if(--colorBucket[s.top().color] == 0){
                    cnt--;
                }
                s.pop();
            }
            s.push(b[i]);
            colorBucket[b[i].color]++;
            cnt += (colorBucket[b[i].color] == 1);
            cout << cnt;
            if (i != n - 1) {
                cout << " ";
            } else {
                cout << endl;
            }
        }
        while (!s.empty()) {
            s.pop();
        }
        delete[] b;
    }
    return 0;
}

int readNum(){
    int tmpChar = getchar();
    int tmpNum = 0;
    while(tmpChar < '0' || tmpChar > '9' || tmpChar == ' ' || tmpChar == '\n') tmpChar=getchar();
    while(tmpChar >= '0' && tmpChar <= '9'){
        tmpNum = tmpNum*10 + tmpChar-'0';
        tmpChar=getchar();
    }
    return tmpNum;
}

int reAssignColor (Building *in,int len){
    Building *b[len];
    for(int i=0;i<len;i++){
        b[i] = in+i;
    }
    sort(b,b+len,Building::colorCmp);
    int j=0;
    for(int i=0;i<len-1;i++){
        if(b[i]->color!=b[i+1]->color){
            b[i]->color = j;
            j++;
            continue;
        }
        b[i]->color = j;
    }
    b[len-1]->color = j;
    return j;
}