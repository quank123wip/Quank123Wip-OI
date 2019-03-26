//Minimal Cost Maximum Flow Algorithm
//Coding with ISO C++ 11 Standard
//By Quank123Wip 2019,Based on my Maximum Flow Algorithm
#include <bits/stdc++.h>
int n, m, s, t;
int cnt = 0;
const int INF = 0x3f3f3f3f;
const int maxn = 100000 + 10;
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
int next[maxn];
inline bool BFS(void)
{
    for(int i=0;i<maxn;i++)
        P.Depth[i]=INF;
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
    return P.Depth[t] < INF;
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
            if(P.Edges[i].to!=t)next[now>>1]=P.Edges[i].to>>1;
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
        while(int now=DFS(s,1e9))
            MaxFlow += now;

    return MaxFlow;
}
using std::cin;
using std::cout;
using std::endl;
int nums[100000];
bool pc[1000010];
int main()
{
    //int n,m,s,t;
    //::scanf("%d%d%d%d",&n,&m,&s,&t);
    for (int i = 0; i < maxn; i++)
        P.Head[i] = -1;
    n=100002;
    s=n-1;
    t=n;
    int n1,p=0,now=0;
    cin>>n1;
    while(p<=n1)
    {
        now++;
        P.AddEdge(s,now<<1,1);
        P.AddEdge((now<<1)|1,t,1);
        for(int i=std::sqrt(now)+1;i*i<now<<1;i++)
            P.AddEdge((i*i-now)<<1,(now<<1)|1,1);
        int f=Dinic();
        if(!f)
            nums[++p]=now;

    }
    cout<<--now<<endl;
    for(int i=1;i<=n1;i++)
    {
        if(!pc[nums[i]])
        {
            int p=nums[i];pc[p]=true;
            while(p)
            {
                printf("%d ",p);
                p=next[p];
                pc[p]=true;
            }
            puts("");
        }
    }

} //Maximum Flow