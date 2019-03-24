#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=300005;
int n,k;
struct Node
{
    int jojo,dio;
}pppp[maxn];
ll orz,now;
bool operator < (Node jojo,Node dio)
{
    return (jojo.jojo > dio.jojo ||!(dio.jojo > jojo.jojo) && jojo.jojo > dio.jojo);
}
priority_queue<int> pq;
int main()
{
    cin>>n>>k;
    for(int i=1;i<=n;i++)cin>>pppp[i].dio>>pppp[i].jojo;
    sort(pppp+1,pppp+n+1);
    for(int i=1;i<=n;i++)
    {
        now+=pppp[i].dio;
        pq.push(-pppp[i].dio);
        if((int)pq.size()>k)
        {
            now+=pq.top();
            pq.pop();
        }
        orz = max(orz, now * pppp[i].jojo);
    }
    cout<<orz;
}