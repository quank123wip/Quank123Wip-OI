//Minimal Cost Maximum Flow Algorithm
//Coding with ISO C++ 11 Standard
//By Quank123Wip 2019,Based on my Maximum Flow Algorithm
#include <bits/stdc++.h>
int n, m, s, t;
int cnt = 0;
const int INF = 0x7f7f7f7f;
namespace NetworkFlow
{
class Minimal_Cost_Maximum_Flow
{
    static const std::size_t MaxN = 5000;
    static const std::size_t MaxM = 100000 * 2 + 10;

  public:
    inline void Add_Edge(int u, int v, int f, int c);
    inline std::pair<int, int> MCMF(int s, int t);

  private:
    int n, m, s, t;
    struct Graph
    {
        int cnt = 0;
        int Head[MaxN];
        int to[MaxM], next[MaxM], flow[MaxM], cost[MaxM];
        Graph(void)
        {
            ::memset(Head, -1, sizeof(Head));
        }
        inline void __addedge(int u, int v, int f, int c)
        {
            to[cnt] = v;
            flow[cnt] = f;
            next[cnt] = Head[u];
            cost[cnt] = c;
            Head[u] = cnt++;
        }
    } P;
    int pre[MaxM], vis[MaxM], dis[MaxM], flowc[MaxM], last[MaxM];
    inline bool SPFA(int s, int t)
    {
        ::memset(vis, 0, sizeof(vis));
        ::memset(dis, 0x7f, sizeof(dis));
        ::memset(flowc, 0x7f, sizeof(flowc));
        std::queue<int> q;
        q.push(s);
        vis[s] = true;
        dis[s] = 0;
        pre[t] = -1;
        while (q.size())
        {
            int now = q.front();
            q.pop();
            vis[now] = false;
            for (int i = P.Head[now]; i != -1; i = P.next[i])
            {
                if (P.flow[i] && dis[P.to[i]] > dis[now] + P.cost[i])
                {
                    dis[P.to[i]] = dis[now] + P.cost[i];
                    pre[P.to[i]] = now;
                    last[P.to[i]] = i;
                    flowc[P.to[i]] = std::min(P.flow[i], flowc[now]);
                    if (!vis[P.to[i]])
                    {
                        vis[P.to[i]] = true;
                        q.push(P.to[i]);
                    }
                }
            }
        }
        if (dis[t] == 0x7f7f7f7f)
            return false;
        return true;
    }
};
inline void Minimal_Cost_Maximum_Flow::Add_Edge(int u, int v, int f, int c)
{
    P.__addedge(u, v, f, c);
    P.__addedge(v, u, 0, -c);
}
inline std::pair<int, int> Minimal_Cost_Maximum_Flow::MCMF(int s, int t)
{
    int MaxFlow = 0, MinCost = 0;
    while (SPFA(s, t))
    {
        int now = t;
        while (now != s)
        {
            P.flow[last[now]] -= flowc[t];
            P.flow[last[now] ^ 1] += flowc[t];
            now = pre[now];
        }
        MaxFlow += flowc[t];
        MinCost += dis[t] * flowc[t];
    }
    return std::make_pair(MaxFlow, MinCost);
}
class Maximum_Cost_Maximum_Flow
{
    static const std::size_t MaxN = 5000;
    static const std::size_t MaxM = 100000 * 2 + 10;

  public:
    inline void Add_Edge(int u, int v, int f, int c);
    inline std::pair<int, int> MCMF(int s, int t);

  private:
    int n, m, s, t;
    struct Graph
    {
        int cnt = 0;
        int Head[MaxN];
        int to[MaxM], next[MaxM], flow[MaxM], cost[MaxM];
        Graph(void)
        {
            ::memset(Head, -1, sizeof(Head));
        }
        inline void __addedge(int u, int v, int f, int c)
        {
            to[cnt] = v;
            flow[cnt] = f;
            next[cnt] = Head[u];
            cost[cnt] = c;
            Head[u] = cnt++;
        }
    } P;
    int pre[MaxM], vis[MaxM], dis[MaxM], flowc[MaxM], last[MaxM];
    inline bool SPFA(int s, int t)
    {
        ::memset(vis, 0, sizeof(vis));
        ::memset(dis, 0x80, sizeof(dis));
        ::memset(flowc, 0x7f, sizeof(flowc));
        std::queue<int> q;
        q.push(s);
        vis[s] = true;
        dis[s] = 0;
        pre[t] = -1;
        while (q.size())
        {
            int now = q.front();
            q.pop();
            vis[now] = false;
            for (int i = P.Head[now]; i != -1; i = P.next[i])
            {
                if (P.flow[i] && dis[P.to[i]] < dis[now] + P.cost[i])
                {
                    dis[P.to[i]] = dis[now] + P.cost[i];
                    pre[P.to[i]] = now;
                    last[P.to[i]] = i;
                    flowc[P.to[i]] = std::min(P.flow[i], flowc[now]);
                    if (!vis[P.to[i]])
                    {
                        vis[P.to[i]] = true;
                        q.push(P.to[i]);
                    }
                }
            }
        }
        if (dis[t] == 0x80808080)
            return false;
        return true;
    }
};
inline void Maximum_Cost_Maximum_Flow::Add_Edge(int u, int v, int f, int c)
{
    P.__addedge(u, v, f, c);
    P.__addedge(v, u, 0, -c);
}
inline std::pair<int, int> Maximum_Cost_Maximum_Flow::MCMF(int s, int t)
{
    int MaxFlow = 0, MaxCost = 0;
    while (SPFA(s, t))
    {
        int now = t;
        while (now != s)
        {
            P.flow[last[now]] -= flowc[t];
            P.flow[last[now] ^ 1] += flowc[t];
            now = pre[now];
        }
        MaxFlow += flowc[t];
        MaxCost += dis[t] * flowc[t];
    }
    return std::make_pair(MaxFlow, MaxCost);
}
//Based on Edmonds-Karp+SPFA
//Next step: use Primal-Dual Algorithm
} // namespace NetworkFlow

int main()
{
    NetworkFlow::Minimal_Cost_Maximum_Flow P1;
    NetworkFlow::Maximum_Cost_Maximum_Flow P2;
    //::scanf("%d%d%d%d", &n, &m, &s, &t);
    int n1;
    ::scanf("%d", &n1);
    t = n = n1 * 2 + 2;
    s = n - 1;
    for (int i = 1; i <= n1; i++)
    {
        P1.Add_Edge(s, i, 1, 0);
        P2.Add_Edge(s, i, 1, 0);
        P1.Add_Edge(i + n1, t, 1, 0);
        P2.Add_Edge(i + n1, t, 1, 0);
        for (int j = 1; j <= n1; j++)
        {
            int a;
            ::scanf("%d", &a);
            P1.Add_Edge(i, j + n1, 1, a);
            P2.Add_Edge(i, j + n1, 1, a);
        }
    }
    std::cout << P1.MCMF(s, t).second << std::endl
              << P2.MCMF(s, t).second;
}
