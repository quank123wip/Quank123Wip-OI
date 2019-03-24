// luogu-judger-enable-o2
// luogu-judger-enable-o2
#include <bits/stdc++.h>
using namespace std;
const int maxn = 100000 + 10;
int n, m;
long long arr[maxn];
long long p;
class Segment_Tree
{
  private:
    struct Node
    {
        int l, r;
        long long Value, lazy_add, lazy_mul;
        Node *lson, *rson;
        Node()
        {
            lson = nullptr;
            rson = nullptr;
            Value = 0;
            lazy_add = 0;
            lazy_mul = 1;
        }
        ~Node()
        {
            delete lson;
            delete rson;
        }
        inline void Pushdown(void)
        {
            if (lson != nullptr)
            {
                lson->lazy_add = (lson->lazy_add*lazy_mul) %p;
                lson->lazy_mul = (lson->lazy_mul*lazy_mul) %p;
                lson->Value = (lson->Value*lazy_mul) %p;
                lson->lazy_add = (lson->lazy_add+lazy_add) %p;
                lson->Value = (lson->Value+((lson->r - lson->l + 1) * lazy_add)) %p;
            }
            if (rson != nullptr)
            {
                rson->lazy_add = (rson->lazy_add*lazy_mul) %p;
                rson->lazy_mul = (rson->lazy_mul*lazy_mul) %p;
                rson->Value = (rson->Value*lazy_mul) %p;
                rson->lazy_add = (rson->lazy_add+lazy_add) %p;
                rson->Value = (rson->Value+((rson->r - rson->l + 1) * lazy_add)) %p;
            }
            lazy_mul = 1;
            lazy_add = 0;
        }
        inline bool islazy(void)
        {
            return islazy_add() || islazy_mul();
        }
        inline bool islazy_add(void)
        {
            return lazy_add != 0;
        }
        inline bool islazy_mul(void)
        {
            return lazy_mul != 1;
        }
    };
    Node *root;
    int l, r;
    inline void Build_Tree(Node *now, long long *Origin)
    {
        if (now->l == now->r)
        {
            now->Value = Origin[now->l] ;
            return;
        }
        now->lson = new Node;
        now->rson = new Node;
        now->lson->l = now->l;
        now->lson->r = (now->l + now->r) / 2;
        now->rson->l = (now->l + now->r) / 2 + 1;
        now->rson->r = now->r;
        Build_Tree(now->lson, Origin);
        Build_Tree(now->rson, Origin);
        now->Value = (now->lson->Value + now->rson->Value) ;
    }
    inline void __update_add(Node *now, int l, int r, long long Value)
    {
        if (now->l == l && now->r == r)
        {
            now->Value = (now->Value+((r - l + 1) * Value)) %p;
            now->lazy_add = (now->lazy_add+Value) %p;
        }
        else
        {
            now->Value+=(r-l+1)*Value%p;
            if (r <= now->lson->r)
            {
                __update_add(now->lson, l, r, Value);
            }
            else if (l >= now->rson->l)
            {
                __update_add(now->rson, l, r, Value);
            }
            else
            {
                __update_add(now->lson, l, now->lson->r, Value);
                __update_add(now->rson, now->rson->l, r, Value);
            }
            //now->Value = (now->lson->Value + now->rson->Value) ;
        }
    }
    inline void __update_mul(Node *now, int l, int r, long long Value)
    {
        if (now->l == l && now->r == r)
        {
            now->Value=(now->Value*Value)%p;
            now->lazy_mul=(now->lazy_mul*Value)%p;
            now->lazy_add=(now->lazy_add*Value)%p;
        }
        else
        {
            if (r <= now->lson->r)
                __update_mul(now->lson, l, r, Value);
            else if (l >= now->rson->l)
                __update_mul(now->rson, l, r, Value);
            else
            {
                __update_mul(now->lson, l, now->lson->r, Value);
                __update_mul(now->rson, now->rson->l, r, Value);
            }
            now->Value = (now->lson->Value + now->rson->Value);
        }
    }
    inline long long __query(Node *now, int l, int r)
    {
        if (now->islazy())
            now->Pushdown();
        if (now->l == l && now->r == r)
        {
            return now->Value %p;
        }
        else
        {
            if (r <= now->lson->r)
                return __query(now->lson, l, r);
            else if (l >= now->rson->l)
                return __query(now->rson, l, r);
            else
            {
                return (__query(now->lson, l, now->lson->r) ) + (__query(now->rson, now->rson->l, r) ) %p;
            }
        }
    }

  public:
    Segment_Tree(long long *Origin, int size);
    ~Segment_Tree();
    inline void Update_add(int l, int r, int Value)
    {
        __update_add(root, l, r, Value);
        return;
    }
    inline void Update_mul(int l, int r, int Value)
    {
        __update_mul(root, l, r, Value);
        return;
    }
    inline long long Query(int l, int r)
    {
        return __query(root, l, r);
    }
};

Segment_Tree::Segment_Tree(long long *Origin, int size)
{
    l = 1;
    r = size;
    root = new Node;
    root->l = l;
    root->r = r;
    Build_Tree(root, Origin);
}

Segment_Tree::~Segment_Tree()
{
    delete root;
}
int main()
{
    scanf("%d%d%lld", &n, &m, &p);
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld", arr + i);
    }
    Segment_Tree Test(arr, n);
    for (int i = 0; i < m; i++)
    {
        int pd;
        long long a, b, c;
        scanf("%d%lld%lld", &pd, &a, &b);
        if (pd == 1)
        {
            scanf("%lld", &c);
            Test.Update_mul(a, b, c);
        }
        else if (pd == 2)
        {
            scanf("%lld", &c);
            Test.Update_add(a, b, c);
        }
        else
        {
            printf("%lld\n", Test.Query(a, b)%p );
        }
    }
}