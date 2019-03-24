#include<bits/stdc++.h>
using namespace std;
int main()
{
    int q;
    scanf("%d",&q);
    while(q--)
    {
        long long n,a,b;
        scanf("%lld%lld%lld",&n,&a,&b);
        if(a<(double)b/2)
        {
            printf("%lld\n",a*n);
        }
        else if(a==(double)b/2)
        {
            printf("%lld\n",a*n);
        }
        else
        {
            printf("%lld\n",(n%2)*a+(long long)(n/2)*b);
        }
        
    }
}