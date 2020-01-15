#include <bits/stdc++.h>
using namespace std;
const int N = 10000;
const int mod = 998244353;
const int P = mod;
int n;
int l[N], r[N], id[N];
long long inv1[N];
int inv(int x) { return x == 1 ? 1 : (1ll * inv(P % x)*(P - P / x)%P); }
long long did(long long i, long long j) {
    swap(i, j);
    if (i > j)
        return j * (j + 1) / 2;
    else {
        return (i + 1) * (j + 1) - (i + 1) * (i + 2) / 2;
    }
}
long long calc(int x, int y) {
    return did(r[x], r[y]) - did(r[x], l[y] - 1) - did(l[x] - 1, r[y]) + did(l[x] - 1, l[y] - 1);
}
int len(int x) {
    return r[x] - l[x] + 1;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1 ; i<= n; i ++)
        scanf("%d %d", &l[i], &r[i]), id[i] = i, inv1[i] = (len(i) % P == 0 ? 0 : inv(len(i) % P));
    sort(id + 1, id + n +1,[](int x, int y) {
         return calc(x, y) < calc(y, x) || (calc(x , y) == calc(y, x)&&r[x] <r[y]);});
    long long ans = 0;
    for (int i = 1; i <= n; i ++)
    for (int j =  i + 1; j <= n; j ++) {
        ans = (ans + calc(id[i], id[j]) %mod * (inv1[id[i]] * inv1[id[j]] %mod)) % mod;
    }
    cout<<ans;
    return 0;
}
