#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
const int mod = 998244353;
const int N = 2e5 + 10;
int a[N];
long long f[N * 4];
int n, q;
int c[N][2], tot;
long long v[N];
void build(int l, int r, int s) {
    if (l == r) {
        f[s] = 1ll * (c[l][1]  - c[l][0] + 1) * v[l] % mod;
        return;
    }
    build(l, (l + r) / 2, s + s);
    build((l + r ) / 2 + 1, r ,s +s + 1);
    f[s] = (f[s+s] + f[s+s+1]) % mod;
}
vector<pair<int, int> > divide(int x, int y) {//求0~x 异或上y后分的log段连续段
    int top = 0;
    vector<pair<int, int> > d;
    for (int i = 29; i >= 0; i --) {
        if ((x >> i) & 1) {
            int z = top ^ (y & (1 << i));
            d.push_back(make_pair(z, z + (1 << i) - 1));
        }
        top ^= ((x ^ y) & (1 << i));
    }
    d.push_back(make_pair(x ^ y, x ^ y));
    return d;
}
long long get(int l, int r, int s, int ll, int rr) {
    if (c[l][0] > rr || ll > c[r][1]) return 0;
    if (ll <= c[l][0] && c[r][1] <= rr)
        return f[s];
    if (l == r){
        return 1ll * (min(c[r][1], rr) - max(c[l][0], ll) + 1) * v[l] % mod;
    }
    return (get(l, (l + r) / 2, s + s, ll, rr) + get((l + r) / 2 + 1, r, s + s + 1, ll, rr)) % mod;
}
int main() {
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i ++)
        scanf("%d", &a[i]);
    sort(a + 1, a + n + 1);
    int last = -1;
    for (int i = 1; i <= n; i ++)
        if (i == 1 || a[i] != a[i - 1]){
            c[++tot][0] = last +1;
            c[tot][1] = a[i] - 1;
            v[tot] = 1ll * (i - 1) * (i - 1) % mod;
            last = a[i] - 1;
        }
    c[++tot][0]  =last + 1;
    c[tot][1] = (1 << 30) - 1;
    v[tot] = 1ll * n * n % mod;
    build(1, tot, 1);
    while (q --) {
        int l, r, x;
        scanf("%d %d %d", &l, &r, &x);
        vector<pair<int, int> > a = divide(r, x);
        long long ans = 0;
        for (auto u:a)
            ans += get(1, tot, 1, u.first, u.second);
        if (l) {
            l --;
            a = divide(l, x);
            for (auto u:a)
                ans += mod - get(1, tot, 1, u.first, u.second);
        }
        printf("%lld\n", ans % mod);
    }
    return 0;
}