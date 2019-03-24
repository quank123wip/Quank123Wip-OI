#include <bits/stdc++.h>
using namespace std;
double a, b, c, d;
inline double f(double p)
{
    return p * p * p * a + p * p * b + p * c + d;
}
int cc = 0;
int main()
{
    cin >> a >> b >> c >> d;
    for (int i = -100; i <= 100; i++)
    {
        double l, r, mid;
        l = i, r = i + 1;
        if (f(l) == 0)
        {
            printf("%.2lf ", l);
            cc++;
        }
        if (f(l) * f(r) < 0)
        {
            while (r - l >= 0.001)
            {
                mid = (l + r) / 2;
                if (f(mid) * f(r) <= 0)
                {
                    l = mid;
                }
                else
                    r = mid;
            }
            printf("%.2lf ", r);
            cc++;
        }
        if (cc == 3)
            return 0;
    }
}