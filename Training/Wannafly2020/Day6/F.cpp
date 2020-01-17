#include <cstdio>
#include <algorithm>
using namespace std;
int n;
int A, B, C, P, D;
int sum[10000][2];
long long ans, v;
long long sqr(long long x) {
    return x * x % P;
}
int main() {
    scanf("%d", &n);
    scanf("%d %d %d %d %d", &A, &B, &C, &P, &D);
    for (int i = 1; i <= n; i ++)
        for (int j = i + 1; j <= n; j ++)
        {
            bool sig = (1ll * A * sqr(i + j)%P + 1ll * B * sqr(i - j) % P +C) % P > D;
            sum[i][sig] ++;
            sum[j][sig] ++;
        }
    for (int i = 1; i <= n; i ++)
        v += 1ll * sum[i][0] * sum[i][1];
    ans = 1ll * n * (n - 1) * (n - 2) / 6 - v / 2;
    printf("%lld\n", ans);
    return 0;
}