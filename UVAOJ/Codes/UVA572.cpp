#include <bits/stdc++.h>
using namespace std;
const int maxn = 101;
int m, n;
int Map[maxn][maxn];
const int runx[10]={0,0,1,-1,1,1,-1,-1};
const int runy[10]={1,-1,0,0,-1,1,1,-1};
inline void reset(void)
{
    for(int i=0;i<maxn;i++)
        for(int j=0;j<maxn;j++)
            Map[i][j]=0;
    for(int i=0;i<m;i++)
        for(int j=0;j<n;j++)
        {
            char a;
            cin>>a;
            if(a=='*')
            {
                Map[i][j]=-1;
            }
        }
}
inline void solve(void)
{
    reset();
    int cc=1;
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(Map[i][j]==0)
            {
                queue<pair<int,int> >q;
                Map[i][j]=cc;
                q.push(make_pair(i,j));
                while(!q.empty())
                {
                    pair<int,int>p=q.front();
                    q.pop();
                    for(int r=0;r<8;r++)
                    {
                        if(p.first+runx[r]>=0&&p.first+runx[r]<m&&p.second+runy[r]>=0&&p.second+runy[r]<n&&Map[p.first+runx[r]][p.second+runy[r]]==0)
                        {
                            Map[p.first+runx[r]][p.second+runy[r]]=cc;
                            q.push(make_pair(p.first+runx[r],p.second+runy[r]));
                        }
                    }
                }
                cc++;
            }
        }
    }
    cout<<cc-1<<endl;
}
int main()
{
    while(cin>>m>>n)
    {
        if(m==0)return 0;
        solve();
    }
}