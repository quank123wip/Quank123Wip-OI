#include <bits/stdc++.h>
using namespace std;
string a, b;
bool pd;
int ans,anssum;
class Tree
{
  private:
    string oa, ob;
    struct Node
    {
        int val;
        Node *lson, *rson;
        Node()
        {
            val = 0;
            lson = nullptr;
            rson = nullptr;
        }
        ~Node()
        {
            if (lson != nullptr)
                delete lson;
            if (rson != nullptr)
                delete rson;

                
        }
    };
    Node *root;
    inline void build(Node *now, vector<int> pa, vector<int> pb)
    {
        vector<int> left1, left2, right1, right2;
        now->val = pb[pb.size() - 1];
        int p;
        for (p = 0; p < pa.size(); p++)
        {
            if (pa[p] == pb[pb.size() - 1])
                break;
        }
        for (int i = 0; i < p; i++)
        {
            left1.push_back(pa[i]);
        }
        for (int i = p + 1; i < pa.size(); i++)
        {
            right1.push_back(pa[i]);
        }
        int q = 0;
        for (int i = 0; i < left1.size(); i++)
        {
            left2.push_back(pb[q++]);
        }
        for (int i = 0; i < right1.size(); i++)
        {
            right2.push_back(pb[q++]);
        }
        if (!left1.empty())
        {
            now->lson = new Node;
            build(now->lson, left1, left2);
        }
        if (!right1.empty())
        {
            now->rson = new Node;
            build(now->rson, right1, right2);
        }
    }
    inline void dfs2(Node *now, int nowv)
    {
        nowv += now->val;
        if (now->lson == nullptr && now->rson == nullptr)
        {
            if(nowv<anssum)
            {
                ans=now->val;
                anssum=nowv;
            }
            return;
        }
        if (now->lson != nullptr)
            dfs2(now->lson,nowv);
        if (now->rson != nullptr)
            dfs2(now->rson,nowv);
    }

  public:
    Tree(vector<int> pa, vector<int> pb)
    {
        root = new Node;
        build(root, pa, pb);
    }
    inline void find(void)
    {
        ans=0;anssum=INT_MAX;
        dfs2(root, 0);
    }
};
Tree *t;
inline void solve(string pa, string pb)
{
    vector<int> vec1, vec2;
    vec1.push_back(0);
    vec2.push_back(0);
    for (int i = 0; i < pa.length(); i++)
    {
        if (isdigit(pa[i]))
        {
            vec1[vec1.size() - 1] += pa[i] - '0';
            vec1[vec1.size() - 1] *= 10;
        }
        else
        {
            vec1[vec1.size() - 1] /= 10;
            vec1.push_back(0);
        }
    }
    vec1[vec1.size() - 1] /= 10;
    for (int i = 0; i < pb.length(); i++)
    {
        if (isdigit(pb[i]))
        {
            vec2[vec2.size() - 1] += pb[i] - '0';
            vec2[vec2.size() - 1] *= 10;
        }
        else
        {
            vec2[vec2.size() - 1] /= 10;
            vec2.push_back(0);
        }
    }
    vec2[vec2.size() - 1] /= 10;
    t = new Tree(vec1, vec2);
    t->find();
    cout << ans << endl;
}
int main()
{
    while (getline(cin, a))
    {
        getline(cin, b);
        solve(a, b);
    }
}