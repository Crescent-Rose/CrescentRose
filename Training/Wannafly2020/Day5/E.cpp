#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 302;
int f[N][N][N], g[N][N], w[N][N];
int n;
int a[N], b[4];
bool bz[4][4];
long long ans;
int d[10];
#include <ctime>
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n ; i ++) {
        scanf("%d", &a[i]);
        for (int j = 1; j<= 300; j++) {
            w[i][j] = w[i - 1][j];
            for (int k = 1; k <= 300; k ++)
                f[i][j][k] = f[i - 1][j][k];
            f[i][j][a[i]] += w[i - 1][j];
        }
        w[i][a[i]] ++;
    }
    for (int i = 0; i < 4; i ++) {
        scanf("%d", &b[i]);
        for (int j = 0; j < i ; j ++)
            bz[i][j] = bz[j][i] = (b[i] == b[j]);
    }
    for (int i = n; i >= 1; i --) {
        for (int j = 1; j <= 300 ; j ++)
            g[i][j] = g[i + 1][j];
        g[i][a[i]] ++;
    }
    for (int i = 1; i <= n ; i++)
        for (int j = 1; j <= 300; j ++)
            g[i][j] += g[i][j - 1];
    for (int i = 3; i < n;i ++)
        for (int j = 1; j <= 300; j ++) {
            if (bz[0][2] != (a[i] == j)) continue;
            int L = 1, R = 300;
            if (bz[0][1]) L = j, R= j;
            for (int k = L; k <= R; k ++) {
                if (bz[0][1] != (k == j) || bz[1][2] != (a[i] == k)||!f[i-1][j][k]) continue;
                if (bz[0][3]) {
                    ans += f[i - 1][j][k] * (g[i + 1][j] - g[i + 1][j - 1]);
                    continue;
                }
                if (bz[1][3]) {
                    ans +=  f[i - 1][j][k] * (g[i + 1][k] - g[i + 1][k - 1]);
                    continue;
                }

                if (bz[2][3]) {
                    ans +=  f[i - 1][j][k] * (g[i + 1][a[i]] - g[i + 1][a[i] - 1]);
                    continue;
                }
                d[0] = 0;
                d[1] = a[i];
                d[2] = j;
                d[3] = k;
                d[4] = 300 + 1;
                if (d[2] < d[1]) {
                    swap(d[2], d[1]);
                }
                if (d[3] < d[1]) {
                    swap(d[3], d[1]);
                }
                if (d[3] < d[2]) {
                    swap(d[3], d[2]);
                }
                //sort(d + 1, d + 4);
                int sum = 0;
                sum += (g[i + 1][d[1] - 1] - g[i + 1][d[0]]);
                if (d[1] != d[2])
                    sum += (g[i + 1][d[2] - 1] - g[i + 1][d[1]]);
                if (d[2] != d[3])
                    sum += (g[i + 1][d[3] - 1] - g[i + 1][d[2]]);
                sum += (g[i + 1][d[4] - 1] - g[i + 1][d[3]]);
                ans += sum * f[i - 1][j][k];
            }
        }
    printf("%lld\n", ans);
    return 0;
}