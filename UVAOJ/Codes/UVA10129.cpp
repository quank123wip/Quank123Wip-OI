#include <bits/stdc++.h>
using namespace std;
const int maxn = 100001;
int n;
struct Node
{
    int id;
    int fa;
    int son;
    bool vis;
} Nodes[maxn];
vector<int>sonset[30];
inline void reset()
{
    cin>>n;
    for(int i=0;i<30;i++)sonset[i].clear();
    for(int i=0;i<n;i++)
    {
        Nodes[i].id=i;
        Nodes[i].vis=false;
    }
    for(int i=0;i<n;i++)
    {
        string a;
        cin>>a;
        sonset[a[0]-'a'].push_back(i);
        Nodes[i].fa=a[0]-'a';
        Nodes[i].son=a[a.length()-1]-'a';
    }
}

inline void dfs(int pos)
{
    if(Nodes[pos].vis)return;
    Nodes[pos].vis=true;
    for(vector<int>::iterator iter=sonset[Nodes[pos].son].begin();iter!=sonset[Nodes[pos].son].end();iter++)
    {
        dfs(*iter);
    }
}

inline void solve()
{
    reset();
    bool pd=false;
    dfs(0);
    for(int i=0;i<n;i++)
    {
        if(!Nodes[i].vis)
        {
            cout<<"The door cannot be opened."<<endl;
            return;
        }
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(i==j)continue;
            bool pd2=true;
            for(int p=0;p<n;p++)
            {
                if(p==i||p==j)continue;
                if(sonset[Nodes[p].fa].size()!=sonset[Nodes[p].son].size())pd2=false;
            }
            if(pd2&&sonset[Nodes[j].fa].size()-sonset[Nodes[j].son].size()==1&&sonset[Nodes[i].son].size()-sonset[Nodes[i].fa].size()==1)pd=true;
        }
    }
    if(pd)cout<<"Ordering is possible."<<endl;
    else  cout<<"The door cannot be opened."<<endl;
}

int main()
{
    int t;
    cin >> t;
    for(int i=0;i<t;i++)
    {
        solve();
    }
    return 0;
}