#include <bits/stdc++.h>
#include <bits/extc++.h>
using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::make_pair;
using std::max;
using std::min;
using std::pair;
using std::sort;

const int maxn = 100000 + 10;
const long long INF=0x50000000000LL;

pair<long long,long long>a[5],h[maxn];
std::set<long long>set;
std::map<long long,long long>map;
long long n,m,p1[maxn],p2[maxn],f1[maxn],f2[maxn],s1[maxn][21],s2[maxn][21],f[maxn][21];

inline void Prepare(void)
{
    for(int i=n;i>=1;i--)
    {
        set.insert(h[i].first);
        a[1].first=*--set.lower_bound(h[i].first);
        a[3].first=*--set.lower_bound(a[1].first); 
        a[2].first=*set.upper_bound(h[i].first); 
        a[4].first=*set.upper_bound(a[2].first);
        for(int j=1;j<5;j++)a[j].second=abs(a[j].first-h[i].first);
        sort(a+1,a+1+4,[](decltype(a[1]) p,decltype(a[1]) q){return p.second==q.second?p.first<q.first:p.second<q.second;});
        p1[i]=a[2].second;
        f1[i]=map[a[2].first];
        p2[i]=a[1].second;
        f2[i]=map[a[1].first];
        if(f1[i])s1[i][0]=p1[i],f[i][0]=f1[i];
        if(f2[f1[i]])s1[i][1]=p1[i],s2[i][1]=p2[f1[i]],f[i][1]=f2[f1[i]];
        for(int j=2;j<=16;j++)
            {if(f[f[i][j-1]][j-1]){
                s1[i][j]=s1[i][j-1]+s1[f[i][j-1]][j-1];
                s2[i][j]=s2[i][j-1]+s2[f[i][j-1]][j-1];
                f[i][j]=f[f[i][j-1]][j-1];
            }
            else break;}
    }
}
double ask1(long long x,long long p){
    long long sa=0,sb=0;
    for(long long i=16;i>=0;i--){
        if(f[x][i]&&sa+sb+s1[x][i]+s2[x][i]<=p){
            sa+=s1[x][i];
            sb+=s2[x][i];
            x=f[x][i];
        }
    }
    return (sb==0?INF:(double)sa/(double)sb);
}
void ask2(long long x,long long p){
    long long sa=0,sb=0;
    for(long long i=16;i>=0;i--){
        if(f[x][i]&&sa+sb+s1[x][i]+s2[x][i]<=p){
            sa+=s1[x][i];
            sb+=s2[x][i];
            x=f[x][i];
        }
    }
    if(f1[x]&&sa+sb+s1[x][0]<=p)sa+=s1[x][0];
    printf("%lld %lld\n",sa,sb);
}
void Solve(){ 
    double minn=INF;
    long long bj,x0;
    scanf("%lld",&x0);
    for(long long i=1;i<=n;i++){
        double op=ask1(i,x0);
        if(op<minn)minn=op,bj=i;
    }
    printf("%lld\n",bj);
    long long m,s0;
    scanf("%lld",&m);
    while(m--){
        scanf("%lld%lld",&s0,&x0);
        ask2(s0,x0);
    }
}
signed main()
{
    set.insert(INF);
    set.insert(INF-1);
    set.insert(-INF);
    set.insert(-INF+1);
    scanf("%lld",&n);
    for(int i=1;i<=n;i++)scanf("%lld",&h[i].first),map[h[i].first]=i;
    Prepare();
    Solve();
}