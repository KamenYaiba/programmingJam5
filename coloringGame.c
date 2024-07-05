#include <stdio.h>
#include <stdlib.h>
#define UNCOLORABLE 'x'

int colorable(char **grid, int d, int *ri, int *ci);

//page 12 in the PDF
int main()
{
    int d = 3;
    int ri[] = {2, 2, 1};
    int ci[] = {3, 1, 1};
    char *grid[] = 
    {"000",
     "0x0",
     "000"};

    printf("%d", colorable(grid, d, ri, ci)); //output: 1
}


int colorable(char **grid, int d, int *ri, int *ci)
{
    int colorableInRows[d];
    int colorableInCols[d];
    for(int i = 0; i < d; i++)
        colorableInRows[i] = colorableInCols[i] = d;

    for(int i = 0; i < d; i++)
    {
        for(int j = 0; j < d; j++)
        {
            if(grid[i][j] == UNCOLORABLE)
            {
                colorableInRows[i]--;
                colorableInCols[j]--;
            }
        }
    }

    for(int i = 0; i < d; i++)
    {
        if(ri[i] > colorableInRows[i] || ci[i] > colorableInCols[i])
            return 0;
    }
    return 1;
}