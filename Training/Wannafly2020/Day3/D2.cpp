#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 1000100;

int P;

int add(int a, int b) { int r = a + b; return r < P ? r : r - P; }
int sub(int a, int b) { int r = a - b; return r < 0 ? r + P : r; }
int mul(ll a, ll b) { return a * b % P; }

bool ip[N]; int ps[N], ph[N], sph[N], pc;
void sieve() {
    fill_n(ip, N, true);
    ip[1] = 0; ph[1] = 1;
    for (int i = 2; i != N; ++i) {
        if (ip[i]) {
            ps[++pc] = i;
            ph[i] = i - 1;
        }
        for (int j = 1; j <= pc; ++j) {
            if (i * ps[j] >= N) break;
            ip[i * ps[j]] = false;
            if (i % ps[j])
                ph[i * ps[j]] = ph[i] * (ps[j] - 1);
            else {
                ph[i * ps[j]] = ph[i] * ps[j];
                break;
            }
        }
    }
    for (int i = 1; i != N; ++i)
        sph[i] = (sph[i - 1] + ph[i]) % P;
}

int i2, i6;
int inv(int x) { return x == 1 ? 1 : mul(inv(P % x), P - P / x); }

int s1(int x) { return mul(mul(x, x + 1), i2); }
int s2(int x) { return mul(mul(x, x + 1), mul(2 * x + 1, i6)); }

namespace mfps {

    int m[N], n, s;

    int sh(int x) {
        return s1(x);
    }

    int sg(int x) {
        return x % P;
    }

    int sf(int x) {
        if (x < N) return sph[x];
        int& res = m[n / x];
        if (res != -1) return res;
        res = sh(x);
        for (int l = 2, r; l <= x; l = r + 1) {
            r = x / (x / l);
            res = sub(res, mul(sub(sg(r), sg(l - 1)), sf(x / l)));
        }
        return res;
    }

    void init(int n_) {
        n = n_; s = ceil(sqrt(n));
        fill_n(m + 1, s, -1);
        sf(n_);
    }

}


int main() {
    int n; scanf("%d%d", &n, &P);

    sieve();

    i2 = inv(2);
    i6 = inv(6);

    mfps::init(n);

    int ans = 0;
    for (int l = 1, r; l <= n; l = r + 1) {
        r = n / (n / l);
        ans = add(ans, mul(sub(s2(r), s2(l - 1)), mfps::sf(n / l)));
    }

    printf("%d\n", ans);

    return 0;
}
