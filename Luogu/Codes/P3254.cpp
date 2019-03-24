//Minimal Cost Maximum Flow Algorithm
//Coding with ISO C++ 11 Standard
//By Quank123Wip 2019,Based on my Maximum Flow Algorithm
#include <bits/stdc++.h>
long long n, m, s, t;
long long cnt = 0;
const long long INF = 0x7f7f7f7f;
namespace NetworkFlow
{
class Maximum_Flow
{
    static const std::size_t MaxN = 10000;
    static const std::size_t MaxM = 100000 * 2 + 10;

  public:
    inline void Add_Edge(long long u, long long v, long long f);
    inline long long Dinic(long long s, long long t);

  private:
    struct Graph
    {
        long long cnt = 0;
        long long Head[MaxN], Cur[MaxN], Depth[MaxN];
        long long to[MaxM], next[MaxM], flow[MaxM];
        Graph(void)
        {
            ::memset(Head, -1, sizeof(Head));
        }
        inline void __addedge(long long u, long long v, long long f)
        {
            to[cnt] = v;
            flow[cnt] = f;
            next[cnt] = Head[u];
            Head[u] = cnt++;
        }
    } P;
    inline bool BFS(long long s, long long t)
    {
        ::memset(P.Depth, 0x7f, sizeof(P.Depth));
        std::queue<long long> q; //From C++ Standard Library,Please include filee "queue"
        for (long long i = 1; i <= n; i++)
            P.Cur[i] = P.Head[i];
        P.Depth[s] = 0;
        q.push(s);
        while (q.size())
        {
            long long now = q.front();
            q.pop();
            for (long long i = P.Head[now]; i != -1; i = P.next[i])
            {
                if (P.Depth[P.to[i]] > 1e9 && P.flow[i])
                {
                    P.Depth[P.to[i]] = P.Depth[now] + 1;
                    q.push(P.to[i]);
                }
            }
        }
        return P.Depth[t] < 1e9;
    }
    inline long long DFS(long long now, long long MinFlow, long long t)
    {
        if (now == t || !MinFlow)
            return MinFlow;
        long long Flow = 0, f;
        for (long long i = P.Cur[now]; i != -1; i = P.next[i])
        {
            P.Cur[now] = i;
            if (P.Depth[P.to[i]] == P.Depth[now] + 1 && (f = DFS(P.to[i], std::min(MinFlow, P.flow[i]), t)))
            {
                MinFlow -= f;
                Flow += f;
                P.flow[i] -= f;
                P.flow[i ^ 1] += f;
                if (!MinFlow)
                    break;
            }
        }
        return Flow;
    }
};
inline void Maximum_Flow::Add_Edge(long long u, long long v, long long f)
{
    P.__addedge(u, v, f);
    P.__addedge(v, u, 0);
}
inline long long Maximum_Flow::Dinic(long long s, long long t)
{
    long long MaxFlow = 0;
    //BFS(s,t);
    while (BFS(s, t))
        while (long long now = DFS(s, 1e9, t))
            MaxFlow += now;
    return MaxFlow;
}
//Based on Dinic
//Next step: use ISAP and HLPP Algorithm;
class Minimal_Cost_Maximum_Flow
{
    static const std::size_t MaxN = 5000;
    static const std::size_t MaxM = 100000 * 2 + 10;

  public:
    inline void Add_Edge(long long u, long long v, long long f, long long c);
    inline std::pair<long long, long long> MCMF(long long s, long long t);

  private:
    long long n, m, s, t;
    struct Graph
    {
        long long cnt = 0;
        long long Head[MaxN];
        long long to[MaxM], next[MaxM], flow[MaxM], cost[MaxM];
        Graph(void)
        {
            ::memset(Head, -1, sizeof(Head));
        }
        inline void __addedge(long long u, long long v, long long f, long long c)
        {
            to[cnt] = v;
            flow[cnt] = f;
            next[cnt] = Head[u];
            cost[cnt] = c;
            Head[u] = cnt++;
        }
    } P;
    long long pre[MaxM], vis[MaxM], dis[MaxM], flowc[MaxM], last[MaxM];
    inline bool SPFA(long long s, long long t)
    {
        ::memset(vis, 0, sizeof(vis));
        ::memset(dis, 0x7f, sizeof(dis));
        ::memset(flowc, 0x7f, sizeof(flowc));
        std::queue<long long> q;
        q.push(s);
        vis[s] = true;
        dis[s] = 0;
        pre[t] = -1;
        while (q.size())
        {
            long long now = q.front();
            q.pop();
            vis[now] = false;
            for (long long i = P.Head[now]; i != -1; i = P.next[i])
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
inline void Minimal_Cost_Maximum_Flow::Add_Edge(long long u, long long v, long long f, long long c)
{
    P.__addedge(u, v, f, c);
    P.__addedge(v, u, 0, -c);
}
inline std::pair<long long, long long> Minimal_Cost_Maximum_Flow::MCMF(long long s, long long t)
{
    long long MaxFlow = 0, MinCost = 0;
    while (SPFA(s, t))
    {
        long long now = t;
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
//Based on Edmonds-Karp+SPFA
//Next step: use Primal-Dual Algorithm
} // namespace NetworkFlow


signed main()
{
    NetworkFlow::Minimal_Cost_Maximum_Flow po;
    //::scanf("%d%d%d%d", &n, &m, &s, &t);
    long long N;
    std::cin>>N;
    long long r[2010];
    long long P,M,F,Ns,S;
    n=2*N+1;
    s=0;
    t=2*N+1;
    for(long long i=1;i<=N;i++)
    {
        std::cin>>r[i];
    }
    std::cin>>P>>M>>F>>Ns>>S;
    for(long long i=1;i<=N;i++)
    {
        po.Add_Edge(s,N+i,r[i],0);
        po.Add_Edge(i,t,r[i],0);
        if(i!=N)po.Add_Edge(N+i,N+i+1,INF,0);
        if(i+M<=N)po.Add_Edge(N+i,i+M,INF,F);
        if(i+Ns<=N)po.Add_Edge(N+i,i+Ns,INF,S);
        po.Add_Edge(s,i,INF,P);
    }
    auto p = po.MCMF(s, t);
    std::cout << p.second;
}

