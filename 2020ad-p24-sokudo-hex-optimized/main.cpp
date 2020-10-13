#include <iostream>
#include <cstring>

using namespace std;

class Block{
    //a 4*4 sudoku block
public:
    char * data[4];
    int t_rotate;
    explicit Block():t_rotate(0){
        for(int i=0;i<4;i++){
            data[i] = new char[4];
        }
    }
    void rotate_anticlockwise(){
        //hardCopy
        char * newData[4];
        for(int i=0; i<4; i++){//第一行是之前的第三列
            newData[i] = new char[4];
            for(int j=0;j<4;j++){
                newData[i][j] = data[j][3-i];
            }
        }
        for(int i=0; i<4; i++){
            delete[] data[i];
            data[i] = newData[i];
        }
        t_rotate++;
    }
    void print(){
        cout << "Block:" << endl;
        for(auto i : data){
            cout << i << endl;
        }
    }
    ~Block(){
        for(auto & i : data){
            delete[] i;
        }
    }
};

void mapInitialize(Block *b[4][4]){
    for(int i=0;i<4;i++){
        for(int j = 0; j<4;j++){
            b[i][j] = new Block();
        }
    }
}
void mapPrint(Block *b[4][4]){
    for(int i=0;i<4;i++){
        for(int j = 0; j<4;j++){
            b[i][j] -> print();
        }
    }
}
void mapRead(Block *b[4][4]){

    char tmp[17];
    for(int i=0; i<16 ;i++){
        cin >> tmp;
        for(int j=0 ; j<16;j++){
            b[i/4][j/4] -> data[i%4][j%4] = tmp[j];
        }
    }
}
void mapDelete(Block * b[4][4]){
    for(int i=0;i<4;i++){
        for(int j = 0; j<4;j++){
            delete b[i][j];
        }
    }
}
void mapCopy(Block * b_bak[4][4],Block * b[4][4]){
    for(int i=0; i<16 ;i++){
        for(int j=0 ; j<16;j++){
            b_bak[i/4][j/4] -> data[i%4][j%4] = b[i/4][j/4] -> data[i%4][j%4];
        }
    }
}
bool mapPartialColCheck(Block *b [4][4],int row,int col,int incol){
    int stat[16];
    memset(stat, 0, sizeof(stat));
    for(int i = 0;i<=row ;i++){
        for(int k = 0;k<4;k++){
            switch(b[i][col] -> data[k][incol]){
                default:
                    stat[b[i][col] -> data[k][incol] - '0' ] ++;
                    break;
                case 'A':
                    stat[10] ++;
                    break;
                case'B':
                    stat[11] ++;
                    break;
                case 'C':
                    stat[12]++;
                    break;
                case 'D':
                    stat[13]++;
                    break;
                case 'E':
                    stat[14]++;
                    break;
                case 'F':
                    stat[15]++;
                    break;
            }
        }
    }
    for(auto i : stat){
        if(i > 1){
            return false;
        }
    }
    return true;
}
bool mapPartialLineCheck(Block *b [4][4],int row,int col,int inrow){
    int stat[16];
    memset(stat, 0, sizeof(stat));
    for(int i = 0;i<=col ;i++){
        for(int k = 0;k<4;k++){
            switch(b[row][i] -> data[inrow][k]){
                default:
                    stat[b[row][i] -> data[inrow][k] - '0' ] ++;
                    break;
                case 'A':
                    stat[10] ++;
                    break;
                case'B':
                    stat[11] ++;
                    break;
                case 'C':
                    stat[12]++;
                    break;
                case 'D':
                    stat[13]++;
                    break;
                case 'E':
                    stat[14]++;
                    break;
                case 'F':
                    stat[15]++;
                    break;
            }
        }
    }
    for(auto i : stat){
        if(i > 1){
            return false;
        }
    }
    return true;
}

bool dfs(Block * b[4][4],int rt[4][4],int row,int col){ //Position Selector
    //get all children
    for(int i=0;i<4; b[row][col]->rotate_anticlockwise(),  rt[row][col] ++, i++){
        bool isValid = mapPartialColCheck(b,row,col,0) && mapPartialLineCheck(b,row,col,0);
        if(isValid){
            if(row==3 && col ==3) return true;
            bool isEnd = false;
            if(col<3){
                isEnd = dfs(b,rt,row,col+1);
            }else if(row<3){
                isEnd = dfs(b,rt,row+1,0);
            }
            if(isEnd){
                return true;
            }else{
                if(i==3){
                    b[row][col]->rotate_anticlockwise();
                    rt[row][col]=0;
                    return false;
                }
                continue;
            }
        }
        if(i==3){
            b[row][col]->rotate_anticlockwise();
            rt[row][col]=0;
            return false;
        }
    }

}

void rtInitialize(int rt[4][4]){
    for(int i=0;i<4;i++){
        memset(rt[i],0, sizeof(rt[i]));
    }
}
void outputAns(int rt[4][4]){
    int ans_ori=0;int ans_1=0;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            ans_ori += rt[i][j];
            ans_1 += (rt[i][j]+2) %4;
        }
    }
    if(ans_ori <= ans_1){
        cout << ans_ori <<endl;
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                for(int k=rt[i][j];k>0;k--){
                    cout << i+1 <<" " << j+1 <<endl;
                }
            }
        }
    }else{
        cout << ans_1 <<endl;
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                for(int k=(rt[i][j]+2)%4 ;k>0;k--){
                    cout << i+1 <<" " << j+1 <<endl;
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    Block * b[4][4];
    int rt[4][4];
    int T=0;
    for(cin >> T;T>0;T--){
        mapInitialize(b);
        mapRead(b);
        rtInitialize(rt);
        dfs(b,rt,0,0);
        outputAns(rt);
        mapDelete(b);
    }
    return 0;
}