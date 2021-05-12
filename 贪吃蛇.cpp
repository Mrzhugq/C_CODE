#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>

#define frame_height 30
#define frame_width 50
#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'

int i,j,k,sp,score;
char ch=UP,state=UP,choo,n;
int grow=0;

struct Food
{
    int x;
    int y;
} food;

struct Snake
{
    
    int x[100];
    int y[100];
    int len;
    int speed;
} snake;

void map(void);
void update_food(void);
void move_snake(void);
int alive(void);
void get_speed(void);
void gotoxy(int x,int y);

int main()
{
    do
    {
        score=0;
        printf("请选择游戏困难度 : \n1:简单 \t2:中等  3:困难\n");
        n=getch();
        switch(n)
        {
        case '1':
        {
            sp=300;
            break;
        }
        case '2':
        {
            sp=230;
            break;
        }
        case '3':
        {
            sp=180;
            break;
        }
        default:
        {
            printf("Congratulations!Welcome to Devil's difficulty\n");
            sp=120;
            break;
        }
        }
        system("cls");
        map();
        while(1)
        {
            update_food();
            get_speed();
            move_snake();
            Sleep(snake.speed);
            if(!(alive()))
            {
                break;
            }
        }
        printf("Game Over!\n");
        printf("1:Restart\t2:exit");
        choo=getch();
    }
    while(choo=='1');
    return 0;
}
void map()
{
    srand(time(NULL));
    food.x=rand()%(frame_height-2)+1;
    food.y=rand()%(frame_width-2)+1; 
    gotoxy(food.x,food.y);
    printf("$");
    snake.x[0]=frame_height/2;
    snake.y[0]=frame_width/2;
    gotoxy(snake.x[0],snake.y[0]);
    printf("@");
    snake.len=3;
    snake.speed=200;
    for(k=1; k<snake.len; k++)
    {
        snake.x[k]=snake.x[k-1]+1;
        snake.y[k]=snake.y[k-1];
        gotoxy(snake.x[k],snake.y[k]);
        printf("@");
    }
    for(j=0; j<frame_width; j++)
    {
        gotoxy(0,j);
        printf("#");
        gotoxy(frame_height-1,j);
        printf("#");
    }
    for(i=0; i<frame_height-1; i++)
    {
        gotoxy(i,0);
        printf("#");
        gotoxy(i,frame_width-1);
        printf("#");
    }
    gotoxy(2,frame_width+3);
    if(n=='1') printf("Difficulty:   easy");
    else if(n=='2') printf("Difficulty:   middle");
    else if(n=='3') printf("Difficulty:   difficult");
    else printf("Welcome to the Devil's difficulty");
    gotoxy(4,frame_width+3);
    printf("UP:   w");
    gotoxy(6,frame_width+3);
    printf("DOWN: s");
    gotoxy(8,frame_width+3);
    printf("LEFT: a");
    gotoxy(10,frame_width+3);
    printf("RIGHT:d");
    gotoxy(12,frame_width+3);
    printf("Your score:%d",score);
    gotoxy(28,frame_width+3);
    printf("那青新制作");
}

void update_food()
{
    if(snake.x[0]==food.x&&snake.y[0]==food.y)
    {
        score+=10;
        gotoxy(12,frame_width+3);
        printf("Your score:%d",score);
        srand(time(NULL));
        int flag=1;
        do
        {
        food.x=rand()%(frame_height-2)+1;
        food.y=rand()%(frame_width-2)+1;
        for(i=0; i<snake.len; i++)
        {
            if(food.x==snake.x[i]&&food.y==snake.y[i])
            {
                flag=0;
                break;
            }
        }
        }
        while(flag==0);
        gotoxy(food.x,food.y);
        printf("$");
        snake.len++;
        grow=1;
    }
}
void move_snake()
{
    while(kbhit())
    {
        ch=getch();
    }
    if(!grow)
    {
        gotoxy(snake.x[snake.len-1],snake.y[snake.len-1]);
        printf(" ");
    }
    for(k=snake.len-1; k>0; k--)
    {
        snake.x[k]=snake.x[k-1];
        snake.y[k]=snake.y[k-1];
    }
    switch(ch)
    {
    case UP:
    {
        if(state==DOWN)
        {
            snake.x[0]++;
            break;
        }
        else
        {
            snake.x[0]--;
            state=UP;
            break;
        }
    }
    case DOWN:
    {
        if(state==UP)
        {
            snake.x[0]--;
            break;
        }
        else
        {
            snake.x[0]++;
            state=DOWN;
            break;
        }
    }
    case LEFT:
    {
        if(state==RIGHT)
        {
            snake.y[0]++;
            break;
        }
        else
        {
            snake.y[0]--;
            state=LEFT;
            break;
        }
    }
    case RIGHT:
    {
        if(state==LEFT)
        {
            snake.y[0]--;
            break;
        }
        else
        {
            snake.y[0]++;
            state=RIGHT;
            break;
        }
    }
    default:
    {
        if(state==DOWN)
        {
            snake.x[0]++;
            break;
        }
        else if(state==UP)
        {
            snake.x[0]--;
            break;
        }
        else if(state==LEFT)
        {
            snake.y[0]--;
            break;
        }
        else if(state==RIGHT)
        {
            snake.y[0]++;
            break;
        }

    }
    }
    gotoxy(snake.x[0],snake.y[0]);
    printf("@");
    grow=0;
    gotoxy(frame_height,0);
}
int alive(void)
{
    if(snake.x[0]==0||snake.x[0]==frame_height-1||snake.y[0]==0||snake.y[0]==frame_width-1)
        return 0;
    for(k=1; k<snake.len; k++)
    {
        if(snake.x[0]==snake.x[k]&&snake.y[0]==snake.y[k])
            return 0;
    }
    return 1;
}
void get_speed()
{
    if(snake.len<=6)
        snake.speed=sp;
    else if(snake.len<=10)
        snake.speed=sp-20;
    else if(snake.len<=20)
        snake.speed=sp-50;
    else if(snake.len<=30)
        snake.speed=sp-60;
    else
        snake.speed=sp-70;
}

void gotoxy(int x,int y)
{
    HANDLE hout;
    COORD cor;
 
    hout=GetStdHandle(STD_OUTPUT_HANDLE);
    cor.X=y;
    cor.Y=x;
    SetConsoleCursorPosition(hout,cor);
}
