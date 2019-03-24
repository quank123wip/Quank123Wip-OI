#include <bits/stdc++.h>
using namespace std;
int n, m, s;
const int maxn = 500000 + 10;
const int maxlogn = 21;
int anc[maxn][maxlogn];
int edgecc;

struct Node
{
    int id;
    int son;
    int father;
    int depth;
} Nodes[maxn];

struct Edge
{
    int to;
    int next;
} Edges[maxn];

inline void add_edge(int from, int to)
{
    auto &p = Edges[edgecc];
    p.to = to;
    p.next = Nodes[from].son;
    Nodes[from].son = edgecc;
    edgecc++;
}

inline void give_father(int now)
{
    for (int i = Nodes[now].son; i != -1; i = Edges[i].next)
    {
        if (Edges[i].to == anc[now][0])
            continue;
        Nodes[Edges[i].to].father = now;
        Nodes[Edges[i].to].depth = Nodes[now].depth + 1;
        anc[Edges[i].to][0] = now;
        give_father(Edges[i].to);
    }
}

inline void init_st(void)
{
    for (int j = 1; (1 << j) <= n; j++)
    {
        for (int i = 1; i <= n; i++)
        {
            anc[i][j] = anc[anc[i][j - 1]][j - 1];
        }
    }
}

inline void init()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        Nodes[i].id = i, Nodes[i].son = -1;
    for (int i = 0; i < n - 1; i++)
    {
        int from, to;
        scanf("%d%d", &from, &to);
        add_edge(from, to);
        add_edge(to, from);
    }
    give_father(1);
    init_st();
}
inline int Query(int x, int y)
{
    if (Nodes[x].depth < Nodes[y].depth)
        swap(x, y);
    int dist = Nodes[x].depth - Nodes[y].depth;
    int i = 0;
    while (dist != 0)
    {
        if ((1 << i) & dist)
            x = anc[x][i], dist -= (1 << i);
        i++;
    }
    if (x == y)
        return x;
    if (x != y)
    {
        for (int i = (int)log2(Nodes[x].depth); i >= 0; i--)
        {
            if (anc[x][i] != anc[y][i])
                x = anc[x][i], y = anc[y][i];
        }
    }
    return anc[x][0];
}
int main()
{
    init();
    for (int i = 0; i < m; i++)
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        int ans = 0x3f3f3f3f, p1, p2, p3;
        p1=Query(a,b);
        p2=Query(b,c);
        p3=Query(a,c);
        if(p1==p2)ans=p3;
        else if(p2==p3)ans=p1;
        else if(p1==p3)ans=p2;
        printf("%d %d\n", ans, Nodes[a].depth+Nodes[b].depth+Nodes[c].depth-Nodes[p1].depth-Nodes[p2].depth-Nodes[p3].depth);
    }
}