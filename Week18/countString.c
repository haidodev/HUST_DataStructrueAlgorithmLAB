#include <stdio.h>
int main()
{
    char currentChar, prevChar = 0;
    int countZero = 0, countOne = 0;
    while ((currentChar = getchar()) != EOF)
    {
        if (currentChar != prevChar)
        {
            if (prevChar == '0')
                ++countZero;
            if (prevChar == '1')
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