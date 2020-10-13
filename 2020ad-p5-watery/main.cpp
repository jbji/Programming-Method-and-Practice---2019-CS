#include <iostream>
#include <queue>

using namespace std;

int calcDelta(queue<int> in);

int main() {
    int T;
    for(cin >> T;T>0;T--){
        int lakeWidth;
        long counter=0;
        int newHeight;
        queue<int> q;
        for(cin >> lakeWidth; lakeWidth > 0; lakeWidth--){
            cin >> newHeight;
            if(q.empty()){
                q.push(newHeight);
            }else{
                if(q.front() > newHeight){
                    q.push(newHeight);
                }else{
                    for(int tmp = q.front();!q.empty();){
                        counter += tmp - q.front();
                        q.pop();
                    }
                    q.push(newHeight);
                }
            }
        }
        queue<int> * pq = &q;
        while(!(pq->empty())){
            int newHeight = pq->front() - calcDelta(*pq);
            pq->pop();

            queue<int> * iq = new queue<int>;
            iq->push(newHeight);
            if (iq->front() <= 0) break;

            while (!pq->empty()) {
                newHeight = pq->front();
                pq->pop();
                if (iq->empty()) {
                    iq->push(newHeight);
                } else {
                    if (iq->front() > newHeight) {
                        iq->push(newHeight);
                    } else {
                        for (int tmp = iq->front(); !iq->empty();) {
                            counter += tmp - iq->front();
                            iq->pop();
                        }
                        iq->push(newHeight);
                    }
                }
            }
            pq = iq;
        }
        cout << counter << endl;
    }
    return 0;
}

int calcDelta(queue<int> in){
    int max = in.front(), secmax=0 ,tmp;
    in.pop();
    while (!in.empty()) {
        tmp = in.front();
        if(tmp > secmax){
            secmax = tmp;
        }
        in.pop();
    }
    return max-secmax;
}
