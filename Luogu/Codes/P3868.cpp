#include<bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
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
ll china(ll a[],ll b[],ll k)
{
    ll ans=0,M=1,x,y;
    for(register int i=1;i<=k;i++)M*=b[i];
    for(register int i=1;i<=k;i++)
    {
        ll mi=M/b[i];
        exgcd(mi,b[i],x,y);
        x=(x%b[i]+b[i])%b[i];
        ans=(ans+slow_mul(slow_mul(mi,x,M),a[i],M))%M;
    }
    return (ans+M)%M;
}
using std::cin;
using std::cout;
using std::endl;
signed main()
{
    ll k,a[20],b[20];
    cin>>k;
    for(register int i=1;i<=k;i++)cin>>a[i];
    for(register int i=1;i<=k;i++)cin>>b[i];
    cout<<china(a,b,k);
}