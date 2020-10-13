#include <iostream>
#include <algorithm>

using namespace std;

class Block{
public:
    int a;
    int b;
    int c;
    int index;
    int min;

    Block(int _a,int _b, int _c,int _index):a(_a),b(_b),c(_c),index(_index){
        if(a < b) swap(a, b);
        if(a < c) swap(a,c);
        if(b < c) swap(b,c);
        min = a < b ? a : b;
        min = min < c ? min : c;
    }
    static bool cmpab(Block *i,Block *j){
        if (i->a != j->a) return i->a < j->a;
        if (i->b != j->b) return i->b < j->b;
        return i->c < j->c;
    }
    static bool cmpbc(Block *i,Block *j){
        if (i->b != j->b) return i->b < j->b;
        if (i->c != j->c) return i->c < j->c;
        return i->a < j->a;
    }
    static bool cmpca(Block *i,Block *j){
        if (i->c != j->c) return i->c < j->c;
        if (i->a != j->a) return i->a < j->a;
        return i->b < j->b;
    }
    static bool cmpmin(Block *i,Block *j){
        return i->min < j->min;
    }
};
int main() {
    int n;
    cin >> n;
    Block * bl[n];
    int a,b,c,maxBlock;
    for(int i=0;i<n;i++){
        scanf("%d %d %d",&a,&b,&c);
        bl[i] = new Block(a,b,c,i);
    }
    //mode single
    sort(bl,bl+n,Block::cmpmin);
    Block * p1 = NULL,* p2 = NULL;
    p1 = bl[n-1];
    maxBlock = p1->min;
    //mode multiple
    sort(bl,bl+n,Block::cmpab);
    for(int i=0;i<n-1;i++){
        if(bl[i]->a == bl[i+1]->a && bl[i]->b == bl[i+1]->b){
            int min = bl[i]->a < bl[i]->b ? bl[i]->a : bl[i]->b;
            min = min < bl[i]->c + bl[i+1]->c ? min : bl[i]->c + bl[i+1]->c;
            if(maxBlock < min){
                maxBlock = min;
                p1 = bl[i];
                p2 = bl[i+1];
            }
        }
    }
    sort(bl,bl+n,Block::cmpbc);
    for(int i=0;i<n-1;i++){
        if(bl[i]->b == bl[i+1]->b && bl[i]->c == bl[i+1]->c){
            int min = bl[i]->b < bl[i]->c ? bl[i]->b : bl[i]->c;
            min = min < bl[i]->a + bl[i+1]->a ? min : bl[i]->a + bl[i+1]->a;
            if(maxBlock < min){
                maxBlock = min;
                p1 = bl[i];
                p2 = bl[i+1];
            }
        }
    }
    sort(bl,bl+n,Block::cmpca);
    for(int i=0;i<n-1;i++){
        if(bl[i]->c == bl[i+1]->c && bl[i]->a == bl[i+1]->a){
            int min = bl[i]->c < bl[i]->a ? bl[i]->c : bl[i]->a;
            min = min < bl[i]->b + bl[i+1]->b ? min : bl[i]->b + bl[i+1]->b;
            if(maxBlock < min){
                maxBlock = min;
                p1 = bl[i];
                p2 = bl[i+1];
            }
        }
    }
    if(p2){
        int i1=p1->index,i2=p2->index;
        cout << "2" << endl << (i1<i2?i1:i2)+1 << " " << (i1>i2?i1:i2)+1 <<endl;
    }else{
        cout << "1" << endl << p1->index+1 <<endl;
    }
    return 0;
}