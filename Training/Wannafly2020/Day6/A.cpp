#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;
typedef long long ll;

const int P = 998244353, e = 116195171, N = 100000;

int add(int a, int b) { int r = a + b; return r < P ? r : r - P; }
int sub(int a, int b) { int r = a - b; return r < 0 ? r + P : r; }
int mul(ll a, ll b) { return a * b % P; }
int qpm(int a, int b) {
    int r = 1;
    do if (b & 1) r = mul(r, a);
    while (a = mul(a, a), b >>= 1);
    return r;
}
int inv(int x) { return x == 1 ? 1 : mul(inv(P % x) , P - P / x); }


const int W = 18, S = 1 << W;
int w[S + 1], rev[S << 1], *r[W + 1];
void init() {
    for (int s = 0; s <= W && (r[s] = rev + (1 << s), 1); ++s)
        for (int i = 0; i != (1 << s); ++i)
            r[s][i] = (r[s][i >> 1] >> 1) | ((i & 1) << (s - 1));
    w[0] = 1; w[1] = qpm(3, (P - 1) / S);
    for (int i = 2; i <= S; ++i) w[i] = mul(w[i - 1], w[1]);
}

int m, s, im;
void init(int n) {
    for (s = 0, m = 1; m < n; m <<= 1, ++s);
    im = inv(m);
}

void ntt(int* p, int t) {
    for (int i = 0; i != m; ++i)
        if (i < r[s][i])
            swap(p[i], p[r[s][i]]);
    for (int i = 1, z = 0; i != m; i <<= 1, z++)
        for (int j = 0; j != m; j += (i << 1))
            for (int k = 0, u, v; k != i; ++k)
                u = p[j + k], v = mul(w[(t?(i<<1)-k:k)<<W-z-1],p[i+j+k]),
                p[j + k] = add(u, v), p[i + j + k] = sub(u, v);
    if (t) for (int i = 0; i != m; ++i) p[i] = mul(p[i], im);
}

int px[S], py[S];
vi mul(const vi& p1, const vi& p2, int n = 0){
    int n1 = p1.size(), n2 = p2.size(), n3 = n1 + n2 - 1;
    init(n3);
    copy_n(p1.begin(), n1, px); fill(px + n1, px + m, 0);
    copy_n(p2.begin(), n2, py); fill(py + n2, py + m, 0);
    ntt(px, 0); ntt(py, 0);
    for (int i = 0; i != m; ++i) px[i] = mul(px[i], py[i]);
    ntt(px, 1); vi p3(n3); copy_n(px, n3, p3.begin());
    if (n && n3 > n) p3.resize(n); return p3;
}

int c[S];

int main() {
    int n; scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        int a; scanf("%d", &a);
        c[a]++;
    }


    vi v(N + 1, 0);
    for (int i = 0; i <= N; ++i)
        v[i] = mul(c[i], qpm(e, P - 1 - (1ll * i * i) % (P - 1)));
    init();
    vi r = mul(v, v);
    int sum = 0;
    for (int i = 0; i != r.size(); ++i)
        sum = add(sum, mul(r[i], qpm(e, 1ll * i * i % (P - 1))));

    printf("%d\n", sum);
    return 0;
}
