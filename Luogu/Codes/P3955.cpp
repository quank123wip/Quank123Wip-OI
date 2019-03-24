#include <bits/stdc++.h>
using namespace std;
int i, i2, n, q, nl[1001], ql, pl, b, ans[1001];
int can;
int main()
{

    cin >> n >> q;
    for (i = 1; i <= n; i++)
    {
        cin >> nl[i];
    }
    for (i = 1; i <= q; i++)
    {
        cin >> pl >> ql;
        pl = pow(10, pl);
        b = 100000000;
        can = 0;
        for (i2 = 1; i2 <= n; i2++)
        {
            if (nl[i2] % pl == ql)
                if (nl[i2] < b)
                {
                    b = nl[i2];
                    can = 1;
                }
        }
        if (can == 1)
            cout << b << endl;
        else
            cout << -1 << endl;
    }
    return 0;
}
