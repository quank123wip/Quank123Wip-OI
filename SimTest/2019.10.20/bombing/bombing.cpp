#include <bits/stdc++.h>
using std::cerr;
using std::endl;
using std::max;
using std::min;
const int maxn = 2010;
int n, ans, a[maxn][maxn], dp1[maxn][maxn], dp2[maxn];
std::string str;
signed main()
{
    freopen("bombing.in","r",stdin);
    freopen("bombing.out","w",stdout);
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        std::cin>>str;
        for(int j=0;j<n;j++)
            a[i][j]=str[j]-'0';
    }
    for (int i = 0; i < n; i++)
        dp1[i][n - 1] = a[i][n - 1];
    for (int i = 0; i < n; i++)
        for (int j = n - 2; j >= 0; j--)
            if (a[i][j])
                dp1[i][j] = dp1[i][j + 1] + 1;
    for (int j = 0; j < n; j++)
    {
        memset(dp2, 0, sizeof dp2);
        for(int i=0;i<n;i++)
        {
            dp2[i]=dp1[i][j];
        }
        std::sort(dp2,dp2+n,[](int a,int b){return a>b;});
        for(int i=0;i<n;i++)
        {
            ans=max(ans,(i+1)*dp2[i]);
        }
    }
    printf("%d",ans);
}