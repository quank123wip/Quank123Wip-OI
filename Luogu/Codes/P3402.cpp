#include <bits/stdc++.h>
const int maxn = 200010;
static int cnt; //Global
int n, m;
struct Node
{
    int f, rk, l, r;
} Nodes[maxn << 5];

int version[maxn];

#define lson Nodes[x].l
#define rson Nodes[x].r
#define mid ((l + r) >> 1)
#define newnode() (++cnt)
#define fa(x) Nodes[x].f
#define rank(x) Nodes[x].rk

inline void build(int &x, int l, int r)
{
    x = newnode();
    if (l == r)
    {
        fa(x) = l;
        return;
    }
    build(lson, l, mid);
    build(rson, mid + 1, r);
}
inline void newver(int &x, int base, int l, int r, int pos, int newf)
{
    x = newnode();
    lson = Nodes[base].l;
    rson = Nodes[base].r;
    if (l == r)
    {
        fa(x) = newf;
        rank(x) = rank(base);
        return;
    }
    if (pos <= mid)
        newver(lson, Nodes[base].l, l, mid, pos, newf);
    else
        newver(rson, Nodes[base].r, mid + 1, r, pos, newf);
}
inline int query(int x, int l, int r, int pos)
{
    if (l == r)
        return x;
    if (pos <= mid)
        return query(lson, l, mid, pos);
    else
        return query(rson, mid + 1, r, pos);
}
inline int father_node(int x, int p)
{
    int ans = query(x, 1, n, p);
    if (p == fa(ans))
        return ans;
    else
        return father_node(x, fa(ans));
}
inline void node_pp(int x, int l, int r, int p)
{
    if (l == r)
    {
        rank(x)++;
        return;
    }
    if (p <= mid)
        node_pp(lson, l, mid, p);
    else
        node_pp(rson, mid + 1, r, p);
}
inline void union_set(int x, int y, int ver)
{
    x = father_node(version[ver], x);
    y = father_node(version[ver], y);
    if (fa(x) == fa(y))
        return;
    if (rank(x) > rank(y))
        std::swap(x, y);
    newver(version[ver], version[ver - 1], 1, n, fa(x), fa(y));
    if (rank(x) == rank(y))
        node_pp(version[ver], 1, n, fa(y));
}
int main()
{
    scanf("%d%d", &n, &m);
    build(version[0], 1, n);
    for (int i = 1; i <= m; i++)
    {
        int opt;
        scanf("%d", &opt);
        switch (opt)
        {
        case 1:
        {
            int a, b;
            scanf("%d%d", &a, &b);
            version[i] = version[i - 1];
            union_set(a, b, i);
            break;
        }
        case 2:
        {
            int a;
            scanf("%d", &a);
            version[i] = version[a];
            break;
        }
        case 3:
        {
            version[i] = version[i - 1];
            int a, b;
            scanf("%d%d", &a, &b);
            if (fa(father_node(version[i], a)) == fa(father_node(version[i], b)))
                printf("1\n");
            else
                printf("0\n");
            break;
        }
        }
    }
}
