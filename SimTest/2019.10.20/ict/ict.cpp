#include<bits/stdc++.h>
int n,m;
const int MaxN=1000010;
struct Edge
{
    long long s,t,next,a,b;
}Edges[MaxN],Edges2[MaxN];
long long Head[MaxN],dfn[MaxN],low[MaxN],id,vis[MaxN],ans,fa[MaxN];
inline void AddEdge(int s,int t,int a,int b)
{
    static int cnt=2;
    Edges[cnt]={s,t,Head[s],a,b};
    Head[s]=cnt++;
}
inline void AddEdge2(int s,int t,int a,int b)
{
    static int cnt=1;
    Edges2[cnt]={s,t,Head[s],a,b};
    cnt++;
}
inline void Tarjan(int u)
{
    dfn[u]=low[u]=++id;
    for(int i=Head[u];i;i=Edges[i].next)
    {
        if(vis[i^1])
            continue;
        vis[i]=true;
        if(!dfn[Edges[i].t])
        {
            Tarjan(Edges[i].t);
            low[u]=std::min(low[u],low[Edges[i].t]);
            if(dfn[u]<low[Edges[i].t])
                ans=ans-Edges[i].a+Edges[i].b;
        }
        else
            low[u]=std::min(low[u],low[Edges[i].t]);
    }
}
inline int find(int x)
{
    if(fa[x]==x)return fa[x];
    return fa[x]=find(fa[x]);
}
signed main()
{
    freopen("ict.in","r",stdin);
    freopen("ict.out","w",stdout);
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;i++)
    {
        long long s,t,a,b;
        scanf("%d%d%d%d",&s,&t,&a,&b);
        AddEdge(s,t,a,b);
        AddEdge(t,s,a,b);
        AddEdge2(s,t,a,b);
        fa[i]=i;
    }
    for(int i=1;i<=n;i++)
        if(!dfn[i])
            Tarjan(i);
    std::sort(Edges2+1,Edges2+1+m,[](Edge a,Edge b){return a.a<b.a;});
    for(int i=1;i<=m;i++)
    {
        if(find(Edges2[i].s)!=find(Edges2[i].t))
            ans+=Edges2[i].a,fa[find(Edges2[i].s)]=find(Edges2[i].t);
    }
    printf("%lld",ans);
}