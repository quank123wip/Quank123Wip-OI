#include <bits/stdc++.h>
using namespace std;
int t, k;
int C[3010][3010];
int Solution[3010][3010];
inline void Prepare(void)
{
    for (int i = 0; i < 2001; i++)
    {
        C[i][0] = 1;
        C[i][i] = 1;
    }
    for (int i = 2; i < 2001; i++)
    {
        for (int j = 1; j < i; j++)
        {
            C[i][j] = ((C[i - 1][j - 1]) + (C[i - 1][j]))%k;
        }
    }
    return;
}
inline void Prefix(int k)
{
    for (int i = 0; i < 2001; i++)
    {
        for (int j = 0; j < 2001; j++)
        {
            Solution[i][j] = Solution[i - 1][j] + Solution[i][j - 1] - Solution[i - 1][j - 1];
            if (C[i][j] == 0)
                Solution[i][j]++;
        }
        Solution[i][i + 1] = Solution[i][i];
    }
}
inline void Solve(int t)
{
    while (t--)
    {
        int n, m;
        cin >> n >> m;
        cout << (m>n?Solution[n][n]:Solution[n][m]) <<endl;
    }
}
int main()
{
    //freopen("problem.in","r",stdin);
    //freopen("problem.out","w",stdout);
    cin >> t >> k;
    Prepare();
    Prefix(k);
    Solve(t);
}