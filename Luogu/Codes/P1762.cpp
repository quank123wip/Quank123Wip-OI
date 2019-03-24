#include<bits/stdc++.h>
typedef long long ll;
void exgcd(long long a,long long b,long long &x,long long &y)
{
    if(b==0){
        x=1,y=0;
        return;
    }
    else
    {
        exgcd(b,a%b,y,x);
        y-=(a/b)*x;
    }
        
}
ll inv(ll b,ll p)
{
    ll x,y;
    exgcd(b,p,x,y);
    return (x+p)%p;
}
ll read()
{
    ll x=0;
    char p=getchar();
    while(!std::isdigit(p))p=getchar();
    while(std::isdigit(p))
        x=((x*10)+(p-'0'))%19260817,
        p=getchar();
    return x;
}
int main()
{
    ll a, b;
    a=read();
    b=read();
    //std::cout<<a<<std::endl<<b<<std::endl;
    //std::cin>>a>>b;
    if(b%19260817==0)puts("Angry!");
    else std::cout<<((a%19260817)*inv(b,19260817)%19260817)%19260817;
}