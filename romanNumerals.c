#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* decrementRoman(char* s);
char* joinSubstrings(char* s1, int end1, char* s2, int end2);

//page 19 in the PDF
int main()
{
    printf("%s\n", decrementRoman("MCMI")); //output: MCM
}


char* decrementRoman(char* s)
{
    int lastIdx;
    if((lastIdx = strlen(s)-1) < 0) return "";

    int charsToRemove = 1;
    char *sfxs[] = {"", "III", "IV", "VIII", "IX", "XXXIX", "XLIX", "LXXXIX",
                     "XCIX", "CCCXCIX", "CDXCIX", "DCCCXCIX", "CMXCIX"};
    char* sfx;

    char c = s[lastIdx];
    switch(c){
        case 'I':
            sfx = sfxs[0];
            break;
        case 'V':
            if(lastIdx > 0 && s[lastIdx-1] == 'I')
            {
                charsToRemove++;
                sfx = sfxs[1];
            }
            else
                sfx = sfxs[2];
            break;
        case 'X':
            if(lastIdx > 0 && s[lastIdx-1] == 'I')
            {
                charsToRemove++;
                sfx = sfxs[3];
            }
            else
                sfx = sfxs[4];
            break;
        case 'L':
            if(lastIdx > 0 && s[lastIdx-1] == 'X')
            {
                charsToRemove++;
                sfx = sfxs[5];
            }
            else
                sfx = sfxs[6];
            break;
        case 'C':
            if(lastIdx > 0 && s[lastIdx-1] == 'X')
            {
                charsToRemove++;
                sfx = sfxs[7];
            }
            else
                sfx = sfxs[8];
            break;
        case 'D':
        if(lastIdx > 0 && s[lastIdx-1] == 'C')
            {
                charsToRemove++;
                sfx = sfxs[9];
            }
            else
                sfx = sfxs[10];
            break;
        case 'M':
            if(lastIdx > 0 && s[lastIdx-1] == 'C')
            {
                charsToRemove++;
                sfx = sfxs[11];
            }
            else
                sfx = sfxs[12];
            break;
        default: return 0;
    }

    return joinSubstrings(s, lastIdx-charsToRemove, sfx, strlen(sfx)-1);    
}


char* joinSubstrings(char* s1, int end1, char* s2, int end2)
{
    int n = end1 + end2 + 3;
    char *joinedStr = (char*) malloc(sizeof(char) * n);
    int idx = 0;
    for(int i = 0; i <= end1; i++)
        joinedStr[idx++] = s1[i];
    for(int i = 0; i <= end2; i ++)
        joinedStr[idx++] = s2[i];
    joinedStr[n-1] = '\0';

    return joinedStr;
}