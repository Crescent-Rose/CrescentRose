#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 2002;
long long a[N][N];
int n, m1, m2;
int _lg[N];
struct node{
    long long v[N][11];
    void build() {
        for (int i = 1; i <= 10; i ++)
            for (int j = 1; j + (1 << i) - 1 <= n; j ++)
                v[j][i] = max(v[j][i - 1], v[j + (1<<(i-1))][i - 1]);
    }
    long long getmx(int l, int r) {
        int tmp = _lg[r - l + 1];
        return max(v[l][tmp], v[r - (1 << tmp) + 1][tmp]);
    }
}f[N / 8];
long long w[N*4][N];
#include <assert.h>
void build(int l, int r, int  s) {
    if (l == r) {
        for (int i= 1; i <= n ; i++)
            w[s][i] = a[l][i];
        return;
    }
    build(l, (l + r) / 2, s + s);
    build((l + r) / 2 + 1, r, s + s+ 1);
    for (int i = 1; i <= n; i ++)
        w[s][i] = max(w[s+s][i], w[s+s+1][i]);
    if (r - l + 1 > 16) {
        for (int i = 1; i <= n; i ++)
            f[s].v[i][0] = w[s][i];
        f[s].build();
        assert(s < N / 8);
    }
}
long long get(int l, int r, int s, int ll, int rr, int lll, int rrr) {
    if (r < ll || rr < l) return 0;
    if (ll <= l && r <= rr) {
        if (r - l + 1 <= 16) {
            long long tmp = 0;
            for (int i = lll; i <= rrr; i ++)
                tmp = max(tmp, w[s][i]);
            return tmp;
        }
        return f[s].getmx(lll, rrr);
    }
    return max(get(l, (l + r)/ 2,  s+ s, ll, rr, lll, rrr), get((l+r)/ 2 + 1,r,s+s+1, ll,rr, lll,rrr));
}
int main() {
    scanf("%d %d %d", &n, &m1, &m2);
    for (int i = 0; i <= 10; i ++)
        _lg[1<<i] = i;
    for (int i = 1; i <= n ; i ++)
        if (!_lg[i])
            _lg[i] = _lg[i - 1];
    while (m1 --) {
        int x1, y1, x2, y2, w;
        scanf("%d %d %d %d %d", &x1, &y1, &x2, &y2, &w);
        a[x1][y1] += w;
        a[x1][y2 + 1] -= w;
        a[x2 + 1][y1] -= w;
        a[x2 + 1][y2 + 1] += w;
    }
    for (int i =1 ; i <= n; i ++)
        for (int j= 1; j <= n; j ++)
            a[i][j] += a[i - 1][j] + a[i][j -1] - a[i - 1][j - 1];
    build(1, n, 1);
    while (m2 --) {
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        printf("%lld\n", get(1, n, 1, x1, x2, y1, y2));
    }
    return 0;
}