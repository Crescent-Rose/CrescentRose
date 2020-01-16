#include <bits/stdc++.h>

using namespace std;

typedef bitset<1024> bs;

char s[1030][1030];
bs b[1030];

const int p = 1000000007;

int qpm(int x, int y) {
    int r = 1;
    do if (y & 1) r = 1ll * r * x % p;
    while (x = 1ll * x * x % p, y >>= 1);
    return r;
}

int main() {
    int k, n; scanf("%d", &k);
    n = 1 << k;
    for (int i = 0; i != n; ++i)
        scanf("%s", s[i]);
    for (int i = 0; i != n; ++i) {
        for (int j = 0; j != n; ++j) {
            bs a;
            for (int x = 0; x != n; ++x) {
                for (int y = 0; y != n; ++y) {
                    a[((x + i) % n) * n + (y + j) % n] = (s[x][y] == '1');
                }
            }
            for (int x = n * n - 1; x >= 0; --x) {
                if (!a[x]) continue;
                if (!b[x][x]) { b[x] = a; break; }
                else a ^= b[x];
                if (a.none()) break;
            }
        }
    }
    int ans = 0;
    for (int i = 0; i != n * n; ++i)
        if (b[i][i]) ans++;

    printf("%d\n", qpm(2, ans));

    return 0;
}
