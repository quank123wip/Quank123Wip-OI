#include<bits/stdc++.h>
using namespace std;
const int maxn=1000000+10;
char s1[maxn],s2[maxn];
int nexts[maxn];
int s1l,s2l;
int i,j;
int main()
{
    scanf("%s%s",s1,s2);
    s1l=strlen(s1);
    s2l=strlen(s2);
    for(i=1,j=0;i<s2l;i++)
    {
        while(j&&s2[i]!=s2[j])j=nexts[j];
        if(s2[i]==s2[j])j++;
        nexts[i]=j;
    }
    for(i=0,j=0;i<s1l;i++)
    {
        while(j&&s1[i]!=s2[j])j=nexts[j];
        if(s1[i]==s2[j])j++;
        if(j==s2l)
        {
            printf("%d\n",i-s2l+2);
            j=nexts[j];
        }
    }
    for(int i=0;i<s2l;i++)
    {
        printf("%d ",nexts[i]);
    }
}