#include<iostream>
#include<graphics.h>
#define width_window 960
#define height_window 576
enum dotTypeEnum {SQUARE,CIRCLE};
dotTypeEnum chooseDot();
int main(){
    initwindow(width_window,height_window);
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
        outtextxy(width_window/2-90,height_window/2-100,"Choose one");
        setcolor(LIGHTBLUE);
        rectangle(300,300,400,400);
        circle(600,350,55);
        int x=mousex();
        int y=mousey();
        if(x>300&&x<400&&y>300&&y<400){
            setcolor(LIGHTRED);
            rectangle(300,300,400,400);
            int a,b;
            getmouseclick(WM_LBUTTONDOWN,a,b);
            if(a>300&&a<400&&b>300&&b<400){
                cleardevice();
                return SQUARE;
            }
        }
        if(x>545&&x<655&&y>295&&y<405){
            setcolor(LIGHTRED);
            circle(600,350,55);
            int a,b;
            getmouseclick(WM_LBUTTONDOWN,a,b);
            if(a>545&&a<655&&b>295&&b<405){
                cleardevice();
                return CIRCLE;
            }
        }
        delay(20);
    }
}
