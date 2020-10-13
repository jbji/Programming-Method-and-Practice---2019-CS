#include <iostream>
#include <queue>
#include <cstring>
#include <vector>

using namespace std;

class Maze{
public:
    int dim_n;
    int dim_m;
    int board[20];
    int hisBoard[20][20];
    int depth;
    Maze(int _dim_n, int _dim_m,char * data[]):dim_n(_dim_n),dim_m(_dim_m),depth(0){
        //to initialize
        memset(board,0, sizeof(board));
        memset(hisBoard,0,sizeof(hisBoard));
        //to copy and compress the data.
        for(int i=0;i<_dim_n;i++){
            int tmp=0;
            for(int j=0;data[i][j]!='\0';j++){
                if(data[i][j]=='1'){
                    tmp |= (1 << (dim_m-1-j));
                }
            }
            board[i]=tmp;
        }
    }
    bool isEnd(){
        bool result = true;
        for(int i=0;i<dim_n;i++){
            if(board[i]){
                result = false;
                break;
            }
        }
        return result;
    }
    void togglePos(int x,int y){
        board[x] ^= (1<<y);
        if(x>0) board[x-1] ^= (1<<y);
        if(x+1<dim_n) board[x+1] ^= (1<<y);
        if(y>0) board[x] ^= (1<<(y-1));
        if(y+1<dim_m) board[x] ^= (1<<(y+1));
        hisBoard[x][y]=1;
        depth++;
    }
};

vector<Maze> getChildMaze(Maze in){
    vector<Maze> childMaze;
    Maze tmp=in;
    for(int i=0;i<in.dim_n;i++){
        for(int j=0;j<in.dim_m;j++){
            if(tmp.hisBoard[i][j] == 0){
                tmp.togglePos(i,j);
                childMaze.push_back(tmp);
                tmp=in;
            }
        }
//        if(!tmp.board[i]){
//
//        }
    }
    return childMaze;
}
int main() {
    int n,m;
    cin >> n >> m;
    char * data[n]; // A SET OF POINTERS
    for(int i=0;i<n;i++){
        data[i] = new char[m+1]; // 此处给小了
        cin >> data[i];
    }
    Maze state0(n,m,data);
    queue<Maze> q;
    q.push(state0);
    while(true){
        Maze current= q.front();
        q.pop();
        if(current.isEnd()){
            cout << current.depth << endl;
            break;
        }
        vector<Maze> tmp = getChildMaze(current);
        for(vector<Maze>::iterator it = tmp.begin();it != tmp.end(); it++){
            q.push(*it);
        }
    }
    return 0;
}