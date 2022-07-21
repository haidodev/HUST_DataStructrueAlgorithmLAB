#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLEN 1000000
int main()
{
    char currentChar, prevChar = 0;
    int countZero = 0, countOne = 0;
    while ((currentChar = getchar()) != EOF)
    {
        if (currentChar != prevChar)
        {
            if (currentChar == '0')
                ++countZero;
            if (currentChar == '1')
                ++countOne;
            prevChar = currentChar;
        }
    }
    if (currentChar == '0')
        ++countZero;
    if (currentChar == '1')
        ++countOne;
    printf("%d %d", countZero, countOne);
}