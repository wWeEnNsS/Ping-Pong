#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#define mapWidth 65
#define mapHeight 25

char mas[mapHeight][mapWidth+1];

typedef struct sRacket{
    int x, y;
    int w;
}TRacket;

TRacket racket1Player;
TRacket racket2Player;

void InitRacket(TRacket* racket1Player, TRacket* racket2Player)
{
    (*racket1Player).w = 7; // width racket
    (*racket1Player).x = (mapWidth - (*racket1Player).w) / 2; // помешение ракетки в карту
    (*racket1Player).y = mapHeight - 1;
    (*racket2Player).w = 7;
    (*racket2Player).x = (mapWidth - (*racket2Player).w) / 2;
    (*racket2Player).y = mapHeight - 24;
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
    InitRacket(&racket1Player, &racket2Player);
    do
    {
         setcur(0, 0);
         ClearMap();

         PutRacket(&racket1Player, &racket2Player);

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

         Sleep(10);
    } while(GetKeyState(VK_ESCAPE) >= 0);
    return 0;
}
