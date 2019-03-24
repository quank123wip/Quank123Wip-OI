#include<bits/stdc++.h>
using namespace std;
int n;
const int maxn=50000000;
int S[maxn],C[maxn],scps,scpc;
int ans;
int cc;
int dpp[2000001];
int *dp=dpp+1000000;
string a;
int main()
{
    scanf("%d",&n);
    getline(cin,a);
    for(int i=0;i<n;i++)
    {
        getline(cin,a);
        for(int j=0;j<a.length();j++)
        {
            if(a[j]=='s')S[i]++;
            if(a[j]=='c')C[i]++;
        }
    }
    for(int i=0;i<n;i++)
    {
        dp[S[i]-C[i]]=max(dp[S[i]-C[i]],dp[(-(S[i]-C[i]))]+);
    }
    cout<<dp[0];
}