#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
typedef long long ll;
const int mod = 998244353;
ll calc(ll x, ll y) {
    ll z = 1;
    x %= mod;
    while (y) {
        if (y &1) z = z * x % mod;
        x = x * x % mod, y >>= 1;
    }
    return z;
}
int T;
int n;
ll k;
const int N = 100;
ll a[N], b[N][N];
ll ni(ll x) {
    return calc(x, mod - 2);
}
ll C(ll x, ll y) {
    return a[x] * ni(a[y]) % mod * ni(a[x - y]) % mod;
}
ll f[N];
int main() {
    scanf("%d", &T);
    a[0] = 1;
    for (int i = 1; i < N; i ++)
        a[i] = a[i - 1] * i % mod;
    for (int i = 1; i < N; i ++) {
        b[i][0] = 1;
        for (int j = 1; j < N ; j++)
            b[i][j] = b[i][j - 1] * i % mod;
    }
    while (T --) {
        scanf("%d %lld", &n, &k);
        memset(f, 0, sizeof(f));
        f[0] = 1;
        for (int i = 1; i <= n; i ++)
            if (k % i == 0) {
                for (int j = n; j >= 1; j --)
                    for (int l = 1; i * l <= j ; l ++)
                        f[j] = (f[j] + f[j - l * i] * C(n - (j - l * i), l * i) % mod * a[l * i] % mod * ni(a[l] * b[i][l]%mod) % mod ) % mod;
            }
        printf("%lld\n" ,f[n]);
    }
    return 0;
}