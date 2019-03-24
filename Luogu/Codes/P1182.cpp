#include <bits/stdc++.h>
using namespace std;
const int maxn = 100005;
int a[maxn];
int n, m;
int l = 0, r;
inline bool check(int p)
{
    int now = 0, need = m;
    for (int i = 0; i < n; i++)
    {
        now += a[i];
        if (now > p)
        {
            now = a[i];
            need--;
        }
    }
    return need>0;
}
int main()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        l = max(l, a[i]), r += a[i];
    }

    while (l < r)
    {
        int mid = (l + r) / 2;
        if (check(mid))
        {
            r = mid;
        }
        else
        {
            l = mid + 1;
        }
    }
    cout << l << endl;
}