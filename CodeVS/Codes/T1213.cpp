#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int Task;
long long a,b,c,d,x,y,p,q,r,s,ans;
inline ll exgcd(ll a,ll b,ll &x,ll &y)
{
    if(b==0){x=1;y=0;return a;}
    ll d=exgcd(b,a%b,y,x);
    y-=a/b*x;return d;
}
int main()
{
    cin>>Task;
    while(Task--)
    {
        a=0,b=0,d=0,x=0,y=0,ans=0;
        scanf("%lld%lld%lld%lld%lld%lld%lld",&a,&b,&c,&p,&q,&r,&s);
        for(int x=p;x<=q;x++)
            for(int y=r;y<=s;y++)
                if(a*x+b*y==-c)ans++;
        cout<<ans<<endl;
    }
}