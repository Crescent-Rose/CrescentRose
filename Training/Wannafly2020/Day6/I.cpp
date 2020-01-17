#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
const int N = 100;
int f[N][N];
int a[N];
int mx[N][N];
int ans[N];
int n, T;
int getsum(int x) {
    return x / 2;
}
int main() {
    scanf("%d", &T);
    while (T --) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i ++) {
            scanf("%d", &a[i]);
            mx[i][i] = a[i];
            for (int j = i - 1;j >= 1; j --)
                mx[j][i] = max(mx[j + 1][i], a[j]);
        }
        memset(f, 0, sizeof(f));
        for (int i = 0; i < n; i ++)
            for (int j = 0; j <= n; j ++) {
                f[i + 1][j] = max(f[i + 1][j], f[i][j] + a[i + 1]);
                for (int k = i + 3; k <= n; k ++)
                    if (j + getsum(k - i) <= n)
                        f[k][j + getsum(k - i)] = max(f[k][j + getsum(k - i)], f[i][j] + mx[i + 1][k] * (k - i));
            }
        for (int i = 1; i <= n; i ++) {
            ans[i] = max(ans[i - 1], f[n][i]);
            printf("%d%c", ans[i], " \n"[i ==n]);
        }
    }
    return 0;
}