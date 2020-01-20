#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 1e5 + 10;
const int mod = 1e9 + 7;

int add(int x, int y) {
    x += y;
    return x >= mod ? x - mod :x;
}
int mul(int x, int y) {
    return 1ll * x * y % mod;
}
struct node{
    int tagi, tagj, tagadd;
    int all;
    void clear(){
        tagi = tagj = tagadd = 0;
        all = 0;
    }
    void updateadd(int v) {
        all = add(all, v);
        tagadd = add(tagadd, v);
    }
    void updatei(int v){
        tagi = add(tagi, v);
    }
    void updatej(int v) {
        tagj = add(tagj, v);
        updateadd(mul(v, tagi));
    }
}f[N * 4];
int n;
int a[N];
int b[N], nib[N];
int ans[N];
int calc(int x, int y) {
    int z = 1;
    while (y) {
        if (y & 1) z = mul(z, x);
        x = mul(x, x), y >>= 1;
    }
    return z;
}
void down(int l, int r, int s) {
    if (f[s].tagj) {
        if (l != r)
            f[s+s].updatej(f[s].tagj), f[s+s+1].updatej(f[s].tagj);
        f[s].tagj = 0;
    }
    if (f[s].tagi) {
        if (l != r)
            f[s+s].updatei(f[s].tagi), f[s+s+1].updatei(f[s].tagi),f[s].tagi = 0;
    }
    if (f[s].tagadd) {
        if (l != r)
            f[s+s].updateadd(f[s].tagadd), f[s+s+1].updateadd(f[s].tagadd);
        f[s].tagadd = 0;
    }
}
void build(int l, int r, int s) {
    down(l, r, s);
    if (l == r) {
        ans[l] = add(ans[l], f[s].all);
        f[s].clear();
        return;
    }
    f[s].clear();
    build(l, (l + r)  / 2,  s + s);
    build((l +r) / 2 + 1, r , s+ s + 1);
}
void add(int l, int  r, int s,int ll, int rr ,int sig, int v) {
    down(l, r, s);
    if (rr < l || r < ll) return;
    if (ll <= l && r <= rr) {
        if (sig == 0) {
            f[s].updatei(v);
        } else {
            f[s].updatej(v);
        }
        return;
    }
    add(l, (l + r) / 2, s + s, ll, rr, sig, v);
    add((l + r) / 2 + 1, r, s + s + 1, ll, rr, sig, v);
}
int main() {
    scanf("%d", &n);
    b[0] = nib[0] = 1;
    for (int i = 1; i <= n; i ++)
        b[i] = mul(b[i - 1], 2);
    nib[1] = calc(2, mod - 2);
    for (int i = 2; i <= n; i ++)
        nib[i] = mul(nib[i - 1], nib[1]);
    for (int i = 1;i <= n; i ++)
        scanf("%d", &a[i]);
    for (int i = 1; i <= n; i ++) {
        add(1, n, 1, 1, a[i] - 1, 1, nib[i]);
        add(1, n, 1, a[i] + 1, n, 0, b[i]);
    }
    build(1, n, 1);
    for (int i = 1; i <= n; i ++) {
        add(1, n, 1, a[i] + 1, n, 1, nib[i]);
        add(1, n, 1, 1, a[i] - 1, 0, b[i]);
    }
    build(1, n, 1);
    for (int i = 1; i <= n; i++)
        printf("%d\n", mul(ans[i], b[n - 1]));
    return 0;
}