#include <iostream>
#define STONE '*'
#define GRASS '.'
using namespace std;

int areaParalell(char **camp, int n);
int nonParalell(char **camp, int n);

int main() {
    int n;
    cin >> n;
    char * camp[n];
    for(int i=0;i<n;i++){
        camp[i]=  new char[n+1];
        cin >> camp[i];
    }
    int ans = areaParalell(camp, n);
    int ans2 = nonParalell(camp, n);
    cout << (ans>ans2?ans:ans2) << endl;
    return 0;
}

bool pvalid(char **camp, int i1,int j1, int i2, int j2){
    int gCnt = 0; //grass
    if(camp[i1][j1] == GRASS){
        gCnt++;
    }
    if(camp[i2][j2] == GRASS){
        gCnt++;
    }
    if(camp[i1][j2] == GRASS){
        gCnt++;
    }
    if(camp[i2][j1] == GRASS){
        gCnt++;
    }
    if(camp[i1][j1] == STONE || camp[i2][j2] == STONE ||camp[i1][j2] == STONE ||camp[i2][j1] == STONE){
        return false;
    }
    return (gCnt <=1);
}
bool npvalid(char **camp, int n,int i1,int j1,int i2){
    /*
     * i1 j1
     * j2
     *
     *
     * */
    int d = i2-(i1+i2)/2;
    int x[4][2] = { {i1,j1} , {i2,j1} ,{(i1+i2)/2, j1-d} ,{(i1+i2)/2, j1+d}};
    int gCnt = 0; //grass
    for(int i=0;i<4;i++){
        if(x[i][1] <0 || x[i][1] >=n){
            return false;
        }
        if(camp[x[i][0]][x[i][1]] == GRASS){
            gCnt++;
        }
        if(camp[x[i][0]][x[i][1]] == STONE){
            return false;
        }
    }
    return (gCnt <=1);
}
bool npvalid_1(char **camp, int n,int i1,int j1,int i2,int j2){
    int dy = i2-i1;
    int dx = j1-j2;
    int x[4][2] = { {i1,j1} , {i2,j2} ,{i1+dx,j1+dy} ,{i1+dx+dy,j1+dy-dx}};
    int gCnt = 0; //grass
//    cout << "checking" << endl;
    for(int i=0;i<4;i++){
        if(x[i][0] <0 || x[i][0] >=n || x[i][1] <0 || x[i][1] >=n){
            return false;
        }
        if(camp[x[i][0]][x[i][1]] == GRASS){
            gCnt++;
        }
        if(camp[x[i][0]][x[i][1]] == STONE){
            return false;
        }
    }
    return (gCnt <=1);
}
int areaParalell(char **camp, int n){
    int ans = 0;
    for(int i1=0;i1<n;i1++){
        for(int j1=0;j1<n;j1++){
            for(int i2=i1+1,j2=j1+1;i2<n && j2<n;j2++,i2++){
                if(pvalid(camp,i1,j1,i2,j2)){
                    ans = max(ans,(i2-i1)*(j2-j1));
                }
            }
        }
    }
    return ans;
}

int nonParalell(char **camp, int n){
    int ans = 0;
    for(int i1=0;i1<n;i1++){
        for(int j1=0;j1<n;j1++){
            for(int j2=j1-1;j2>=0;j2--){
                for(int i2=i1+1;i2<n;i2++){
//                    cout << "i1: " << i1 << " j1: " << j1<<endl;
//                    cout << "i2: " << i2 << " j2: " << j2<<endl;
                    if(npvalid_1(camp,n,i1,j1,i2,j2)){
                        ans = max(ans,(i2-i1)*(i2-i1)+(j2-j1)*(j2-j1));
                    }
                }
            }
        }
    }
    return ans;
}