#include<bits/stdc++.h>
using namespace std;
const int maxn = 200001;
int n;
int a[maxn];
long long ans;
int main() {
	int cache;
    cin>>n;
	for(int i=0;i<n;i++)cin>>a[i];
    ans=a[n-1];
    for(int i=n-2;i>=0;i--)
        ans+=a[i]=min(max(0,a[i+1]-1),a[i]);
    cout<<ans;
	
}