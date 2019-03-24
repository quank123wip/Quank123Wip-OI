#include <cstdio>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <queue>
using namespace std;
const int maxn = 1010;
int n;
struct Node
{
    int son;
    int set_from;
    Node(void)
    {
        son = -1;
    }
} Nodes[maxn];
inline int Find_set(int p)
{
    if (p != Nodes[p].set_from)
        Nodes[p].set_from = Find_set(Nodes[p].set_from);
    return Nodes[p].set_from;
}
inline void Union(int a, int b)
{
    if (Find_set(a) == Find_set(b))
        return;
    Nodes[Find_set(a)].set_from = Find_set(b);
}
struct Edge
{
    int from, to, Value;
    bool operator < (const Edge p)const
    {
        return this->Value<p.Value;
    }
} Edges[100010];
int main() //Kruskal
{
    while (scanf("%d", &n))
    {
        int ans=0;
        if(n==0)return 0;
        for (int i = 1; i <= n; i++)
        {
            Nodes[i].son = -1;
            Nodes[i].set_from = i;
        }
        for (int i = 0; i < (n * (n - 1)) / 2; i++)
        {
            scanf("%d%d%d",&Edges[i].from,&Edges[i].to,&Edges[i].Value);
        }
        sort(Edges,Edges+(n * (n - 1)) / 2);
        for (int i = 0; i < (n * (n - 1)) / 2; i++)
        {
            if(Find_set(Edges[i].from)!=Find_set(Edges[i].to))
            {
                ans+=Edges[i].Value;
                Union(Edges[i].from,Edges[i].to);
            }
        }
        printf("%d\n",ans);
    }
}