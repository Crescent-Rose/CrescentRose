#include <bits/stdc++.h>

using namespace std;
const int N = 101;
typedef long long ll;
const int P = 998244353, i2 = (P + 1) / 2;

int add(int a, int b) { int r = a + b; return r < P ? r : r - P; }
int sub(int a, int b) { int r = a - b; return r < 0 ? r + P : r; }
int mul(ll a, ll b) { return a * b % P; }
int inv(int x) { return x == 1 ? 1 : mul(inv(P % x), P - P / x); }

ll x[N], l[N], r[N];
int li[N], ri[N], w[N], b11[N][N], b12[N][N], b1[N][N], b2[N][N], dp1[N][N], dp2[N][N], c;
int bi[N][N];


int main() {
    int n; scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%lld", &l[i]);
    for (int i = 1; i <= n; ++i)
        scanf("%lld", &r[i]), r[i]++;
    for (int i = 2; i <= n; ++i)
        l[i] = max(l[i], l[i - 1]);
    for (int i = n - 1; i >= 1; --i)
        r[i] = min(r[i], r[i + 1]);
    for (int i = 1; i <= n; ++i)
        x[++c] = l[i], x[++c] = r[i];
    for (int i = 0; i <= n; ++i) {
        bi[i][0] = bi[i][i] = 1;
        for (int j = 1; j < i; ++j)
            bi[i][j] = add(bi[i - 1][j - 1], bi[i - 1][j]);
    }
    sort(x + 1, x + c + 1); c = unique(x + 1, x + c + 1) - x - 1;
    for (int i = 1; i <= n; ++i)
        li[i] = lower_bound(x + 1, x + c + 1, l[i]) - x;
    for (int i = 1; i <= n; ++i)
        ri[i] = lower_bound(x + 1, x + c + 1, r[i]) - x;
    for (int i = 1; i <= c; ++i) {
        w[i] = (x[i + 1] - x[i]) % P;
        b11[i][0] = 1;
        for (int j = 1; j <= min(w[i] + 1, n); ++j)
            b11[i][j] = mul(b11[i][j - 1], mul(w[i] - j + 1, inv(j)));
        for (int j = 1; j <= n; ++j)
            for (int k = 1; k <= min(w[i] + 1, j); ++k)
                b1[i][j] = add(b1[i][j], mul(b11[i][k], bi[j - 1][k - 1]));
        for (int j = 1; j <= n; ++j)
            b2[i][j] = mul(b1[i][j], mul(add((x[i + 1] - 1) % P, x[i] % P), mul(j, i2)));
    }

    dp1[0][0] = 1;
    for (int i = 1; i <= n; ++i)
        for (int j = li[i]; j < ri[i]; ++j)
            for (int x = 0; x < i; ++x)
                if (ri[x + 1] > j)
                for (int y = 0; y < j; ++y)
                    dp1[i][j] = add(dp1[i][j], mul(dp1[x][y], b1[j][i - x]));

    dp2[0][0] = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = li[i]; j < ri[i]; ++j)
            for (int x = 0; x < i; ++x)
                if (ri[x + 1] > j)
                for (int y = 0; y < j; ++y)
                    dp2[i][j] = add(dp2[i][j], add(mul(dp1[x][y], b2[j][i - x]), mul(dp2[x][y], b1[j][i - x])));

    int sum = 0;
    for (int j = li[n]; j < ri[n]; ++j)
        sum = add(sum, dp2[n][j]);

    printf("%d\n", sum);

    return 0;
}
