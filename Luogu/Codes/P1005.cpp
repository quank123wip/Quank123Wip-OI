#include <bits/stdc++.h>
using namespace std;
typedef __int128 LLL;

istream &operator>>(istream &input, __int128 &p)
{
    char a;
    bool pd;
    while (input >> a)
    {
        if (a == '-' && pd != true)
        {
            pd = true;
            continue;
        }
        if (!isdigit(a) && (a=='-'?pd == true:true))
        {
            input.putback(a);
            break;
        }
        p += int(a - '0');
        p *= 10;
    }
    p /= 10;
    if (pd)
        p = -p;
    return input;
}
ostream &operator<<(ostream &output, __int128 &p)
{
    if(p<0){
        output<<"-";
        p=-p;
    }
    stack<char>cache;
    while(p>9)
    {
        cache.push(p%10+'0');
        p/=10;
    }
    output<<p;
    while(!cache.empty())
    {
        output<<cache.top();
        cache.pop();
    }
    return output;
}
int main()
{
}