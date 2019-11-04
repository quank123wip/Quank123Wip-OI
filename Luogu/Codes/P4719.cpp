#include <bits/stdc++.h>
constexpr int maxn = 100000 + 10;
int n, m;
int a[maxn];
int head[maxn << 1], next[maxn << 1], to[maxn << 1], size[maxn], fa[maxn], depth[maxn], son[maxn], top[maxn], bottom[maxn], id[maxn], f[maxn], g[maxn][2];

struct Matrix
{
    long long p[2][2];
    Matrix()
    {
        p[0][0] = p[1][0] = p[0][1] = p[1][1] = 0;
    }
};
inline Matrix operator*(const Matrix &p, const Matrix &q)
{
    Matrix v;
    for (int i = 0; i <= 1; i++)
        for (int j = 0; j <= 1; j++)
            for (int k = 0; k <= 1; k++)
                v.p[i][j] = std::max(v.p[i][j], p.p[i][k] + q.p[k][j]);
    return v;
}
Matrix DP[maxn];
inline void __addedge(int u, int v)
{
    static int cnt = 0;
    to[++cnt] = v;
    next[cnt] = head[u];
    head[u] = cnt;
}

inline void AddEdge(int u, int v)
{
    __addedge(u, v);
    __addedge(v, u);
}

inline void DFS1(int u)
{
    size[u] = 1;
    depth[u] = depth[fa[u]] + 1;
    for (int i = head[u]; i; i = next[i])
    {
        if(to[i]==fa[u])continue;
        fa[to[i]] = u;
        DFS1(to[i]);
        size[u] += size[to[i]];
        if (size[to[i]] > size[son[u]])
            son[u] = to[i];
    }
}

inline void DFS2(int u, int top)
{
    static int cnt = 0;
    id[u] = ++cnt, f[cnt] = u;
    ::top[u] = top;
    bottom[top] = std::max(bottom[top], cnt);
    g[u][0] = 0, DP[u].p[1][0] = g[u][1] = a[u];
    if (son[u])
    {
        DFS2(son[u], top);
        g[u][0] += std::max(g[son[u]][0], g[son[u]][1]);
        g[u][1] += g[son[u]][0];
    }
    for (int i = head[u]; i; i = next[i])
    {
        if (to[i] == fa[u] || to[i] == son[u])
            continue;
        DFS2(to[i], to[i]);
        g[u][0] += std::max(g[to[i]][0], g[to[i]][1]);
        g[u][1] += g[to[i]][0];
        DP[u].p[0][0]+=std::max(g[to[i]][0], g[to[i]][1]);
        DP[u].p[0][1]=DP[u].p[0][0];
        DP[u].p[1][0]+=g[to[i]][0];
    }
}

namespace SegmentTree
{
    #define mid ((l+r)>>1)
    ::Matrix p[maxn<<2];
    inline void update(int pos)
    {
        p[pos]=p[pos<<1]*p[pos<<1|1];
        return;
    }
    inline void buildup(int pos,int l,int r)
    {
        if(l==r) p[pos]=DP[f[l]];
        else
        {
            buildup(pos<<1,l,mid);
            buildup(pos<<1|1,mid+1,r);
            update(pos);
        }
    }
    inline void Update(int v,int pos,int l,int r)
    {
        if(l==r)
            p[pos]=DP[f[v]];
        else
        {
            if(v<=mid) Update(v,pos<<1,l,mid);
            else Update(v,pos<<1|1,mid+1,r);
            update(pos);
        }
    }
    inline Matrix Query(int pos,int L,int R,int l,int r)
    {
        if(L<=l&&r<=R) return p[pos];
        if(R<=mid)
            return Query(pos<<1,L,R,l,mid);
        else if(L>mid)
            return Query(pos<<1|1,L,R,mid+1,r);
        else return Query(pos<<1,L,R,l,mid)*Query(pos<<1|1,L,R,mid+1,r);
    }
    #undef mid
}

inline void Update(int a,int b)
{
    DP[a].p[1][0]+=b-::a[a];
    ::a[a]=b;
    Matrix history, future;
    while(a)
    {
        history=SegmentTree::Query(1,id[top[a]],bottom[top[a]],1,n);
        SegmentTree::Update(id[a],1,1,n);
        future=SegmentTree::Query(1,id[top[a]],bottom[top[a]],1,n);
        a=fa[top[a]];
        DP[a].p[0][0]+=std::max(future.p[0][0],future.p[1][0])-std::max(history.p[0][0],history.p[1][0]);
        DP[a].p[0][1]=DP[a].p[0][0];
        DP[a].p[1][0]+=future.p[0][0]-history.p[0][0];
    }
}

signed main()
{
    ::scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++)
        ::scanf("%d",a+i+1);
    for(int i=1;i<n;i++)
    {
        int a,b;
        ::scanf("%d%d",&a,&b);
        AddEdge(a,b);
    }
    DFS1(1);DFS2(1,1);
    SegmentTree::buildup(1,1,n);
    for(int i=0;i<m;i++)
    {
        int a,b;
        ::scanf("%d%d",&a,&b);
        Update(a,b);
        Matrix nowans = SegmentTree::Query(1,id[1],bottom[1],1,n);
        ::printf("%d\n",std::max(nowans.p[0][0],nowans.p[1][0]));
    }
}