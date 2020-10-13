#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Plant{
public:
    int risk;
    int productivity;
    Plant(int rk=0,int pd=0):risk(rk),productivity(pd){}
    static bool cmp(Plant i,Plant j){
//        return !( j.productivity > i.productivity || (j.productivity == i.productivity && j.risk < i.risk) );
        //如果要升序排列，那么return i<j. 因此降序排列就是 return j<i
        return j.productivity < i.productivity && (j.productivity != i.productivity || j.risk > i.risk);
//        if (j.productivity > i.productivity){ //先取生产力大的
//            return 0;
//        }else if(j.productivity == i.productivity && j.risk < i.risk){
//            return 0;
//        }else {
//            return 1;
//        }
    }
};
//定义流输出便于调试
//ostream& operator << (ostream &out, const Plant &p){
//    out << "(Plant: " << "Productivity," << p.productivity << ";Risk," << p.risk <<")";
//    return out;
//}

int main() {
//    vector<Plant> inputs{Plant(1,2),Plant(3,2),Plant(4,5)};
    vector<Plant> inputs;
    int n,k,tmp;
    long long int sumRisk = 0,sumPd = 0;
    cin >> n >> k;
    for(int i=0 ; i<n ; i++){
        cin >> tmp;
        inputs.push_back(Plant(tmp));
    }
    for(int i=0 ; i<n ; i++){
        cin >> tmp;
        inputs[i].productivity = tmp;
    }
    sort(inputs.begin(),inputs.end(), Plant::cmp);
    for(vector<Plant>::iterator it = inputs.begin(); it != inputs.begin()+k; it++){
        sumRisk += (*it).risk;
        sumPd += (*it).productivity;
    }
    cout << sumRisk <<" " << sumPd << endl;
    return 0;
}