#include <bits/stdc++.h>
#include <ext/pb_ds/priority_queue.hpp>
const int maxn = 5000 + 10;
const int maxm = 200000 + 10;
struct Node
{
    int id, firstson, firstsonf, cnt;
} Nodes[maxn];
struct Edge
{
    int from, to, next, nextf;
    double Value;
} Edges[maxm];
int n, m;
int ans;
int maxans;
int pp;
double E;
double h[maxn]; //A*估价
//__gnu_pbds::priority_queue<int,std::less<int>,__gnu_pbds::thin_heap_tag> Example;
int mp_eptr = 0;
inline void Make_Path(int u, int v, double d)
{
    Edges[mp_eptr].next = Nodes[u].firstson;
    Edges[mp_eptr].Value = d;
    Edges[mp_eptr].to = v;
    Edges[mp_eptr].nextf = Nodes[v].firstsonf;
    Edges[mp_eptr].from = u;
    Nodes[v].firstsonf = mp_eptr;
    Nodes[u].firstson = mp_eptr++;
}
inline void Dijkstra_Fill(void) //Get h[]
{
    memset(h, 0x7f, sizeof(h));
    __gnu_pbds::priority_queue<std::pair<double, int>, std::greater<std::pair<double, int>>, __gnu_pbds::thin_heap_tag> tool;
    h[n] = 0.0;
    tool.push(std::make_pair(0.0, n));
    while (!tool.empty())
    {
        int here = tool.top().second;
        tool.pop();
        for (int i = Nodes[here].firstsonf; i != -1; i = Edges[i].nextf)
            if (h[Edges[i].from] > h[here] + Edges[i].Value)
                tool.push(std::make_pair(h[here] + Edges[i].Value, Edges[i].from));
    }
    return;
}
inline void Prepare(void)
{
    std::scanf("%d%d%lf", &n, &m, &E);
    for (int i = 1; i <= n; i++)
    {
        Nodes[i].id = i;
        Nodes[i].firstson = -1;
        Nodes[i].firstsonf = -1;
    }
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        double d;
        std::scanf("%d%d%lf", &u, &v, &d);
        Make_Path(u, v, d);
    }
    Dijkstra_Fill();
    pp=E/h[1];
}
struct State
{
    int pos;
    double f;
    double p;
};
struct CMP
{
    bool operator()(State a, State b)
    {
        return a.f > b.f;
    }
};
inline void A_Star(void)
{
    __gnu_pbds::priority_queue<State, CMP, __gnu_pbds::thin_heap_tag> Tool;
    State start;
    start.pos = 1;
    start.f = 0.0;
    start.p = 0.0;
    Tool.push(start);
    while (!Tool.empty())
    {
        State now = Tool.top();
        Nodes[now.pos].cnt++;
        Tool.pop();
        if (now.f > E)
            return;
        if (now.pos == n)
        {
            E -= now.f;
            ans++;
            continue;
        }
        if(Nodes[now.pos].cnt>pp)continue;
        for (int i = Nodes[now.pos].firstson; i != -1; i = Edges[i].next)
        {
            State newstate;
            newstate.pos=Edges[i].to;
            newstate.p=now.p+Edges[i].Value;
            newstate.f=h[newstate.pos]+now.p+Edges[i].Value;
            Tool.push(newstate);
        }
    }
}
int main()
{
    Prepare();
    A_Star();
    printf("%d", ans);
}