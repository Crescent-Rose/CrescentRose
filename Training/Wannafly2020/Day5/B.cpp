#include <algorithm>
#include <cstdio>
#include <vector>
#include <unordered_map>
using namespace std;
const int N = 5e5 + 10;
int n, m;
int fa[N], ans[N];
int edge[N][2];
int id[N];
int getfa(int x) {return x == fa[x] ? x: fa[x] = getfa(fa[x]);}
unordered_map<long long , int>f;
int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i ++)
        fa[i] = i, ans[i] = 1;
    for (int i = 1;i < n; i ++)
        scanf("%d %d", &edge[i][0], &edge[i][1]);
    for (int i = 1; i <= m; i ++)
        scanf("%d", &id[i]);
    for (int ww = m;  ww >= 1 ;ww --){
        int x = id[ww];
        int y = edge[x][0];
        x = edge[x][1];
        if (x>y)swap(x, y);
        int v = ans[x] + ans[y]- f[1ll * 10000000 * x + y];
        ans[x] = ans[y] = v;
        f[1ll * 10000000 * x + y] = v;
        if (getfa(x) != getfa(y)) {
            fa[getfa(x)] = y;
        }
    }
    for (int i = 1; i <= n; i ++)
        printf("%d%c", max(ans[i], 1), " \n"[i == n]);
    return 0;
}