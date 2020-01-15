#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
using namespace std;
const int N = 1e5 + 10;
int n, k, sig;
int sum[N];
int tag[N];
int a[N];
long long w1[N], w2[N];
long long * f1 = w1, *f2 = w2;
int L = 0, R = 0;
long long w;
long long C(long long x) {
    return x * (x - 1) / 2;
}
void turn(int l, int r) {
    if ( abs(l - L) + abs(r - R) > abs(r - l)) {
        sig++;
        L = l, R = l - 1;
        w = 0;
    }

    while (R < r) {
        R ++;
        if (tag[a[R]] != sig) {
            tag[a[R]] = sig;
            sum[a[R]] = 0;
        }
        w += C(sum[a[R]] + 1) - C(sum[a[R]]);
        sum[a[R]] ++;
    }
    while (L > l) {
        L --;
        if (tag[a[L]] != sig) {
            tag[a[L]] = sig;
            sum[a[L]] = 0;
        }
        w += C(sum[a[L]] + 1) - C(sum[a[L]]);
        sum[a[L]] ++;
    }
    while (R > r) {
        w += C(sum[a[R]] - 1) - C(sum[a[R]]);
        sum[a[R]] --;
        R --;
    }
    while (L < l) {
        w += C(sum[a[L]] - 1) - C(sum[a[L]]);
        sum[a[L]] --;
        L ++;
    }
}
void work(int l, int r, int ll, int rr) {
    if (ll > rr )return;
    int midd = (ll + rr) / 2;
    long long mn = 1e18;
    int mid = l;
    turn(l, midd);
    mn = w + f1[l - 1];
    for (int i = l + 1 ;i <= r && i <= midd; i ++)
    {
        turn(i, midd);
        if (mn > w + f1[i - 1])
            mn = w + f1[i - 1], mid = i;
    }
    f2[midd] = mn;
    work(mid, r, midd + 1, rr);
    work(l, mid, ll, midd - 1);
}
int main() {
    scanf("%d%d", &n, &k);
    for (int i= 1; i <= n; i ++) {
        int x;
        scanf("%d", &x);
        a[i] = x;
    }
    for (int i = 1; i <= n; i ++)
        f1[i] = 1e18;
    while (k --) {
        for (int i = 1; i <= n; i ++)
            f2[i] = 1e18;
        work(1, n, 1, n);
        swap(f1, f2);
    }
    printf("%lld\n", f1[n]);
    return 0;
}