#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
const int N = 1e6 + 10;
bool bz[26];
int sum[N];
long double a[N];
char s[N];
int main() {
    bz['a' - 'a'] = 1;
    bz['e' - 'a'] = 1;
    bz['i' - 'a'] = 1;
    bz['o' - 'a'] = 1;
    bz['u' - 'a'] = 1;
    bz['y' - 'a'] = 1;
    scanf("%s", s + 1);
    int n = strlen(s + 1);
    for (int i = 1; i <= n; i ++) {
        sum[i] = sum[i - 1] + bz[s[i] - 'a'];
    }
    long double ans = 0;
    for (int i = 1; i <= n ;i ++)
        a[i] = a[i - 1] + (long double) 1 / i;
    for (int i= 1; i <= n; i ++)
        ans += sum[i] * a[i];
    for (int i = 0; i < n; i ++)
        ans -= sum[i] * a[n - i];
    printf("%.10f\n", (double) ans * 2 / n / (n + 1));
    return 0;
}