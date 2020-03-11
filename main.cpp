#include "board.h"
#include"board.cpp"
int main()
{   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |FOREGROUND_RED |FOREGROUND_GREEN | FOREGROUND_BLUE);
    int row;
    int column;
    string flag;
    cout<<"Game Start"<<endl;
    Board board;
    board.initialization();
    board.mineCreate();
    board.printTrueNumber();
    while (1)
    {   cout<<"Enter the row,column and you want to open it(O) or flag it(F) e.g:2 3 F"<<endl;
        cin>>row;
        row-=1;
        cin>>column;
        cout<<endl;
        column-=1;
        cin>>flag;
        if (flag=="O"){  //如果操作是：翻开棋子
            if (board.game(row,column)!=-1){  //-1 means game over
                board.printTrueNumber();
            }
            else {
                board.printMineforFinal();
                break;   //如果输了 调用输界面
            
            };
        }
        else if (flag=="F"&&(board.mask[row][column]==0)){ //如果操作是：插旗 且该位置还没插旗
            board.mask[row][column]=1; //要插旗的地方 同位置mask变为1
            board.printTrueNumber();
        }
        else if (flag=="F"&&(board.mask[row][column]==1)){ //如果操作是：插旗 且该位置已经插旗
            board.mask[row][column]=0; //两次插旗=取消插旗
            board.printTrueNumber();
        }
    
    }
    cout<<"End"<<endl;


}
