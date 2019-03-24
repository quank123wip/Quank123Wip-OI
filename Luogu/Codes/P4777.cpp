#include<bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
ll gcd(ll a,ll b)
{
    return b==0?a:gcd(b,a%b);
}
void exgcd(ll a,ll b,ll &x,ll &y)
{
    if(!b)
        x=1,y=0;
    else
        exgcd(b,a%b,y,x),y-=(a/b)*x;
}
ll slow_mul(ll a,ll b,ll mod)
{
    lll a1=a,b1=b,mod1=mod;
    return (a1*b1)%mod1;
}
ll excrt(ll a[],ll b[],ll k)
{
    ll ans=a[1],M=b[1],x=0,y=0,g;
    for(int i=2;i<=k;i++)
    {
        ll bi=((a[i]-ans)%b[i]+b[i])%b[i];
        g=gcd(M,b[i]);
        exgcd(M,b[i],x,y);
        x=slow_mul(bi/g,x,b[i]);
        ans+=M*x;
        M*=b[i]/g;
        ans=(ans+M)%M;
    }
    return (ans%M+M)%M;
}
using std::cin;
using std::cout;
using std::endl;
signed main()
{
    ll k,a[200000],b[200000];
    cin>>k;
    for(int i=1;i<=k;i++)cin>>a[i]>>b[i];
    cout<<excrt(b,a,k);
}