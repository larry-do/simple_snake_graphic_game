#include<iostream>
#include"class.h"
int main(){
    initwindow(width_window,height_window,"Snake Game");
    srand(time(NULL));
    snake a;
    fruit b;
    backToMenu:
    a.init();
    b.initFruit();
    int score=0;
    Sleep(1000);
    while(true){
        showScore(score);
        b.show();
        if(a.controlAndMove()){
            goto backToMenu;
        }
        a.show();
        if(getScore(a,b)){
            b.initFruit();
            score+=10;
        }
        if(a.isDead()){
            system("Pause");
        }
        Sleep(level);
        cleardevice();
    }
    getch();
    return 1;
}
