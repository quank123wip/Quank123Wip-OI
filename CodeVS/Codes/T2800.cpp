#include <bits/stdc++.h>
const int maxn = 21;
const int inf = 0x3f3f3f3f;
int n;
int Map[maxn][maxn];
int dp[1 << maxn][maxn];
int origin;
inline int solve(int pos, int ps)
{
    if (dp[pos][ps] != 0)
        return dp[pos][ps];
    if (pos == origin)
    {
        dp[pos][ps] = Map[ps][0];
        return dp[pos][ps];
    }
    dp[pos][ps] = inf;
    for (int i = 0; i < n; i++)
    {
        if ((pos & (1 << i)) == 0)
            dp[pos][ps] = std::min(dp[pos][ps], solve(pos + (1 << i), i + 1) + Map[ps][i + 1]);
    }
    return dp[pos][ps];
}
int main()
{
    std::cin >> n;
    origin = (1 << n) - 1;
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            std::cin >> Map[i][j];
        }
    }
    for (int f_a = 0; f_a <= n; f_a++)
        for (int f_b = 0; f_b <= n; f_b++)
            for (int f_c = 0; f_c <= n; f_c++)
                Map[f_b][f_c] = std::min(Map[f_b][f_c], Map[f_b][f_a] + Map[f_a][f_c]);
    std::cout << solve(0, 0);
}