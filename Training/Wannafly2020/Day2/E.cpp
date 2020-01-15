#include <bits/stdc++.h>
#define N 100001
using namespace std;

typedef long long ll;

vector<int> g[N];
set<int> s[N];

ll ans[N];

void ins(set<int>& s, int x, ll& a) {
    auto it = s.insert(x).first;
    ll pv = -1, nv = -1;
    if (it != s.begin()) pv = *prev(it);
    if (next(it) != s.end()) nv = *next(it);
    if (pv != -1 && nv != -1) a -= (nv - pv) * (nv - pv);
    if (pv != -1) a += (x - pv) * (x - pv);
    if (nv != -1) a += (nv - x) * (nv - x);
}

void dfs(int u) {
    int mv = -1;
    for (int v : g[u]) {
        dfs(v);
        if (mv == -1 || s[v].size() > s[mv].size())
            mv = v;
    }
    if (mv != -1) swap(s[u], s[mv]), ans[u] = ans[mv];
    ins(s[u], u, ans[u]);
    for (int v : g[u]) if (v != mv)
        for (int x : s[v])
            ins(s[u], x, ans[u]);
}

int main() {
    int n; scanf("%d", &n);
    for (int i = 2; i <= n; ++i) {
        int f; scanf("%d", &f);
        g[f].push_back(i);
    }

    dfs(1);

    for (int i = 1; i <= n; ++i)
        printf("%lld\n", ans[i]);

    return 0;
}
