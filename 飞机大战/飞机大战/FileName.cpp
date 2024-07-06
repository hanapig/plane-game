#pragma once
#include<iostream>
#include<Windows.h>
using namespace std;
#include <conio.h>//键盘输入
#include <ctime>//控制时间





typedef struct posenemy
{
    COORD position[2];//存坐标

};//定义一个数组，代表每敌机下标及其坐标
class Game
{
public:
    int menu();//菜单
    void SetPos(int a, int b);//设置坐标
    void drawPlane();//飞机创建
    void setplanepos(COORD centren);//传入飞机和敌机坐标，设置位置
    void planeMove(char x);//飞机移动
    void play();//执行
    void clearplane();//消除飞机
    void HideCursor();//隐藏光标
    void drawenemy();//生成敌人
    void posenemyplane(int num);//敌人位置
    void enemyposmove();//敌人移动
    void clearenemies();//清除敌人
    void movespeed();//移动速度
    bool judge(posenemy enemytest, COORD posjudge);//碰撞检测
    bool enemyjudge();//敌人是否碰到


};
int enemtime;//移动时间
clock_t lasttime = clock();  // 记录上一次更新时间
COORD pos[900];//位置坐标存储个数
COORD enemypos[900];//敌人坐标存储用于生成
posenemy enemy[8];//存每个敌人自身及坐标
bool judge(posenemy enemytest, COORD posjudge);

//设置坐标点位
void Game::SetPos(int a, int b)
{
    HANDLE hout;//句柄管理win资源
    COORD coord;//字符串在屏幕上的坐标
    coord.X = a;
    coord.Y = b;
    hout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hout, coord);//指向句柄设置坐标
}


//主菜单
int Game:: menu()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);//字体颜色
	system("title 飞 机 大 战");
	SetPos(55, 1);//设置文字坐标
	cout << "飞机大战";
	SetPos(30, 11);
	cout << "1.开始游戏";
	SetPos(30, 14);
	cout << "2. ESC";
    HideCursor();
    int choice = _getch();  
    return choice;//返回选择
}

//飞机图形
void Game::drawPlane()
{
    for (int i = 0; i < 9; i++)
    {
        SetPos(pos[i].X, pos[i].Y); 
        if (i != 5)
        {
            cout << "#";
        }
    }
}
//敌人飞机位置及生成
void Game::drawenemy()
{
    for (int i = 0; i < 8; i++)
    { // 每个敌机
        for (int j = 0; j < 1; j++) 
        { // 每个敌机的坐标点
            SetPos(enemy[i].position[j].X, enemy[i].position[j].Y);
            cout <<"**" ;

        }
    }
}


//敌军图形
void Game::posenemyplane(int num)
{
    for (int i=0;i<num;i++)
    {
        COORD baseposition;
        baseposition.X = rand() % 99; // 确保敌机不会超出屏幕边缘
        baseposition.Y = 1;  // 初始Y坐标

        // 设置敌机的左上角和右下角坐标
        enemy[i].position[0].X = baseposition.X;
        enemy[i].position[0].Y = baseposition.Y;

        enemy[i].position[1].X = baseposition.X+2 ;  // 右下角X坐标
        enemy[i].position[1].Y = baseposition.Y+2 ;  // 右下角Y坐标
        
    }
}

//敌人移动
void Game::enemyposmove()
{
    for (int i = 0; i < 8; i++) // 有8个敌人
    {
        int maxmove = 5;
        for (int j = 0; j < 2; j++)//两个坐标
            enemy[i].position[j].Y++;
        int move = rand() % (2 * maxmove + 1) - maxmove; // -maxmove 到 maxmove 之间的数

        for (int j = 0; j < 2; j++) {
            enemy[i].position[j].X += move;
            if (enemy[i].position[j].X < 0)
            {
                enemy[i].position[j].X = 0;  
            }
            if (enemy[i].position[j].Y >46)
            {
                clearenemies();
                enemy[i].position[j].Y = 0;
            }
            else if (enemy[i].position[j].X > 99)
            {
                enemy[i].position[j].X = 99;  
            }
        }

    }
}

//清除敌人
void Game::clearenemies() 
{
    for (int i = 0; i < 8; i++) 
    {
        for (int j = 0; j < 8; j++) 
        {  
            SetPos(enemy[i].position[j].X, enemy[i].position[j].Y);
            cout << "  ";  // 覆盖旧的敌机字符
        }
    }
}

//移动速度
void Game::movespeed()
{
    int enemtime ;//移动时间
    clock_t lasttime = clock();  // 记录上一次更新时间

}


//飞机图形摆放位置
void Game::setplanepos(COORD centren)
{
        pos[0].X = pos[7].X = centren.X;
        pos[1].X = centren.X - 2;
        pos[2].X = pos[6].X = centren.X - 1;
        pos[3].X = pos[8].X = centren.X + 1;
        pos[4].X = centren.X + 2;
        for (int i = 0; i <= 4; i++)
        {
            pos[i].Y = centren.Y;
        }
        for (int i = 6; i <= 8; i++)
        {
            pos[i].Y = centren.Y + 1;
        }
}

//隐藏光标
void Game:: HideCursor()
{
    CONSOLE_CURSOR_INFO cursor_info = { 1,0 };//第二个值0表示隐藏光标
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void ResizeConsole(int width, int height) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD newSize = { short(width), short(height) };

    SMALL_RECT rect = { 0, 0, short(width - 1), short(height - 1) };

    // 设置屏幕缓冲区大小
    SetConsoleScreenBufferSize(hOut, newSize);
    // 设置窗口大小
    SetConsoleWindowInfo(hOut, TRUE, &rect);
}
//移动飞机

void Game::planeMove(char x)
{
    ResizeConsole(100, 50);
    if (x == 75)
    {
        if (pos[1].X >1)//左边界
        {
            for (int i = 0; i <= 9; i++)
            {
                pos[i].X -= 2;
            }
        }
    }

    if (x == 80)
    {
        if (pos[7].Y <49)//下边界
        {
            for (int i = 0; i <= 9; i++)
            {
                pos[i].Y += 1;
            }
        }
    }

    if (x == 77 && (pos[4].X <99))//右边界
    {
        for (int i = 0; i <= 9; i++)
        {
            pos[i].X += 2;
        }
    }

    if (x == 72 && (pos[0].Y >0))//上边界
    {
        for (int i = 0; i <= 9; i++)
        {
            pos[i].Y -= 1;
        }
    }
}

//消除飞机
 void Game:: clearplane() {
     for (int i = 0; i < 9; i++)
     {
         SetPos(pos[i].X, pos[i].Y);
         cout << " ";
     }

}

//碰撞
  bool Game:: judge(posenemy posenemes, COORD posjudge) 
 {
      if ((posjudge.X >= posenemes.position[0].X) && (posjudge.X <= posenemes.position[1].X) //检测四个方向
          &&(posjudge.Y >= posenemes.position[0].Y) && (posjudge.Y <= posenemes.position[1].Y))
     {
         return true;
     }
     return false;
 }

 //敌机检测
bool Game:: enemyjudge()
 {
     for (int i = 0; i < 8; i++)
     {
         for (int j = 0; j < 9; j++)
         {
             if (judge(enemy[i], pos[j]))
             {
                 SetPos(45, 20);
                 cout << "  结束,5s后自动返回菜单      ";
                 return true;
             }
         }
     }
     return false;
 }

//游戏进行
 void Game::play()
 {
     game_start:
     int enemtime = 100;
     bool game = false;
     bool run = true;
     while (run)
     {
         if (_kbhit())
         {

             COORD centren;
             centren.X = 55;
             centren.Y = 40;
             char x = _getch();
             switch (x)
             {
             case '1':
                 system("cls");
                 game = true;
                 setplanepos(centren);//传入坐标
                 posenemyplane(8);
                 HideCursor();
                 break;
             case '2':
                 exit;
                 break;
                 case 75:
                 case 77:
                 case 72:
                 case 80: //移动方向符
                     HideCursor();
                     clearplane();//消除飞机
                     planeMove(x); // 飞机移动
                     drawPlane(); // 重绘飞机
                 }
             if (enemyjudge())
             {
                 Sleep(5000);
                 system("cls");
                 break;
             }
         }
         if (game && (clock() - lasttime ) >enemtime ) //更新时间
         {
             clearenemies();
             enemyposmove();
             drawenemy();
             lasttime = clock();
         }

     }
 }

int main()
{
    srand(time(NULL));//初始不一样
    Game game;//实例化'
    int re;
    do 
    {
        re = game.menu();
        if (re == '1')
        {
            game.play();
        }
    } while (re != '2');
    return 0;
}
