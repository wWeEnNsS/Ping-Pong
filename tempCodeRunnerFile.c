#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <math.h>
#include <string.h>
#define mapWidth 65
#define mapHeight 25

char mas[mapHeight][mapWidth+1];

typedef struct sRacket{
    int x, y;
    int w;
}TRacket;

typedef struct sBall{
    float x, y;
    int ix, iy;
    float alfa;
    float speed;
} TBall;

TRacket racket1Player;
TRacket racket2Player;

TBall ball;

void initBall(TBall* ball)
{
    (*ball).x = 2;
    (*ball).y = 2;

    (*ball).alfa = -1;
    (*ball).speed = 0.5;
}

void PutBall(TBall* ball)
{
    mas[(*ball).iy][(*ball).ix] = '*';
}

void moveBall(float xP, float yP)
{
     ball.x = xP;
     ball.y = yP;
     ball.ix = (int)round(ball.x);
     ball.iy = (int)round(ball.y);
}

void AutoMoveBall()
{
    if (ball.alfa < 0)
    {
        ball.alfa += M_PI*2;
    }
    if (ball.alfa > M_PI*2)
    {
        ball.alfa -= M_PI*2;
    }
    TBall bl = ball;
    moveBall(ball.x + cos(ball.alfa) * ball.speed
             ,ball.y + sin(ball.alfa) * ball.speed);
    if ((mas[ball.iy][ball.ix] == '#') || (mas[ball.iy][ball.ix] == '='))
    {
        if ((ball.ix != bl.ix) && (ball.iy != bl.iy))
        {
            if (mas[bl.iy][ball.ix] == mas[ball.iy][bl.ix])
            {
                bl.alfa = bl.alfa + M_PI;
            }else
            {
                if (mas[bl.iy][ball.ix] == '#')
                {
                    bl.alfa = (2*M_PI - bl.alfa);
                }else
                {
                    bl.alfa = (2*M_PI - bl.alfa);
                }
            }
        }else if (ball.iy == bl.iy)
        {
            bl.alfa = (2*M_PI - bl.alfa) + M_PI;
        }else
        {
            bl.alfa = (2*M_PI - bl.alfa);
        }
    }
}

void InitRacket(TRacket* racket1Player, TRacket* racket2Player)
{
    (*racket1Player).w = 7; // width racket
    (*racket1Player).x = (mapWidth - (*racket1Player).w) / 2; // помешение ракетки в карту
    (*racket1Player).y = mapHeight-2;
    (*racket2Player).w = 7;
    (*racket2Player).x = (mapWidth - (*racket2Player).w) / 2;
    (*racket2Player).y = mapHeight - 23;
}

void PutRacket(TRacket* racket1Player, TRacket* racket2Player)
{
    for(int i = (*racket1Player).x; i < (*racket1Player).x + (*racket1Player).w; i++)
    {
        mas[(*racket1Player).y][i] = '=';
    }

    for (int i = (*racket2Player).x; i < (*racket2Player).x + (*racket2Player).w; i++)
    {
        mas[(*racket2Player).y][i] = '=';
    }
}

void ClearMap()
{
    for(int i = 0; i < mapWidth; i++)
    {
        mas[0][i] = '#';
    }
    mas[0][mapWidth] = '\0';

    strncpy(mas[1], mas[0], mapWidth+1);
    for(int i = 1; i < mapWidth-1; i++)
    {
        mas[1][i] = ' ';
    }

    for(int i = 2; i < mapHeight; i++)
    {
        strncpy(mas[i], mas[1], mapWidth+1);
    }
}

void ShowMap()
{
    printf("\n");
  //mas[mapHeight-1][mapWidth-1] = '\0';
    for (int i = 0; i < mapHeight; i++)
    {
        printf("%s", mas[i]);
        if (i < mapHeight - 1)
        {
            printf("\n");
        }
    }
}

void moveRacketFor1Player(int xP)
{
    racket1Player.x = xP;
    if (racket1Player.x < 1)
    {
        racket1Player.x = 1;
    }
    if (racket1Player.x + racket1Player.w >= mapWidth)
    {
        racket1Player.x = mapWidth - 1 - racket1Player.w;
    }

}

void moveRacketFor2Player(int xP)
{
    racket2Player.x = xP;
    if (racket2Player.x < 1)
    {
        racket2Player.x = 1;
    }
    if (racket2Player.x + racket2Player.w >= mapWidth)
    {
        racket2Player.x = mapWidth - 1 - racket2Player.w;
    }
}

void setcur(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int main()
{
    BOOL run = FALSE;
    InitRacket(&racket1Player, &racket2Player);
    initBall(&ball);
    do
    {
         setcur(0, 0);

         if (run)
         {
             AutoMoveBall();
         }

         ClearMap();

         PutRacket(&racket1Player, &racket2Player);
         PutBall(&ball);
         ShowMap();

         if (GetKeyState('A') < 0)
         {
             moveRacketFor1Player(racket1Player.x - 1);
         }else if (GetKeyState('D') < 0)
         {
             moveRacketFor1Player(racket1Player.x + 1);
         }

         if (GetKeyState('J') < 0)
         {
             moveRacketFor2Player(racket2Player.x - 1);
         }else if (GetKeyState('L') < 0)
         {
             moveRacketFor2Player(racket2Player.x + 1);
         }
         if (GetkeyState('W') < 0)
         {
             run = TRUE;
         }
         if (!run)
         {
             moveBall(racket1Player.x + racket1Player.w / 2, racket1Player.y - 1);
         }

         Sleep(10);
    } while(GetKeyState(VK_ESCAPE) >= 0);
    return 0;
}
