#include <bits/stdc++.h>
int n, k;
std::string q;
//bool flag[1000];
int main()
{
    std::cin >> n;
    while (n--)
    {
        //memset(flag, 0, sizeof(flag));
        int ans=0;
        std::cin >> k >> q;
        int a=0,b=INT_MAX;
        for (int i = 0; i < q.length(); i++)
        {
            if (q[i] == '<')
            {
                a=i;
            }
            else
            {
                b=std::min(b,i);
            }
        }
        ans=std::min(b,k-a-1);
        std::cout<<ans<<std::endl;
    }
}