#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
const int N = 40001;
const int mod = 998244353;
//vector<vector<int> >f[N];
vector<int>edge[N];
int n, m;
int leafs[N];
int add(int x, int y) {
    x += y;
    return x >= mod ? x - mod : x;
}
int sub(int x, int y) {
    x -= y;
    return x < 0 ? x + mod : x;
}
int mul(int x, int y) {
    return 1ll * x * y % mod;
}
int calc(int x, int y) {
    int s = 1;
    while (y) {
        if (y & 1) s = mul(s, x);
        x = mul(x, x), y >>= 1;
    }
    return s;
}
int sumson[N];

void dfs(int x, int fa) {
    leafs[x] = 1;
    for (auto u:edge[x])
        if (u != fa) {
            dfs(u, x);
            leafs[x] += leafs[u];
            sumson[x] ++;
        }
}
pair<vector<int>, vector<int> > ww;
void dfs1(int x, int fa) {
    if (sumson[x] == 0) {
        vector<int> tmp(2, 0);
        vector<int> tmp1(2, 0);
        tmp1[1] = 1;
        ww  =make_pair(tmp, tmp1);
        return;
    }
    int UP = min(leafs[x] + 1, m +1);
    vector<int> f = vector<int>(min(leafs[x] + 1, m +1), 0);
    vector<int> g = vector<int>(min(leafs[x] + 1, m +1), 0);
    g[0] = 1;
    int all = 2;
    for (auto u:edge[x])
        if (u!=fa) {
            dfs1(u,x);
            vector<int> &tmp = ww.first;
            vector<int> &v = ww.second;
            vector<int> ff = f, gg = g, vv = v;
            vv[1] = sub(vv[1], 1);
            int mx = max(tmp.size(), max(vv.size(), v.size()));
            int lastall = all;
            all = min(all + mx, UP);
            tmp.resize(mx, 0);
            vv.resize(mx, 0);
            v.resize(mx, 0);
            for (int j = 0; j < lastall; j ++)
                for (int k = 0; j + k < all && k < mx; k ++)
                    f[j + k] = add(add(f[j + k], mul(ff[j], add(tmp[k], vv[k]))), mul(gg[j], add(tmp[k], v[k])));
            for (int j = 0; j < lastall; j ++)
                for (int k = 0; j + k < all && k < mx; k ++)
                    g[j + k] = add(g[j + k], mul(gg[j], add(tmp[k], vv[k])));
        }
    g.push_back(0);
    for (int j = g.size() -1 ; j >= 1; j --)
        g[j] = g[j - 1];
    g[0] = 0;
    if ((int)g.size() - 1 > m)
        g.resize(m + 1);
    while (g.size() > 3&& !g[g.size() - 1])g.pop_back();
    while (f.size() > 3&& !f[f.size() - 1])f.pop_back();
    ww = make_pair(f, g);
}
int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i < n; i ++) {
        int x, y;
        scanf("%d %d", &x, &y);
        edge[x].push_back(y);
        edge[y].push_back(x);
    }
    dfs(1, 0);
    dfs1(1, 0);
    int ans = 0;
    for (auto u:ww.first)
        ans = add(ans, u);
    for (auto u:ww.second)
        ans = add(ans, u);
    printf("%d", ans);
    return 0;
}