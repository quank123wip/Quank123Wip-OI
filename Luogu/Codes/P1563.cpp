#include <bits/stdc++.h>
using namespace std;
int n, m,step;
bool isrev[200000],isleft;
char str[200000][101];
int main()
{
    //freopen("toy.in", "r", stdin);
    //freopen("toy.out", "w", stdout);
    scanf("%d%d",&n,&m);
    int ansptr=0;
    for(int i=0;i<n;i++)
    {
        int cache;
        scanf("%d",&cache);
        isrev[i]=cache==1?true:false;
        scanf("%s",str[i]);
    }
    for(int i=0;i<m;i++)
    {
        int cache;
        scanf("%d",&cache);
        isleft=cache==1?true:false;
        scanf("%d",&step);
        if(isleft^isrev[ansptr])
            ansptr=(ansptr+step)%n;
        else
            ansptr=((ansptr-step)%n+n)%n;
    }
    printf("%s",str[ansptr]);
}
