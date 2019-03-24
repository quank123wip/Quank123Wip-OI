#include<bits/stdc++.h>
using namespace std;
constexpr double eps=1e-10;
constexpr int maxn=10005;
int t;
int n;
int a[maxn],b[maxn],c[maxn];
inline int compare_double(double objecta)
{
    if(objecta<-eps)return -1;
    if(objecta>eps)return 1;
    return 0;
}
inline double FunctionF(double pos)
{
    double ans=-1.0/0.0;
    for(int i=0;i<n;i++)
    {
        ans=max(ans,a[i]*pos*pos+b[i]*pos+c[i]);
    }
    return ans;
}
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        for(int i=0;i<n;i++)
        {
            scanf("%d%d%d",&a[i],&b[i],&c[i]);
        }
        double l=static_cast<double>(0);
        double r=static_cast<double>(1000);
        while(compare_double(l-r)==-1)
        {
            double mid1=l+((r-l)/3.0);
            double mid2=r-((r-l)/3.0);
            if(compare_double(FunctionF(mid1)-FunctionF(mid2))<0)
            {
                r=mid2;
            }
            else
            {
                l=mid1;
            }
        }
        printf("%.4lf\n",FunctionF(l));
    }
}