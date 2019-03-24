#include<bits/stdc++.h>
#include<ext/pb_ds/priority_queue.hpp>
using namespace std;
const int maxn=1000100;
const int maxm=2*maxn;

int n,m,s;
int dis[maxn];
int edgec;

struct node
{
    int id;
    int son;
};



struct edge
{
    int from;
    int to;
    int next;
    int val;
};

node nodes[maxn];
edge edges[maxn];

inline void addedge(int from,int to,int val)
{
    edges[edgec].from=from;
    edges[edgec].to=to;
    edges[edgec].val=val;
    edges[edgec].next=nodes[edges[edgec].from].son;
    nodes[edges[edgec].from].son=edgec;
    edgec++;
}

int main()
{
    cin>>n>>m>>s;
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
    for(int i=1;i<=n;i++)
        nodes[i].id=i,nodes[i].son=-1;
    for(int i=0;i<m;i++)
    {
        int from,to,val;
        scanf("%d%d%d",&from,&to,&val);
        addedge(from,to,val);
    }
    __gnu_pbds::priority_queue<pair<int,int>,greater<pair<int,int> >,__gnu_pbds::pairing_heap_tag>pq;
    pq.push(make_pair(dis[s],s));
    while(!pq.empty())
    {
        auto p=pq.top();
        pq.pop();
        if(p.first>dis[p.second])continue;
        for(int i=nodes[p.second].son;i!=-1;i=edges[i].next)
        {
            if(dis[p.second]+edges[i].val<dis[edges[i].to])
            {
                dis[edges[i].to]=dis[p.second]+edges[i].val;
                pq.push(make_pair(dis[edges[i].to],edges[i].to));
            }
        }
    }
    for(int i=1;i<=n;i++)
        printf("%d ",dis[i]);
}