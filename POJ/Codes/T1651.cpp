// POJ 1651
// 等效于矩阵链乘法
// O(n^2)算法
// 最优算法O(nlogn)?
#include <cstdio>
#include <cstring>
#include <algorithm>

using std::memset;
using std::min;
using std::printf;
using std::scanf;

const int MaxN = 100 + 10;

int n, a[MaxN];
int f[MaxN][MaxN]; // DP数组, f[i][j]表示取出i～j之间数字的最小花费

signed main()
{
    scanf("%d", &n);
    memset(f, 0x3f, sizeof f); // Tricks: memset为0x3f会使得每个数组中的数字都为0x3f3f3f3f, 是一个极大值, 在数组值比较小的情况下可以视为INF, 并且这个极大值的两倍仍然不会溢出, 相应的, 负无穷可以用0xcf替代
    for (int i = 1; i <= n; i++)
        scanf("%d", a + i);                    // Tricks: a+i等效于指向a[i]的指针(数组事实上是指向分配内存空间首部的指针)
    for (int len = 2; len <= n; len++)         // 枚举长度
        for (int i = 1; i + len - 1 <= n; i++) // 枚举起始
        {
            f[i][i] = f[i][i + 1] = 0;
            for (int j = i + len - 1, k = i; k < j; k++)
                f[i][j] = min(f[i][k] + f[k][j] + a[i] * a[k] * a[j], f[i][j]);
        }
    printf("%d", f[1][n]);
}