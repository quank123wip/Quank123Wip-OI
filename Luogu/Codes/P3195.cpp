#include <bits/stdc++.h>

const int maxn = 100010;

long long n, L;
long long S[maxn], f[maxn];
long long head = 1, tail = 1, Q[maxn];

#define a(i) (double)((double)S[i] + i)
#define b(i) (double)(a(i) + L + 1)
#define x(i) (double)(b(i))
#define y(i) (double)((double)f[i] + x(i) * x(i))
#define slope(i, j) ((y(i) - y(j)) / (x(i) - x(j)))

signed main()
{
    scanf("%lld%lld", &n, &L);
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld", &S[i]);
        S[i] += S[i - 1];
    }
    for (int i = 1; i <= n; i++)
    {
        while (head < tail && slope(Q[head], Q[head + 1]) < 2 * a(i))
            ++head;
        f[i] = f[Q[head]] + (a(i) - b(Q[head])) * (a(i) - b(Q[head]));
        while (head < tail && slope(i, Q[tail - 1]) < slope(Q[tail - 1], Q[tail]))
            --tail;
        Q[++tail] = i;
    }
    printf("%lld\n", f[n]);
}