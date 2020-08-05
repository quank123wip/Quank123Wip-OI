//UVA1626
//区间DP
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int MaxN = 100 + 10;
const int INF = 0x3f3f3f3f; //Trick

int n, f[MaxN][MaxN]; //区间内最优解长度
string s;

#define isMatch1(l, r) (s[l] == '(' && s[r] == ')')
#define isMatch2(l, r) (s[l] == '[' && s[r] == ']')
#define isMatch(l, r) (isMatch1(l, r) || isMatch2(l, r))

inline void DP()
{
    for (int i = 0; i < MaxN; i++)
        f[i][i] = 1, f[i + 1][i] = 0;
    for (int i = s.length() - 2; i >= 0; i--)     //从后向前枚举, 枚举起点
        for (int j = i + 1; j <= s.length(); j++) //枚举终点
        {
            f[i][j] = INF;
            if (isMatch(i, j))
                f[i][j] = f[i + 1][j - 1];                     // 考虑两端
            for (int k = i; k < j; k++)                        // 枚举断点
                f[i][j] = min(f[i][j], f[i][k] + f[k + 1][j]); // 状态转移
        }
}

void PrintAns(int l, int r)
{
    if (l > r)
        return;
    if (l == r)
    {
        if (s[l] == '(' || s[l] == ')') cout<<"()";
        else cout<<"[]";
        return;
    }
    if(isMatch(l,r)&&f[l][r] == f[l + 1][r - 1])//两端
    {
        cout<<s[l];
        PrintAns(l+1,r-1);
        cout<<s[r];
        return;
    }
    for (int k = l; k < r; k++)
        if(f[l][r] == f[l][k] + f[k + 1][r])
        {
            PrintAns(l,k);
            PrintAns(k+1,r);
            return;
        }
}

signed main()
{
    cin >> n;
    while (n--)
    {
        getline(cin, s);
        getline(cin, s);
        DP();
        PrintAns(0,s.length()-1);
        cout<<endl;
        if(n)
        cout<<endl;
    }
}