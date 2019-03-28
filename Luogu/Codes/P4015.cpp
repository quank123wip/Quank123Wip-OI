#include <bits/stdc++.h>
const int MaxN = 2010;
const int INF = 0x3f3f3f3f;
struct Edge
{
    int to, next, flow, cost;
};
Edge P[200010];
int head[MaxN], dis[MaxN], vis[MaxN], flow[MaxN], pre[MaxN], MaxFlow, Mincost;
int cont=1;
inline void AddEdge(int u, int v, int f, int c)
{
    P[++cont]=((Edge){v, head[u], f, c});
    head[u] = cont;
    P[++cont]=((Edge){u, head[v], 0, -c});
    head[v] = cont;
}
inline void MCMF(int s, int t)
{
    std::queue<int> q;
    MaxFlow = Mincost = 0;
    for (;;)
    {
        memset(dis, 0x3f, sizeof dis);
        q.push(s);
        flow[s] = INF;
        dis[s] = 0;
        while (q.size())
        {
            int now = q.front();
            q.pop();
            vis[now] = false;
            for (int i = head[now]; i != -1; i = P[i].next)
            {
                if (P[i].flow && dis[P[i].to] > dis[now] + P[i].cost)
                {
                    dis[P[i].to] = dis[now] + P[i].cost;
                    flow[P[i].to] = std::min(flow[now], P[i].flow);
                    pre[P[i].to] = i;
                    if (!vis[P[i].to])
                    {
                        q.push(P[i].to);
                        vis[P[i].to] = true;
                    }
                }
            }
        }
        if (dis[t] == INF)
            return;
        for (int i = pre[t]; i; i = pre[P[i ^ 1].to])
            P[i].flow -= flow[t], P[i ^ 1].flow += flow[t];
        MaxFlow += flow[t];
        Mincost += dis[t] * flow[t];
    }
}
int n, m, a[MaxN], b[MaxN], c[MaxN][MaxN];
using std::cin;
using std::cout;
using std::endl;
int main()
{
    memset(head, -1, sizeof head);
    cont=1;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= m; i++)
        cin >> b[i];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> c[i][j];
    for (int i = 1; i <= n; i++)
    {
        AddEdge(n+m+1,i,a[i],0);
        for (int j = 1; j <= m; j++)
            AddEdge(i,j+n,INF,c[i][j]);
    }
    for (int j = 1; j <= m; j++)
        AddEdge(j+n,n+m+2,b[j],0);
    MCMF(n+m+1,n+m+2);
    cout<<Mincost<<endl;
    memset(head, -1, sizeof head);
    cont=1;
    for (int i = 1; i <= n; i++)
    {
        AddEdge(n+m+1,i,a[i],0);
        for (int j = 1; j <= m; j++)
            AddEdge(i,j+n,INF,-c[i][j]);
    }
    for (int j = 1; j <= m; j++)
        AddEdge(j+n,n+m+2,b[j],0);
    MCMF(n+m+1,n+m+2);
    cout<<-Mincost;
}