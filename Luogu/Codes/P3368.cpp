// luogu-judger-enable-o2
#include<bits/stdc++.h>
using namespace std;
#define Lowbit(x) (x&-x)
//#define Debug
typedef long long LL;
class bitree
{
    public:
        inline bitree(void){
            originarr.push_back(0);
            bitarr.push_back(0);
        }
        inline void resize(long long length){
            originarr.resize(length+1);
            bitarr.resize(length+1);
        }
        inline void edit(long long pos,long long value){
            long long origin=originarr[pos];
            originarr[pos]=value;
            value-=origin;
            long long cache=pos;
            while(cache<=bitarr.size()){
                bitarr[cache]+=value;cache+=Lowbit(cache);
            }
        }
        inline long long query(long long leftpos/*,long long rightpos*/){
            //return prefix(rightpos)-prefix(leftpos-1);
            return prefix(leftpos);
        }
        inline long long getorigin(long long pos){
            return originarr[pos];
        }
    private:
        vector<long long>originarr;
        vector<long long>bitarr;
        inline long long prefix(long long pos){
            long long pfans=0;
            long long cache=pos;
            while(cache>0){
                pfans+=bitarr[cache];cache-=Lowbit(cache);
            }
            return pfans;
        }
} test;
int main()
{
    LL n=0;LL m=0;LL cache2=0;
    scanf("%lld%lld",&n,&m);
    test.resize(n);
    for(int i=0;i<n;i++){
        LL cache;
        scanf("%lld",&cache);
        test.edit(i+1,cache-cache2);
        cache2=cache;
    }
    for(int i=0;i<m;i++){
        int a;
        LL b=0,c=0;
        LL value=0;
        scanf("%d%lld",&a,&b);
        if(a==1){
            scanf("%lld%lld",&c,&value);
            test.edit(b,test.getorigin(b)+value);
            if(c+1<=n)test.edit(c+1,test.getorigin(c+1)-value);
        }else{
            printf("%lld\n",test.query(b));
        }
    }
    return 0;
}