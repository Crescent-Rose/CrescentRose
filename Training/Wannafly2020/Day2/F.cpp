#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
const int N = 1e6 + 10;
long long ff[N * 4];
int n, m;
vector<pair<int, int> > g[N];
long long f[N];
int upv[N], downv[N];
long long sum[N];
int fa[N], b[N][2], h[N], l[N], r[N];
void dfs(int x) {
    for (auto u:g[x])
        if (u.first != fa[x]) {
            fa[u.first] = x;
            upv[u.first] = u.second;
            dfs(u.first);
            if (b[u.first][1] + 1 > b[x][1]) {
                b[x][1] = b[u.first][1] + 1, b[x][0] = u.first;
                downv[x] = u.second;
            }
        }
}
void dfs1(int x) {
    static int cnt = 0;
    l[x] = ++ cnt;
    if (b[x][0]) {
        h[b[x][0]] = h[x] , dfs1(b[x][0]);
    }
    for (auto u:g[x])
        if (u.first != fa[x] && u.first != b[x][0])
            h[u.first] = u.first, dfs1(u.first);
    r[x] = cnt;
}

void insff(int l, int r, int s, int ll, long long v) {
    ff[s] += v;
    if (l == r) return;
    if ((l +r) / 2 >= ll) return insff(l, (l + r) / 2, s + s, ll, v);
    else
        return insff((l+r) /2 + 1, r ,s +s + 1, ll, v);
}
long long getff(int l, int r, int s ,int ll, int rr) {
    if (r < ll || rr < l) return 0;
    if (ll <= l && r <= rr) return ff[s];
    return getff(l, (l + r) / 2, s + s, ll, rr) + getff((l+r) / 2 + 1, r, s + s + 1, ll, rr);
}
void up(int x, int y) {
    while (x) {
        x = h[x];
        if (x != 1)
            f[fa[x]] += 1ll * y * upv[x];
        x = fa[x];
    }
}
int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i ++) {
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        g[x].push_back(make_pair(y, z));
        g[y].push_back(make_pair(x, z));
    }
    dfs(1);
    h[1] = 1;
    dfs1(1);
    scanf("%d", &m);
    int st = 1;
    long long allsum = 0;
    while (m --) {
        int sig, x, y;
        scanf("%d %d", &sig, &x);
        if (sig == 1) {
            scanf("%d", &y);
            insff(1, n, 1, l[x], y);
            sum[x] += y;
            allsum += y;
            up(x, y);
        } else {
            st = x;
        }
        long long ans = 0;
        if (st != 1) {
            ans+= upv[st] * (allsum - getff(1, n, 1, l[st], r[st]));
        }
        ans += f[st];
        if (b[st][0]) {
            ans += upv[b[st][0]] * getff(1, n ,1, l[b[st][0]], r[b[st][0]]);
        }
        printf("%lld\n",ans);
    }
    return 0;
}