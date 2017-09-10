#include<iostream>
#include<string>
#include<sstream>
#include<graphics.h>
#include<windows.h>
#define width_window 960
#define height_window 576
bool credits();
int main(){
    initwindow(width_window,height_window);
    credits();
    getch();
    return 1;
}
bool credits(){
    float x=width_window/2-170;
    float y=height_window/2;
    while(true){
        settextstyle(4,0,2);
        outtextxy(x,y,"Credit: Dou Ding Nyat");
        if(kbhit()){
            char c=getch();
            if(c=='e'||c=='E'){
                cleardevice();
                return true;
            }
        }
    }
}
