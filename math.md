# 数论、数学模板总结

## $\text{gcd}$(欧几里得算法)

辗转相除法：

对于两个整数$a$,$b$，求它们的最大公因数$gcd(a,b)$,对于$a\div b=c……d$,其中$c=\lfloor a\div b\rfloor ,d=a\ mod\ b$,易证当$d=0$时$gcd(a,b)=min(a,b)$,当$d\neq 0$时,$gcd(a,b)=gcd(b,d)$

由此可递归求出$gcd(a,b)$

```cpp
long long gcd(long long a,long long b)
{
    return b==0?a:gcd(b,a%b);
}
```

## $\text{Exgcd}$(扩展欧几里得算法)

定义$ax+by=gcd(a,b)$,由$exgcd$可求$x,y$的一个值,,时间复杂度为$O(nlogn)$

```cpp
void exgcd(long long a,long long b,long long &x,long long &y)
{
    if(b==0){
        x=1,y=0;
        return;
    }
    else
    {
        exgcd(b,a%b,y,x);
        y-=(a/b)*x;
    }
        
}
```

## $\text{Euler}$筛(线性筛)

由$\text{Eratosthenes}$筛法,我们可以得出以下过程
> 从2开始,每找到一个素数,将它的所有倍数从表中划去
>
> 然后跳过被划过的数,下一个数便是下一个素数

很明显,这个算法是不够优秀的,为了优化,可以根据一些素数定理,得到线性筛法,其复杂度为$O(n)$

```cpp
const int maxn=100010;
int prime[maxn],prime_cnt=0;
bool sieve[maxn];
void EulerSieve(int n=maxn)
{
    for(int i=2;i<=n;i++)
    {
        if(sieve[i]==false)
            prime[prime_cnt++]=i;
        for(int j=0;j<prime_cnt;j++)
        {
            if(i*prime[j]>n)
                break;
            sieve[i*prime[j]]=true;
            if(i%prime[j]==0)
                break;
        }
    }
    return;
}
```
## 乘法逆元

当$a\perp b$时,如果$ax\equiv1(mod\ b)$,则称$x$是$a$在模$b$意义下的逆元,记作$a^{-1}$

根据以上定义,我们可以得出乘法逆元的应用,即

$a\div b\ mod\ n=ab^{-1}\ mod \ n$

在求解同余方程可以以此快速计算同余除法.

在引入乘法逆元之后,我们可以得出模运算的运算规则

>$(a+b)\ mod\ p=(a\ mod\ p+b\ mod\ p)\ mod\ p$
>
>$(a-b)\ mod\ p=(a\ mod\ p-b\ mod\ p)\ mod\ p$
>
>$(a\times b)\ mod\ p=(a\ mod\ p\times b\ mod\ p)\ mod\ p$
>
>$a^b\ mod\ p=(a\ mod\ p)^b\ mod\ p$
>
>$(a\div b)\ mod\ p=a\times b^{-1}\ mod\ p$

同时,我们发现,对于$ax\equiv1(mod\ p)$,可转化成$ax\ mod\ p=1$,可用扩展欧几里得定理求出$x$,时间复杂度为$O(nlogn)$
```cpp
void exgcd(long long a,long long b,long long &x,long long &y)
{
    if(b==0){
        x=1,y=0;
        return;
    }
    else
    {
        exgcd(b,a%b,y,x);
        y-=(a/b)*x;
    }
        
}
long long inverse(long long b,long long p)
{
    long long x,y;
    exgcd(b,p,x,y);
    return (x+p)%p;
}
```
[Luogu P1082 同余方程](https://www.luogu.org/problemnew/show/P1082)(直接求乘法逆元)

[Luogu P2613 有理数取余](https://www.luogu.org/problemnew/show/P2613)(带有技巧性,需要在快读的同时取模)
## 中国剩余定理

>"有物不知其数,三三数之剩二,五五数之剩三,七七数之剩二.问物几何?"

中国剩余定理是指形似:
$$\left\{\begin{array}{cc}
x\equiv a_1\ (mod\ m_1)\\
x\equiv a_2\ (mod\ m_2)\\
.\\
.\\
.\\
x\equiv a_n\ (mod\ m_n)\\
\end{array}\right.$$
的同余方程有解的条件

对于上述同余方程,若整数$m_1,m_2,...,m_n$两两互质,对任意整数$a_1,a_2,...,a_n$,上述方程有解,其通解如下:

设$M=\prod^{n}_{i=1}m_i$,并对于任意$i\in{1,2,...,n}$,有$M_i=M\div m_i$,即$M_i=\prod^{n}_{j=1}[j\neq i]m_i$,设$t_i=M_i^{-1}(mod\ m_i)$,其通解为$x=kM+\sum^n_{i=1}a_it_iM_i,k\in \mathbb{Z}$,即,在模$M$意义下仅有一个解$x=(\sum^n_{i=1}a_it_iM_i)mod\ M$

```
typedef long long ll;
typedef __int128 lll;
void exgcd(ll a,ll b,ll &x,ll &y)
{
    if(!b)
        x=1,y=0;
    else
        exgcd(b,a%b,y,x),y-=(a/b)*x;
}
ll slow_mul(ll a,ll b,ll mod)
{
    lll a1=a,b1=b,mod1=mod;
    return (a1*b1)%mod1;
}
ll china(ll a[],ll b[],ll k)
{
    ll ans=0,M=1,x,y;
    for(register int i=1;i<=k;i++)M*=b[i];
    for(register int i=1;i<=k;i++)
    {
        ll mi=M/b[i];
        exgcd(mi,b[i],x,y);
        x=(x%b[i]+b[i])%b[i];
        ans=(ans+slow_mul(slow_mul(mi,x,M),a[i],M))%M;
    }
    return (ans+M)%M;
}
```
[P3868 [TJOI2009]猜数字](https://www.luogu.org/problemnew/show/P3868)(模板题,数据较毒瘤)
## 扩展中国剩余定理
```cpp
typedef long long ll;
typedef __int128 lll;
ll gcd(ll a,ll b)
{
    return b==0?a:gcd(b,a%b);
}
void exgcd(ll a,ll b,ll &x,ll &y)
{
    if(!b)
        x=1,y=0;
    else
        exgcd(b,a%b,y,x),y-=(a/b)*x;
}
ll slow_mul(ll a,ll b,ll mod)
{
    lll a1=a,b1=b,mod1=mod;
    return (a1*b1)%mod1;
}
ll excrt(ll a[],ll b[],ll k)
{
    ll ans=a[1],M=b[1],x=0,y=0,g;
    for(int i=2;i<=k;i++)
    {
        ll bi=((a[i]-ans)%b[i]+b[i])%b[i];
        g=gcd(M,b[i]);
        exgcd(M,b[i],x,y);
        x=slow_mul(bi/g,x,b[i]);
        ans+=M*x;
        M*=b[i]/g;
        ans=(ans+M)%M;
    }
    return (ans%M+M)%M;
}
```
## $\text{Euler}函数$

$\varphi(n)=n\cdot \prod^s_{i=1}(1-\frac{1}{p_i})$

我们发现,欧拉函数和质数有紧密的联系,因此可以修改欧拉筛求出$0~n$的欧拉函数,时间复杂度为$O(n)$
```cpp

```