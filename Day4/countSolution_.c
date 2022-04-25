#include<stdio.h>
#include<string.h>
#define MAX_SZ 1000

#define FOR(x,a,b,i) for (int x=(a),_b=(b),_i=(i);x<=_b;x+=_i)
#define FOD(x,a,b,i) for (int x=(a),_b=(b),_i=(i);x>=_b;x-=_i)
#define ll long long
#define max(a,b) (a>b)? a:b
#define min(a,b) (a<b)? a:b

int n,m;
int a[10000010];
ll dp[10000010];
ll sum;

int main()
{
    scanf("%d%d",&n,&m);
    FOR(i,1,n,1) 
    {
        scanf("%d",&a[i]);
        sum+=a[i];
    }
    dp[sum]=1;
    FOR(i,1,n,1)
        FOR(j,sum+a[i],m,1)
        {
            dp[j]+=dp[j-a[i]];
        }
    // FOR(i,1,m,1) printf("%d ",dp[i]);
    printf("%lld",dp[m]);
}