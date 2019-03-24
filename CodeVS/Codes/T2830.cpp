#include <bits/stdc++.h>
using namespace std;
long long n;
struct node
{
    long long origin, k;
    long long p;
    bool operator<(const node b) const
    {
        if(k==b.k)return p>b.p;
        else return k>b.k;
    }
};
priority_queue<node> pq;
int main()
{
    string cache;long long now;
    long long a;
    while (cin >> cache && cache[0] != '#')
    {
        cin >> now >> a;
        node c;
        c.origin=a;
        c.k=a;
        c.p=now;
        pq.push(c);
    }
    cin >> n;
    while(n--)
    {
        node now=pq.top();
        pq.pop();
        cout<<now.p<<endl;
        now.k+=now.origin;
        pq.push(now);
    }
}