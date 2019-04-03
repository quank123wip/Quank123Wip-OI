#include<bits/stdc++.h>
namespace ISAP
{
    static const int MaxN=100010;
    static const int MaxM=100010;
    int head[MaxN],dep[MaxN],gap[MaxN];
    int to[MaxM],f[MaxN],next[MaxM];
    void bfs(int t)
    {
        memset(dep,-1,sizeof dep);
        memset(gap,0,sizeof gap);
        dep[t]=0;
        gap[0]=1;
        std::queue<int>q;
        q.push(t);
        while(q.size())
        {
            
        }
    }
}