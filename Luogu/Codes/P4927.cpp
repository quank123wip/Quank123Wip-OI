#include <bits/stdc++.h>

// type defination
typedef long long ll;
typedef unsigned long long ull;
typedef __int128_t lll;
typedef __uint128_t ulll;
// FastIO defination
namespace FastIO
{
inline int read_int(void)
{
    int ans = 0;
    bool p = false;
    char ch = std::getchar();
    while (!std::isdigit(ch))
    {
        if (ch == '-')
            p = true;
        else
            p = false;
        ch = std::getchar();
    }
    while (std::isdigit(ch))
    {
        ans = (ans << 1) + (ans << 3) + ch - '0';
        ch = std::getchar();
    }
    return p ? -ans : ans;
}
inline ll read_ll(void)
{
    ll ans = 0;
    bool p = false;
    char ch = std::getchar();
    while (!std::isdigit(ch))
    {
        if (ch == '-')
            p = true;
        else
            p = false;
        ch = std::getchar();
    }
    while (std::isdigit(ch))
    {
        ans = (ans << 1) + (ans << 3) + ch - '0';
        ch = std::getchar();
    }
    return p ? -ans : ans;
}
inline ull read_ull(void)
{
    ull ans = 0;
    char ch = std::getchar();
    while (!std::isdigit(ch))
        ch = std::getchar();
    while (std::isdigit(ch))
    {
        ans = (ans << 1) + (ans << 3) + ch - '0';
        ch = std::getchar();
    }
    return ans;
}
inline lll read_lll(void)
{
    lll ans = 0;
    bool p = false;
    char ch = std::getchar();
    while (!std::isdigit(ch))
    {
        if (ch == '-')
            p = true;
        else
            p = false;
        ch = std::getchar();
    }
    while (std::isdigit(ch))
    {
        ans = (ans << 1) + (ans << 3) + ch - '0';
        ch = std::getchar();
    }
    return p ? -ans : ans;
}
inline ulll read_ulll(void)
{
    ulll ans = 0;
    char ch = std::getchar();
    while (!std::isdigit(ch))
        ch = std::getchar();
    while (std::isdigit(ch))
    {
        ans = (ans << 1) + (ans << 3) + ch - '0';
        ch = std::getchar();
    }
    return ans;
}
inline void print(lll p)
{
    if (p > 10)
        print(p / 10);
    std::putchar(p % 10 + '0');
}
} // namespace FastIO
// problem data
const int maxn = 100000 + 10;
const int mod = 998244353;
int n, m;
int a[maxn];
// math function
lll fstpow(lll b, lll p, lll modder = mod)
{
    b%=mod;
    lll ans = 1;
    while (p)
    {
        if (p & 1)
            ans*=b;
        p >>= 1;
        b = b* b% modder;
    }
    return ans;
}
void exgcd(lll a, lll b, lll &x, lll &y)
{
    if (b == 0)
    {
        x = 1, y = 0;
        return;
    }
    else
    {
        exgcd(b, a % b, y, x);
        y -= (a / b) * x;
    }
}
lll inverse(lll b, lll p)
{
    lll x, y;
    exgcd(b, p, x, y);
    return (x + p) % p;
}
// segment tree
#define lson (now << 1)
#define rson (now << 1 | 1)
lll summ[maxn << 2], val[maxn << 2], lazy[maxn << 2], len[maxn << 2], lenm[maxn << 2], lenp[maxn << 2];
inline void addlazy(int now, int add)
{
    lazy[now] += add;
    summ[now] += 2 * lenp[now] * lazy[now] + lenm[now] * add * add;
    lenp[now] += lenm[now] * add;
    val[now] += add * len[now];
}
inline void pushup(int now)
{
    val[now] = val[lson] + val[rson];
    summ[now] = (summ[lson] + summ[rson]) + (val[now] * val[now]);
    lenp[now] = (lenp[lson] + lenp[rson]) + val[now] * len[now];
}
inline void pushdown(int now)
{
    if (lazy[now])
    {
        lll q = lazy[now], lazy = 0;
        addlazy(lson, q);
        addlazy(rson, q);
    }
}
inline void build(int now = 1, int l = 1, int r = n)
{
    if (l == r)
    {
        lazy[now] = 0;
        val[now] = a[l];
        summ[now] = a[l] * a[l];
        lenp[now] = a[l];
        lenm[now] = 1;
        len[now] = 1;
        return;
    }
    build(lson, l, (l + r) >> 1);
    build(rson, ((l + r) / 2) + 1, r);
    len[now] = (r - l + 1);
    lenm[now] = lenm[lson] + lenm[rson] + len[now] * len[now];
    pushup(now);
}
inline void segadd(int now, int ln, int rn, int l, int r, int p)
{
    if (ln >= l && rn <= r)
    {
        addlazy(now, p);
        return;
    }
    pushdown(now);
    if (l <= (ln + rn) / 2)
        segadd(lson, ln, (ln + rn) / 2, l, r, p);
    if (r > (ln + rn) / 2)
        segadd(rson, (ln + rn) / 2 + 1, rn, l, r, p);
    pushup(now);
}

// refer to standard library
using std::cin;
using std::cout;
using std::endl;
//using std::scanf;
//using std::printf;
signed main()
{
    n = FastIO::read_int();
    m = FastIO::read_int();
    for (int i = 1; i <= n; i++)
        a[i] = FastIO::read_int();
    build();
    while (m--)
    {
        int opt = FastIO::read_int();
        if (opt == 1)
        {
            int l, r, p;
            l = FastIO::read_int();
            r = FastIO::read_int();
            p = FastIO::read_int();
            segadd(1, 1, n, l, r, p);
        }
        else
        {
            int qaq=summ[1]/std::__gcd(summ[1],val[1]);
            int qwq=val[1]/std::__gcd(summ[1],val[1]);
            FastIO::print(qaq*inverse(qwq,mod)%mod);
            cout << endl;
        }
    }
}