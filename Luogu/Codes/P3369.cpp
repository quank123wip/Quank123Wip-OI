#include <bits/stdc++.h>
template <typename T>
class Treap
{
  public:
    Treap(void) : root(nullptr) {}
    inline void insert(T __key)
    {
        __insert(root,__key);
    }
    inline void erase(T __key)
    {
        __erase(root,__key);
    }
    inline int kth(T __key)
    {
        return __kth(root,__key);
    }
    inline T query(int __rank)
    {
        return __query(root,__rank);
    }
    inline T prev(T __key)
    {
        return __prev(root,__key,__key);
    }
    inline T next(T __key)
    {
        return __next(root,__key,__key);
    }

  private:
    struct Node
    {
        Node *lson, *rson;
        T key;
        int cnt, rand, size;
        Node(T __key = T(), Node *l = nullptr, Node *r = nullptr) : lson(l), rson(r), key(__key), cnt(1), rand(std::rand()), size(1){}
        inline void pushup(void) 
        {
            size=cnt;
            if(lson)size+=lson->size;
            if(rson)size+=rson->size;
        }
    };
    Node *root;
    inline T key(Node *p){return p!=nullptr?p->key:T();}
    inline int cnt(Node *p){return p!=nullptr?p->cnt:0;}
    inline int rand(Node *p){return p!=nullptr?p->rand:0;}
    inline int size(Node *p){return p!=nullptr?p->size:0;}
    inline void zig(Node *&x)
    {
        Node *y = x->lson;
        x->lson = y->rson;
        y->rson = x;
        x = y;
        x->rson->pushup();
        x->pushup();
    }
    inline void zag(Node *&x)
    {
        Node *y = x->rson;
        x->rson = y->lson;
        y->lson = x;
        x = y;
        x->lson->pushup();
        x->pushup();
    }
    inline void __insert(Node *&now, T __key)
    {
        if(now==nullptr)
        {
            now=new Node(__key);
            return;
        }
        if(now->key==__key)now->cnt++;
        else if(__key>now->key)
        {
            __insert(now->rson,__key);
            if(now->rson->rand>now->rand)zag(now);
        }
        else
        {
            __insert(now->lson,__key);
            if(now->lson->rand>now->rand)zig(now);
        }
        now->pushup();
    }
    inline void __erase(Node *&now, T __key)
    {
        if(now==nullptr)return;
        if(__key==now->key)
        {
            if(now->cnt>1)now->cnt--;
            else if(now->lson==nullptr&&now->rson==nullptr)
                delete now,now=nullptr;
            else if(now->lson==nullptr)
                now=now->rson;
            else if(now->rson==nullptr)
                now=now->lson;
            else
            {
                if(now->lson->key>now->rson->key)
                    zag(now),__erase(now->lson,__key);
                else
                    zig(now),__erase(now->rson,__key);
            }
        }
        else if(__key<now->key)__erase(now->lson,__key);
        else __erase(now->rson,__key);
        if(now)now->pushup();
    }
    inline int __kth(Node *&now, T __key)
    {
        if(now==nullptr)return 0;
        if(now->key==__key)
            return size(now->lson)+1;
        else if(now->key<__key)
            return size(now->lson)+now->cnt+__kth(now->rson,__key);
        else
            return __kth(now->lson,__key);
    }
    inline T __query(Node *&now, int __rank)
    {
        if(now==nullptr)
            return T();
        if(size(now->lson)>=__rank)
            return __query(now->lson,__rank);
        else if(size(now->lson)+now->cnt<__rank)
            return __query(now->rson,__rank-size(now->lson)-now->cnt);
        else 
            return now->key;
    }
    inline T __prev(Node *&now, T __key, T data)
    {
        if(now==nullptr)
            return -2147483647;
        else if(now->key<__key)
        {
            data=now->key;
            data=__prev(now->rson,__key,data);
        }
        else data=__prev(now->lson,__key,data);
        return data;
    }
    inline T __next(Node *&now, T __key,T data)
    {
        if(now==nullptr)
            return 2147483647;
        else if(now->key>__key)
        {
            data=now->key;
            data=__next(now->lson,__key,data);
        }
        else data=__next(now->rson,__key,data);
        return data;
    }
};
Treap<int>orz;
int main()
{
    srand(time(0));
    //freopen("testdata.in", "r", stdin);
    //freopen("testdata.out", "w", stdout);
    int n, opt, x;
    scanf("%d", &n);
    while (n--)
    {
        scanf("%d%d", &opt, &x);
        if (opt == 1)
            orz.insert(x);
        else if (opt == 2)
            orz.erase(x);
        else if (opt == 3)
            printf("%d", orz.kth(x)),
                puts("");
        else if (opt == 4)
            printf("%d", orz.query(x)),
                puts("");
        else if (opt == 5)
            printf("%d", orz.prev(x)),
                puts("");
        else if (opt == 6)
            printf("%d", orz.next(x)),
                puts("");
    }
}