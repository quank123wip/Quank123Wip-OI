#include <bits/stdc++.h>
namespace ISAP
{
static const int MaxN = 100010;
static const int MaxM = 100010;
static const int inf = 0x3f3f3f3f;
int n, s, t;
int cnt = 1;
int head[MaxN], dep[MaxN], gap[MaxN], cur[MaxN];
int to[MaxM], f[MaxN], next[MaxM];
int maxflow;
inline void addedge(int u, int v, int flow)
{
    to[++cnt] = v;
    f[cnt] = flow;
    next[cnt] = head[u];
    head[u] = cnt;
    to[++cnt] = u;
    f[cnt] = 0;
    next[cnt] = head[v];
    head[v] = cnt;
}
inline void bfs(int t)
{
    memset(dep, -1, sizeof dep);
    memset(gap, 0, sizeof gap);
    dep[t] = 0;
    gap[0] = 1;
    std::queue<int> q;
    q.push(t);
    while (q.size())
    {
        int now = q.front();
        q.pop();
        for (int i = head[now]; i; i = next[i])
        {
            if (dep[to[i]] != -1)
                continue;
            dep[to[i]] = dep[now] + 1;
            q.push(to[i]);
            gap[dep[to[i]]]++;
        }
    }
}
inline int dfs(int from, int flow)
{
    if (from == t)
    {
        maxflow += flow;
        return flow;
    }
    int used = 0;
    for (int i = head[from]; i; i = next[i])
    {
        if (f[i] && dep[to[i]] + 1 == dep[from])
        {
            int p = dfs(to[i], std::min(f[i], flow - used));
            if (p)
            {
                f[i] -= p;
                f[i ^ 1] -= p;
                used += p;
            }
            if(used==flow)return used;
        }
    }
    --gap[dep[from]];
    if (!gap[dep[from]])
        dep[s] = n + 1;
    dep[from]++;
    return used;
}
int ISAP()
{
    maxflow = 0;
    bfs(t);
    while (dep[s] < n)
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