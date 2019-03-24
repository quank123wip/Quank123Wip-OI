#include <bits/stdc++.h>
using namespace std;
char a;
int a1, a2, b1, b2;
string ans1, ans2;
int main()
{
    while (cin >> a)
    {
        if (a == 'E')
            break;
        if ((a1 >= 11 || a2 >= 11) && abs(a1 - a2) >= 2)
        {
            stringstream cachea;
            cachea << a1 << ":" << a2 << endl;
            ans1 += cachea.str();
            cachea.clear();
            a1 = 0;
            a2 = 0;
        }
        if ((b1 >= 21 || b2 >= 21) && abs(b1 - b2) >= 2)
        {
            stringstream cacheb;
            cacheb << b1 << ":" << b2 << endl;
            ans2 += cacheb.str();
            cacheb.clear();
            b1 = 0;
            b2 = 0;
        }
        if (a == 'W')
        {
            a1++;
            b1++;
        }
        else if (a == 'L')
        {
            a2++;
            b2++;
        }
    }
    if (!ans1.empty() && !ans2.empty())
    {
        cout << ans1;
        if (a1 != 0 || a2 != 0)
        {
            cout << a1 << ":" << a2 << endl;
        }
        cout << endl
             << ans2;
        if (b1 != 0 || b2 != 0)
        {
            cout << b1 << ":" << b2 << endl;
        }
    }
    else
    {
        cout << a1 << ":" << a2 << endl;
        if ((a1 >= 11 || a2 >= 11) && abs(a1 - a2) >= 2)
            cout << "0:0" << endl;
        cout << endl
             << b1 << ":" << b2;
        if ((b1 >= 21 || b2 >= 21) && abs(b1 - b2) >= 2)
            cout << "0:0" << endl;
    }
}