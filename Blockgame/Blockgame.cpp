#include "Blockgame.h"

using namespace std;

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
