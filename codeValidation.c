#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
    char *array;
    int capacity;
    int lastEntryIdx;
}Stack;

Stack* newStack(int capacity);
void destroyStack(Stack *stk);
bool push(Stack *stk, char c);
char pop(Stack *stk);
bool validateCode(char* text);


int main()
{
    Stack *stk = newStack(3);
    validateCode("<table> <row> <cell>vegetable</cell><cell>potato</cell><cell>onion</cell><cell>carrot</cell> </row> </table>");
}


bool validateCode(char* text)
{
    char c;
    int starts, ends, idx, lastStart;
    starts = ends = idx = lastStart = 0;
    bool inside = false;

    while((c = text[idx++]) != '\0')
    {
        if(c != '<' && c != '>')
            continue;

        if(!inside)
        {
            if(c == '>') return false;
            lastStart = idx;
            starts++;
            inside++;
        }

        else if(inside)
        {
            if(c == '<' || idx-1 == lastStart) return false;
            ends++;
            inside--;
        } 
    }

    if(starts != ends) return false;
    text = tokenize(text);

    Stack *stk = newStack(3);
}


char* tokenize(char* text)
{

}


Stack* newStack(int capacity)
{
    Stack *stk = malloc(sizeof(Stack));
    stk->capacity = capacity;
    stk->lastEntryIdx = -1; //empty
    char *arr = malloc(capacity * sizeof(char));
    stk->array = arr;
}


void destroyStack(Stack *stk)
{
    free(stk->array);
    free(stk);
}


bool push(Stack *stk, char c)
{
    if(stk->lastEntryIdx+1 == stk->capacity)
        return false;
    
    stk->array[++stk->lastEntryIdx] = c;
    return true;
}


char pop(Stack *stk)
{
    if(stk->lastEntryIdx == -1)
        return 0; //null
    
    return stk->array[stk->lastEntryIdx--];
}