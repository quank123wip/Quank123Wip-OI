#include <bits/stdc++.h>
#define lowbit(x) (x & -x)
const int maxn = 1010;
int C, n, ans, t[maxn], b[maxn], f[maxn][1 << 8][50];
using std::min;
inline void Process(void)
{
    scanf("%d", &n);
    ans = 1e9;
    for (int i = 1; i <= n; i++)
        scanf("%d%d", t + i, b + i);
    memset(f, 0x3f, sizeof f);
    f[1][0][7] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < (1 << 8); j++)
            for (int k = -8; k < 8; k++)
                if (f[i][j][k+8] < 1e9)
                {
                    if (j & 1)
                    {
                        f[i + 1][j >> 1][k + 7] = min(f[i + 1][j >> 1][k + 7], f[i][j][k + 8]);
                    }
                    else
                    {
                        int tmp = 0x3f3f3f3f;
                        for (int pos = 0; pos <= 7; pos++)
                        {
                            if ((j >> pos) & 1)
                                continue;
                            if (tmp < i + pos)
                                break;
                            tmp = min(tmp, i + pos + b[i + pos]);
                            if (i + k)
                                f[i][j | (1 << pos)][pos + 8] = min(f[i][j | (1 << pos)][pos + 8], f[i][j][k + 8] + (t[i + pos] ^ t[i + k]));
                            else
                                f[i][j | (1 << pos)][pos + 8] = min(f[i][j | (1 << pos)][pos + 8], f[i][j][k + 8]);
                        }
                    }
                }
    for (int k = 0; k <= 8; k++)
        ans = min(ans, f[n + 1][0][k]);
    printf("%d", ans);
    puts("");
}
signed main()
{
    scanf("%d", &C);
    while (C--)
        Process();
}