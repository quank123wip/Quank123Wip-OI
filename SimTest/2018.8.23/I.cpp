#include<bits/stdc++.h>
using namespace std;
int sums[100000];
int main()
{
    ios::sync_with_stdio(false);
    int n;
    sums[1]=1;
    for(int i=0;i<65536;i++)
    {
        sums[i]=sums[i-1]+i;
    }
    while(cin>>n)
    {
        int sum=0;
        for(int i=0;i<n;i++)
        {
            int now;
            cin>>now;
            sum+=now;
        }
        int ans;
        for(int i=0;i<65536;i++)
        {
            if(sums[i]>=sum)
            {
                ans=i;
                break;
            }
        }
        cout<<"yes"<<endl;
        if(sums[ans]==sum)
        cout<<1<<endl;
        else
        cout<<ans<<endl;
    }
}