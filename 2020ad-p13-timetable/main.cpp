#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class Task{
public:
    int s;
    int e;
    Task(int _s=0,int _e=0):s(_s),e(_e){}
    static bool p_cmp(Task *i,Task *j){
        return i->e < j->e;
//        if(i.e!=j.e) return i.e<j.e;
//        return i.s>j.s;
    }
};

int main() {
    int n=0;
    cin >> n;
    Task * t[n];
    for(int i=0;i<n;i++){
        t[i] = new Task(0,0);
        scanf("%d %d", &t[i]->s,&t[i]->e);
    }
    sort(t,t+n,Task::p_cmp);
    int cnt=0;
    int before_end=0;
    for(int i=0;i<n;i++){
        if(t[i]->s >= before_end){
            before_end = t[i]->e;
            cnt++;
        }
    }
    cout << cnt << endl;
    return 0;
}