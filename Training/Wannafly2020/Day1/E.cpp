#include <bits/stdc++.h>

using namespace std;
const int N = 3e5+ 10;
const int S = 19;
int n, m;
int fa[N][S+1], deep[N];
long long ans[N], vo[N], sumo[N], sigman[N], sigmai[N], vall[N], vo1[N], upf[N];
vector<int>g[N];
vector<pair<int, pair<int, int> > > w[N];
void dfs(int x) {
    for (int i = 0; fa[fa[x][i]][i]; i ++) fa[x][i + 1] = fa[fa[x][i]][i];
    deep[x] ++;
    for (auto u:g[x])
        if (u != fa[x][0]) {
            fa[u][0] = x;
            deep[u] = deep[x];
            dfs(u);
        }
}
int getlca(int x, int y) {
    int i = S;
    if (deep[x] <deep[y]) swap(x, y);
    while (deep[x] != deep[y]) {
        while (deep[fa[x][i]] <deep[y]) i --;
        x = fa[x][i];
    }
    i = S;
    while (x != y) {
        while (i &&fa[x][i] == fa[y][i]) i --;
        x = fa[x][i], y = fa[y][i];
    }
    return x;
}
int up(int x, int y) {
    int i = S;
    while (deep[x] > y) {
        while (deep[fa[x][i]] < y) i --;
        x = fa[x][i];
    }
    return x;
}
void dfs1(int x) {
    for (auto u:w[x])
        if (u.first == 1)
            sumo[x] ++, sigman[x] += u.second.first;
    for (auto u:g[x])
        if (u != fa[x][0]) {
            dfs1(u);
            vall[x] += vall[u];
            sumo[x] += sumo[u];
            sigman[x] += sigman[u];
            sigmai[x] += sigmai[u] + sumo[u];
            vo[x] += vo[u] + sigman[u] - 2 * sigmai[u] - sumo[u];

            upf[u] += vo[u] + sigman[u] - 2 * sigmai[u] - sumo[u];
            for (auto v:w[u])
                if (v.first == -1) {
                    sigman[x] -= v.second.first;
                    sumo[x] --;
                    sigmai[x] -= deep[v.second.second] - deep[x];
                    vo[x] -= 1ll * (v.second.first - (deep[v.second.second] - deep[x])) * (deep[v.second.second] - deep[x]);
                }
        }
}
void dfs2(int x, long long extra) {
    ans[x] = vall[x] + extra + vo[x];
    for (auto u:g[x])
    if (u != fa[x][0]) {
        dfs2(u, extra + vo[x] - upf[u] +vall[x] - vall[u] - vo1[u]);
    }
}
int main()
{
    scanf("%d %d", &n, &m);
    for (int i = 1; i < n; i ++) {
        int x , y;
        scanf("%d %d", &x , &y);
        g[x].push_back(y);
        g[y].push_back(x);
    }
    dfs(1);
    while (m --) {
        int x, y;
        scanf("%d %d", &x, &y);
        if (x == y) continue;
        int lca = getlca(x, y);
        if (lca == y) swap(x, y);
        int len = deep[x] + deep[y] - deep[lca] * 2;
        vo1[lca] += 1ll * (len - (deep[x] - deep[lca])) * (deep[x] - deep[lca]);
        vall[fa[lca][0]] += 1ll * (len - (deep[x] - deep[lca])) * (deep[x] - deep[lca]);
        if (lca == x) {
            w[y].push_back(make_pair(1, make_pair(len, y)));
            w[up(y, deep[lca] + 1)].push_back(make_pair(-1, make_pair(len, y)));
        } else {
            w[x].push_back(make_pair(1, make_pair(len, x)));
            w[y].push_back(make_pair(1, make_pair(len, y)));
            w[up(x, deep[lca] + 1)].push_back(make_pair(-1, make_pair(len, x)));
            w[up(y, deep[lca] + 1)].push_back(make_pair(-1, make_pair(len, y)));
        }
    }
    dfs1(1);
    for (int i = 1; i <= n; i ++) vo[i] += vo1[i];
    dfs2(1, 0);
    for (int i = 1; i <= n ; i ++)
        printf("%lld\n", ans[i]);
    return 0;
}
