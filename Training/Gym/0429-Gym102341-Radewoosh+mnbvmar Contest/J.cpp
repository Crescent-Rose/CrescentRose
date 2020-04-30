#include <bits/stdc++.h>
using namespace std;

const int N = 3005;

char g[N][N];
bool f[N][N];
int a[N];

int main(void) {
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        scanf("%s", g[i] + 1);

    bool ans = false;
    for (int i = 1; i <= n - 1; ++i)
        for (int j = m - 1; j >= 1; --j)
            if (g[i + 1][j] == g[i][j + 1]) {
                f[i][j] = 1;
                int res = 0;
                for (int w = j - 1; w >= 1; w -= w & -w)
                    res += a[w];
                if (res) {
                    ans = true;
                    break;
                }
                for (int w = j; w <= m; w += w & -w)
                    a[w]++;
            }


    for (int i = 1; i <= n - 1; ++i)
        for (int j = m - 1; j >= 1; --j)
            if (f[i][j] && (f[i + 1][j] || f[i][j + 1]))
                ans = true;

    printf(ans ? "YES\n" : "NO\n");
    return 0;
}