#include <bits/stdc++.h>
using namespace std;
#define nullptr NULL
struct node
{
    int num;
    node *lson , *rson ;
    node *fa;
    node(){
        lson=nullptr;
        rson=nullptr;
    }
} tree[20];
int n;
inline void solve1(node *p)
{
    cout << p->num << " ";
    if (p->lson != nullptr)
        solve1(p->lson);
    if (p->rson != nullptr)
        solve1(p->rson);
}
inline void solve2(node *p)
{
    if (p->lson != nullptr)
        solve2(p->lson);
    cout << p->num << " ";
    if (p->rson != nullptr)
        solve2(p->rson);
}
inline void solve3(node *p)
{
    if (p->lson != nullptr)
        solve3(p->lson);
    if (p->rson != nullptr)
        solve3(p->rson);
    cout << p->num << " ";
}
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        int l, r;
        cin >> l >> r;
        tree[i].num = i;
        if (l != 0)
            tree[i].lson = tree+l;
        if (r != 0)
            tree[i].rson = tree+r;
        if (l != 0)
            tree[l].fa = tree+i;
        if (r != 0)
            tree[r].fa = tree+i;
    }
    solve1(tree+1);
    cout<<endl;
    solve2(tree+1);
    cout<<endl;
    solve3(tree+1);
}