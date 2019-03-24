//Minimal Cost Maximum Flow Algorithm
//Coding with ISO C++ 11 Standard
//By Quank123Wip 2019,Based on my Maximum Flow Algorithm
#include <bits/stdc++.h>
int n, m, s, t;
int cnt = 0;
const int INF = 0x7f7f7f7f;
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
        while (int now = DFS(s, 1e9))
            MaxFlow += now;
    return MaxFlow;
}
using std::cin;
using std::cout;
using std::endl;
bool sign[160];
int main()
{
    for (int i = 0; i < maxn; i++)
        P.Head[i] = -1;
    int n1, m1;
    cin >> n1 >> m1;
    n = n1 * 2 + 2;
    s = n - 1, t = n;
    for (int i = 1; i <= n1; i++)
        P.AddEdge(s, i, 1), P.AddEdge(i + n1, t, 1);
    for (int i = 0; i < m1; i++)
    {
        int a, b;
        cin >> a >> b;
        P.AddEdge(a, b + n1, 1);
    }
    int ans = Dinic();
    for (int i = 1; i <= n1; i++)
    {
        if (!sign[i])
        {
            int now = i;
            cout << now << " ";
            while (now)
            {
                bool flag = false;
                sign[now] = true;
                for (int j = P.Head[now]; j != -1; j = P.Edges[j].next)
                {
                    if (now <= n1 && now >= 1 && P.Edges[j].to > n1 && P.Edges[j].to <= n1 * 2 && P.Edges[j].w == 0)
                    {
                        flag = true;
                        now = P.Edges[j].to;
                        break;
                    }
                }
                if (!flag)
                    break;
                now -= n1;
                cout << now << " ";
            }
            cout << endl;
        }
    }
    cout <<n1-ans;
}