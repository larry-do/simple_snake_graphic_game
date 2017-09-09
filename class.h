#include<graphics.h>
#include<vector>
#include<cctype>
#include<ctime>
#include<cstring>
#include<cstdio>
#include<windows.h>
#define height_window 704
#define width_window 1280
////////////////////////////////////////////////////////////////////////
enum statusEnum {UP,DOWN,RIGHT,LEFT};
enum gameTypeEnum {NO_BORDER,BORDER};
enum dotTypeEnum {SQUARE,CIRCLE};
////////////////////////////////////////////////////////////////////////
int level = 50;
gameTypeEnum gameType = NO_BORDER;
dotTypeEnum dotType = SQUARE;
////////////////////////////////////////////////////////////////////////
class squareDot{
private:
    int a;
    int x,y;
    colors color;
public:
    void init(int _x,int _y,int _a,colors _color);
    int X();
    int Y();
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
////////////////////////////////////////////////////////////////////////
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
    x=48;
    y=16;
    squareDot a;
    a.init(x,y,15,LIGHTRED);
    body.push_back(a);
    a.init(x-32,y,15,LIGHTBLUE);
    body.push_back(a);
    a.init(x-64,y,15,LIGHTBLUE);
    body.push_back(a);
    status=RIGHT;
}
void snake::show(){
    for(int i=0;i<body.size();i++){
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
    if(gameType == NO_BORDER){
        if(x>=width_window)
            body[0].setPos(x=16,y);
        if(x<=0)
            body[0].setPos(x=1280-16,y);
        if(y>=height_window)
            body[0].setPos(x,y=16);
        if(y<=0)
            body[0].setPos(x,y=704-16);
    }
    if(kbhit()){
        char key=getch();
        if('W'==toupper(key)&&status!=DOWN) status=UP;
        if('S'==toupper(key)&&status!=UP) status=DOWN;
        if('A'==toupper(key)&&status!=RIGHT) status=LEFT;
        if('D'==toupper(key)&&status!=LEFT) status=RIGHT;
        if('P'==toupper(key)){
            setcolor(RED);
            settextstyle(3,0,2);
            outtextxy(width_window/2-200,height_window/2,"Game paused. Press any key to continue...");
            system("pause");
        }
        if('I'==toupper(key)){
            setcolor(RED);
            settextstyle(3,0,2);
            outtextxy(width_window/2-100,height_window/2,"Restarting...");
            delay(2000);
            exit(42);
        }
        if('O'==toupper(key)){
            setcolor(RED);
            settextstyle(3,0,2);
            outtextxy(width_window/2-100,height_window/2,"Back to menu...");
            delay(2000);
            body.clear();
            return true;
        }
        if('T'==toupper(key)){
            if(dotType==SQUARE) dotType=CIRCLE;
            else dotType=SQUARE;
            PlaySoundA("change.wav",NULL,SND_ASYNC);
        }
        if('R'==toupper(key)){
            if(gameType==BORDER) gameType=NO_BORDER;
            else gameType=BORDER;
            PlaySoundA("change.wav",NULL,SND_ASYNC);
        }
        if('Y'==toupper(key)){
            level+=10;
            PlaySoundA("speedup.wav",NULL,SND_ASYNC);
        }
        if('U'==toupper(key)){
            if(level>10) level-=10;
            PlaySoundA("speedup.wav",NULL,SND_ASYNC);
        }
    }
    return false;
}
bool snake::isDead(){
    for(int i=1;i<body.size();i++){
        if(x==body[i].X()&&y==body[i].Y()){
            PlaySoundA("dead.wav",NULL,SND_ASYNC);
            return true;
        }
    }
    if(gameType==BORDER){
        if(x<=0||x>=width_window||y<=0||y>=height_window){
            PlaySoundA("dead.wav",NULL,SND_ASYNC);
            return true;
        }
    }
    return false;
}
//////////////////////////////////////////////////////
class fruit:public squareDot{
public:
    void initFruit();
    friend bool getScore(snake &a, fruit &b);
};
void fruit::initFruit(){
    int _x=16+(rand()%39)*32;
    int _y=16+(rand()%21)*32;
    squareDot::init(_x,_y,15,LIGHTGREEN);
}
///////////////////////////////////////////////////////
bool getScore(snake &a,fruit &b){
    if(a.x==b.X()&&a.y==b.Y()){
        PlaySoundA("getscore.wav",NULL,SND_ASYNC);
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
