#include<bits/stdc++.h>
#include<ext/pb_ds/priority_queue.hpp>
using namespace std;
__gnu_pbds::priority_queue<int,greater<int>,__gnu_pbds::thin_heap_tag>Heap;
int main()
{
    int n;
    cin>>n;
    while(n--)
    {
        int id;
        scanf("%d",&id);
        
        switch (id)
        {
            
            case 1:
            {
                int p;
                scanf("%d",&p);
                Heap.push(p);
                break;
            };
            
            case 2:
            {
                printf("%d\n",Heap.top());
                break;
            };
            
            case 3:
            {
                Heap.pop();
                break;
            };
            
        }
        
    }
}