#include<iostream>
#include<graphics.h>
enum dotTypeEnum {SQUARE,CIRCLE};
dotTypeEnum chooseDot();
int main(){
    initwindow(1280,704);
    dotTypeEnum dotType;
    dotType = chooseDot();
    while(true){
    };
    getch();
    return 1;
}
dotTypeEnum chooseDot(){
    cleardevice();
    while(true){
        setcolor(WHITE);
        settextstyle(4,0,2);
        outtextxy(120,60,"Choose one");
        setcolor(LIGHTBLUE);
        rectangle(100,150,150,200);
        rectangle(101,151,149,199);
        circle(300,175,25);
        circle(300,175,26);
        int x=mousex();
        int y=mousey();
        if(x>100&&x<150&&y>150&&y<200){
            setcolor(LIGHTRED);
            rectangle(100,150,150,200);
            rectangle(101,151,149,199);
            int a,b;
            getmouseclick(WM_LBUTTONDOWN,a,b);
            if(a>100&&a<150&&b>150&&b<200){
                cleardevice();
                return SQUARE;
            }
        }
        if(x>275&&x<325&&y>150&&y<200){
            setcolor(LIGHTRED);
            circle(300,175,25);
            circle(300,175,26);
            int a,b;
            getmouseclick(WM_LBUTTONDOWN,a,b);
            if(a>275&&a<325&&b>150&&b<200){
                cleardevice();
                return CIRCLE;
            }
        }
        delay(20);
    }
}
