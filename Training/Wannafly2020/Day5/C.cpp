#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
const int N = 501;
const int M = 2e5 + 10;
int includ[N][N], jiao[N][N];
int n, m;
int f[N];
int w[N][N];
vector<int>g[N], gg[N];
void ins(int x, int v) {
    while (x <= n) {
        f[x] += v;
        x += x & -x;
    }
}
int get(int x) {
    int v = 0;
    while (x) {
        v += f[x];
        x -= x & -x;
    }
    return v;
}
int get(int l, int r) {
    return get(r) - get(l - 1);
}
int main() {
    scanf("%d %d", &n, &m);
    int sum = 0;
    for (int i = 1; i <= m; i ++) {
        int x, y;
        scanf("%d %d", &x, &y);
        sum += (y - x + 1) == n;
        g[y].push_back(x);
        gg[x].push_back(y);
    }
    for (int i = n; i >= 1; i --) {
        for (auto u:g[i])
            ins(u, 1);
        for (int j = i; j >= 1; j --) {
            includ[j][i] = get(1, j);
            jiao[j][i] += get(i + 1, n);
        }
    }
    memset(f, 0, sizeof(f));
    for (int i = 1; i <= n; i ++) {
        for (auto u:gg[i])
            ins(u, 1);
        for (int j = i ; j <= n; j ++) {
            jiao[i][j] += get(1, i - 1);
        }
    }
    for (int i = 1;i <= n; i++)
        for (int j = i; j <= n; j ++)
            jiao[i][j] = m - includ[i][j] - jiao[i][j];
    for (int i = 2; i <= n; i ++) {
        for (int j = 1; j + i - 1 <= n; j ++){
            int l = j, r =i + j - 1;
            w[l][r] = 1e9;
            for (int k = l; k < r; k ++)
                w[l][r] = min(w[l][r], w[l][k] + w[k + 1][r] + includ[l][k] + includ[k + 1][r] - 2 * includ[l][r] + jiao[l][r]);
        }
    }
    printf("%d\n", w[1][n] + sum);
    return 0;
}