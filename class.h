#define _WIN32_WINNT 0x0500
#include<graphics.h>
#include<vector>
#include<cctype>
#include<ctime>
#include<cstring>
#include<cstdio>
#include<windows.h>
#define height_window 576
#define width_window 960
bool checkKey(int key){
    return GetAsyncKeyState(key);
}
///////////////////////////////////////////////////////
enum statusEnum {UP,DOWN,RIGHT,LEFT};
enum dotTypeEnum {SQUARE,CIRCLE};
///////////////////////////////////////////////////////
int level = 50;
dotTypeEnum dotType = SQUARE;
///////////////////////////////////////////////////////
class squareDot{
private:
    int a;
    int x,y;
    colors color;
public:
    void init(int _x,int _y,int _a,colors _color);
    int X();
    int Y();
    colors kolor();
    void setPos(int _x,int _y);
    void show();
};
void squareDot::init(int _x,int _y,int _a,colors _color){
    x=_x;
    y=_y;
    a=_a;
    color=_color;
}
int squareDot::X(){
    return x;
}
int squareDot::Y(){
    return y;
}
colors squareDot::kolor(){
    return color;
}
void squareDot::setPos(int _x,int _y){
    x=_x;
    y=_y;
}
void squareDot::show(){
    if(dotType==SQUARE){
        setcolor(color);
        rectangle(x-a-1,y-a-1,x+a+1,y+a+1);
        rectangle(x-a,y-a,x+a,y+a);
    }
    else{
        setcolor(color);
        circle(x,y,a);
        circle(x,y,a+1);
    }
}
///////////////////////////////////////////////////////
class fruit;
class snake {
private:
    int x,y;
    statusEnum status;
    std::vector<squareDot> body;
public:
    void init();
    void show();
    bool controlAndMove();
    bool isDead();
    friend bool getScore(snake &a, fruit &b);
};
void snake::init(){
    squareDot a;
    x=48;
    y=16;
    a.init(x,y,15,LIGHTRED);
    body.push_back(a);
    a.init(x-32,y,15,LIGHTBLUE);
    body.push_back(a);
    a.init(x-64,y,15,LIGHTBLUE);
    body.push_back(a);
    status=RIGHT;
}
void snake::show(){
    for(unsigned int i=0;i<body.size();i++){
        body[i].show();
    }
}
bool snake::controlAndMove(){
    for(int i=body.size()-1;i>0;i--){
        body[i].setPos(body[i-1].X(),body[i-1].Y());
    }
    if(status==UP)
        body[0].setPos(x,y-=32);
    if(status==DOWN)
        body[0].setPos(x,y+=32);
    if(status==LEFT)
        body[0].setPos(x-=32,y);
    if(status==RIGHT)
        body[0].setPos(x+=32,y);
    if(x>=width_window)
        body[0].setPos(x=16,y);
    if(x<=0)
        body[0].setPos(x=width_window-16,y);
    if(y>=height_window)
        body[0].setPos(x,y=16);
    if(y<=0)
        body[0].setPos(x,y=height_window-16);
    if(checkKey(VK_RIGHT)&&status!=LEFT) status=RIGHT;
    if(checkKey(VK_LEFT)&&status!=RIGHT) status=LEFT;
    if(checkKey(VK_UP)&&status!=DOWN) status=UP;
    if(checkKey(VK_DOWN)&&status!=UP) status=DOWN;
    if(GetAsyncKeyState(VK_ESCAPE)){
        setcolor(RED);
        settextstyle(3,0,2);
        outtextxy(width_window/2-100,height_window/2,"Back to menu...");
        delay(2000);
        body.clear();
        return true;
    }
    if(GetAsyncKeyState(VK_LCONTROL)){
        level+=10;
        PlaySoundA("data/speedup.wav",NULL,SND_ASYNC);
    }
    if(GetAsyncKeyState(VK_RCONTROL)){
        if(level>10) level-=10;
        PlaySoundA("data/speedup.wav",NULL,SND_ASYNC);
    }
    if(kbhit()){
        char key=getch();
        if('T'==toupper(key)){
            if(dotType==SQUARE) dotType=CIRCLE;
            else dotType=SQUARE;
            PlaySoundA("data/change.wav",NULL,SND_ASYNC);
        }
        if('D'==toupper(key)&&status!=LEFT) status=RIGHT;
        if('A'==toupper(key)&&status!=RIGHT) status=LEFT;
        if('W'==toupper(key)&&status!=DOWN) status=UP;
        if('S'==toupper(key)&&status!=UP) status=DOWN;
    }
    return false;
}
bool snake::isDead(){
    for(unsigned int i=1;i<body.size();i++){
        if(x==body[i].X()&&y==body[i].Y()){
            PlaySoundA("data/dead.wav",NULL,SND_ASYNC);
            body.clear();
            return true;
        }
    }
    return false;
}
///////////////////////////////////////////////////////
class fruit:public squareDot{
public:
    void initFruit(colors _color);
    friend bool getScore(snake &a, fruit &b);
};
void fruit::initFruit(colors _color){
    int _x=16+(rand()%29)*32;
    int _y=16+(rand()%17)*32;
    squareDot::init(_x,_y,15,_color);
}
///////////////////////////////////////////////////////
bool getScore(snake &a,fruit &b){
    if(a.x==b.X()&&a.y==b.Y()&&(b.kolor()==LIGHTCYAN||b.kolor()==LIGHTGREEN)){
        PlaySoundA("data/getscore.wav",NULL,SND_ASYNC);
        squareDot c;
        c.init(0,0,15,LIGHTBLUE);
        a.body.push_back(c);
        return true;
    }
    return false;
}
///////////////////////////////////////////////////////
void showScore(int score){
    settextstyle(8,0,2);
    outtext("Score: ");
    char a[10];
    sprintf(a,"%d", score);
    outtext(a);
}
///////////////////////////////////////////////////////
