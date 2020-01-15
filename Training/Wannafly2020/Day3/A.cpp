#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN = 1007;
ll a[MAXN][MAXN], ans[MAXN], sum = 0;
int main()
{
    int n; scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            scanf("%lld", &a[i][j]), sum += a[i][j];
    if (n == 2)
    {
        printf("%lld %lld", a[1][2] / 2, a[1][2] / 2);
        return 0;
    }
    sum /= (2 * n - 2);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++) ans[i] += a[i][j];
        ans[i] = (ans[i] - sum) / (n - 2);
    }
    for (int i = 1; i <= n; i++) printf("%lld%c", ans[i], " \n"[i == n]);
    return 0;
}