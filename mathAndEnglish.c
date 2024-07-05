#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int lisLen(char *s);
int binarySearch(char *s, int n, char k);


//page 11 in the PDF
int main()
{
    char *s = "AFBGCE";
    printf("%d", lisLen(s)); //output: 4
}


//nice video explaining the algorithm: www.youtube.com/watch?v=0wT67DOzqBg
int lisLen(char *s)
{
    int n = strlen(s);
    char arr[n];
    int size = 0, idx = 0;

    for(int i = 0; i < n; i++)
    {
        idx = binarySearch(arr, size, s[i]);
        if(idx == -1)
            arr[size++] = s[i];
        else
            arr[idx] = s[i];
    }
    return size;
}


int binarySearch(char *s, int n, char k)
{
    int high, low, mid;
    high = n-1;
    low = 0;
    while(high >= low)
    {
        mid = low + ((high - low) / 2);
        if(s[mid] >= k)
        {
            if(k > s[mid-1] || mid == 0)
                return mid;

            high = mid-1;   
        }
        else
            low = mid+1;
    }
    return -1;
}