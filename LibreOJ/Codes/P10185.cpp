//任务规划 2 凸优化 O(nlogn)
#include<cstdio>
#include<cstring>
#include<algorithm>

using std::min;

const int MaxN = 300000 + 10;

int n,s;
int t[MaxN], c[MaxN];
int f[MaxN], Q[MaxN];

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
    {
        //TODO
    }
    printf("%d",f[n]);
}