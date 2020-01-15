#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 52;
const int mod = 1e9 + 7;
const int allmask = (1ll << 31) - 1;
int n, k;
int a[N];
int f[N][2][2];
int mul(int x, int y) {return 1ll * x * y % mod;}
int add(int x, int y) {x += y;return x >= mod ? x - mod : x; }
int main() {
    while (scanf("%d %d", &n, &k)!=EOF) {
        int x = 0;
        for (int i = 1; i <= n ; i++) {
            scanf("%d", &a[i]);
            x ^= a[i];
        }
        int ans = (x == k);
        for (int i = 30; i >= 0; i --) {
            int mask = 0;
            for (int j = 30; j > i; j --)
                mask += (1 << j);
            int v = (k & mask);
            for (int j = 1; j <= n ; j ++)
                v ^= (a[j] & mask);
            if (v) continue;
            for (int j = 0; j <= n; j ++)
                for (int k = 0; k <2 ; k ++)
                    f[j][k][0] = f[j][k][1] = 0;
            f[0][0][0] = 1;
            int remask = (allmask ^ mask ^ (1 << i));
            for (int j = 0; j < n ; j ++)
                for (int k = 0; k < 2; k ++)
                    for (int l = 0; l < 2; l ++)
                        if (f[j][k][l]) {
                            if ((a[j + 1] >> i) & 1) {
                                if (!l)
                                    f[j + 1][k][1] = add(f[j + 1][k][1], f[j][k][l]);
                                else
                                    f[j + 1][k][1] = add(f[j +1][k][1], mul(f[j][k][l], (remask + 1) % mod));
                                f[j +1][k ^ 1][l] = add(f[j +1][k ^ 1][l], mul(f[j][k][l], ((a[j + 1] & remask) + 1)% mod));
                            } else {
                                f[j + 1][k][l] = add(f[j + 1][k][l], mul(f[j][k][l], ((a[j + 1] & remask) + 1) % mod));
                            }
                        }
            ans = add(ans, f[n][(k >> i) & 1][1]);
        }
        printf("%d\n",ans);
    }
    return 0;
}