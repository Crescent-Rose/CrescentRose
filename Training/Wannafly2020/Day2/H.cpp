#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1000005;
//const ll p2 = 1919810021, b2 = 364;

int getm_odd(ll n) {
    ll l = 0, r = 1e9;
    while (l <= r) {
        ll mid = (2 * ((l + r) / 2) + 1);
        if (mid * (mid - 1) / 2 + 1 <= n) l = (l + r) / 2 + 1;
        else r = (l + r) / 2  - 1;
    }
    return 2 * r + 1;
}

int getm_even(ll n) {
    ll l = 0, r = 1e9;
    while (l <= r) {
        ll mid = (2 * ((l + r) / 2));
        if (mid * (mid) / 2 <= n) l = (l + r) / 2  + 1;
        else r = (l + r) / 2  - 1;
    }
    return 2 * r;
}

ll getm(ll n) {
    return max(getm_odd(n), getm_even(n));
}

ll cal_n(ll m) {
    if (m % 2 == 0)
        return m * m / 2;
    else
        return m * (m - 1) / 2 + 1;
}

typedef pair<int, int> pii;
vector<pii> g[10001];
void adde(int u, int v) {
    //cout << u << ' ' << v << endl;
    if (u != v) {
        g[u].push_back({ v, g[v].size() });
        g[v].push_back({ u, g[u].size() - 1 });
    }
}

const int maxn = 2000000;

int ans[maxn + 1], c = 0;

void eulerian_path(int*r, int w) {
    static int s[N], t; s[++t] = w;
    while (t) {
        int u = s[t];
        if (g[u].empty())
            r[++c] = u, --t;
        else {
            pii p = g[u].back();
            int v = p.first, i = p.second;
            if (v != u) {
                if (i + 1 != g[v].size()) {
                    pii& q = g[v].back();
                    g[q.first][q.second].second = i;
                    swap(g[v][i], q);
                }
                g[u].pop_back();
                g[v].pop_back();
                s[++t] = v;
            }
            else {
                g[u].pop_back();
                s[++t] = u;
            }
        }
    }
}

int main() {
    ll n;
    scanf("%lld", &n);
    ll m = getm(n);

    printf("%lld\n", m);
    if (cal_n(m) <= maxn) {
        if (m % 2 == 0) {
            for (int i = 1; i <= m; ++i) {
                for (int j = i + 1; j <= m; ++j) {
                    if (i != 1 && j == i + m / 2)
                        ans[++c] = i, ans[++c] = j;
                    else
                        adde(i, j);
                }
            }
        }
        else {
            for (int i = 1; i <= m; ++i) {
                for (int j = i + 1; j <= m; ++j) {
                    adde(i, j);
                }
            }
        }

        eulerian_path(ans, 1);

        while (c != n) ans[++c] = 1;

        for (int i = 1; i <= n; ++i)
            printf("%d%c", ans[i], " \n"[i == n]);
    }
    return 0;
}
