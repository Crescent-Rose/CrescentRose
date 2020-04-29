#include<iostream>
#include<assert.h>
#define ll long long
using namespace std;
ll f(ll N, ll k)
{
	if (k == 1) return N;
	ll n = 1, fn = 0;
	while (n < N)
	{
		ll x = min(N - n, (n  - fn) / (k - 1));
		n += x; fn += k * x;
		assert(fn <= n);
		while (n < N && fn < n) n++, fn += k;
		fn %= n;
	}
	return fn + 1;
}
int main()
{
	int T; scanf("%d", &T);
	while (T--)
	{
		ll n, s, m; scanf("%lld%lld%lld", &n, &s, &m);
		printf("%lld\n", (f(n, m) + s - 1) % n + 1);
	}
	return 0;
}