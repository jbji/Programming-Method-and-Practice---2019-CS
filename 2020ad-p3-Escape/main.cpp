/*
 * Description
小张是一个密室逃脱爱好者，在密室逃脱的游戏中，你需要解开一系列谜题最终拿到出门的密码。现在小张需要打开一个藏有线索的箱子，但箱子上有下图所示的密码锁。



每个点是一个按钮，每个按钮里面有一个小灯。如上图，红色代表灯亮，白色代表灯灭。每当按下按钮，此按钮的灯以及其上下左右四个方向按钮的灯状态会改变（如果原来灯亮则灯灭，如果原来灯灭则灯亮）。如果小张通过按按钮将灯全部熄灭则能可以打开箱子。

对于这个密码锁，我们可以先按下左上角的按钮，密码锁状态变为下图。



再按下右下角的按钮，密码锁状态变为下图。



最后按下中间的按钮，灯全部熄灭。



现在小张给你一些密码锁的状态，请你告诉他最少按几次按钮能够把灯全部熄灭。

Input
第一行两个整数 n,m(1 \leq n,m \leq 16 ) 。

接下来 n 行，每行一个长度为 m 的01字符串，0表示灯初始状态灭，1表示灯初始状态亮。

Output
一行一个整数，表示最少按几次按钮可以把灯全部熄灭。

Notes
第一个样例见题目描述，第二个样例按左上和右下两个按钮。

测试用例保证一定有解。


 */
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