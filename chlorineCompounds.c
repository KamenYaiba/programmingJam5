#include <stdio.h>
#include <math.h>
#define X 0
#define Y 1


int* chlorineCompounds(int pX, int pY, int pZ, int L);

//Page 2 in the PDF
int main()
{
    int *ans = chlorineCompounds(50, 30, 40, 10);
    printf("%d %d", ans[X], ans[Y]); //output: 5 5
}


/*
a(pX) + b(pY) = pZ
a + b = 1.0

therefore: b = |(pX - pZ) / (pY - pX)|
*/ 

int* chlorineCompounds(int pX, int pY, int pZ, int L) //returns {-1, -1} if no solution
{
    static int result[] = {-1, -1};

    if( (pZ < pX && pZ < pY) || (pZ > pX && pZ > pY) ) return result;

    float b = fabsf( ((float)pX - pZ) / ((float)pY - pX) );
    float a = 1 - b;
    a*=L;
    b*=L;

    result[X] = round(a);
    result[Y] = round(b);

    return result;
}


