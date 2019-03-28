//Minimal Cost Maximum Flow Algorithm
//Coding with ISO C++ 11 Standard
//By Quank123Wip 2019,Based on my Maximum Flow Algorithm
#include <bits/stdc++.h>
int n, m, s, t;
int cnt = 0;
const int INF = 0x3f3f3f3f;
const int maxn = 10000 + 10;
const int maxm = (1000000 + 10);
class Graph
{
  private:
    struct Edge
    {
        int to /*Point to*/, next /*Next Edge(A*Link)*/, w /*Weight*/;
    };

  public:
    int Head[maxn], Cur[maxn], Depth[maxn];
    Edge Edges[maxm];
    void __addE(int u, int v, int w)
    {
        Edges[cnt] = (Edge){v, Head[u], w};
        Head[u] = cnt++;
    }
    void AddEdge(int u, int v, int w)
    {
        __addE(u, v, w);
        __addE(v, u, 0);
    }
} P;
inline bool BFS(void)
{
    std::memset(P.Depth, 0x7f, sizeof(P.Depth));
    std::queue<int> q;
    for (int i = 1; i <= n; i++)
        P.Cur[i] = P.Head[i];
    P.Depth[s] = 0;
    q.push(s);
    while (!q.empty())
    {
        int now = q.front();
        q.pop();
        for (int i = P.Head[now]; i != -1; i = P.Edges[i].next)
        {
            if (P.Depth[P.Edges[i].to] > 1e9 && P.Edges[i].w)
            {
                P.Depth[P.Edges[i].to] = P.Depth[now] + 1;
                q.push(P.Edges[i].to);
            }
        }
    }
    return P.Depth[t] < 1e9;
}
int DFS(int now, int MinFlow)
{
    if (now == t || !MinFlow)
        return MinFlow;
    int Flow = 0, f;
    for (int i = P.Cur[now]; i != -1; i = P.Edges[i].next)
    {
        P.Cur[now] = i;
        if (P.Depth[P.Edges[i].to] == P.Depth[now] + 1 && (f = DFS(P.Edges[i].to, std::min(MinFlow, P.Edges[i].w))))
        {
            MinFlow -= f;
            Flow += f;
            P.Edges[i].w -= f;
            P.Edges[i ^ 1].w += f;
            if (!MinFlow)
                break;
        }
    }
    return Flow;
}
int Dinic(void)
{
    int MaxFlow = 0;
    while (BFS())
        MaxFlow += DFS(s, 1e9);

    return MaxFlow;
}
using std::cin;
using std::cout;
using std::endl;
int ship[100][100], pe[100], len[100];
int main()
{
    for (int i = 0; i < maxn; i++)
        P.Head[i] = -1;
    int n1, m1, k1;
    cin >> n1 >> m1 >> k1;
    m=m1;
    n1 += 2;
    t = n = maxn - 1;
    s = t - 1;
    for (int i = 1; i <= m1; i++)
    {
        cin >> pe[i] >> len[i];
        for (int j = 0; j < len[i]; j++)
        {
            cin >> ship[i][j];
            ship[i][j] += 2;
        }
    }
    int p = 0;
    int ans = 0;
    while (p < 500)
    {
        P.AddEdge(s, n1 * p + 2, INF);
        P.AddEdge(n1 * p + 1, t, INF);
        if (p)
        {
            for (int i = 1; i <= n1; i++)
                P.AddEdge(n1 * (p - 1) + i, n1 * p + i, INF);
            for (int i = 1; i <= m1; i++)
            {
                int a = ship[i][(p - 1) % len[i]];
                int b = ship[i][p % len[i]];
                P.AddEdge(n1 * (p - 1) + a, n1 * p + b, pe[i]);
            }
        }
        ans += Dinic();
        if (ans >= k1)
        {
            cout << p << endl;
            return 0;
        }
        p++;
    }
    cout << 0 << endl;
}