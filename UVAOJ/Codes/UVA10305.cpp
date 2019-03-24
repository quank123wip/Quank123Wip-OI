#include <bits/stdc++.h>
using namespace std;
struct node
{
    int fac;
    int value;
    int son;
    bool used;
};
node graph[101];
pair<int, int> path[201];
int cc=1;
inline void reset(void)
{
    cc = 1;
    for (int i = 0; i < 101; i++)
    {
        graph[i].fac = 0;
        graph[i].value = i;
        graph[i].son = 0;
        graph[i].used = false;
    }
    for (int i = 0; i < 201; i++)
    {
        path[i].first = 0;
        path[i].second = 0;
    }
}
inline void set_path(int from, int to)
{
    graph[to].fac++;
    path[cc].first = to;
    path[cc].second = graph[from].son;
    graph[from].son = cc;
    cc++;
}
inline void solve(int n, int m)
{
    queue<int> q;
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        set_path(a, b);
    }
    while (q.size() != n)
    {
        for (int i = 1; i <= n; i++)
        {
            if (graph[i].used == false && graph[i].fac == 0)
            {
                graph[i].used = true;
                q.push(graph[i].value);
                pair<int, int> now = path[graph[i].son];
                for (;;)
                {
                    graph[now.first].fac--;
                    now = path[now.second];
                    if (now.first == 0)
                        break;
                }
                i=1;
            }
        }
    }
    while (!q.empty())
    {
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;
}
int main()
{
    int m, n;
    while (cin >> n >> m)
    {
        if (n == 0 && m == 0)
            return 0;
        reset();
        solve(n, m);
    }
}