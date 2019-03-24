#include <iostream>
#include <cmath>
using namespace std;
int n;
int arr[101], dp[101][101];
int main()
{
    while (cin >> n)
    {
        for (int i = 1; i <= n; i++)
            cin >> arr[i];
        for (int i = 3; i <= n; i++)
            for (int j = 1; j + i - 1 <= n; j++)
            {
                int point = j + i - 1;
                dp[j][point] = INT_MAX;
                for (int bp = j + 1; bp < point; bp++)
                {
                    dp[j][point] = min(dp[j][point], dp[j][bp] + dp[bp][point] + (arr[j] * arr[bp] * arr[point]));
                }
            }
        cout << dp[1][n] << endl;
    }
}