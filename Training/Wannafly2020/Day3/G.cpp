#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
const int N = 1e6;
int n, k;
bool bz[N];
long long ans[N];
vector<pair<int, int> > g[N];
long long f[N], longest[N], longest2[N], idl1[N], idl2[N];
int sum[N];
void dfs(int x, int fa) {
    if (!bz[x]) longest[x] = -1;
    else
        longest[x] = 0;
    longest2[x] = -1;
    for (auto u:g[x])
        if (u.first != fa) {
            dfs(u.first, x);
            if (longest[u.first] != -1) {
                if (longest[x] <= longest[u.first] + u.second){
                    longest2[x] = longest[x];
                    idl2[x] = idl1[x];
                    longest[x] = longest[u.first] + u.second;
                    idl1[x] = u.first;
                }else
                    if (longest2[x] < longest[u.first] + u.second) {
                        longest2[x] = longest[u.first] + u.second;
                        idl2[x] = u.first;
                    }
                f[x] += f[u.first] + u.second * 2;
                sum[x] ++;
            }
        }
}
void dfs1(int x, int fa, long long fv, long long upv) {
    if (upv != -1) {
        ans[x] = f[x] + fv - max(longest[x], upv);
    } else {
        ans[x] = f[x] - longest[x];
    }
    for (auto u:g[x])
        if (u.first != fa) {
            long long newfv = fv;
            long long newupv = upv;
            if (upv || (sum[x] - (longest[u.first] != -1)) > 0 || bz[x])
                newfv += u.second * 2;
            newfv += f[x];
            if (longest[u.first] != -1)
                 newfv -= (f[u.first] + u.second * 2);
            if (longest[x] > newupv && idl1[x] != u.first)
                newupv = longest[x];
            if (longest2[x] > newupv && idl2[x] != u.first)
                newupv = longest2[x];
            if ( bz[u.first] && newupv == -1)
                newupv = 0;
            if (newupv != -1)
                newupv += u.second;
            dfs1(u.first, x, newfv, newupv);
        }
}
int main() {
    scanf("%d %d", &n, &k);
    for (int i = 1; i < n; i ++) {
        int x, y, z;
        scanf("%d %d %d",&x,&y, &z);
        g[x].push_back(make_pair(y, z));
        g[y].push_back(make_pair(x, z));
    }
    for (int i = 1;i <= k; i++) {
        int x;
        scanf("%d", &x);
        bz[x] = 1;
    }
    dfs(1, 0);
    dfs1(1, 0, 0, -1);
    for (int i =1 ; i<= n; i ++)
        printf("%lld\n", ans[i]);
    return 0;
}