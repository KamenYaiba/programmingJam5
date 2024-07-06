#include <stdio.h>
#include <stdlib.h>
#define VERTICAL 0
#define HORIZONTAL 1
#define DIAGONAL 2
#define WHITE '0'
#define BLACK '1'

/*
0000
0001 h 
0010 df
0100 db
1000 h
*/

typedef struct Image{
    char **pixals;
    int n;
    int m;
    char **visited;
} Image;


int* numberOfEdges(Image *img);
Image* newImage(char **pixals, int n, int m);
void destroyImage(Image *img);
int markDF(Image *img, int i, int j);
int markDB(Image *img, int i, int j);
int markV(Image *img, int i, int j);
int markH(Image *img, int i, int j);

//page 14 in the PDF
int main()
{
    int n = 8;
    int m = 8;
    char *pixals[] = {
        "00000000",
        "10000000",
        "10111111",
        "10100000",
        "00100000",
        "10101000",
        "10000100",
        "10110010"
    };
    Image *img = newImage(pixals, n, m);
    int *ans = numberOfEdges(img);
    destroyImage(img);
    printf("%d,%d,%d", ans[HORIZONTAL], ans[VERTICAL], ans[DIAGONAL]); //output: 2,3,2
    free(ans);
}


/*
"an edge is defined as a sequence of 1 values in horizontal,
 vertical or diagonal direction.
An edge is composed of at least of two values of 1."

"A diagonal edge can be tilt to the left of the right, in either case it is called diagonal."

wierd and confusing definition tbh
according to this defination, the image:
1 1
1 0
actually has three edges ([0][1] and [1][0] is a diagonal edge)

and the image:
1 1 1
1 1 1
1 1 1
has 12 edges !!


*/
int* numberOfEdges(Image *img)
{
    char **pixals = img->pixals;
    char **visited = img->visited;
    int m = img->m;
    int n = img->n;
    char status;
    int hEdges = 0;
    int vEdges = 0;
    int dEdges = 0;

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            if(pixals[i][j] == WHITE) continue;
            
            status = visited[i][j];
            
            if( !(status & 0b1000) )
                hEdges += markH(img, i, j);

            if( !(status & 0b0001) )
                vEdges += markV(img, i, j);    

            if( !(status & 0b0010) )
                    dEdges += markDF(img, i, j);

            if( !(status & 0b0100) )
                dEdges += markDB(img, i, j);
                
        }
    }
    int* result = (int*) malloc(sizeof(int) * 3);
    result[VERTICAL] = vEdges;
    result[HORIZONTAL] = hEdges;
    result[DIAGONAL] = dEdges;
    return result;
    
}


int markDF(Image *img, int i, int j)
{
    char **pixals = img->pixals;
    char **visited = img->visited;
    int m = img->m;
    int n = img->n;

    if(i == n-1 || j == m-1 || pixals[i+1][j+1] == WHITE) return 0;

    do
    {
        visited[++i][++j] |= 0b0010;
    }while(i < n-1 && j < m-1 && pixals[i+1][j+1] == BLACK);
    
    return 1;
}


int markDB(Image *img, int i, int j)
{
    char **pixals = img->pixals;
    char **visited = img->visited;
    int m = img->m;
    int n = img->n;

    if(i == n-1 || j == 0 || pixals[i+1][j-1] == WHITE) return 0;

    do
    {
        visited[++i][--j] |= 0b0100;
    }while(i < n-1 && j > 0 && pixals[i+1][j-1] == BLACK);

    return 1;      
}


int markV(Image *img, int i, int j)
{
    char **pixals = img->pixals;
    char **visited = img->visited;
    int n = img->n;

    if(i == n-1 || pixals[i+1][j] == WHITE) return 0;

    do
    {
        visited[++i][j] |= 0b0001;
    } while(i < n-1 && pixals[i+1][j] == BLACK);
    
    return 1;
}


int markH(Image *img, int i, int j)
{
    char **pixals = img->pixals;
    char **visited = img->visited;
    int m = img->m;
    if(j == m-1 || pixals[i][j+1] == WHITE) return 0;

    do
    {
        visited[i][++j] |= 0b1000;
    }while(j < m-1 && pixals[i][j+1] == BLACK);
        
    return 1;
}



Image* newImage(char **pixals, int n, int m)
{
    Image *img = (Image*) malloc(sizeof(Image));
    img->m = m;
    img->n = n;
    img->pixals = pixals;
    char **visited = (char**) malloc(sizeof(char*) * n);
    for(int i = 0; i < n; i++)
        visited[i] = (char*) malloc(sizeof(char) * n);

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
            visited[i][j] = 0;
    }

    img->visited = visited;

    return img;
}


void destroyImage(Image *img)
{

}