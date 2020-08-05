// POJ 3311
#include <cstdio>
#include <cstring>
#include <algorithm>

using std::memset;
using std::min;
using std::printf;
using std::scanf;

const int MaxN = 10 + 1;
const int INF = 0x3f3f3f3f;

int n;
int dist[MaxN][MaxN];
int f[1 << 16][MaxN]; // 状态压缩

inline void Floyd()
{
    for (int k = 0; k <= n; k++)
        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= n; j++)
                dist[i][j] = min(dist[i][k] + dist[k][j], dist[i][j]);
}

signed main()
{
    scanf("%d", &n);
    while (n)
    {
        memset(f, 0x3f, sizeof f);
        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= n; j++)
                scanf("%d", &dist[i][j]);
        Floyd();
        f[1][0] = 0;
        for (int i = 1; i < (1 << (n + 1)); i++) //状态枚举
        {
            i |= 1;
            for (int j = 0; j <= n; j++)
                if (f[i][j] != INF)
                    for (int k = 0; k <= n; k++) //枚举断点
                    {
                        int now = i | (1 << k);
                        if (j != k)
                            f[now][k] = min(f[now][k], f[i][j] + dist[j][k]);
                    }
        }
        printf("%d\n", f[(1 << (n + 1)) - 1][0]); //输出答案,答案的状态转换为二进制即为n个1
        scanf("%d", &n);
    }
}