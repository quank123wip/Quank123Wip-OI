#include <bits/stdc++.h>
using namespace std;
const int maxn = 100001;
const int BinMaxn = 21;
#define Bin(n) (1 << n)
int n, m;
int MaxV[maxn][BinMaxn];
int OriginArr[maxn];
int main()
{
    scanf("%d%d",&n,&m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d",&OriginArr[i]);
        MaxV[i][0] = OriginArr[i];
    }
    for (int j = 1; j <= (int)(log2(n) / log2(2)); j++)
    {
        for (int i = 1; i <= n - Bin(j) + 1; i++)
        {
            MaxV[i][j] = max(MaxV[i][j - 1], MaxV[i + Bin(j - 1)][j - 1]);
        }
    }
    for (int i = 0; i < m; i++)
    {
        int l, r;
        scanf("%d%d",&l,&r);
        int k=log2(r - l + 1);
        printf("%d\n",max(MaxV[l][k], MaxV[r - (1<<k) + 1][k]));
    }
}