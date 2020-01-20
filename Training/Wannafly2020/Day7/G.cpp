#include <algorithm>
#include <cstdio>
using namespace std;
int n, m, xx, yy;
long long k;
long long ans;
int a[100][100];
int lasttime[100][100];
int b[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
long long did(long long x) {
    return x * (x + 1) / 2;
}
void dfs(int x, int y, int t, long long v) {
    int tmp = lasttime[x][y];
    v += t - tmp;
    if (x == xx && y == yy) {
        if (!t)
            v += a[x][y];
    } else {
        if (!lasttime[x][y])
            v += a[x][y];
    }
    if (t == k - 1) {
        ans = max(ans, v);
        return;
    }
    lasttime[x][y] = t;
    for (int i = 0; i < 4; i ++) {
        int xx = x + b[i][0], yy = y + b[i][1];
        if (1 <= xx && xx <= n && 1 <= yy && yy <= m) {
            dfs(xx, yy, t + 1, v);
        }
    }
    lasttime[x][y] = tmp;
}
int main() {
    scanf("%d %d %d %d %lld", &n, &m, &xx, &yy, &k);
    long long all = 0;
    for (int i = 1; i <=n ; i ++)
        for (int j = 1; j <= m; j ++)
            scanf("%d", &a[i][j]), all += a[i][j];
    if (k < n * m){
        dfs(xx, yy, 0, 0);
        printf("%lld\n", ans);
    } else {
        ans += did(n * m - 1);
        k -= n * m;
        ans += k * (n * m);
        printf("%lld\n", ans + all);
    }
    return 0;
}