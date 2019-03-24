#include <bits/stdc++.h>
using namespace std;
int n, p,finalans=1;
int primes[10001000], prinow;
bool isprime[10001000];
int morethings[10010000];
int eulersieve(int num = n+100)
{
    memset(isprime, 1, sizeof(isprime));
    isprime[1] = false;
    for (int i = 2; i <= num; i++)
    {
        if (isprime[i])
            primes[++prinow] = i;
        for (int j = 1; j <= prinow && i * primes[j] <= num; j++)
        {
            isprime[i * primes[j]] = false;
            if (i % primes[j] == 0)
                break;
        }
    }
}
void more(int a)
{
    int num=a;
    for(int i=1;isprime[num]!=true;i++){
        if(num%primes[i]==0){
            num/=primes[i];
            morethings[primes[i]]++;
        }
    }
    morethings[num]++;
}
int main()
{
    cin >> n >> p;
    eulersieve();
    for(int i=4;i<=n;i++){
        if(!isprime[i]){
            more(i);
        }
    }
    for(int i=2;i<=n;i++){
        if(isprime[i]){
            finalans%=p;
            finalans*=(morethings[i]+2)%p;
            finalans%=p;
        }
    }
    cout<<finalans;
}

