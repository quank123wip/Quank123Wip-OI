#include<bits/stdc++.h>
using namespace std;
long long ans;
int main()
{
    int n;
    scanf("%d",&n);
    string a;
    cin>>a;
    for(int i=0;i<n;i++)
    {
        int ai=a[i]-'0';
        if(ai%2==0)
        {
            ans+=i+1;
        }
    }
    cout<<ans;
}