#include <algorithm>
#include <cstdio>
using namespace std;
int a1, a2;
int ans;
int main() {
    ans = 1e9;
    scanf("%d %d", &a1, &a2);
    int T;
    scanf("%d", &T);
    while (T --) {
        int x, y;
        scanf("%d %d", &x, &y);
        int l = 1, r = 1e6, mid, s = 1e6;
        while (l <= r) {
            mid = (l + r) / 2;
            long long v = 1ll * mid * (mid + 1) / 2;
            if (v + a1 * mid >= x && 1ll * a2 * mid + v - max(x - 1ll * a1 * mid, 1ll *0) >= y ) {
                r = mid  -1;
                s = min(s, mid);
            }else
                l = mid + 1;
        }
        ans = min(ans, s);
    }
    printf("%d\n", ans);
    return 0;
}