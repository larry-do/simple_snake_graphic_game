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
        if(getScore(a,b)){
            b.initFruit(LIGHTGREEN);
            score+=10;
        }
        if((score%70==0) && c.kolor()!=LIGHTCYAN && score!=0){
            c.initFruit(LIGHTCYAN);
        }
        if(getScore(a,c)&&c.kolor()==LIGHTCYAN){
            c.initFruit(CYAN);
            score+=30;
        }
        if(a.isDead()){
            goto backToMenu;
        }
        showScore(score);
        if(c.kolor()==LIGHTCYAN) c.show();
        b.show();
        a.show();
        Sleep(level);
        cleardevice();
    }
    exit(42);
    return 1;
}
