#include <bits/stdc++.h>
#include<ext/pb_ds/priority_queue.hpp>
using namespace std;
int n, m, q, u, v, t, cc, cnt1, cnt2, h1 = 1, h2 = 1, h = 1;
long double p;
queue<int> cuta, cutb,pq;
vector<int>origin,ansq;
int main()
{
    scanf("%d%d%d%d%d%d", &n, &m, &q, &u, &v, &t);
    p = static_cast<long double>(u) / static_cast<long double>(v);
    for (int i = 0; i < n; i++)
    {
        int cache;
        scanf("%d", &cache);
        origin.push_back(cache);
    }
    sort(origin.begin(),origin.end(),[](int a,int b){return a>b;});
    for(int i=0;i<n;i++)pq.push(origin[i]);
    for (int i = 1; i <= m; i++)
    {
        int now;
        int a=INT_MIN,b=INT_MIN,c=INT_MIN;
        if(!pq.empty())a=pq.front();
        if(!cuta.empty())b=cuta.front();
        if(!cutb.empty())c=cutb.front();
        now=max(a,max(b,c));
        if(now==a)pq.pop();
        else if(now==b)cuta.pop();
        else if(now==c)cutb.pop();
        now+=cc;
        int c1,c2;
        c1=static_cast<int>(floor(static_cast<long double>(now)*p));
        c2=now-c1;
        cc+=q;
        c1-=cc;
        c2-=cc;
        cuta.push(c1);
        cutb.push(c2);
        if(i%t==0)printf("%d ",now);
    }
    printf("\n");
    while(!cuta.empty())ansq.push_back(cuta.front()),cuta.pop();
    while(!cutb.empty())ansq.push_back(cutb.front()),cutb.pop();
    while(!pq.empty())ansq.push_back(pq.front()),pq.pop();
    sort(ansq.begin(),ansq.end(),[](int a,int b){return a>b;});
    int cnt=1;
    for(auto &i:ansq)
    {
        if(cnt%t==0)
        printf("%d ",i+cc);
        cnt++;
    }
}
