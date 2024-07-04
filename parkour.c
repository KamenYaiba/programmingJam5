#include <stdio.h>
#include <stdlib.h>

#define FRONT 0
#define RIGHT 1
#define BACK 2
#define LEFT 3

int const DEAD_END = SHRT_MAX;


typedef struct parkourMap
{
    int m;
    int n;
    char** heightMap;
    short** visited;
}parkourMap;


int min(int *arr, int n);
short explore(parkourMap* pm, int i, int j);
int shortestPath(parkourMap* pm);
int validJump(char s, char d);
int isEndLine(parkourMap *pm, int j);
void displayPaths(parkourMap *pm);
parkourMap* newParkourMap(int m, int n, char* rawMap);
int destroyParkourMap(parkourMap* pm);



//page 6 in the PDF
int main ()
{
    int m = 10;
    int n = 8;
    char* rawMap = "60717932\n26234456\n68197014\n54248755\n95112362\n95356477\n13518534\n53774695\n78998716\n34551385";
    
    parkourMap *pm = newParkourMap(m, n, rawMap);
    int ans = shortestPath(pm);
    //displayPaths(pm);  //if you want to see the actual path (not required in the problem statment) ^^
    destroyParkourMap(pm);
    pm = NULL;
    
    printf("%d", ans); //output: 20
}


int shortestPath(parkourMap* pm)
{
    if (pm == NULL) return -1;

    int min = DEAD_END;
    int m = pm->m;
    for(int i = 0; i < m; i++)
    {
        int temp = explore(pm, i , 0);
        if (temp < min) min = temp;
    }
    if (min == DEAD_END) return 0;
    return min;
}



short explore(parkourMap* pm, int i, int j)
{
    short **visited = pm->visited;
    char **map = pm->heightMap;
    if(visited[i][j]) return visited[i][j];

    visited[i][j] = DEAD_END; //temp

    int neighbors [4] = {DEAD_END, DEAD_END, DEAD_END, DEAD_END};

    if(j < pm->n-1 && validJump(map[i][j], map[i][j+1]))
    {
        if(isEndLine(pm, j+1))
        {
            visited[i][j] = 1;
            return 1;
        }
        neighbors[FRONT] = explore(pm, i, j+1);
    }

    if(i < pm->m-1 && validJump(map[i][j], map[i+1][j]))
    {
        neighbors[LEFT] = explore(pm, i+1, j);
    }

    if(i > 0 && validJump(map[i][j], map[i-1][j]))
    {
        neighbors[RIGHT] = explore(pm, i-1, j);
    }

    if(j > 0 && validJump(map[i][j], map[i][j-1]))
    {
        neighbors[BACK] = explore(pm, i, j-1);
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


int validJump(char s, char d)
{
    int r = s - d;
    return r == 1 || r == -1 || r == 0;
}


int isEndLine(parkourMap *pm, int j)
{
    return j == pm->n-1;
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



parkourMap* newParkourMap(int rows, int cols, char* rawMap)
{
    parkourMap *pm = (parkourMap*) malloc(sizeof(parkourMap));
    pm->m = rows;
    pm->n = cols;

    char **heightMap = (char**) malloc(sizeof(char*) * rows);
    short **visited = (short**) malloc(sizeof(short*) * rows);

    for(int i = 0; i < rows; i++)
    {
        heightMap[i] = (char*) malloc(sizeof(char) * cols);
        visited[i] = (short*) malloc(sizeof(short) * cols);
    }

    int i, j, idx;
    i = j = idx = 0;
    char c;
    while( (c = rawMap[idx++]) != '\0' )
    {
        if(c != '\n')
        {
            heightMap[i][j] = c;
            visited[i][j++] = 0;
        }
            
        else
        {
            i++;
            j = 0;
        }
    }
    pm->heightMap = heightMap;
    pm->visited = visited;

    return pm;
}


int destroyParkourMap(parkourMap* pm)
{
    if(pm == NULL) return -1;
    int m = pm->m;

    char **heightMap = pm->heightMap;
    if(heightMap != NULL)
    {
        for(int i = 0; i < m; i++)
            free(heightMap[i]);

        free(heightMap);
        pm->heightMap = NULL;
    }
    
    short **visited = pm->visited;
    if(visited != NULL)
    {
        for(int i = 0; i < m; i++)
            free(visited[i]);

        free(visited);
        pm->visited = NULL;
    }

    free(pm);
    return 0;
}


void displayPaths(parkourMap *pm)
{
    int m = pm->m;
    int n = pm->n;
    short **paths = pm->visited;
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            printf("%7d   ", paths[i][j]);
        }
        printf("\n\n");
    }
}