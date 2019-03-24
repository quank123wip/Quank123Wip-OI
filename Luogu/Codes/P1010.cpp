#include <bits/stdc++.h>
using namespace std;
int n;
inline string sq(int a)
{
    vector<int> v;
    int p = a;
    while (p != 0)
    {
        v.push_back(p & 1);
        p = p >> 1;
    }
    string c;
    for (int i = v.size() - 1; i >= 0; i--)
    {
        if (v[i] == 1)
        {
            if (i != 1)
            {
                c += "2(";
                if (i == 0 || i == 2)
                {
                    c += i + '0';
                }
                else
                {
                    c += sq(i);
                }
                c += ")+";
            }
            else
            {
                c += "2+";
            }
        }
    }
    c.erase(c.length() - 1, 1);
    return c;
}
int main()
{
    cin >> n;
    cout << sq(n);
}