/*
TOO MANY BUGS :((
DO NOT RELEASE
*/
#include<graphics.h>
#include<iostream>
#include<vector>
#define height_window 576
#define width_window 960
int adjustLevel();
int level=0;
class levelClass {
public:
    int value;
    int left;
    int top;
    int right;
    int bottom;
    void init(int _value,int _left,int _top,int _right,int _bottom){
        value=_value;
        left=_left;
        top=_top;
        right=_right;
        bottom=_bottom;
    }
    void show(){
        setcolor(WHITE);
        rectangle(left,top,right,bottom);
    }
    void showChoose(){
        setcolor(RED);
        rectangle(left,top,right,bottom);
    }
};
///////////////////////////////////////////////
int main(){
    initwindow(width_window,height_window);
    std::cout<<adjustLevel();
    getch();
    return 1;
}
/////////////////////////////////////////////////
int adjustLevel(){
    std::vector<levelClass> a;
    for(int i=0;i<10;i++){
        levelClass b;
        b.init((11-i)*10,300+i*30,400-i*20,330+i*30,450);
        a.push_back(b);
    }
    while(true){
        setcolor(WHITE);
        settextstyle(3,0,3);
        outtextxy(390,150,"Choose level");
        for(int i=0;i<10;i++)
            a[i].show();
        for(int i=9;i>=0;i--){
            int x = mousex();
            int y = mousey();
            if(x>a[i].left&&x<a[i].right&&y>a[i].top&&y<a[i].bottom){
                for(int j=0;j<=i;j++){
                    a[j].showChoose();
                }
            }
        }
        int m,n;
        getmouseclick(WM_LBUTTONDOWN,m,n);
        for(int i=0;i<10;i++){
            if(m>a[i].left&&m<a[i].right&&n>a[i].top&&n<a[i].bottom){
                cleardevice();
                return a[i].value;
            }
        }
        delay(50);
    }
}
