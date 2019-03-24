#include <bits/stdc++.h>
#include <iostream>
#include <string>
using namespace std;
const int maxn = 50;
int n, cc;
int check[50];
string a, b, ans;
int main()
{
    cin >> n >> a >> b;
    for (int i = 0; i < a.length(); i++)
    {
        check[a[i] - 'a']++;
        check[b[i] - 'a']--;
    }
    if (a == b)
    {
        cout << "0";
        return 0;
    }
    for (int i = 0; i < 50; i++)
    {
        if (check[i] != 0)
        {
            cout << "-1";
            return 0;
        }
    }

    while (a != b)
    {
        for (int i = 0; i < b.length(); i++ /*操作符*/)
        {
            if (a[i] != b[i])
            {
                int where=-1;
                for(int j=i+1;j<b.length();j++)if(a[j]==b[i]){
                    where=j;break;
                }
                for (int j = where-1; j >=i; --j)
                {
                    ans += j + 1 + '0';
                    ans += " ";
                    cc++;
                    char cache;
                    cache = a[j];
                    a[j] = a[j+1];
                    a[j+1] = cache;
                }
            }
        }
    }
    cout << cc << endl
        << ans;
}
