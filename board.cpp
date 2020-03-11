#ifndef BOARD_CPP
#define BOARD_CPP
#include"board.h"
using namespace std;
class Board{
public:
    int size;
    int direction[3]={-1,0,1};
    int keyboard[10][10];               //keyboard用来表示数字
    int mask[10][10];                   //mask用来表示是否插旗图
    void initialization()
    {
        for (int i=0;i<9;i++){
            for (int j=0;j<9;j++){
                keyboard[i][j]=-1;     //Keyboard图未读到的数字为-1
                mask[i][j]=0;          //Mask图上0表示未插旗，1表示插旗
            }
        }
    }
    void mineCreate(){
        int x;
        int y;
        srand((unsigned)time(NULL));
        for (int i=0;i<9;i++){
            x=rand()%9;
            y=rand()%9;
            while (keyboard[x][y]==9){
                x=rand()%9;
                y=rand()%9;
            }
            keyboard[x][y]=9;
             //9 represent mine
        }
    }
    void printTrueNumber()
    {
        for (int i=0;i<9;i++)
        {
            for (int j=0;j<9;j++)
            {   if (mask[i][j]==0){           //对于不插旗的位置正常操作
                    if (keyboard[i][j]!=-1&&(keyboard[i][j]!=9)){
                        cout<<keyboard[i][j]<<" ";   //被翻过,不是雷的地方显示数字
                    }
                    else cout<<"# ";                 //没被翻过的地方显示#
                }
                else if (mask[i][j]==1)
                {   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
                    cout<<"*"<< " ";
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |FOREGROUND_RED |FOREGROUND_GREEN | FOREGROUND_BLUE);}  //插过旗的地方显示*
            }
            cout<<endl;
        }
        cout<<endl;
    }
    int calculateMine(int x,int y)
    {   int count=0;
        if (keyboard[x][y]==9) return 9;
        else{                                     //这个点不是雷
            if ((x!=0)&&(x!=8)&&(y!=0)&&(y!=8)){
                                 //如果这个点不在地图边界
                for (int i=0;i<3;i++){
                    for (int j=0;j<3;j++){
                        if (keyboard[x+direction[i]][y+direction[j]]==9){

                            count+=1;
                        }
                    }
                }
                keyboard[x][y]=count;}
            else if ((x==0)||(y==8)||(x==8)||(y==0)) //如果这个点在四个边上
                {

                for (int i=0;i<3;i++){
                    for (int j=0;j<3;j++){
                        if ((0<=x+direction[i])&&(0<=y+direction[j])&&(x+direction[i]<=8)&&(y+direction[j]<=8))
                            {
                            if (keyboard[x+direction[i]][y+direction[j]]==9){
                               count+=1;                        }
                            }
                        else continue;
                    }

                }
                }


        }
        keyboard[x][y]=count;
        return count;
    }
    int game(int x,int y)
    {
        int count=0;
        count=calculateMine(x,y);
        if (win()){
            cout<<"You win"<<endl;
            return -1;
        }
        if (count==9){
            cout<<"You lose"<<endl;
            return -1; //    -1 means game over
        }
        else if (count==0){
            expansion(x,y);
            return 0;
        }
        else return 0; // two situation return 0 means game continue
    }
    void expansion(int x,int y)
    {
        int count=0;
        for (int i=0;i<3;i++){
            for (int j=0;j<3;j++){
                if ((0<=x+direction[i])&&(0<=y+direction[j])&&(x+direction[i]<=8)&&(y+direction[j]<=8)&&((direction[i]!=0)||(direction[j]!=0))&&
                        (keyboard[x+direction[i]][y+direction[j]]==-1))  //要查找的周围的数没有超出边界，不是本身，而且没有被翻开过，do
                {
                    count=calculateMine(x+direction[i],y+direction[j]);
                    if (count==0)
                    {
                        expansion(x+direction[i],y+direction[j]);
                    }
                }
                else continue;
            }

        }
        return;
    }
    void printMineforFinal(){
        {   cout<<"Red X means the mine is found by you, Red M means the mine is not found"<<endl;
            for (int i=0;i<9;i++)
            {
                for (int j=0;j<9;j++)
                {   if (mask[i][j]==0){           //对于不插旗的位置正常操作
                        if (keyboard[i][j]!=-1&&(keyboard[i][j]!=9)){
                            cout<<keyboard[i][j]<<" ";   //被翻过,不是雷的地方显示数字
                        }
                        else if (keyboard[i][j]==9){   //没被插旗的所有雷显示红M
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
                            cout<<"M"<< " ";
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |FOREGROUND_RED |FOREGROUND_GREEN | FOREGROUND_BLUE);}
                        
                    
                        else cout<<"# ";                 //没被翻过的地方显示#
                    }
                    else if (mask[i][j]==1){
                        if (keyboard[i][j]==9){            //插过旗的雷显示红X
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
                            cout<<"X"<< " ";
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |FOREGROUND_RED |FOREGROUND_GREEN | FOREGROUND_BLUE);}
                        
                        else cout<<"# ";   //插旗没插对的地方不显示数字
                    };  
                }
                cout<<endl;
            }
            cout<<endl;
        }
    }
    bool win(){
        int count=0;
        for (int i=0;i<=8;i++){
            for (int j=0;j<=8;j++){
                if (keyboard[i][j]!=-1) count+=1;
            }
        }
        if (count>=81) return true;
        else return false;
    }

};
#endif // BOARD_CPP
