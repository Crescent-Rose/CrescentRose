#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 18;
int edge[1 << N];
int  f[1 << N];
int id[1 << N], g[1 << N];
int n, m;
int main(){
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n ; i++)
        id[1 << i] = i, edge[i] = 1 << i;
    int mask = (1 << n) - 1;
    while (m --) {
        int x ,y;
        scanf("%d %d", &x, &y);
        x --;
        y --;
        edge[x] |= (1 << y);
        edge[y] |= (1 << x);
    }
    f[0] = 1 << n;
    for (int i = 0; i <= mask; i ++)
        if (f[i]) {
            int v = mask ^ (f[i] - (1 << n));
            while (v) {
                int x = v & -v;
                f[i + x] = f[i] | edge[id[x]];
                v -= x;
            }
        }
    g[0] = 1;
    int ans = 0;
    while (!g[mask]) {
        ans ++;
        for (int i = mask - 1; i >= 0; i --)
        if (g[i] == 1){
            g[i] = 2;
            int x = (mask ^ i);
            for (int j = x; j; j = (j - 1) & x)
                if (f[j])
                    g[i + j] = max(g[i + j], 1);
        }
    }
    printf("%d\n", ans - 1);
    return 0;
}

