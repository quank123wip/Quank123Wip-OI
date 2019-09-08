#include<bits/stdc++.h>
const int MaxN=200010;
const int INF=0x3f3f3f3f;
int n,m;
namespace Kruskal
{
    inline int find(int x);
}
namespace Graph
{
    int Head[MaxN],fa[MaxN][21],val[MaxN][21],depth[MaxN];
    struct Edge
    {
        int u,v,w,next;
    }Edges[MaxN];
    inline void AddEdge(int u,int v,int w)
    {
        static int cnt=1;
        Edges[cnt]={u,v,w,Head[u]},Head[u]=cnt++;
        Edges[cnt]={v,u,w,Head[v]},Head[v]=cnt++;
    }
    inline void DFS(int now)
    {
        depth[now]=depth[fa[now][0]]+1;
        for(int i=Head[now];i;i=Edges[i].next)
        {
            if(depth[Edges[i].v])continue;
            fa[Edges[i].v][0]=now;
            val[Edges[i].v][0]=Edges[i].w;
            DFS(Edges[i].v);
        }
    }
    inline void Init(void)
    {
        for(int i=1;i<=n;i++)
        {
            if(depth[i]==0)
            {
                depth[i]=1;
                DFS(i);
                fa[i][0]=i;
                val[i][0]=INF;
            }
        }
        for(int i=1;i<=20;i++)
        {
            for(int j=1;j<=n;j++)
            {
                fa[j][i]=fa[fa[j][i-1]][i-1];
                val[j][i]=std::min(val[j][i-1],val[fa[j][i-1]][i-1]);
            }
        }
    }
    inline int LCA(int x,int y)
    {
        if(Kruskal::find(x)!=Kruskal::find(y))
            return -1;
        int ans=INF;
        if(depth[x]>depth[y])std::swap(x,y);
        for(int i=20; i>=0; i--)
            if(depth[fa[y][i]]>=depth[x])
            {
                ans=std::min(ans, val[y][i]);
                y=fa[y][i];
            }
        if(x==y)return ans;
        for(int i=20; i>=0; i--)
            if(fa[x][i]!=fa[y][i])
            {
                ans=std::min(ans, std::min(val[x][i],val[y][i]));
                x=fa[x][i];
                y=fa[y][i];
            }
        ans=std::min(ans, std::min(val[x][0],val[y][0]));
        return ans;

    }
    inline void main(void)
    {
        Init();
        int q,u,v;
        scanf("%d",&q);
        while(q--)
        {
            scanf("%d%d",&u,&v);
            printf("%d\n",LCA(u,v));
        }   
    }
}
namespace Kruskal
{
    int Head[MaxN],UnionSet[MaxN];
    Graph::Edge Edges[MaxN];
    inline void AddEdge(int u,int v,int w)
    {
        static int cnt=1;
        Edges[cnt]={u,v,w,Head[u]},Head[u]=cnt++;
    }
    inline void Init(void)
    {
        int p=0;
        for(auto &i:UnionSet)
            i=p++;
        std::sort(Edges+1,Edges+1+m,[](Graph::Edge a,Graph::Edge b){return a.w>b.w;});
    }
    inline int find(int x)
    {
        UnionSet[x]=x!=UnionSet[x]?find(UnionSet[x]):UnionSet[x];
        return UnionSet[x];
    }
    inline void Union(int x,int y,int w)
    {
        UnionSet[find(x)]=find(y);
        Graph::AddEdge(x,y,w);
    }
    inline void main(void)
    {
        Init();
        for(auto i:Edges)
            if(i.u!=0&&i.v!=0&&find(i.u)!=find(i.v))
                Union(i.u,i.v,i.w);

    }
}
signed main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;i++)
    {
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        Kruskal::AddEdge(u,v,w);
    }
    Kruskal::main();
    Graph::main();
}