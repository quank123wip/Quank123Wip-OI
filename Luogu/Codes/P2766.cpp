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
int a[510], f[510], len,ans;
int main()
{
    //int n,m,s,t;
    //::scanf("%d%d%d%d",&n,&m,&s,&t);
    for (int i = 0; i < maxn; i++)
        P.Head[i] = -1;
    int n1;
    cin >> n1;
    n = 2*n1+2;
    s=n-1;
    t=n;
    for (int i = 1; i <= n1; i++)
        cin >> a[i];
    for (int i = 1; i <= n1; i++)
        f[i] = 1;
    for (int i = 1; i <= n1; i++)
    {
        for (int j = 1; j < i; j++)
            if (a[j] <= a[i])
                f[i] = std::max(f[i], f[j] + 1);
        len=std::max(f[i],len);
    }
    for(int i=1;i<=n1;i++)
    {
        P.AddEdge(i,i+n1,1);
        if(f[i]==1)
            P.AddEdge(s,i,1);
        if(f[i]==len)
            P.AddEdge(i+n1,t,1);
        for(int j=1;j<i;j++)
            if(a[i]>=a[j]&&f[j]+1==f[i])
                P.AddEdge(j+n1,i,1);
    }
    ans+=Dinic();
    cout<<len<<endl<<ans<<endl;
    P.AddEdge(s,1,INF);
    P.AddEdge(1,1+n1,INF);
    if(f[n1]==len)
    {
        P.AddEdge(n1,n1+n1,INF);
        P.AddEdge(n1+n1,t,INF);
    }
    ans+=Dinic();
    cout<<ans<<endl;

} //Maximum Flow