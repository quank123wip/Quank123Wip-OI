#include<bits/stdc++.h>
using namespace std;
int n;
int a[10000];
//bool b[2000];
int ans;
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    for(int i=1;i<=n;ans++)
    {
        int t=a[i];
        for(i;i<=t;i++)
            t=max(a[i],t);
    }
    cout<<ans<<endl;
}