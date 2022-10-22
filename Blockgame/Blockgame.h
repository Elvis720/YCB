#include<iostream>
#include<vector>
using namespace std;
//点
struct dot{
    int row;
    int col;
};
//不同形状的块
struct block{
    int rows;
    int cols;
    vector<dot> dots;
};

class Blockgame{
public:

    Blockgame(int n,int m){
        this->cols = m;
        this->rows = n;

        vector<int> temp(m,0);
        for(int i = 0;i < n;i++){
            board.emplace_back(temp);
        }
    }

    bool is_full(int row);
    //判断row 行是否满
    //board 为棋盘的引用  row 为需要判断的行

    bool lock_dot(const dot &Dot);
    //判断某点是否为空
    //board 为棋盘的引用 Dot 为需要判断的点

    bool lock_piece(const block &Block,const dot &start);
    //判断某块是否能填入
    //board 为棋盘的引用 block 为需要判断的块 start 为所判断块区的左上角

    
    int setdot(const dot &Dot);
    //填充点

    int setblock(const block &Block,const dot &start);
    //填充块

private:
    int cols ;
    int rows ;
    vector<vector<int>> board;

};