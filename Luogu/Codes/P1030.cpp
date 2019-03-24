#include <bits/stdc++.h>
using namespace std;
string a, b;
inline void solve(string now1,string now2)
{
    if(now1.length()==0)return;
    cout<<now1[now1.length()-1];
    int p=now2.find(now1[now1.length()-1]);
    string left1,left2,right1,right2;
    for(int i=0;i<p;i++)
    {
        left2+=now2[i];
    }
    for(int i=p+1;i<now2.length();i++)
    {
        right2+=now2[i];
    }
    int i1=0;
    for(int i=0;i<left2.length();i++){
        left1+=now1[i1++];
    }
    for(int i=0;i<right2.length();i++){
        right1+=now1[i1++];
    }
    solve(left1,left2);
    solve(right1,right2);
}
int main()
{
    cin >> a >> b;
    solve(b,a);
}