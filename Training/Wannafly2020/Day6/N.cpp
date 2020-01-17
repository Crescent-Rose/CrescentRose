#include <algorithm>
#include <cstdio>
using namespace std;
int n;
long long ans;
int main() {
    scanf("%d", &n);
    long long all = 0;
    while (n --) {
        int x;
        scanf("%d", &x);
        ans += x * all;
        all += x;
    }
    printf("%lld\n", ans);
    return 0;
}