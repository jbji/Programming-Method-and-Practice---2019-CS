#include <iostream>
#include <vector>
#define MAX(X,Y) (X>Y?X:Y)
using namespace std;

int main() {
    char RNAmap[128];
    RNAmap['A'] = 'U';
    RNAmap['U'] = 'A';
    RNAmap['G'] = 'C';
    RNAmap['C'] = 'G';
    int T;
    for(cin >> T;T>0;T--){
        int Bucket[128]={0};
        int len;
        cin >> len;
        int result = 0;
        vector<char> reverseA;
        //使用字符串快读
        char tmp = getchar();
        while(tmp <'A' || tmp >'Z') tmp = getchar();
        while('A' <= tmp && tmp <= 'Z' ){
            reverseA.push_back(RNAmap[tmp]);
            tmp = getchar();
        }
        //使用字符串快读和vector迭代器
        while(tmp <'A' || tmp >'Z') tmp = getchar();
        auto itA = reverseA.begin();
        while('A' <= tmp && 'Z' > tmp){
            //对于能否匹配的情况进行统计
            if ( *(itA) != tmp){
                if(RNAmap[tmp] == *itA){
                    Bucket[tmp]++;
                }else{
                    Bucket['X']++;
                }
            }
            itA++;
            tmp = getchar();
        }
        //输出统计结果
        result = MAX(Bucket['G'],Bucket['C']) + MAX(Bucket['A'],Bucket['U']) + Bucket['X'];
        cout << result << endl;
        while(!reverseA.empty()){
            reverseA.pop_back();
        }
    }
    return 0;
}