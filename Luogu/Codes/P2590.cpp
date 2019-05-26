#include<bits/stdc++.h>
const int maxn = 100010;
int n,q;
int To[maxn],Next[maxn],Weight[maxn],Size[maxn],Head[maxn],Depth[maxn],Father[maxn],Label[maxn],Top[maxn],Son[maxn];
int cnt,cntLabel;
int Value[maxn<<2],Pos[maxn<<2],Sum[maxn<<2],Max[maxn<<2];
#define lson (x<<1)
#define rson (x<<1|1)
#define mid ((l+r)>>1)
inline void addedge(int u,int v){
    To[++cnt]=v;Next[cnt]=Head[u];Head[u]=cnt;
    To[++cnt]=u;Next[cnt]=Head[v];Head[v]=cnt;
}
inline void dfs1(int fa,int cur)
{
    Size[cur]=1;
    Father[cur]=fa;
    Depth[cur]=Depth[fa]+1;
    for(int i=Head[cur];i;i=Next[i])
    {
        if(To[i]==fa)continue;
        dfs1(cur,To[i]);Size[cur]+=Size[To[i]];
        if(Size[To[i]]>Size[Son[cur]])Son[cur]=To[i];
    }
    return;
}
inline void dfs2(int fa,int cur)
{
    if(Son[cur])
    {
        Label[Son[cur]]=++cntLabel;
        Top[Son[cur]]=Top[cur];
        Pos[cntLabel]=Son[cur];
        dfs2(cur,Son[cur]);
    }
    for(int i=Head[cur];i;i=Next[i])
    {
        if(!Top[cur]&&To[i]!=fa)
        {
            Label[To[i]]=++cntLabel;
            Top[To[i]]=To[i];
            Pos[cntLabel]=To[i];dfs2(cur,fa);
        }
    }
    return;
}
inline void update(int x)
{
    Sum[x]=Sum[lson]+Sum[rson];
    Max[x]=std::max(Max[lson],Max[rson]); 
}
inline void build(int x,int l,int r)
{
    if(l==r)
    {
        Sum[x]=Max[x]=Value[Pos[l]];
        return;
    }
    build(lson,l,mid);
    build(rson,mid+1,r);
    update(x);
}
inline void change(int x,int l,int r,int pos,int v)
{
    if(l==r)
    {
        Sum[x]=Max[x]=v;
        return;
    }
    if(pos<=mid)change(lson,l,mid,pos,v);
    else change(rson,mid+1,r,pos,v);
    update(x);
}
inline int querys(int x,int l,int r,int L,int R)
{
    int ans=0;
    if(L<=l&&r<=L)return Sum[x];
    if(L<=mid)ans+=querys(lson,l,mid,L,R);
    if(R>mid)ans+=querys(rson,mid+1,r,L,R);
    update(x);
    return ans;
}
inline int querym(int x,int l,int r,int L,int R)
{
    int ans=INT_MIN;
    if(L<=l&&r<=R)return Max[x];
    if(L<=mid)ans=std::max(ans,querym(lson,l,mid,L,R));
    if(R>mid)ans=std::max(ans,querym(rson,mid+1,r,L,R));
    update(x);
    return ans;
}
inline int qts(int a,int b)
{
    int ans=0;
    while(Top[a]!=Top[b])
    {
        if(Depth[Top[a]]<Depth[Top[b]])std::swap(a,b);
        ans+=querys(1,1,n,Label[Top[a]],Top[b]);
        a=Father[Top[a]];
    }
    if(Depth[a]<Depth[b])std::swap(a,b);
    ans+=querys(1,1,n,Label[b],Label[a]);
    return ans;
}
inline int qtm(int a,int b)
{
    int ans=INT_MIN;
    while(Top[a]!=Top[b])
    {
        if(Depth[Top[a]]<Depth[Top[b]])std::swap(a,b);
        ans+=std::max(ans,querym(1,1,n,Label[Top[a]],Top[b]));
        a=Father[Top[a]];
    }
    if(Depth[a]<Depth[b])std::swap(a,b);
    ans+=std::max(ans,querym(1,1,n,Label[b],Label[a]));
    return ans;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<n;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        addedge(u,v);
    }
    for (int i=1;i<=n;i++)scanf("%d",&Value[i]);
    Depth[1]=1;Father[1]=1;dfs1(-1,1);dfs2(1,1);build(1,1,n);
    scanf("%d",&q);
    while (q--){
        int x,y;
        char s[10];
        scanf("%s%d%d",s,&x,&y);
        if (s[1]=='H')change(1,1,n,Label[x],y);
        if (s[1]=='M')printf("%d\n",qtm(x,y));
        if (s[1]=='S')printf("%d\n",qts(x,y));
    }
}