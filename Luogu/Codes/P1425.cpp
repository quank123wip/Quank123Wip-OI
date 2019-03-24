#include <bits/stdc++.h>
using namespace std;

int main()
{
    int a, b, c, d, e, f, ft, lt, s1;
    cin >> a >> b >> c >> d;
    ft = a * 60 + b;
    lt = c * 60 + d;
    s1 = lt - ft;
    e = s1 / 60;
    f = s1 % 60;
    cout << e << " " << f << endl;
    return 0;
}