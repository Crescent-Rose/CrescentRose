#include <bits/stdc++.h>
using namespace std;
int P;
const int N = 1000005;

int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }

typedef long long ll;
int add(int a, int b) { a %= P; b %= P; int r = a + b; return r < P ? r : r - P; }
int sub(int a, int b) { a %= P; b %= P; int r = a - b; return r < 0 ? r + P : r; }
int mul(ll a, ll b) { return a * b % P; }
int inv(int x) { x %= P; if (!x) return 0; return x == 1 ? 1 : mul(inv(P % x), P - P / x); }
int qpm(int a, int b) {
    a %= P;
    int r = 1;
    do if (b & 1) r = mul(r, a);
    while (a = mul(a, a), b >>= 1);
    return r;
}

int i2, i6;

bool ip[N]; int ps[N], pc;
void sieve() {
    fill(ip + 2, ip + N, 1);
    for (int i = 2; i != N; ++i) {
        if (ip[i]) ps[++pc] = i;
        for (int j = 1; j <= pc; ++j) {
            if (i * ps[j] >= N) break;
            ip[i * ps[j]] = 0;
            if (i % ps[j] == 0) break;
        }
    }
}

int s1(int x) {
    if (x % 2 == 0) return mul(x / 2, x + 1);
    else return mul((x + 1) / 2, x);
}
int s2(int x) {
    int a[3] = { x, x + 1, 2 * x + 1 };
    for (int i = 0; i != 3; ++i) {
        if (a[i] % 2 == 0) {
            a[i] /= 2; break;
        }
    }
    for (int i = 0; i != 3; ++i) {
        if (a[i] % 3 == 0) {
            a[i] /= 3; break;
        }
    }
    return mul(a[0], mul(a[1], a[2]));
}

int n, sq, r, w[N], c, id1[N], id2[N];
int sp[3][N], g[3][N];

inline int id(int x) { return x <= sq ? id1[x] : id2[n / x]; }

void init(int n_) {
    if (!pc) sieve();
    n = n_; sq = sqrt(n); c = 0;
    for (r = 1; ps[r] <= sq; ++r);
    for (int i = 1; i <= r; ++i) {
        sp[0][i] = sp[0][i - 1] + 1;
        sp[1][i] = add(sp[1][i - 1], ps[i]);
        sp[2][i] = add(sp[2][i - 1], mul(ps[i], ps[i]));
    }
    for (int x = 1, y; x <= n; x = y + 1) {
        int v = w[++c] = n / x; y = n / v;
        (v <= sq ? id1[v] : id2[n / v]) = c;
        g[0][c] = v - 1;
        g[1][c] = sub(s1(v), 1);
        g[2][c] = sub(s2(v), 1);
    }
    for (int i = 1; i <= r; ++i) {
        int p = ps[i];
        for (int j = 1; j <= c && p * p <= w[j]; ++j) {
            int k = id(w[j] / p);
            g[0][j] = sub(g[0][j], sub(g[0][k], sp[0][i - 1]));
            g[1][j] = sub(g[1][j], mul(p, sub(g[1][k], sp[1][i - 1])));
            g[2][j] = sub(g[2][j], mul(mul(p, p), sub(g[2][k], sp[2][i - 1])));
        }
    }
}

int get_f(int p, int e, int q) {
    if (e == 0) return 1;
    int x = qpm(p, e - 1);
    int z = mul(mul(mul(x, x), p), add(p, 1));
    return sub(z, x);
}

int get_s(int n, int i = 0) {
    if (ps[i] >= n) return 0;
    int k = id(n), s[3];
    for (int j = 0; j != 3; ++j) s[j] = sub(g[j][k], sp[j][i]);
    int sum = sub(add(s[2], s[1]), s[0]);
    for (int j = i + 1; j <= r && 1ll * ps[j] * ps[j] <= n; ++j) {
        for (ll q = ps[j], e = 1; q <= n; q *= ps[j], ++e)
            sum = add(sum, mul(get_f(ps[j], e, q), add(get_s(n / q, j), (e != 1))));
    }
    return add(sum, (i == 0));
}

//int get_f_bf(int x) {
//    int r = 0;
//    for (int i = 1; i <= x; ++i)
//        for (int j = 1; j <= x; ++j)
//            r = add(r, gcd(i, gcd(j, x)));
//    return r;
//}

int main(void) {
    int x; scanf("%d%d", &x, &P);
    i2 = inv(2); i6 = inv(6);

//    int ss[100];
//    for (int i = 1; i <= x; ++i) {
//        init(i);
//        ss[i] = get_s(i);
//    }
//    for (int i = 1; i <= x; ++i)
//        printf("%d %d\n", ss[i] - ss[i - 1], get_f_bf(i));

    init(x);

    printf("%d\n", get_s(x));

    return 0;
}
