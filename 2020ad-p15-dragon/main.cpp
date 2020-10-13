#include <iostream>
#include <algorithm>

using namespace std;
class Dragon{
public:
    int dif; //difficulty
    int exp; //exp
    int ra;//剩余最大攻击力
    Dragon(int _x,int _y): dif(_x), exp(_y), ra(_x + _y){}
    long long int kill(long long int & attack){
        long long int money=0;
        if(attack >= dif){
            attack += exp;
            return 0;
        }else{
            money = dif - attack;
            attack = dif + exp;
        }
        return money;
    }
    static bool cmpRemainingAttack(Dragon *i,Dragon * j){
        if(i->ra != j->ra) return i->ra > j->ra;
        return i->exp > j->exp;
    }
    static bool cmpdiff(Dragon *i,Dragon * j){
        return i->dif < j->dif;
    }
    static bool cmpexp(Dragon *i,Dragon * j){
        return i->exp > j->exp;
    }
};
int main() {
    int n=0;
    cin >> n;
    Dragon *d[n];

    int tmpx,tmpy;
    long long int A = 0;
    long long int money = 0;
    for(int i=0;i<n;i++){
        scanf("%d %d",&tmpx,&tmpy);
        d[i] = new Dragon(tmpx,tmpy);
    }
    int i=0;
    sort(d,d+n,Dragon::cmpexp);
    while( i<n && d[i]->exp >= 0){
        i++;
    }
    sort(d,d+i,Dragon::cmpdiff);
    for(int j=0;j<i;j++){
        money += d[j]->kill(A);
    }
    if(i<n) sort(d+i,d+n,Dragon::cmpRemainingAttack);
    for(int j=i;j<n;j++){
        money += d[j]->kill(A);
    }
    cout << money << endl;
    return 0;
}