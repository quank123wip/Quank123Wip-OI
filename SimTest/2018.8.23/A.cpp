#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
int n, t;
int Edgec;
int Dist[10010];
struct Node
{
    int son;
    Node()
    {
        son=-1;
    }
} Nodes[10010];
struct Edge
{
    int from;
    int to;
    int Value;
    int next;
} Edges[10010];
inline void Addpath(int from, int to, int Value)
{
    Edges[Edgec].next = Nodes[from].son;
    Edges[Edgec].from = from;
    Edges[Edgec].to = to;
    Edges[Edgec].Value = Value;
    Nodes[from].son = Edgec;
    Edgec++;
}
inline void Dijkstra(int Start)
{
    for (int i = 1; i <= n; i++)
        Dist[i] = i != Start ? 0x3f3f3f3f : 0;
    priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > >pq;
    pq.push(make_pair(Dist[Start],Start));
    while(!pq.empty())
    {
        pair<int,int> now=pq.top();
        pq.pop();
        if(now.first>Dist[now.second])continue;
        for(int i=Nodes[now.second].son;i!=-1;i=Edges[i].next)
        {
            if(Dist[Edges[i].to]>Dist[now.second]+Edges[i].Value)
            {
                Dist[Edges[i].to]=Dist[now.second]+Edges[i].Value;
                pq.push(make_pair(Dist[Edges[i].to],Edges[i].to));
            }
        }
    }
}
int main()
{
    scanf("%d%d", &t, &n);
    for (int i = 0; i < t; i++)
    {
        int from, to, Value;
        scanf("%d%d%d", &from, &to, &Value);
        Addpath(from, to, Value);
        Addpath(to, from, Value);
    }
    Dijkstra(n);
    printf("%d", Dist[1]);
}
