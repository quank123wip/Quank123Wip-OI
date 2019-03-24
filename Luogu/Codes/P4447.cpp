#include <bits/stdc++.h>
using namespace std;
const int maxn = 100000 + 5;
int n, m;
int a[maxn];
vector<deque<int> > vec;
inline bool cmp(deque<int> a,deque<int> b)
{
    return a.size()<b.size();
}
int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    sort(a, a + n);
    deque<int>ed;
    vec.resize(1);
    for (int i = 0; i < n; i++)
    {
        bool pd=false;
        for(vector<deque<int> >::iterator iter=vec.begin();iter!=vec.end();iter++){
            if(iter->size()==0||iter->back()==a[i]-1){
                iter->push_back(a[i]);
                pd=true;
                break;
            }
            else if(iter->front()==a[i]+1){
                iter->push_front(a[i]);
                pd=true;
                break;
            }
        }
        if(pd==false){
            ed.push_back(a[i]);
            vec.push_back(ed);
            ed.clear();
        }
        sort(vec.begin(),vec.end(),cmp);
    }
    cout<<vec.begin()->size();
}