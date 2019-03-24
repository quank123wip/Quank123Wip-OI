#include <bits/stdc++.h>
using namespace std;
const int maxn = 200010;
int n;
int a[maxn];
int even[maxn], odd[maxn];
int ans;
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        if (i % 2 == 0)
        {
            even[i] = a[i] + even[i - 1];
            odd[i] = odd[i - 1];
        }
        else
        {
            odd[i] = a[i] + odd[i - 1];
            even[i] = even[i - 1];
        }
    }
    for (int i = 1; i <= n; i++)
    {
        if (i == 1)
        {
            if (odd[n] - a[i] == even[n])
                ans++;
        }
        else if (i == n)
        {
            if (n % 2 == 0)
            {
                if (even[n] - a[i] == odd[n])
                {
                    ans++;
                }
            }
            else
            {
                if (odd[n] - a[i] == even[i])
                {
                    ans++;
                }
            }
        }
        else
        {
            if ((odd[i - 1] + even[n] - even[i]) == (even[i - 1] + odd[n] - odd[i]))
            {
                ans++;
            }
        }
    }
    printf("%d",ans);
}