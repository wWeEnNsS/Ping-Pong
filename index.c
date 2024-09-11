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

TRacket racket;
void InitRacket(TRacket* racket)
{
    (*racket).w = 7; // width racket
    (*racket).x = (mapWidth - (*racket).w) / 2; // помешение ракетки в карту
    (*racket).y = mapHeight - 1;
}

void PutRacket(TRacket* racket)
{
    for(int i = (*racket).x; i < (*racket).x + (*racket).w; i++)
    {
        mas[(*racket).y][i] = '=';
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

void moveRacket(int xP)
{
    racket.x = xP;
    if (racket.x < 1)
    {
        racket.x = 1;
    }
    if (racket.x + racket.w >= mapWidth)
    {
        racket.x = mapWidth - 1 - racket.w;
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
    InitRacket(&racket);
    do
    {
         setcur(0, 0);
         ClearMap();

         PutRacket(&racket);

         ShowMap();

         if (GetKeyState('A') < 0)
         {
             moveRacket(racket.x - 1);
         }
         if (GetKeyState('D') < 0)
         {
             moveRacket(racket.x + 1);
         }

    } while(GetKeyState(VK_ESCAPE) >= 0);
    return 0;
}