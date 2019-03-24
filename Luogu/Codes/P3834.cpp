//#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
constexpr long long maxn = 200000 + 10;
constexpr long long maxm = maxn;
//Constant Data
long long n, m;
long long Original_Data[maxn], Index_Unique[maxn], Unique_Size;
class Functional_SegmentTree
{
  private:
    //long long SizeofTree;
    long long VersionNow = 0;
    struct Node
    {
        long long Val = 0;
        Node *lson = nullptr, *rson = nullptr;
    };
    Node **roots;
    inline void __build_basetree(Node *now, long long l, long long r)
    {
        if (l < r)
        {
            now->lson = new Node;
            now->rson = new Node;
            __build_basetree(now->lson, l, (l + r) / 2);
            __build_basetree(now->rson, ((l + r) / 2) + 1, r);
        }
    }
    inline void __build_new_ver(Node *PreVer, Node *now, long long l, long long r, long long value)
    {
        *now = *PreVer;
        now->Val++;
        if (l < r)
        {
            if (value <= (l + r) / 2)
            {
                now->lson = new Node;
                __build_new_ver(PreVer->lson, now->lson, l, (l + r) / 2, value);
            }
            else
            {
                now->rson = new Node;
                __build_new_ver(PreVer->rson, now->rson, (l + r) / 2 + 1, r, value);
            }
        }
    }
    inline long long __query(Node *a, Node *b, long long l, long long r, long long k)
    {
        if (!(l < r))
            return l;
        long long p=b->lson->Val-a->lson->Val;
        if (p >= k)
            return __query(a->lson, b->lson, l, (l + r) / 2, k);
        else
            return __query(a->rson, b->rson, (l + r) / 2 + 1, r, k - p);
    }

  public:
    Functional_SegmentTree(long long n)
    {
        //SizeofTree = n;
        roots = new Node *[n];
        roots[0] = new Node;
        __build_basetree(roots[0], 1, n);
    }
    inline void Build_New_Version(long long l, long long r, long long Value)
    {
        roots[VersionNow + 1] = new Node;
        __build_new_ver(roots[VersionNow], roots[VersionNow + 1], l, r, Value);
        VersionNow++; //Update
    }
    inline long long Query(long long l, long long r, long long k)
    {
        return __query(roots[l - 1], roots[r], 1, Unique_Size, k);
    }
};
int main()
{
    scanf("%lld%lld", &n, &m);
    for (/*register*/ long long i = 1; i <= n; i++) //Because of the SegmentTree,so we must start from 1;
        scanf("%lld", Original_Data + i),
        Index_Unique[i] = Original_Data[i]; //Copy
    sort(Index_Unique + 1, Index_Unique + n + 1);
    Unique_Size = unique(Index_Unique + 1, Index_Unique + n + 1) - Index_Unique - 1;
    Functional_SegmentTree AC_Tools(Unique_Size);
    for (long long i = 1; i <= n; i++)
        AC_Tools.Build_New_Version(1, Unique_Size, lower_bound(Index_Unique + 1, Index_Unique + Unique_Size + 1, Original_Data[i]) - Index_Unique);
    for (long long i = 1; i <= m; i++)
    {
        long long l, r, k;
        scanf("%lld%lld%lld", &l, &r, &k);
        printf("%lld\n", Index_Unique[AC_Tools.Query(l, r, k)]);
    }
}