//任务规划 1 O(n^2)
#include<cstdio>
#include<cstring>
#include<algorithm>

using std::min;

const int MaxN = 300000 + 10;

int n,s;
int t[MaxN], c[MaxN];
int f[MaxN];

signed main()
{
    scanf("%d%d",&n,&s);
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d",t+i,c+i);
        t[i]+=t[i-1];
        c[i]+=c[i-1];
    }
    memset(f,0x3f,sizeof f);
    f[0]=0;
    for(int i=1;i<=n;i++)
        for(int j=0;j<i;j++)
            f[i]=min(f[i],f[j]+s*(c[n]-c[j])+t[i]*(c[i]-c[j]));
    printf("%d",f[n]);
}