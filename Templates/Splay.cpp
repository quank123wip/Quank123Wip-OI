#include <bits/stdc++.h>
struct Splay
{
    static const int MaxN = 200010;
    int root=0, cnt=0;
    struct Node
    {
        int ch[2], val, cnt, parent, size;
    } Nodes[MaxN];
    inline void pushup(int x)
    {
        Nodes[x].size = Nodes[Nodes[x].ch[0]].size + Nodes[Nodes[x].ch[1]].size+Nodes[x].cnt;
    }
    inline void rotate(int x)
    {
        int fa = Nodes[x].parent, gr = Nodes[fa].parent, k = Nodes[fa].ch[1] == x, p = Nodes[x].ch[k ^ 1];
        Nodes[fa].ch[k] = p;
        Nodes[p].parent = fa;
        Nodes[gr].ch[Nodes[gr].ch[1] == fa] = x;
        Nodes[x].parent = gr;
        Nodes[x].ch[k ^ 1] = fa;
        Nodes[fa].parent = x;
        pushup(fa), pushup(x);
    }
    inline void splay(int x, int target = 0)
    {
        while (Nodes[x].parent != target)
        {
            int fa = Nodes[x].parent, gr = Nodes[fa].parent;
            if (gr != target)
            {
                if ((Nodes[fa].ch[1] == x) == (Nodes[gr].ch[1] == fa))
                    rotate(fa);
                else
                    rotate(x);
            }
            rotate(x);
        }
        if (!target)
            root = x;
    }
    inline void find(int x)
    {
        if (!root)
            return;
        int cur = root;
        while (Nodes[cur].ch[x > Nodes[cur].val] && x != Nodes[cur].val)
            cur = Nodes[cur].ch[x > Nodes[cur].val];
        splay(cur);
    }
    inline void insert(int x)
    {
        int cur = root, p = 0;
        while (cur && Nodes[cur].val != x)
            p = cur,
            cur = Nodes[cur].ch[x > Nodes[cur].val];
        if (cur)
            Nodes[cur].cnt++;
        else
        {
            cur = ++cnt;
            if (p)
                Nodes[p].ch[x > Nodes[p].val] = cur;
            Nodes[cur] = {{0, 0}, x, 1, p, 1};
        }
        splay(cur);
    }
    inline int kth(int k)
    {
        int cur = root;
        for (;;)
        {
            if (Nodes[cur].ch[0] && k <= Nodes[Nodes[cur].ch[0]].size)
                cur = Nodes[cur].ch[0];
            else if (k > Nodes[Nodes[cur].ch[0]].size + Nodes[cur].cnt)
                k -= Nodes[Nodes[cur].ch[0]].size + Nodes[cur].cnt,
                    cur = Nodes[cur].ch[1];
            else
                return cur;
        }
    }
    inline int rank(int x)
    {
        find(x);
        return Nodes[Nodes[root].ch[0]].size;
    }
    inline int prev(int x)
    {
        find(x);
        if (Nodes[root].val < x)
            return root;
        int cur = Nodes[root].ch[0];
        while (Nodes[cur].ch[1])
            cur = Nodes[cur].ch[1];
        return cur;
    }
    inline int next(int x)
    {
        find(x);
        if (Nodes[root].val > x)
            return root;
        int cur = Nodes[root].ch[1];
        while (Nodes[cur].ch[0])
            cur = Nodes[cur].ch[0];
        return cur;
    }
    inline void remove(int x)
    {
        int p = prev(x), n = next(x);
        splay(p);
        splay(n, p);
        int rem = Nodes[n].ch[0];
        if (Nodes[rem].cnt > 1)
            Nodes[rem].cnt--,
                splay(rem);
        else
            Nodes[n].ch[0] = 0;
    }
}orz;
int main()
{
    //srand(time(0));
    //freopen("testdata.in", "r", stdin);
    //freopen("testdata.out", "w", stdout);
    int n, opt, x;
    scanf("%d", &n);
    orz.insert(0x3f3f3f3f);
    orz.insert(0xcfcfcfcf);
    while (n--)
    {
        scanf("%d%d", &opt, &x);
        if (opt == 1)
            orz.insert(x);
        else if (opt == 2)
            orz.remove(x);
        else if (opt == 3)
            printf("%d", orz.rank(x)),
                puts("");
        else if (opt == 4)
            printf("%d", orz.Nodes[orz.kth(x+1)].val),
                puts("");
        else if (opt == 5)
            printf("%d", orz.Nodes[orz.prev(x)].val),
                puts("");
        else if (opt == 6)
            printf("%d", orz.Nodes[orz.next(x)].val),
                puts("");
    }
}