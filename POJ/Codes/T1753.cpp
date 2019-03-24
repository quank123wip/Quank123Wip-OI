#include <bits/stdc++.h>
using namespace std;
pair<int, int> start,now;
queue<pair<int, int>> q1, q2;
int ans1, ans2;
int main()
{
    int starta;
    for (int i = 0; i < 16; i++)
    {
        char a;
        cin >> a;
        if (a == 'b')
            starta += 1;
        starta << 1;
    }
    start.first = starta;
    q1.push(start);
    q2.push(start);
    while (!q1.empty())
    {
        now=q1.front();q1.pop;
        for (int i = 0; i < 16; i++)
        {
            if(i!=0&&i!=3&&i!=4&&i!=7&&i!=8&&i!=11&&i!=12&&i!=15){
                
            }else{
                if(i==)
            }
        }
    }
    while (!q2.empty())
    {
    }
}