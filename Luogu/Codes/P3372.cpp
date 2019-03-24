// luogu-judger-enable-o2
// luogu-judger-enable-o2
#include <bits/stdc++.h>
using namespace std;
const int maxn = 100000 + 10;
int n, m;
long long arr[maxn];
class Segment_Tree
{
  private:
    struct Node
    {
        int l, r;
        long long Value, lazy;
        Node *lson, *rson;
        Node()
        {
            lson = nullptr;
            rson = nullptr;
            Value=0;
            lazy=0;
        }
        ~Node()
        {
            delete lson;
            delete rson;
        }
        inline void Pushdown(void)
        {
            Value += (r - l + 1) * lazy;
            if (lson != nullptr)
            {
                lson->lazy += lazy;
            }
            if (rson != nullptr)
            {
                rson->lazy += lazy;
            }
            lazy = 0;
        }
        inline bool unlazy(void)
        {
            return (!lazy)?true:false;
        }
    };
    Node *root;
    int l, r;
    inline void Build_Tree(Node *now, long long *Origin)
    {
        if (now->l == now->r)
        {
            now->Value = Origin[now->l];
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
        now->Value = now->lson->Value + now->rson->Value;
    }
    inline void __update(Node *now, int l, int r, long long Value)
    {
        if (now->l == l && now->r == r)
        {
            now->lazy += Value;
            return;
        }

        else
        {
            now->Value += (r - l + 1) * Value;

            if (r <= now->lson->r)
            {
                __update(now->lson, l, r, Value);
                return;
            }

            else if (l >= now->rson->l)
            {
                __update(now->rson, l, r, Value);
                return;
            }

            else
            {
                __update(now->lson, l, now->lson->r, Value);
                __update(now->rson, now->rson->l, r, Value);
                return;
            }
        }
    }
    inline long long __query(Node *now, int l, int r)
    {
        if (!now->unlazy())
            now->Pushdown();
        if (now->l == l && now->r == r)
        {
            return now->Value;
        }
        else
        {
            if (r <= now->lson->r)
            {
                return __query(now->lson, l, r);
            }

            else if (l >= now->rson->l)
            {
                return __query(now->rson, l, r);
            }

            else
            {
                return __query(now->lson, l, now->lson->r) + __query(now->rson, now->rson->l, r);
            }
        }
    }

  public:
    Segment_Tree(long long *Origin, int size);
    ~Segment_Tree();
    inline void Update(int l, int r, int Value)
    {
        __update(root, l, r, Value);
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
    root->l=l;
    root->r=r;
    Build_Tree(root, Origin);
}

Segment_Tree::~Segment_Tree()
{
    delete root;
}

int main()
{
    scanf("%d%d", &n, &m);
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
            Test.Update(a,b,c);
        }
        else
        {
            printf("%lld\n",Test.Query(a,b));
        }
    }
}