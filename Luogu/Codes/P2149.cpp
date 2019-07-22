#include <bits/stdc++.h>
#include <bits/extc++.h>
using __gnu_pbds::priority_queue;
using std::array;
using std::cerr;
using std::cin;
using std::endl;
using std::cout;
using std::end;
using std::greater;
using std::istream;
using std::lower_bound;
using std::make_pair;
using std::max;
using std::min;
using std::ostream;
using std::pair;
using std::set;
using std::upper_bound;
using std::vector;
const int MaxN = 10000;
int n, m, s1, t1, s2, t2;
priority_queue<pair<int, int>, greater<pair<int, int>>> pq;
namespace Graph
{
int to[MaxN << 2], next[MaxN << 2], val[MaxN << 2], head[MaxN];
inline void AddEdge(int u, int v, int w)
{
    static int cnt = 1;
    to[cnt] = v;
    val[cnt] = w;
    next[cnt] = head[u];
    head[u] = cnt++;
}
inline array<int, MaxN> Dijkstra(int s)
{
    array<int, MaxN> dis;
    for (auto &i : dis)
        i = 0x3f3f3f3f;
    dis[s] = 0;
    pq.clear();
    pq.push(make_pair(0, s));
    while (pq.size())
    {
        auto p = pq.top();
        pq.pop();
        for (auto i = head[p.second]; i; i = next[i])
            if (dis[to[i]] > dis[p.second] + val[i])
                dis[to[i]] = dis[p.second] + val[i],
                pq.push(make_pair(dis[to[i]], to[i]));
    }
    return dis;
}

} // namespace Graph
namespace Graph1
{
int to[MaxN << 2], next[MaxN << 2], val[MaxN << 2], head[MaxN], deg[MaxN];
inline void AddEdge(int u, int v, int w)
{
    static int cnt = 1;
    //cerr<<"1:"<<u<<"->"<<v<<":"<<w<<endl;
    to[cnt] = v;
    val[cnt] = w;
    next[cnt] = head[u];
    head[u] = cnt++;
    deg[v]++;
}
} // namespace Graph1
namespace Graph2
{
int to[MaxN << 2], next[MaxN << 2], val[MaxN << 2], head[MaxN], deg[MaxN];
inline void AddEdge(int u, int v, int w)
{
    static int cnt = 1;
    //cerr<<"2:"<<u<<"->"<<v<<":"<<w<<endl;
    to[cnt] = v;
    val[cnt] = w;
    next[cnt] = head[u];
    head[u] = cnt++;
    deg[v]++;
}
} // namespace Graph2
inline void Process1(array<int, MaxN> dis1, array<int, MaxN> dis2, array<int, MaxN> dis3, array<int, MaxN> dis4)
{
    using Graph::head;
    using Graph::next;
    using Graph::to;
    using Graph::val;
    using Graph1::AddEdge;
    for (int i = 1; i <= n; i++)
        for (auto j = head[i]; j; j = next[j])
        {
            if (dis1[t1] == dis1[i] + val[j] + dis2[to[j]] && dis3[t2] == dis3[i] + val[j] + dis4[to[j]])
                AddEdge(i, to[j], val[j]);
        }
}
inline void Process2(array<int, MaxN> dis1, array<int, MaxN> dis2, array<int, MaxN> dis3, array<int, MaxN> dis4)
{
    using Graph::head;
    using Graph::next;
    using Graph::to;
    using Graph::val;
    using Graph2::AddEdge;
    for (int i = 1; i <= n; i++)
        for (auto j = head[i]; j; j = next[j])
        {
            if (dis1[t1] == dis1[i] + val[j] + dis2[to[j]] && dis3[t2] == dis4[i] + val[j] + dis3[to[j]])
                AddEdge(i, to[j], val[j]);
        }
}
int dp1[MaxN << 1], dp2[MaxN << 1],ans1,ans2;
inline void ProcessAns1(void)
{
    using namespace Graph1;
    std::queue<int>q;
    for(int i=1;i<=n;i++)
        if(!deg[i])q.push(i);
    while(q.size())
    {
        auto u=q.front();
        q.pop();
        for(auto i=head[u];i;i=next[i])
        {
            deg[to[i]]--;
            dp1[to[i]]=max(dp1[to[i]],dp1[u]+val[i]);
            if(!deg[to[i]])
                q.push(to[i]);
        }
    }
    for(auto i:dp1)
        ans1=max(ans1,i);
}
inline void ProcessAns2(void)
{
    using namespace Graph2;
    std::queue<int>q;
    for(int i=1;i<=n;i++)
        if(!deg[i])q.push(i);
    while(q.size())
    {
        auto u=q.front();
        q.pop();
        for(auto i=head[u];i;i=next[i])
        {
            deg[to[i]]--;
            dp2[to[i]]=max(dp2[to[i]],dp2[u]+val[i]);
            if(!deg[to[i]])
                q.push(to[i]);
        }
    }
    for(auto i:dp2)
        ans2=max(ans2,i);
}
int main()
{
    //std::ios::sync_with_stdio(false);
    scanf("%d%d", &n, &m);
    scanf("%d%d%d%d", &s1, &t1, &s2, &t2);
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        Graph::AddEdge(u, v, w);
        Graph::AddEdge(v, u, w);
    }
    auto dis1 = Graph::Dijkstra(s1);
    auto dis2 = Graph::Dijkstra(t1);
    auto dis3 = Graph::Dijkstra(s2);
    auto dis4 = Graph::Dijkstra(t2);
    Process1(dis1,dis2,dis3,dis4);
    Process2(dis1,dis2,dis3,dis4);
    ProcessAns1();
    ProcessAns2();
    printf("%d", max(ans1,ans2));
    return 0;
}