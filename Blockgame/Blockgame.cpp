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

bool Blockgame::is_full(int row){
    int n = board.size();
    int m = board[0].size();
    for(int i = 0;i < m;i++){
        if(board[row][i] != 1){
            return false;
        }
    }
    return true;
}

bool Blockgame::lock_dot(const dot &Dot){
    return board[Dot.row][Dot.col] == 0;
}

bool Blockgame::lock_piece(const block &Block,const dot &start){
    for(dot temp: Block.dots){
        int n = temp.row + start.row;
        int m = temp.col + start.col;
        if(n > rows || m > cols){
            cout << "超出棋盘范围" <<endl;
            return false;
        }
        else if(board[n][m] != 0){
            return false;
        }
    }
    return true;
}


int Blockgame::setdot(const dot &Dot){
    if(Dot.col > cols || Dot.row > rows){
        cout << "超出棋盘范围" <<endl;
    }
    else if(board[Dot.row][Dot.col]){
        cout  <<"该点已有元素" <<endl;
    }
    else{
        board[Dot.row][Dot.col] = 1;
    }
    return 0;
}

int Blockgame::setblock(const block &Block,const dot &start){
    if(lock_piece(Block,start)){
        for(dot ele:Block.dots){
            setdot(ele);
        }
    }
    else{
        cout << "该块无法填充此位置" <<endl;
    }
}
