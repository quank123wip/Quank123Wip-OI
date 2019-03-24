#include <bits/stdc++.h>
using namespace std;
string n;
int k;
int p[10];
bool canreach[10][10];
long double ans = static_cast<long double>(1);
int main()
{
    cin >> n >> k;
    for (int i = 0; i < k; i++)
    {
        int f, t;
        cin >> f >> t;
        canreach[f][t] = true;
    }
    for (int k = 0; k < 10; k++)
        for (int i = 0; i < 10; i++)
            for (int j = 0; j < 10; j++)
                    canreach[i][j] = (canreach[i][j]||canreach[i][k] && canreach[k][j]);
    for (int i = 0; i < n.length(); i++)
    {
        int now = 1;
        for (int j = 0; j < 10; j++)
            if (n[i] - '0' != j && canreach[n[i] - '0'][j] == true)
                now++;
        ans *= now;
    }
    printf("%.0Lf",ans);
}