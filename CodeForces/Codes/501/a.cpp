#include <iostream>
#include<vector>
using namespace std;
const int maxn = 101;
int n, m, arr[maxn],ans;
int main()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        int a, b;
        cin >> a >> b;

        for (int j = a; j <= b; j++ /*操作符*/)
        {
            arr[j] = true;
        }
    }
    
    for(int i = 1; i <= m; i++/*操作符*/)
    {
        if(arr[i]==false)ans++;
    }
    cout<<ans<<endl;
    for(int i=1;i<=m;i++)
    {
        if(arr[i]==false)cout<<i<<" ";
    }
}