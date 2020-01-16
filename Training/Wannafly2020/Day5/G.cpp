#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int invs[1<<21];
typedef pair<int, int> pii;
pii v[1<<21], s[1<<21];
int main() {
    int T; scanf("%d", &T);
    while (T--) {
        int p; scanf("%d", &p);
        invs[1] = 1;
        int m = p, t = p;
        int c = 0, z = 0;
        for (int i = 2; i <= p - 1; ++i) {
            invs[i] = 1ll * invs[p % i] * (p - p / i) % p;
            if (invs[i] < i) break;
            s[++c] = { i, invs[i] };
        }
        for (int i = 1; i <= c; ++i) {
            pii w = s[i];
            if (w.second < m) {
                m = w.second;
                v[++z] = w;
            }
        }
        copy_n(v + 1, z, v + z + 1);
        reverse(v + z + 1, v + 2 * z + 1);
        for (int i = z + 1; i <= 2 * z; ++i)
            swap(v[i].first, v[i].second);
        int e = 2 * z;
        if (p == 3) e--;
        printf("%d\n", e);
        for (int i = 1; i <= e; ++i)
            printf("%d %d\n", v[i].first, v[i].second);
    }
//
//    srand(time(0));
//    int cnt = 500;
//    while(cnt) {
//        int p = rand() | (rand() << 15);
//        p %= 100001;
//        if (!ip(p)) continue;
//        vector<ll> invs(p, 0);
//        ll m = p;
//        invs[1] = 1;
//        cout << p << endl;
//        cnt--;
//        for (int i = 2; i <= p - 1; ++i) {
//            invs[i] = 1ll * invs[(p % i)] * (p - p / i) % p;
//            if (invs[i] < m) {
//                cout << i << ' ' << invs[i] << endl;
//                m = invs[i];
//            }
//        }
//        cout << endl;
//    }

    return 0;
}
