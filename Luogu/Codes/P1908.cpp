#include <bits/stdc++.h>
using namespace std;
const int maxn = 40000 + 5;
int n;
int arr[maxn];
int cache[maxn];
inline int solve(int l, int r)
{
    if(l==r)return 0;
    int mid = (l + r) / 2;
    int ans = 0;
    ans += solve(l, mid) + solve(mid + 1, r);
    int i1 = l, i2 = mid + 1, pos = l;
    while (i1 <= mid && i2 <= r)
    {
        if (arr[i1] > arr[i2])
        {
            cache[pos++] = arr[i2++];
            ans += mid - i1 + 1;
        }
        else
        {
            cache[pos++] = arr[i1++];
        }
    }
    while (i1 <= mid)

        cache[pos++] = arr[i1++];

    while (i2 <= r)

        cache[pos++] = arr[i2++];
    for(int i=l;i<=r;i++)
    {
        arr[i]=cache[i];
    }
    return ans;
}
int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    cout << solve(0, n - 1);
}