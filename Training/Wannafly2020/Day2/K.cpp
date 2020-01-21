#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1000005;
//const ll p2 = 1919810021, b2 = 364;

char s[N], t[N];

int g[N][26], f[N], sf[N], l[N], val[N], nc; bool e[N];

ll dp[N];

int main() {

    int n; scanf("%d", &n);
    nc = 1;
    for (int i = 1; i <= n; ++i) {
        scanf("%s", s + 1);
        int p = 0, n1 = strlen(s + 1);
        for (int j = 1; j <= n1; ++j) {
            int o = s[j] - 'a';
            if (!g[p][o]) {
                g[p][o] = nc++;
                l[g[p][o]] = l[p] + 1;
                val[g[p][o]] = INT_MAX;
            }
            p = g[p][o];
        }
        e[p] = 1;
        int x; scanf("%d", &x);
        val[p] = min(val[p], x);
    }

    queue<int> q;
    for (int i = 0; i != 26; ++i)
        if (g[0][i]) q.push(g[0][i]);

    while(!q.empty()) {
        int u = q.front(); q.pop();
        for (int o = 0; o != 26; ++o) {
            int& v = g[u][o];
            if (!v) v = g[f[u]][o];
            else {
                f[v] = g[f[u]][o];
                q.push(v);
                if (e[f[v]]) sf[v] = f[v];
                else sf[v] = sf[f[v]];
            }
        }
    }
//
//    cout << nc << endl;
//    for(int i = 0; i != nc; ++i)
//        cout << l[i] <<' ' << e[i] <<' ' << f[i] << ' ' <<sf[i] << endl;

    scanf("%s", t + 1);
    int p = 0, n2 = strlen(t + 1);
    for (int i = 1; i <= n2 ; ++i) {
        int o = t[i] - 'a';
        p = g[p][o];
        dp[i] = LLONG_MAX;
        int q = p;
        while (q) {
            if (e[q] && dp[i - l[q]] != LLONG_MAX)
                dp[i] = min(dp[i], dp[i - l[q]] + val[q]);
            q = sf[q];
        }
    }

    ll ans = dp[n2];
    if (ans == LLONG_MAX) ans = -1;
    printf("%lld\n", ans);

    return 0;
}