#include <cstdio>
#include <cstring>
#include <cstdlib>
int total;
int n, m;
char Site[1010][10010];
struct KMP
{
    char *str;
    int *next;
    inline void init(char *str)
    {
        int strl = strlen(str);
        next = new int[strl];
        next[0] = -1;
        int j, k;
        j = 0, k = -1;
        while (j < strl - 1)
        {
            if (k == -1 || str[j] == str[k])
            {
                k++, j++;
                if (str[j] != str[k])
                    next[j] = k;
                else
                    next[j] = next[k];
            }
            else
            {
                k = next[k];
            }
        }
    }
} Virus[1001];
inline void KMP_Search(char *Site, KMP Virus)
{
    int i = 0, j = 0;
    int strl1 = strlen(Site);
    int strl2 = strlen(Virus.str);
    while (i < strl1 && j < strl2)
    {
    }
}
inline void KMP_Search(char *Site, KMP Virus, int pos)
{
    int i = 0, j = 0;
    int strl1 = strlen(Site);
    int strl2 = strlen(Virus.str);
    while (i < strl1 && j < strl2)
    {
    }
}
int main()
{
    
}
