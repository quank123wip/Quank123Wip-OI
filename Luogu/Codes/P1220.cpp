#include <bits/stdc++.h>
using std::max;
using std::min;
constexpr int MaxN = 100;
int n, c, a[MaxN], b[MaxN], prefix[MaxN], f[MaxN][MaxN][2]; // 0 for i, 1 for j
int main()
{
    scanf("%d%d", &n, &c);
    memset(f, 0x3f, sizeof f);
    f[c][c][0]=f[c][c][1]=0;
    for (int i = 1; i <= n; i++)
        scanf("%d%d", a + i, b + i),
        prefix[i]=prefix[i-1]+b[i];
    for(int len=2;len<=n;len++)
    {
        for(int i=1;i+len-1<=n;i++)
        {
            int j=i+len-1;
            f[i][j][0]=min(f[i+1][j][0]+(prefix[i]-prefix[j]+prefix[n])*(a[i+1]-a[i]),f[i+1][j][1]+(prefix[i]-prefix[j]+prefix[n])*(a[j]-a[i]));
            f[i][j][1]=min(f[i][j-1][0]+(prefix[i-1]-prefix[j-1]+prefix[n])*(a[j]-a[i]),f[i][j-1][1]+(prefix[i-1]-prefix[j-1]+prefix[n])*(a[j]-a[j-1]));
        }
    }
    printf("%d",min(f[1][n][0],f[1][n][1]));
}