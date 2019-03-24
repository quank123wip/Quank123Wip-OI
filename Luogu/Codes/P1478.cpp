#include <bits/stdc++.h>
using namespace std;
struct node
{
    int x, y;
};
node ap[5001];
int n, s, a, b, i, m, hi;
bool cmp(node a, node b)
{
    return a.y < b.y;
}
int main()
{
    m = 0;
    cin >> n >> s;
    cin >> a >> b;
    hi = a + b;
    for (i = 1; i <= n; i++)
    {
        cin >> ap[i].x >> ap[i].y;
    }
    sort(ap + 1, ap + n + 1, cmp);
    for (i = 1; i <= n; i++)
    {
        if (hi >= ap[i].x && ap[i].y <= s)
        {
            s = s - ap[i].y;
            m++;
            //cout<<ap[i].x<<" "<<ap[i].y<<" "<<m<<endl;
        }
    }
    cout << m << endl;
    return 0;
}