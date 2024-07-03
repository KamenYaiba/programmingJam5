#include <stdio.h>

#define M 10
#define N 8

#define DEAD_END 100 
#define FRONT 0
#define RIGHT 1
#define BACK 2
#define LEFT 3

int min(int *arr, int n);
void printPaths();
int explore(int i, int j);
int shortestPath(int m);
int validJump(int s, int d);
int isEndLine(int j);


    


int array[M][N] =
{
            {6, 0, 7, 1, 7, 9, 3, 2},
            {2, 6, 2, 3, 4, 4, 5, 6},
            {6, 8, 1, 9, 7, 0, 1, 4},
            {5, 4, 2, 4, 8, 7, 5, 5},
            {9, 5, 1, 1, 2, 3, 6, 2},
            {9, 5, 3, 5, 6, 4, 7, 7},
            {1, 3, 5, 1, 8, 5, 3, 4},
            {5, 3, 7, 7, 4, 6, 9, 5},
            {7, 8, 9, 9, 8, 7, 1, 6},
            {3, 4, 5, 5, 1, 3, 8, 5}
};

int visited[M][N] =
 {
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0}
};



//page 6 in the PDF
int main ()
{
    int ans = shortestPath(M);
    printf("%d \n", ans);
}


int shortestPath(int m)
{
    int min = DEAD_END;
    for(int i = 0; i < m; i++)
    {
        int temp = explore(i , 0);
        if (temp < min) min = temp;
    }
    if (min == DEAD_END) return 0;
    return min;
}



int explore(int i, int j)
{
    if(visited[i][j]) return visited[i][j];
    visited[i][j] = DEAD_END; //temp

    int neighbors [4] = {DEAD_END, DEAD_END, DEAD_END, DEAD_END};

    if(j < N-1 && validJump(array[i][j], array[i][j+1]))
    {
        if(isEndLine(j+1))
        {
            visited[i][j] = 1;
            return 1;
        }
        neighbors[FRONT] = explore(i, j+1);
    }

    if(i < M-1 && validJump(array[i][j], array[i+1][j]))
    {
        neighbors[LEFT] = explore(i+1, j);
    }

    if(i > 0 && validJump(array[i][j], array[i-1][j]))
    {
        neighbors[RIGHT] = explore(i-1, j);
    }

    if(j > 0 && validJump(array[i][j], array[i][j-1]))
    {
        neighbors[BACK] = explore(i, j-1);
    }

 
    int m = min(neighbors, 4);
    if(m == DEAD_END)
    {
        visited[i][j] =  DEAD_END;
        return visited[i][j];
    }

    visited[i][j] =  m + 1;
    return visited[i][j];
}


int validJump(int s, int d)
{
    int r = s - d;
    return r == 1 || r == -1 || r == 0;
}


int isEndLine(int j)
{
    return j == N-1;
}



int min(int *arr, int n)
{
    int min = arr[0];
    for(int i = 1; i < n; i++)
    {
        if(arr[i] < min) min = arr[i];
    }
    return min;
}



void printPaths()
{
    for(int i = 0; i < M; i++)
    {
        for(int j = 0; j < N; j++)
        {
            printf("%4d   ", visited[i][j]);
        }
        printf("\n");
    }
}