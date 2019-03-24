#include<bits/stdc++.h>
using namespace std;
//set<int>ans;
int Set_find[1010];
int cc;
inline int Find_set(int x)
{
    if(x!=Set_find[x])Set_find[x]=Find_set(Set_find[x]);
    return Set_find[x];
}
inline void Union(int a,int b)
{
    if(Find_set(a)==Find_set(b))return;
    Set_find[Find_set(a)]=Find_set(b);
    cc--;
    return;
}
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n,m;
        cin>>n>>m;
        cc=n;
        for(int i=1;i<=n;i++)
        {
            Set_find[i]=i;
        }
        for(int i=0;i<m;i++)
        {
            int a,b;
            cin>>a>>b;
            Union(a,b);
        }
        cout<<cc;
        if(t!=0)cout<<endl;
    }
}