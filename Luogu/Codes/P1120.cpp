#include <bits/stdc++.h>
using namespace std;
int n, m, a[100], nxt[100], cnt, sum, len;
bool pd[100], flag;
bool cmp(int a, int b) { return a > b; }
void dfs(int k, int last, int rest)
{
    int i;
    if (!rest)
    {
        if (k == m)
        {
            flag = 1;
            return;
        }

        for (i = 1; i <= cnt; i++)
            if (!pd[i])
                break;
        pd[i] = 1;
        dfs(k + 1, i, len - a[i]);
        pd[i] = 0;
        if (flag)
            return;
    }

    int l = last + 1, r = cnt, mid;
    while (l < r)
    {
        mid = (l + r) >> 1;
        if (a[mid] <= rest)
            r = mid;
        else
            l = mid + 1;
    }
    for (i = l; i <= cnt; i++)
    {
        if (!pd[i])
        {
            pd[i] = 1;
            dfs(k, i, rest - a[i]);
            pd[i] = 0;
            if (flag)
                return;

            if (rest == a[i] || rest == len)
                return;
            i = nxt[i];
            if (i == cnt)
                return;
        }
    }
}
int main()
{
    cin>>n;
    int d;
    for (int i = 1; i <= n; i++)
    {
        cin>>d;
        if (d > 50)
            continue;
        a[++cnt] = d;
        sum += d;
    }
    sort(a + 1, a + cnt + 1, cmp);

    nxt[cnt] = cnt;
    for (int i = cnt - 1; i > 0; i--)
    {
        if (a[i] == a[i + 1])
            nxt[i] = nxt[i + 1];
        else
            nxt[i] = i;
    }
    for (len = a[1]; len <= sum / 2; len++)
    {
        if (sum % len != 0)
            continue;
        m = sum / len;
        flag = 0;
        pd[1] = 1;
        dfs(1, 1, len - a[1]);
        pd[1] = 0;
        if (flag)
        {
            cout<<len;
            return 0;
        }
    }
    cout<<sum;
    return 0;
}