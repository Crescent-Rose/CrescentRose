#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 1503;
const ll inf = LLONG_MAX;
struct edge { int v, p; ll c, f, w; };
vector<edge> g[N];
int cur[N], nc;

int addv(int cnt) {
    while (cnt--) {
        int p = ++nc;
        g[p].resize(0);
    }
    return nc;
}

void adde(int u, int v, ll c, ll w) {
    g[u].push_back({ v, g[v].size(), c, 0, w });
    g[v].push_back({ u, g[u].size() - 1, c, c, -w });
}


bool inq[N]; ll dis[N];
bool spfa_mcmf(int s, int t) {
    fill_n(dis + 1, nc, LLONG_MAX);
    queue<int> q; q.push(s); inq[s] = 1; dis[s] = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop(); inq[u] = 0;
        for (edge e : g[u]) {
            int v = e.v; ll dv = e.w + dis[u];
            if (dis[v] <= dv || e.c == e.f) continue;
            dis[v] = dv; if (!inq[v]) q.push(v), inq[v] = 1;
        }
    }
    return dis[t] != LLONG_MAX;
}

ll dfs_mcmf(int u, int t, ll f) {
    if (u == t) return f; ll sf = 0; inq[u] = 1;
    for (int& i = cur[u]; i != g[u].size(); ++i) {
        edge& e = g[u][i]; int v = e.v;
        if (e.c == e.f || dis[u] + e.w != dis[v] || inq[v]) continue;
        ll df = dfs_mcmf(v, t, min(f, e.c - e.f));
        e.f += df; sf += df; f -= df; g[v][e.p].f -= df;
        if (!f) break;
    }
    inq[u] = 0; return sf;
}

pair<ll, ll> mcmf(int s, int t, ll mf = inf) {
    ll sf = 0, sc = 0;
    while (spfa_mcmf(s, t)) {
        if (dis[t] > 0) break;
        fill_n(cur + 1, nc, 0);
        ll df = dfs_mcmf(s, t, mf);
        mf -= df; sf += df;
        sc += dis[t] * df;
    }
    return { sf, sc };
}

int main(void) {
    int n, m, k; scanf("%d%d%d", &n, &m, &k);
    addv(n * m);
    int s = addv(1), t = addv(1);
    while (k--) {
        int x1, y1, x2, y2; ll ww;
        scanf("%d%d%d%d%lld", &x1, &y1, &x2, &y2, &ww);
        int i1 = (x1 - 1) * m + y1, i2 = (x2 - 1) * m + y2;
        if ((x2 + y2) % 2 == 0) swap(i1, i2);
        adde(i1, i2, 1, -ww);
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if ((i + j) % 2 == 0)
                adde(s, (i - 1) * m + j, 1, 0);
            else
                adde((i - 1) * m + j, t, 1, 0);

    cout << -mcmf(s, t).second << endl;
    return 0;
}
