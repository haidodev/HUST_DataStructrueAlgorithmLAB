#include<stdio.h>
#include<string.h>
#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MAXLEN 256
int main(){
    char date[MAXLEN];
    int cnt[12] = {0}, res = 0;
    while ((scanf("%s", date)) && strcmp(date, "#") != 0){
        int year, month, day;
        sscanf(date, "%d-%d-%d", &year, &month, &day);
        ++cnt[month - 1];
        res = MAX(res, cnt[month - 1]);
    }
    printf("%d", res);
    return 0;
}