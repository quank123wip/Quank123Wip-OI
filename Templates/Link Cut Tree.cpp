#include <bits/stdc++.h>
using namespace std;
int val[200010];
const int maxn = 200010;
int top, st[maxn];
int ch[maxn][2], fa[maxn], xr[maxn], rev[maxn];
inline void update(int x)
{
    xr[x] = xr[ch[x][0]] ^ xr[ch[x][1]] ^ val[x];
}
inline void pushdown(int x)
{
    int l = ch[x][0], r = ch[x][1];
    if (rev[x])
    {
        rev[l] ^= 1;
        rev[r] ^= 1;
        rev[x] ^= 1;
        swap(ch[x][0], ch[x][1]);
    }
}
inline bool isroot(int x) { return ch[fa[x]][0] != x && ch[fa[x]][1] != x; }
inline void rotate(int x)
{
    int y = fa[x], z = fa[y], l, r;
    if (ch[y][0] == x)
        l = 0;
    else
        l = 1;
    r = l ^ 1;
    if (!isroot(y))
    {
        if (ch[z][0] == y)
            ch[z][0] = x;
        else
            ch[z][1] = x;
    }
    fa[x] = z;
    fa[y] = x;
    fa[ch[x][r]] = y;
    ch[y][l] = ch[x][r];
    ch[x][r] = y;
    update(y);
    update(x);
}
inline void splay(int x)
{
    top = 1;
    st[top] = x;
    for (int i = x; !isroot(i); i = fa[i])
        st[++top] = fa[i];
    for (int i = top; i; i--)
        pushdown(st[i]);
    while (!isroot(x))
    {
        int y = fa[x], z = fa[y];
        if (!isroot(y))
        {
            if ((ch[y][0] == x) ^ (ch[z][0] == y))
                rotate(x);
            else
                rotate(y);
        }
        rotate(x);
    }
}
inline void access(int x)
{
    for (int y = 0; x; y = x, x = fa[x])
        splay(x), ch[x][1] = y,update(x);
}
inline void makeroot(int x)
{
    access(x);
    splay(x);
    rev[x] ^= 1;
}
inline int findroot(int x)
{
    access(x);
    splay(x);
    while (ch[x][0])
        x = ch[x][0];
    return x;
}
inline void split(int x, int y)
{
    makeroot(x);
    access(y);
    splay(y);
}
inline void link(int x, int y)
{
    makeroot(x);
    fa[x] = y;
}
inline void cut(int x, int y)
{
    makeroot(x);
    access(y);
    split(x, y);
    if (findroot(y) == x && ch[y][0] == x && ch[x][1] == 0)
        ch[y][0] = 0, fa[x] = 0;
}
int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &val[i]);
        xr[i] = val[i];
    }
    for (int i = 0; i < m; i++)
    {
        int opt, x, y;
        scanf("%d%d%d", &opt, &x, &y);
        switch (opt)
        {
        case 1:
        {
            int a = findroot(x), b = findroot(y);
            if (a != b)
                link(x, y);
            break;
        }
        case 2:
        {
            int a = findroot(x), b = findroot(y);
            if (a == b)
                cut(x, y);
            break;
        }
        case 3:
        {
            access(x);
            splay(x);
            val[x] = y;
            update(x);
            break;
        }
        case 0:
        {
            split(x, y);
            printf("%d\n", xr[y]);
            break;
        }
        }
    }
}