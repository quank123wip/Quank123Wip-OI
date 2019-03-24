#include <bits/stdc++.h>
using namespace std;
const int maxn = 21;
int n, m;
int a[maxn * maxn];
bool flag;
int p[1010];
int ans[maxn][maxn];
int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n * n; i++)
    {
        scanf("%d", &a[i]);
        p[a[i]]++;
    }
    if(n==0)
    {
        puts("YES");
        printf("%d",a[0]);
    }
    sort(a, a + n * n);
    int m = unique(a, a + n * n) - a;
    if (n % 2 == 0)
    {
        for (int i = 1; i <= 1000; i++)
        {
            if (p[i] && p[i] % 4 != 0)
            {
                puts("NO");
                return 0;
            }
        }
        puts("YES");
        for (int k = 0; k < m; k++)
        {
            while (p[a[k]])
                for (int i = 1; i <= n; i++)
                {
                    if (p[a[k]] == 0)
                        break;
                    for (int j = 1; j <= n; j++)
                    {
                        if (p[a[k]] == 0)
                            break;
                        if (ans[i][j])
                            continue;
                        else
                        {
                            ans[i][j] = ans[n - i + 1][j] = ans[i][n - j + 1] = ans[n - i + 1][n - j + 1] = a[k];
                            p[a[k]] -= 4;
                        }
                    }
                }
        }
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                printf("%d ",ans[i][j]);
            }
            puts("");
        }
        return 0;
    }
    else
    {
        int qaq=n*2-1;
        for (int i = 1; i <= 1000; i++)
        {
            if (p[i] && p[i] % 4 != 0)
            {
                if (!flag)
                    flag = true;
                else if(qaq&&(p[i]%4)%2==0)
                    qaq--;
                else
                {
                    puts("NO");
                    return 0;
                }
            }
        }
        puts("YES");
        for (int k = 0; k < m; k++)
        {
            while (p[a[k]]>1)
                for (int i = 1; i <= n; i++)
                {
                    if (p[a[k]]<=1)
                        break;
                    for (int j = 1; j <= n; j++)
                    {
                        if (p[a[k]]<=1)
                            break;
                        if(i==(n+1)/2&&j==(n+1)/2)continue;
                        if(i==(n+1)/2||j==(n+1)/2)
                        {
                            if(i==(n+1)/2)
                            {
                                ans[i][j]=ans[i][n-j+1]=a[k];
                                p[a[k]] -= 2;
                            }
                            else
                            {
                                ans[i][j]=ans[n-i+1][j]=a[k];
                                p[a[k]] -= 2;
                            }
                            
                            continue;
                        }
                        if (ans[i][j])
                            continue;
                        else
                        {
                            ans[i][j] = ans[n - i + 1][j] = ans[i][n - j + 1] = ans[n - i + 1][n - j + 1] = a[k];
                            p[a[k]] -= 4;
                        }
                    }
                }
            if(p[a[k]]==1)
            {
                ans[(n+1)/2][(n+1)/2]=a[k];
                p[a[k]]--;
            }
        }
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                printf("%d ",ans[i][j]);
            }
            puts("");
        }
    }
}