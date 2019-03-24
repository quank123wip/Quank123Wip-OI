//Minimal Cost Maximum Flow Algorithm
//Coding with ISO C++ 11 Standard
//By Quank123Wip 2019,Based on my Maximum Flow Algorithm
#include <bits/stdc++.h>
int n, m, s, t;
int cnt = 0;
const int INF = 0x7f7f7f7f;
namespace NetworkFlow
{
class Maximum_Flow
{
    static const std::size_t MaxN = 10000;
    static const std::size_t MaxM = 100000 * 2 + 10;

  public:
    inline void Add_Edge(int u, int v, int f);
    inline int Dinic(int s, int t);
    struct Graph
    {
        int cnt = 0;
        int Head[MaxN], Cur[MaxN], Depth[MaxN];
        int to[MaxM], next[MaxM], flow[MaxM];
        Graph(void)
        {
            ::memset(Head, -1, sizeof(Head));
        }
        inline void __addedge(int u, int v, int f)
        {
            to[cnt] = v;
            flow[cnt] = f;
            next[cnt] = Head[u];
            Head[u] = cnt++;
        }
    } P;
    inline bool BFS(int s, int t)
    {
        ::memset(P.Depth, 0x7f, sizeof(P.Depth));
        std::queue<int> q; //From C++ Standard Library,Please include filee "queue"
        for (int i = 1; i <= n; i++)
            P.Cur[i] = P.Head[i];
        P.Depth[s] = 0;
        q.push(s);
        while (q.size())
        {
            int now = q.front();
            q.pop();
            for (int i = P.Head[now]; i != -1; i = P.next[i])
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
    inline int DFS(int now, int MinFlow, int t)
    {
        if (now == t || !MinFlow)
            return MinFlow;
        int Flow = 0, f;
        for (int i = P.Cur[now]; i != -1; i = P.next[i])
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
inline void Maximum_Flow::Add_Edge(int u, int v, int f)
{
    P.__addedge(u, v, f);
    P.__addedge(v, u, 0);
}
inline int Maximum_Flow::Dinic(int s, int t)
{
    int MaxFlow = 0;
    //BFS(s,t);
    while (BFS(s, t))
        while (int now = DFS(s, 1e9, t))
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
    inline void Add_Edge(int u, int v, int f, int c);
    inline std::pair<int, int> MCMF(int s, int t);
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
//Based on Edmonds-Karp+SPFA
//Next step: use Primal-Dual Algorithm
} // namespace NetworkFlow
int main()
{
    NetworkFlow::Maximum_Flow P;
    //int n,m,s,t;
    //::scanf("%d%d%d%d",&n,&m,&s,&t);
    int K,N,M=0;
    std::cin>>K>>N;
    n=K+N+2;
    t=n;
    s=0;
    for(int i=1;i<=K;i++)
    {
        int a;
        std::cin>>a;
        M+=a;
        P.Add_Edge(N+i,t,a);
    }
    for(int i=1;i<N;i++)
    {
        int p;
        std::cin>>p;
        P.Add_Edge(s,i,1);
        for(int j=0;j<p;j++)
        {
            int orz;
            std::cin>>orz;
            P.Add_Edge(i,N+orz,1);
        }
    }
    int qaq=P.Dinic(s,t);
    if(qaq!=M)
    {
        puts("No Solution!");
        exit(0);
    }
    for(int i=N+1;i<=N+K;i++)
    {
        std::cout<<i-N<<": ";
        for(int j=P.P.Head[i];j!=-1;j=P.P.next[j])
        {
            if(P.P.to[j]!=t)
            {
                if(P.P.flow[j^1]==0)
                {
                    std::cout<<P.P.to[j]<<" ";
                }
            }
        }
        std::cout<<std::endl;
    }
}//Maximum Flow

