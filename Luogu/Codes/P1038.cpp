#include<bits/stdc++.h>
using namespace std;
const int maxn = 101;
const int maxm = 10001;
int n, m;
bool got[maxn];
class Node
{
public:
    Node();
    ~Node();
    int c, u;
    bool isinput = true, isoutput = true;
    int son;
private:

}point[maxn];

Node::Node()
{
    son = -1;
}

Node::~Node()
{
}
struct Road
{
    int to, next, val;
}path[maxm];
int main()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        int a, b;
        cin >> a >> b;
        point[i].c = a;
        point[i].u = b;
    }
    int cc = 1;
    for (int i = 0; i < m; i++)
    {
        int from, to, val;
        cin >> from >> to >> val;
        path[cc].next = point[from].son;
        path[cc].to = to;
        path[cc].val = val;
        path[cc].to = cc;
        cc++;
        point[from].isoutput = false;
        point[to].isinput = false;
    }
    queue<int>q;
    for (int i = 0; i < n; i++)
    {
        if (point[i].isinput&&point[i].c > 0)
        {
            q.push(i);
        }
    }
    while (!q.empty())
    {
        int fa = q.front();
        q.pop();
        got[fa] = false;
        if (point[fa].c > point[fa].u)
        {
            point[fa].c -= point[fa].u;
            Road cache = path[point[fa].son];
            for (;;)
            {
                if (cache.next == -1)
                {
                    point[cache.to].c += point[cache.to].c*cache.val;
                    if (got[cache.to] == false)
                    {
                        got[cache.to] = true;
                        q.push(cache.to);
                    }
                    break;
                }
                else
                {
                    point[cache.to].c += point[cache.to].c*cache.val;
                    if (got[cache.to] == false)
                    {
                        got[cache.to] = true;
                        q.push(cache.to);
                    }
                    cache = path[cache.next];
                }
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (point[i].isoutput&&point[i].c > 0)
        {
            cout << i + 1 << " " << point[i].c << endl;
        }
    }
    return 0;
}