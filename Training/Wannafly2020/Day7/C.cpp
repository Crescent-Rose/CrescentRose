#include<bits/stdc++.h>
using namespace std;

int main()
{
    int T; scanf("%d", &T);
    while (T--)
    {
        int n, L; scanf("%d%d", &n, &L);
        if (L == 1)
        {
            printf("1\n1 1 1 1 \n");
            continue;
        }
        if (L == 2)
        {
            printf("1\n1 1 2 2 \n");
            continue;
        }
        if (L == 3)
        {
            if (n == 3) printf("2\n1 1 1 2 2 2 3 \n");
            else 
            {
                printf("1\n2 2 2 3 \n");
            }
            continue;
        }
        L--;
        if (L % 3 == 0)
        {
            printf("%d\n", (4 + L - 1) / 3);
            printf("%d %d ", 1, 1);
            for (int i = 1; i <= L; i++) printf("%d ", i);
            printf("%d %d ", L, L);
            puts("");
        }
        else if (L % 3 == 1)
        {
            printf("%d\n", (4 * L - 1) / 3);
            for (int i = 1; i <= L; i++) printf("%d %d %d %d ", i, i, i, i);
            puts("");
        }
        else if (L % 3 == 2)
        {
            printf("%d\n", (4 * L - 4 - 1) / 3);
            printf("1 1 1 2 2 2 ");
            for (int i = 3; i <= L - 2; i++) printf("%d %d %d %d ", i, i, i, i);
            printf("%d %d %d %d %d %d ", L - 1, L - 1, L - 1, L, L, L);
            puts("");
        }
    }
}