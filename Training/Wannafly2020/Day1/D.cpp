#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int mod = 998244353;
const int MAXN = 407;
int add(int x, int y) {int res = x + y; if (res >= mod) res -= mod; return res;}
int sub(int x, int y) {int res = x - y; if (res < 0) res += mod; return res;}
int mul(int x, int y) {ll res = (ll)x * y; res -= res / mod * mod; return res;}
int ksm(int a, int b)
{
    int res = 1;
    while (b)
    {
        if (b & 1) res = mul(res, a);
        a = mul(a, a); b >>= 1;
    }
    return res;
}

char G1[MAXN][MAXN], G2[MAXN][MAXN];
int A[MAXN][MAXN << 1], B[MAXN][MAXN];

int deal(int n, int m)
{
    int res = 1;
    for (int i = 1; i <= n; i++)
    {
        int p = i;
        for (int j = i; j <= n; j++) if (A[j][i])
        {
            p = j;
            break;
        }
        if (p != i)
        {
            for (int j = 1; j <= m; j++) swap(A[i][j], A[p][j]);
            res = sub(0, res);
        }
        res = mul(res, A[i][i]);
        int inv = ksm(A[i][i], mod - 2);
        for (int j = 1; j <= m; j++) A[i][j] = mul(A[i][j], inv);
        for (int j = 1; j <= n; j++) if (j != i)
        {
            int temp = A[j][i];
            for (int k = 1; k <= m; k++)
                A[j][k] = sub(A[j][k], mul(A[i][k], temp));
        }
    }
    return res;
}
int main()
{
    int n; scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%s", G1[i] + 1);
    for (int i = 1; i <= n; i++) scanf("%s", G2[i] + 1);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            if (G1[i][j] == '1') 
            {
                A[i][j] = sub(A[i][j], 1), A[i][i] = add(A[i][i], 1);
                if (G2[i][j] == '1') B[i][j] = sub(B[i][j], 1), B[i][i] = add(B[i][i], 1);
            }
        }
    // for (int i = 1; i <= n; i++)
    //     for (int j = 1; j <= n; j++)
    //         printf("%d%c\n", A[i][j], " \n"[j == n]);
    n--;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            A[i][j + n] = (i == j);
    int detA = deal(n, n << 1);
    int tr = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            tr = add(tr, mul(A[i][j + n], B[i][j]));
    printf("%d\n", mul(detA, tr));
    return 0;
}