/*本题两种写法，O(n)与O(nlogn),注释掉了O(nlogn)*/
#include <bits/stdc++.h>
using namespace std;
const int maxn = 200005;
int n,minq;
int a[maxn],ans,c[maxn];
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    minq=min(0,c[1]);ans=a[1];
    for(int i=1;i<=n;i++)
    {
        c[i]=c[i-1]+a[i];
    }
    for(int i=1;i<=n;i++)
    {
        ans=max(ans,c[i]-minq);
        minq=min(minq,c[i]);
    }
    cout<<ans;
}
/*施工中*/