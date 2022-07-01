#include<stdio.h>
#define MOD 1000000007
int expmod(unsigned long long a, unsigned long long b){
    //printf("%llu %llu \n", a, b);
    if (b == 1) return a;
    long long tmp = expmod(a, b / 2);
    tmp = tmp * tmp % MOD;
    if (b % 2) tmp = tmp * a;
    tmp %= MOD;
    return tmp;
}
int main(){
    unsigned long long a, b;
    scanf("%llu %llu", &a, &b);
    a %= MOD;
    printf("%d", expmod(a, b));
}