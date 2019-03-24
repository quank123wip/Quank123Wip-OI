#include<bits/stdc++.h>
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
long long inverse(long long b,long long p)
{
    long long x,y;
    exgcd(b,p,x,y);
    return (x+p)%p;
}
int main()
{
    long long b,p;
    std::cin>>b>>p;
    std::cout<<inverse(b,p);
}