#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 21;
int to[1<<N];
int n, m, q;
int edge[N];
int sum[1<<N][N], sum1[1<<N][N];
int bz[1<<N];
int st;
int d[1<<N], d1[1<<N];
int did(int sum[][N], int x, long long k, int r) {
    int l = 1, mid, s = r;
    while (l <= r) {
        if (sum[mid = (l + r) / 2][x] >= k) r = mid - 1, s = min(s, mid);
        else
            l = mid + 1;
    }
    return s;
}
int main() {
    scanf("%d %d %d", &n, &m, &q);
    for (int i = 0; i < n; i ++){
        int x;
        scanf("%d", &x);
        st ^= (x<<i);
    }
    for (int i = 1; i <= m; i ++) {
        int x, y;
        scanf("%d %d", &x, &y);
        x --;
        y --;
        edge[x] ^= (1 << y);
    }
    for (int i = 0; i < (1 << n); i ++){
        int v = 0;
        for (int j = 0; j < n; j ++)
            if ((i >> j) & 1)
                v ^= edge[j];
        to[i] = v;
    }
    d[1] = st;
    d[0] = 1;
    bz[st] = 1;
    while (!bz[st = to[st]]) {
        d[++d[0]] = st;
        bz[st] = d[0];
    }
    d1[0] = d[0] - bz[st] + 1;
    for (int i = 1; i <= d1[0]; i ++) {
        d1[i] = d[bz[st] + i - 1];
        for (int j = 0; j < n; j ++)
            sum1[i][j] = sum1[i - 1][j] + ((d1[i]>>j) & 1);
    }
    for (int i = 1; i <= d[0]; i ++) {
        for (int j = 0; j < n; j ++)
            sum[i][j] = sum[i-1][j] + ((d[i] >> j) & 1);
    }
    while (q --) {
        int x;
        long long k;
        scanf("%d %lld", &x, &k);
        if (!k) {
            printf("0\n");
            continue;
        }
        x --;
        if (!sum[d[0]][x]) {
            puts("-1");
            continue;
        }
        if (sum[d[0]][x] >= k) {
            printf("%d\n", did(sum, x, k, d[0]) - 1);
            continue;
        }
        long long ans = d[0];
        k -= sum[d[0]][x];
        if (!sum1[d1[0]][x]) {
            puts("-1");
            continue;
        }
        ans += ((k - 1) / sum1[d1[0]][x]) * d1[0];
        k %= sum1[d1[0]][x];
        if (!k) k = sum1[d1[0]][x];
        ans += did(sum1, x, k, d1[0]);
        printf("%lld\n" , ans - 1);
    }
    return 0;
}