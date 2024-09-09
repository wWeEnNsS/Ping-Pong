#include <stdio.h>

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
        printf("%s\n", mas[i]);
    }
}

int main()
{

    InitRacket(&racket);

    ClearMap();

    PutRacket(&racket);

    ShowMap();
    return 0;
}
