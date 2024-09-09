#include <stdio.h>

#define mapWidth 65
#define mapHeight 25

char mas[mapHeight][mapWidth+1];

typedef struct sRacket
{
    int x, y;
}TRacket;

void ClearMap()
{
    for (int i = 0; i < mapWidth; i++)
    {
        
    }
}

void ShowMap()
{
    mas[mapHeight-1][mapWidth-1] = '\0';
}

int main()
{
    
    return 0;
}