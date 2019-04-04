#include <bits/stdc++.h>
using namespace std;
namespace ISAP
{
static const int maxn = 200010;
static const int inf = 0x3f3f3f3f;
int n, s, t;
int cnt = 1;
int maxflow;
int head[maxn], cur[maxn], flow[maxn], depth[maxn], gap[maxn];
int to[maxn], next[maxn], f[maxn];
inline void addedge(int u, int v, int w)
{
    to[++cnt] = v;
    f[cnt] = w;
    next[cnt] = head[u];
    head[u] = cnt;
    to[++cnt] = u;
    f[cnt] = 0;
    next[cnt] = head[v];
    head[v] = cnt;
}
inline void bfs(int t)
{
    memset(depth, -1, sizeof depth);
    memset(gap, 0, sizeof gap);
    queue<int> q;
    depth[t] = 0;
    gap[0] = 1;
    q.push(t);
    while (q.size())
    {
        int now = q.front();
        q.pop();
        for (int i = head[now]; i; i = next[i])
        {
            int v = to[i];
            if (depth[v] != -1)
                continue;
            depth[v] = depth[now] + 1;
            q.push(v);
            gap[depth[v]]++;
        }
    }
}
inline int dfs(int now, int flow)
{
    if (now == t)
    {
        maxflow += flow;
        return flow;
    }
    int used = 0;
    for (int i = cur[now]; i; i = next[i])
    {
        cur[now] = i;
        if (f[i] && depth[to[i]] + 1 == depth[now])
        {
            int p = dfs(to[i], min(flow - used, f[i]));
            if(p)
            {
            f[i] -= p;
            f[i ^ 1] += p;
            used += p;
            }
            if (used == flow)
                return used;
        }
    }
    --gap[depth[now]];
    if (!gap[depth[now]])
        depth[s] = n + 1;
    depth[now]++;
    gap[depth[now]]++;
    return used;
}
inline int ISAP()
{
    maxflow = 0;
    bfs(t);
    while (depth[s] < n)
    {
        memcpy(cur, head, sizeof head);
        dfs(s, inf);
    }
    return maxflow;
}
} // namespace ISAP
int main()
{
    int n, m, s, t;
    scanf("%d%d%d%d", &n, &m, &s, &t);
    ISAP::n = n;
    ISAP::s = s;
    ISAP::t = t;
    for (int i = 0; i < m; i++)
    {
        int u, v, f;
        scanf("%d%d%d", &u, &v, &f);
        ISAP::addedge(u, v, f);
    }
    printf("%d", ISAP::ISAP());
}