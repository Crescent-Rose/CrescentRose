#include <bits/stdc++.h>

using namespace std;
const int N = 1e5 + 10;
int n, m;
long long k;
int a[N], b[N], c[N];
bool check(long long v) {
    long long K = k;
    for (int i = 0; i < n ; i ++)
        if (a[i] < 0) {
            long long w = v / (-a[i]);
            if (w * (-a[i]) < v) w ++;
            K -= m - (lower_bound(b, b + m, w) - b);
        } else {
            long long w = v / a[i];
            if (w *a[i] < v) w ++;
            K -= m - (lower_bound(c, c + m, w) - c);
        }
    return K <= 0;
}
int main()
{
    scanf("%d %d %lld", &n, &m, &k);
    for (int i = 0; i < n; i ++)
        scanf("%d", &a[i]);
    for (int i = 0; i < m; i ++)
        scanf("%d", &b[i]), b[i] = -b[i];
    sort(b, b + m);
    for (int i = 0; i < m ; i ++)
        c[i] = -b[m - i - 1];
    long long ans = -1e12;
    long long l = -1e12, r = 1e12, mid;
    check(2);
    while (l <= r) {
        if (check(mid = (l + r) / 2)) l = mid + 1, ans = max(ans, mid);
        else
            r = mid - 1;
    }
    printf("%lld\n",ans);
    return 0;
}
