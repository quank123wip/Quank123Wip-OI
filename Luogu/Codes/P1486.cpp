#include <bits/stdc++.h>
const int maxn = 1000010;
const int inf = 0x3f3f3f3f;
int val[maxn], fix[maxn], lson[maxn], rson[maxn], size[maxn];
int cnt, root, deltav;
int n, minv, l;

char string[10];
inline void Update(int x)
{
    size[x] = size[lson[x]] + size[rson[x]] + 1;
}
inline int newnode(int v)
{
    val[++cnt] = v;
    size[cnt] = 1;
    fix[cnt] = std::rand();
    return cnt;
}
inline int merge(int x, int y)
{
    if (!x || !y)
        return x + y;
    if (fix[x] < fix[y])
    {
        rson[x] = merge(rson[x], y);
        Update(x);
        return x;
    }
    else
    {
        lson[y] = merge(x, lson[y]);
        Update(y);
        return y;
    }
}
inline void split(int now, int k, int &x, int &y)
{
    if (!now)
        x = y = 0;
    else
    {
        if (val[now] <= k)
        {
            x = now;
            split(rson[now], k, rson[now], y);
        }
        else
        {
            y = now;
            split(lson[now], k, x, lson[now]);
        }
        Update(now);
    }
}
inline void insert(int x)
{
    root = merge(root, newnode(x));
}
inline int kth(int now, int k)
{
    for (;;)
    {
        if (k <= size[lson[now]])
            now = lson[now];
        else if (k == size[lson[now]] + 1)
            return now;
        else
            k -= size[lson[now]] + 1, now = rson[now];
    }
}
int main()
{
    srand(time(NULL));
    scanf("%d%d", &n, &minv);
    int x, y, z, opt;
    for (int i = 1; i <= n; i++)
    {
        scanf("%s%d", string, &opt);
        switch (string[0])
        {
        case 'I':
        {
            if (opt >= minv)
            {
                opt -= deltav;
                split(root, opt, x, y);
                root = merge(x, merge(newnode(opt), y));
            }
            break;
        }
        case 'A':
        {
            deltav += opt;
            break;
        }
        case 'S':
        {
            deltav -= opt;
            split(root, minv - deltav - 1, x, y);
            root = y;
            l += size[x];
            break;
        }
        case 'F':
        {
            if (size[root] < opt)
                puts("-1");
            else
                printf("%d\n", val[kth(root, size[root] - opt + 1)] + deltav);
            break;
        }
        }
    }
    printf("%d\n", l);
}