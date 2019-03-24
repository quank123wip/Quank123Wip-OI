#include <bits/stdc++.h>
using namespace std;
const int maxn = 100001;
class Solution
{
  private:
    int n;
    struct Node
    {
        int pos;
        int next;
        int Value;
        int nextV;
        Node()=default;
        Node(int pos, int next, int Value, int nextV)
        {
            pos = pos;
            next = next;
            Value = Value;
            nextV = nextV;
        }
    } Nodes[maxn];
    inline int Check(int pos)
    {
        int ans = 0;
        Node now = Nodes[pos];
        int v = now.Value;
        while (v >= now.nextV)
        {
            ans++;
            v -= now.nextV;
            now = Nodes[now.next];
            v += now.Value;
            if (ans == n)
                break;
        }
        return ans;
    }
    inline int DotheThing(void)
    {
        for (int i = 1; i <= n;)
        {
            if (Check(i) == n)
                return i;

            else
            {
                i = Check(i) + i + 1;
            }
        }
        return -1;
    }

  public:
    Solution()=default;
    ~Solution()=default;
    friend istream &operator>>(istream &input, Solution &Object);
    friend ostream &operator<<(ostream &output, Solution &Object);
};
istream &operator>>(istream &input, Solution &Object)
{
    input >> Object.n;
    for (int i = 1; i <= Object.n; i++)
    {
        Object.Nodes[i].pos = i;
        Object.Nodes[i].next = i + 1;
        input >> Object.Nodes[i].Value;
    }
    Object.Nodes[Object.n].next = 1;
    for (int i = 1; i <= Object.n; i++)
        input >> Object.Nodes[i].nextV;
    return input;
}
ostream &operator<<(ostream &output, Solution &Object)
{
    int p = Object.DotheThing();
    if (p == -1)
        output << "Not possible";
    else
        output << "Possible from station " << p;
    output << endl;
    return output;
}
int main()
{
    int t;
    cin>>t;
    for(int i=1;i<=t;i++)
    {
        Solution Now;
        cin>>Now;
        cout<<"Case "<<i<<": "<<Now;
    }
    return 0;
}