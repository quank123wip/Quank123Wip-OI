#include<algorithm>
#include<iostream>
#include<map>
#include<string>
#include<cstdlib>
#include<cstdio>
#include<cstring>
class Solution
{
    private:
        struct Node
        {
            int id;
            std::string p;
            int son;
            int fa;
            int depth;
        }Nodes[100010];
        std::pair<int,int>Edges[100010];
        int st[100010][20];
        int Edgec;
        int n,m;
        std::map<std::string,int>p;
        inline void Addpath(std::string a,std::string b)
        {
            int from=p[a];
            int to=p[b];
            Edges[Edgec].first=to;
            Edges[Edgec].second=Nodes[from].son;
            Nodes[from].son=Edgec;
            Edgec++;
        }
        inline void dfs(int pos,int depth)
        {
            Nodes[pos].depth=depth;
            for(int i=Nodes[pos].son;i!=-1;i=Edges[i].second)
            {
                dfs(Edges[i].first,depth+1);
            }
            st[pos][0]=Nodes[pos].fa;
        }
        inline void Init(void)
        {
            for(int i=0;i<n;i++)
            {
                if(Nodes[i].fa==i)
                {
                    dfs(i,0);
                    break;
                }
            }
            for(int i=0;i<n;i++)
            {
                for(int j=1;(1<<j)<=Nodes[i].depth;j++)
                {
                    st[i][j]=st[st[i][j-1]][j-1];
                }
            }
        }
        inline int LCA(std::string as,std::string bs)
        {
            //int ans;
            int a=p[as],b=p[bs];
            if(Nodes[a].depth>Nodes[b].depth)std::swap(a,b);
            for(int i=20;i>=0;i--)
                if(Nodes[a].depth<Nodes[b].depth&&Nodes[st[b][i]].depth>=Nodes[a].depth)
                    b=st[b][i];
            for(int i=20;i>=0;i--)
                if(st[a][i]!=st[b][i])
                {
                    a=st[a][i];
                    b=st[b][i];
                }
            return st[a][0];
        }
    public:
        friend std::istream& operator >> (std::istream &iput,Solution &Object);
        friend std::ostream& operator << (std::ostream &oput,Solution &Object);
};
std::istream& operator >> (std::istream &iput,Solution &Object)
{
    memset(Object.st,0,sizeof(Object.st));
    Object.Edgec=0;
    iput>>Object.n>>Object.m;
    int cc=0;
    for(int i=1;i<Object.n;i++)
    {
        std::string pa,pb;
        iput>>pa>>pb;
        if(!Object.p.count(pa))
        {
            Object.Nodes[cc].p=pa;
            Object.Nodes[cc].id=cc;
            Object.Nodes[cc].son=-1;
            Object.Nodes[cc].fa=cc;
            Object.p[pa]=cc;
            cc++;
        }
        if(!Object.p.count(pb))
        {
            Object.Nodes[cc].p=pb;
            Object.Nodes[cc].id=cc;
            Object.Nodes[cc].son=-1;
            Object.Nodes[cc].fa=Object.p[pa];
            Object.p[pb]=cc;
            cc++;
        }
        else
        {
            Object.Nodes[Object.p[pb]].fa=Object.p[pa];
        }
        
        Object.Addpath(pa,pb);
    }
    Object.Init();
    return iput;
}
std::ostream& operator << (std::ostream &oput,Solution &Object)
{
    for(int i=0;i<Object.m;i++)
    {
        std::string a,b;
        std::cin>>a>>b;
        int p=Object.LCA(a,b);
        std::cout<<Object.Nodes[p].depth-Object.Nodes[Object.p[a]].depth+1;
    }
    return oput;
}

int main()
{
    int t;
    std::cin>>t;
    while(t--)
    {
        Solution test;
        std::cin>>test;
        std::cout<<test;
    }
}