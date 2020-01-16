#include <algorithm>
#include <cstdio>
#include <bitset>
using namespace std;
int sum[100];
bitset<100000> f[3], tmp;
int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    for (int i = 0; i < k; i ++) {
        f[i] ^= f[i];
        int w;
        scanf("%d", &w);
        while (w --) {
            int x;
            scanf("%d", &x);
            f[i][x - 1] = 1;
        }
    }
    for (int i = 1; i < (1<< k); i ++) {
        tmp.set();
        for (int j = 0; j < k; j ++)
            if ((i >> j) & 1)
                tmp &= f[j];
            else
                tmp ^= (tmp & f[j]);
        sum[i] = tmp.count();
    }
    int ans = 0;
    for (int i = (1 << k) - 1; i >= 1; i --) {
        for (int j = (1  << k) - 1; j >= 1; j--)
            if (!(i & j)) {
                if (__builtin_popcount(i) == 1 && __builtin_popcount(j) == 1) continue;
                int v = min(sum[i], sum[j]);
                ans += v;
                sum[i] -= v;
                sum[j] -= v;
            }
        if (__builtin_popcount(i) == 1) continue;
        ans += sum[i];
        sum[i] = 0;
    }
    int v = min(sum[1], min(sum[2], sum[4]));
    ans += v;
    sum[1] -=v;
    sum[2] -=v;
    sum[4] -= v;
    for (int i = (1 << k) - 1; i >= 1; i --) {
        for (int j = (1  << k) - 1; j >= 1; j--)
            if (!(i & j)) {
                int v = min(sum[i], sum[j]);
                ans += v;
                sum[i] -= v;
                sum[j] -= v;
            }
        ans += sum[i];
        sum[i] = 0;
    }
    printf("%d\n", ans);
    return 0;
}