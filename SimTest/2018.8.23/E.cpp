#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;
class Dijkstra
{
    private:
        int n,m,Edgec=0;
        int from,to;
        int son[500];
        struct Edge
        {
            int to,Cost,next;
        }Edges[100000];
        int Dist[500];
        inline void Add(int from,int to,int cost)
        {
            Edges[Edgec].next=son[from];
            Edges[Edgec].to=to;
            Edges[Edgec].Cost=cost;
            son[from]=Edgec;
            Edgec++;
        }
        inline void init(int s)
        {
            Dist[s]=0;
            priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > >pq;
            pq.push(make_pair(Dist[s],s));
            while(!pq.empty())
            {
                pair<int,int> now=pq.top();
                pq.pop();
                for(int i=son[now.second];i!=-1;i=Edges[i].next)
                {
                    if(Dist[Edges[i].to]>Dist[now.second]+Edges[i].Cost)
                    {
                        Dist[Edges[i].to]=Dist[now.second]+Edges[i].Cost;
                        pq.push(make_pair(Dist[Edges[i].to],Edges[i].to));
                    }
                }
            }
        }
    public:
        Dijkstra(int N,int M)
        {
            n=N;
            m=M;
        }
        //~Dijkstra();
        friend istream& operator >> (istream &in, Dijkstra &Object);
        friend ostream& operator << (ostream &out,Dijkstra &Object);
};
istream& operator >> (istream &in, Dijkstra &Object)
{
    //in>>Object.n>>Object.m;
    for(int i=1;i<=Object.n;i++)Object.son[i]=-1,Object.Dist[i]=0x3f3f3f3f;
    for(int i=0;i<Object.m;i++)
    {
        int from,to,cost;
        in>>from>>to>>cost;
        Object.Add(from,to,cost);
        Object.Add(to,from,cost);
    }
    //in>>Object.from>>Object.to;
    Object.from=1,Object.to=Object.n;
    return in;
}
ostream& operator << (ostream &out,Dijkstra &Object)
{
    Object.init(Object.from);
    if(Object.Dist[Object.to]>=0x3f3f3f3f)out<<-1<<endl;
    else out<<Object.Dist[Object.to]<<endl;
    return out;
}
int main()
{
    int n,m;
    while(cin>>n>>m)
    {
        if(n==0&&m==0)return 0;
        Dijkstra Solution(n,m);
        cin>>Solution;
        cout<<Solution;
    }
}