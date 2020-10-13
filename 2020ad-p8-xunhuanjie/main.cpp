#include <iostream>
#include <queue>
#include <stack>

using namespace std;

int output(queue<char> *input,queue<char> *result,int L,int times);
int getinput(queue<char> *input,int L);
int fixResult(queue<char> *result,queue<char> * input);

int main() {
    int L;
    cin >> L;
    queue<char> input;
    queue<char> result;
    //to gei input
    int outputTimes=1;
    int remain = getinput(&input,L);
    if(remain == 0){
        //if we have no reamin, we could create a num and repeat it.
        for(int i=0;i<L;i++){
            result.push(input.front());
            input.pop();
        }
        //下面是对结果进行进位
        outputTimes = fixResult(&result,&input);
    }else{
        //if we have remains,we can only generate a number like 1000000···0
        result.push('1');
        input.pop();
        for(int i=0;i<L-1;i++){
            result.push('0');
            if(!input.empty()) input.pop();
        }
    }
    output(&input,&result,L,outputTimes);
    return 0;
}
int fixResult(queue<char> *result,queue<char> * input){
    //请注意，此时需要被修正的result和input一定满足这样的关系：
    //注意 二者大小都被循环节长度L整除
    //要么 result非空， input为空
    //要么 result非空， input非空，
    bool allEqualFlag = true;
    bool needFix = true;
    int isbreak=false;
    long long inbiggercounter=0;
    long long resultbiggercounter=0;
    queue<char> tmpIn=*input;
    while(!tmpIn.empty()){
        needFix=false;
        queue<char> tmpResult=*result;
        while(!tmpResult.empty()){
            if(!tmpIn.empty()){
                //只要在出现第三种情形前，出现了就一定不用被修复的情形：tmpIn.front() < tmpResult.front()
                //!!!全部都出现，才需要被修复的情形：tmpIn.front() == tmpResult.front()
                //一旦出现，就需要被修复的情形 tmpIn.front() > tmpResult.front()
                if(tmpIn.front() < tmpResult.front()){
                    allEqualFlag = false;
                    resultbiggercounter++;
                    if(inbiggercounter==0){
                        needFix=false;
                        isbreak= true;
                        break;
                    }

                }else if(tmpIn.front() > tmpResult.front()){
                    allEqualFlag = false;
                    inbiggercounter++;
                    if(resultbiggercounter==0){
                        needFix=true;
                        isbreak= true;
                        break;
                    }

                };
                tmpIn.pop();
            }
            tmpResult.pop();
        }
        if(isbreak){
            break;
        }
    }
    needFix = needFix || allEqualFlag;
    //修正就是加一位，问题在于上面需要修正的判据为何。
    if(needFix){
        stack<char> adder;
        stack<char> tmpout;
        //convert the result to fix into a stack
        while(!result->empty()){
            adder.push(result->front());
            result->pop();
        }
        //add operate
        int tmpUp = 1;
        int tmpNum;
        while(!adder.empty()){
            tmpNum = adder.top() - '0';
            tmpout.push((tmpNum + tmpUp) % 10 + '0');
            tmpUp = (tmpNum + tmpUp) / 10;
            adder.pop();
        }
        allEqualFlag = false;
        while(tmpUp !=0 ){
            tmpout.push((tmpUp) % 10 + '0');
            tmpUp /= 10;
            allEqualFlag = true;
        }
        //convert stack into queue
        while(!tmpout.empty()){
            result->push(tmpout.top());
            tmpout.pop();
        }
    }
    return allEqualFlag ? 2 : 1;
}

int getinput(queue<char> *input,int L){
    int remain=0;
    char c = getchar();
    while(c>'9' || c<'0') c=getchar();
    while(c<='9' && c>= '0'){
        (*input).push(c);
        remain++;
        if(remain == L){
            remain=0;
        }
        c=getchar();
    }
    return remain;
}
int output(queue<char> *input,queue<char> *result,int L,int times){
    for(int k=0;k<times;k++){
        queue<char> tmp = *result;
        //output what's in the result queue.
        for(int i=0;i<L;i++){
            cout << tmp.front();
            tmp.pop();
        }
    }
    //output remaining places.
    while(!(*input).empty()){
        queue<char> tmp = *result;
        for(int i=0;i<L;i++){
            cout << tmp.front();
            tmp.pop();
            if(!(*input).empty()) (*input).pop();
        }
    }
    cout << endl;
    return 0;
}