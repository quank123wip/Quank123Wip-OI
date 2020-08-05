// 单调队列优化
#include <cstdio>
#include <cstring>
#include <algorithm>

using std::min;

#define initqueue front = back = 1, Q[front] = INF
#define val (f[m] - m / b[i]) //钱数

const int MaxN = 200 + 10;
const int INF = 0x3f3f3f3f;

int n, k, b[MaxN], c[MaxN], f[MaxN * MaxN], Q[MaxN * MaxN], pos[MaxN * MaxN], front, back;

signed main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", b + i);
    for (int i = 1; i <= n; i++)
        scanf("%d", c + i);
    scanf("%d", &k);
    memset(f, 0x3f, sizeof f);
    f[0] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < b[i]; j++)
        {
            initqueue;
            for (int m = j; m <= k; m += b[i])//枚举钱数
            {
                while (front <= back && pos[front] < m - c[i] * b[i])// 单调队列优化, 保证硬币数和钱数满足单调性
                    front++;
                while (front <= back && Q[back] >= val)
                    back--;
                Q[++back] = val;
                pos[back] = m;
                f[m] = min(f[m], Q[front] + m / b[i]);
            }
        }
    printf("%d", f[k]);
}