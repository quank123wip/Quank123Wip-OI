#include <bits/stdc++.h>
using namespace std;
const int moder = 1000000;
int n;
set<int> pets, people;
long long ans;
int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int a, b;
        cin >> a >> b;
        if (i == 0)
        {
            if (a == 0)
            {
                pets.insert(b);
            }
            else
            {
                people.insert(b);
            }
            continue;
        }
        if (pets.empty())
        {
            if (a == 0)
            {
                pets.insert(b);
                if (b < *(people.begin()))
                {
                    ans += abs(*people.begin() - b);
                    people.erase(*people.begin());
                    pets.erase(b);
                }
                else if (b > *(--people.end()))
                {
                    ans += abs(*(--people.end()) - b);
                    people.erase(*(--people.end()));
                    pets.erase(b);
                }
                else
                {
                    int l = *(--people.lower_bound(b));
                    int r = *(people.lower_bound(b));
                    if (abs(b - l) >= abs(b - r))
                    {
                        ans = (ans + (abs(b - r)));
                        people.erase(r);
                        pets.erase(b);
                    }
                    else
                    {
                        ans = (ans + (abs(b - l)));
                        people.erase(l);
                        pets.erase(b);
                    }
                }
            }
            else
            {
                people.insert(b);
            }
        }
        if (people.empty())
        {
            if (a == 0)
            {
                pets.insert(b);
            }
            else
            {
                people.erase(b);
                if (b < *pets.begin())
                {
                    ans += abs(*pets.begin() - b);
                    pets.erase(pets.begin());
                    people.erase(b);
                }
                else if (b > *(--pets.end()))
                {
                    ans += abs(*(--pets.end()) - b);
                    pets.erase(--pets.end());
                    people.erase(b);
                }
                else
                {
                    int l = *(--pets.lower_bound(b));
                    int r = *(pets.lower_bound(b));
                    if (abs(b - l) >= abs(b - r))
                    {
                        ans += abs(b - r);
                        pets.erase(r);
                        people.erase(b);
                    }
                    else
                    {
                        ans += abs(b - l);
                        pets.erase(l);
                        people.erase(b);
                    }
                }
            }
        }
    }
    cout << ans % moder;
}
//not yet
