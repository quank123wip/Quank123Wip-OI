// POJ 1129
// 由四色定理可知, 答案最大为4
#include <cstdio>
#include <algorithm>
#include <cstring>

const int MaxN = 50;

int n, f[MaxN], map[MaxN][MaxN], ans;
char s, str[MaxN];

inline bool check()
{
    bool rtv = true;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (map[i][j] && f[i] == f[j])
                rtv = false;
    return rtv;
}

inline bool DFS(int pos)
{
    if (pos == n)
        return check();
    for (int i = 1; i <= ans; i++)
    {
        f[pos] = i;
        if (DFS(pos + 1))
            return true;
    }
    return false;
}

signed main()
{
    scanf("%d\n", &n);
    while (n)
    {
        memset(f, 0, sizeof f);
        memset(map, 0, sizeof map);
        memset(str, 0, sizeof str);
        for (int i = 0; i < n; i++)
        {
            scanf("%s\n", str);
            for (int j = 2; j < strlen(str); j++)
                map[str[0] - 'A'][str[j] - 'A'] = 1;
        }
        for (int i = 1; i <= 4; i++)
        {
            ans = i;
            if (DFS(0))
            {
                if (ans == 1)
                {
                    printf("1 channel needed.\n");
                    break;
                }
                else
                {
                    printf("%d channels needed.\n", ans);
                    break;
                }
            }
        }
        scanf("%d", &n);
    }
}