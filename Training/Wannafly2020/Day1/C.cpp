#include <bits/stdc++.h>

using namespace std;

const int P = 998244353;

typedef long long ll;

inline int add(int a, int b) { int r = a + b; return r < P ? r : r - P; }
inline int sub(int a, int b) { int r = a - b; return r < 0 ? r + P : r; }
inline int mul(ll a, ll b) { return a * b % P; }
int inv(int x) { return x == 1 ? 1 : mul(inv(P % x), P - P / x); }

int i2 = inv(2), i6 = inv(6);
inline int s1(int x) { return mul(mul(x, x + 1), i2); }
inline int s2(int x) { return mul(mul(x, x + 1), mul(2 * x + 1, i6)); }


int f(int n, int x, int y) {
    int sum = mul(sub(mul(n, n), n), y - x + 1);
    for (int l = x, r; l <= y; l = r + 1) {
        int w = n / l; r = min(n / w, y);
        sum = add(sum, sub(mul(sub(s1(r), s1(l - 1)), add(mul(w, w), w)), mul(mul(2 * n, r - l + 1), w)));
    }
    sum = mul(sum, i2);
    return sum;
}

int main()
{
    int T; scanf("%d", &T);

    //mt19937_64 mt(time(0));
    while (T--) {
        //uniform_int_distribution<int> un(1, 1000000000);
        int n, l, r; scanf("%d%d%d", &n, &l, &r);
//        n = un(mt);
//        uniform_int_distribution<int> ulr(1, n);
//        l = ulr(mt);
//        r = ulr(mt);
//        if (l > r) swap(l, r);
        printf("%d\n", f(n, l, r));
    }
    return 0;
}
