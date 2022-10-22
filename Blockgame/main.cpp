//#include<iostream>
#include<vector>
#include"Blockgame.cpp"
//#include"Blockgame.cpp"
using namespace std;

int main(){
    cout << "设定棋盘大小" << endl;
    int n,m;
    cout << "长：" ;
    cin >> n;
    cout << "宽：" ;
    cin >> m;

    //栈上创建
    Blockgame A = Blockgame(n,m);
    for(int i = 0;i < n-2;i++){
        for(int j = 0;j < m;j++){
            dot ele = {i,j};
            A.setdot(ele);
        }
    }
    //验证各个函数
    cout << A.is_full(n-1) << endl;
    cout << A.is_full(0) << endl;

    dot ele = {0,0};
    A.setdot(ele);

    ele = {n-2,0};
    A.setdot(ele);

    block B;
    dot start = {0,0};
    B.dots ={{0,0},{0,1}};
    cout << A.lock_piece(B,start) <<endl;

    start = {n-1,0};
    cout << A.lock_piece(B,start) <<endl;

    return 0;
}


