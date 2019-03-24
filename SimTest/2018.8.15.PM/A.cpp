#ifndef _GLIBCXX_NO_ASSERT
#include <cassert>
#endif
#include <cctype>
#include <cerrno>
#include <cfloat>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#if __cplusplus >= 201103L
#include <ccomplex>
#include <cfenv>
#include <cinttypes>
#include <cstdalign>
#include <cstdbool>
#include <cstdint>
#include <ctgmath>
#include <cuchar>
#include <cwchar>
#include <cwctype>
#endif

// C++
#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>

#if __cplusplus >= 201103L
#include <array>
#include <atomic>
#include <chrono>
#include <codecvt>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#endif

#if __cplusplus >= 201402L
#include <shared_mutex>
#endif

#if __cplusplus >= 201703L
#include <charconv>
#include <filesystem>
#endif

using namespace std;
const int MaxN = 100001;
class DP
{
  private:
    int n;
    int Origin[MaxN];
    int dp[MaxN];
    int MaxSum,StartPos,EndPos;
    inline void Solve(void)
    {
        /*
        只求子段和
        dp[1]=Origin[1];
        for(int i=2;i<n;i++)
        {
            dp[i]=max(dp[i-1]+Origin[i],Origin[i]);
        }
        */
        MaxSum=0xcfcfcfcf;
        int PosS;
        StartPos=EndPos=PosS=1;
        dp[1]=Origin[1];
        for(int i=1;i<=n;i++)
        {
            //思路：每次更新时，如果加上新的更优，那就更新结尾区间，否则将起点拉过来抛弃以前的区间
            //Powered By Quank123Wip 2018
            if(dp[i-1]+Origin[i]<Origin[i])
            {
                dp[i]=Origin[i];
                PosS=i;
            }
            else
            {
                dp[i]=dp[i-1]+Origin[i];
            }
            if(dp[i]>MaxSum)
            {
                MaxSum=dp[i];
                StartPos=PosS;
                EndPos=i;
            }
        }
    }
  public:
    DP();
    //~DP();
    friend istream& operator >> (istream &Input,DP &Object);
    friend ostream& operator << (ostream &Output,DP &Object);
};
DP::DP()
{
    n=0;
}
/*
DP::~DP()
{
    //Default
}
*/
istream& operator >> (istream &Input,DP &Object)
{
    //Initialize The Object When Reading
    Input>>Object.n;
    for(int i=1;i<=Object.n;i++)
        Input>>Object.Origin[i];
    Object.Solve();
    return Input;
}
ostream& operator << (ostream &Output,DP &Object)
{
    Output<<Object.MaxSum<<" "<<Object.StartPos<<" "<<Object.EndPos;
    return Output;
}
int main()
{
    int t,memt;
    cin>>t;
    memt=t;
    DP *Solution;
    while(t--)
    {
        if(memt!=t+1)cout<<endl<<endl;
        Solution=new DP;
        cin>>*Solution;
        cout<<"Case "<<memt-t<<":"<<endl
            <<*Solution;
        delete Solution;
    }
    cout<<endl;
}