#include<iostream>
#include"class.h"
int main(){
    initwindow(width_window,height_window,"Snake Game");
    HWND myConsole = GetConsoleWindow();
    ShowWindow(myConsole,1);
    srand(time(NULL));
    snake a;
    fruit b;
    fruit c;
    backToMenu:
    a.init();
    b.initFruit(LIGHTGREEN);
    c.initFruit(CYAN);
    int score=0;
    Sleep(1000);
    while(true){
        if(a.controlAndMove()){
            goto backToMenu;
        }
        a.show();//mỗi lần làm gì với a thì in ra luôn. để khỏi trễ hình gây nhấp nháy
        if(getScore(a,b)){
            b.initFruit(LIGHTGREEN);
            score+=10;
        }
        b.show();//mỗi lần làm gì với b thì in ra luôn. để khỏi trễ hình gây nhấp nháy
        if((score%70==0) && c.kolor()!=LIGHTCYAN && score!=0){
            c.initFruit(LIGHTCYAN);
        }
        if(getScore(a,c)&&c.kolor()==LIGHTCYAN){
            c.initFruit(CYAN);
            score+=30;
        }
        if(c.kolor()==LIGHTCYAN) c.show();//mỗi lần làm gì với c thì in ra luôn. để khỏi trễ hình gây nhấp nháy
        if(a.isDead()){
            goto backToMenu;
        }
        showScore(score);//phải in ra sau cùng để không bị nhấp nháy snake. Tuy bị nhấp nháy score
        Sleep(level);
        cleardevice();
    }
    exit(42);
    return 1;
}
