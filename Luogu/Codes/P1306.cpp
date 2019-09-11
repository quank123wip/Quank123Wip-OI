#include <bits/stdc++.h>
using std::__gcd;
using std::cin;
using std::cout;
using std::endl;
int n, m, p;
long long fib[2][2] = {1, 1};
long long a[2][2] = {{1, 1}, {1, 0}};
long long ans[2][2] = {{1, 0}, {0, 1}};
long long cache[2][2];
inline long long work(int p)
{
    while (p)
    {
        if (p & 1)
        {
            memset(cache, 0, sizeof(cache));
            for (int i = 0; i < 2; i++)
                for (int j = 0; j < 2; j++)
                    for (int k = 0; k < 2; k++)
                        cache[i][j] += ans[i][k] * a[k][j],cache[i][j]%=(int)1e8;
            memcpy(ans, cache, sizeof(ans));
        }
        p >>= 1;
        memset(cache, 0, sizeof(cache));
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                for (int k = 0; k < 2; k++)
                    cache[i][j] += a[i][k] * a[k][j],cache[i][j]%=(int)1e8;
        memcpy(a, cache, sizeof(a));
    }
    memset(cache, 0, sizeof(cache));
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            for (int k = 0; k < 2; k++)
                cache[i][j] += fib[i][k] * ans[k][j],cache[i][j]%=(int)1e8;
    memcpy(fib, cache, sizeof(a));
    return fib[0][0];
}
signed main()
{
    std::cin >> n >> m;
    p = __gcd(n, m);
    if (p <= 2)
        puts("1"), exit(0);
    else
        cout << work(p - 2);
}