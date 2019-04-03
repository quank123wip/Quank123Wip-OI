#include <bits/stdc++.h>
using namespace std;
namespace Treap
{
static const int MaxN = 100010;
int cnt,root;
int val[MaxN], size[MaxN], rand[MaxN];
int lson[MaxN], rson[MaxN];
bool lazy[MaxN];
inline void update(int x)
{
    size[x] = size[lson[x]] + size[rson[x]] + 1;
}
inline int newnode(int v)
{
    val[++cnt] = v;
    size[cnt] = 1;
    rand[cnt] = std::rand();
    return cnt;
}
inline void pushdown(int x)
{
    if (x && lazy[x])
    {
        std::swap(lson[x], rson[x]);
        if (lson[x])
            lazy[lson[x]] ^= 1;
        if (rson[x])
            lazy[rson[x]] ^= 1;
        lazy[x] = 0;
    }
}
inline int merge(int x,int y)
{
    if(!x||!y)return x+y;
    if(rand[x]<rand[y])
    {
        pushdown(x);
        rson[x]=merge(rson[x],y);
        update(x);
        return x;
    }
    pushdown(y);
    lson[y]=merge(x,lson[y]);
    update(y);
    return y;
}
inline void split(int now,int k,int &x,int &y)
{
    if(!now)
    {
        x=y=0;
        return;
    }
    pushdown(now);
    if(size[lson[now]]<k)
    {
        x=now;
        split(rson[now],k-size[lson[now]]-1,rson[now],y);
    }
    else
    {
        y=now;
        split(lson[now],k,x,lson[now]);
    }
    update(now);
}
inline void insert(int x)
{
    root=merge(root,newnode(x));
}
inline void reverse(int l,int r)
{
    int a,b,c;
    split(root,l-1,a,b);
    split(b,r-l+1,b,c);
    lazy[b]^=1;
    root=merge(a,merge(b,c));
}
inline void output(int p=root)
{
    if(!p)return;
    pushdown(p);
    output(lson[p]);
    printf("%d ",val[p]);
    output(rson[p]);
}
} // namespace Treap
int n,m;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        Treap::insert(i);
    while(m--)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        Treap::reverse(l,r);
        //Treap::output();
    }
    Treap::output();
}