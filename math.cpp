#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll gcd(ll a,ll b)
{
    return b==0?a:gcd(b,a%b);
}
long long exgcd(long long a,long long b,long long &x,long long &y)
{
    long long d;
    if(b==0)
    {
        x=1,y=0;
        d=a;
    }
    else
    {
        d=exgcd(b,a%b,y,x);
        long long x1=x,y1=y;
        x=y1;
        y=x1-(a/b)*y1;
    }
    return d;
}
const int maxn=100010;
int prime[maxn],prime_cnt=0;
bool sieve[maxn];
void EulerSieve(int n=maxn)
{
    for(int i=2;i<=n;i++)
    {
        if(sieve[i]==false)
            prime[prime_cnt++]=i;
        for(int j=0;j<prime_cnt;j++)
        {
            if(i*prime[j]>n)
                break;
            sieve[i*prime[j]]=true;
            if(i%prime[j]==0)
                break;
        }
    }
    return;
}
int main()
{
    
}