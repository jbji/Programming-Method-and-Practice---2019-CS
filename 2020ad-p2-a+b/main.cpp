/*
 *
 *
 *
 * Description
学过《计算机科学导论》的你应该熟悉“二进制运算”吧？

和十进制不同的是：二进制运算“逢二进一”。下面举一个二进制加法的运算实例:


   11101
+    110
--------
  100011
下面请你模拟这个过程。

Input
第一行输入一个正整数 T 空格 左括号 1 小於等於 T 小於等於 10 右括号，表示接下来有 T 组数据；
接下来 T 行，每行输入两个二进制串 a 和 b 中间用空格隔开，保证它们长度 1 小於等於 竖线 a 竖线 逗號 空格 竖线 b 竖线 小於等於 10 的 5 次方 并且没有前导 0。
Output
对于每组数据，请按模拟二进制加法，按题目描述的格式输出正确的运算结果，注意换行，没有多余的空格和换行。


 */
#include <iostream>
#include <string>
#include <stack>
#include <iomanip>

using namespace std;

class BinaryNum{
public:
    char data[200000];
    void read(){
        cin >> data;
    }
    char* toString(){
        return data;
    }

    BinaryNum add(BinaryNum num){
        stack<int> s1,s2,result;
        int tmp=0,tmpUp=0;
        // to Convert data into stack
        for(int i=0;data[i]!='\0';i++){
            s1.push(data[i]-'0');
        }
        for(int i=0;num.data[i]!='\0';i++){
            s2.push(num.data[i]-'0');
        }
        //to perform add operate
        while(!(s1.empty()&&s2.empty())){
            tmp=tmpUp;
            if(!s1.empty()){
                tmp+=s1.top();
                s1.pop();
            }
            if(!s2.empty()){
                tmp+=s2.top();
                s2.pop();
            }
            if(tmp>1){
                tmpUp=1;
                if(tmp==2){
                    result.push(0);
                }else if(tmp==3){
                    result.push(1);
                }
            }else{
                tmpUp=0;
                result.push(tmp);
            }
        }
        if(tmpUp==1){
            result.push(1);
        }
        // to convert stack to result;
        BinaryNum rlt;
        int i=0;
        while(!result.empty()){
            rlt.data[i]=result.top()+'0';
            i++;
            result.pop();
        }
        rlt.data[i]='\0';
        return rlt;
    }
};

int main() {
    int T;
    for(cin >> T;T>0;T--){
        BinaryNum * n1, * n2;
        n1 = new BinaryNum();
        n2 = new BinaryNum();
        n1->read();
        n2->read();
        string result = n1->add(*n2).toString();
        cout << setw(result.length()+2) << n1->data << endl;
        cout << "+" << setw(result.length()+1) << n2->data << endl;
        cout << setfill('-') << setw(result.length()+2) << '-'<< endl;
        cout << setfill(' ') << setw(result.length()+2) << result << endl;
        delete n1;
        delete n2;
    }

    return 0;
}