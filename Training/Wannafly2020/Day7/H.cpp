#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 10001;

bool ip[N]; vector<int> ps;
int ph[N];
void sieve() {
    fill_n(ip, N, 1);
    ip[1] = 0; ph[1] = 1;
    for (int i = 2; i != N; ++i) {
        if (ip[i]) ps.push_back(i), ph[i] = i - 1;
        for (int j : ps) {
            if (i * j >= N) break;
            ip[i * j] = 0;
            if (i % j == 0) {
                ph[i * j] = ph[i] * j;
                break;
            }
            else ph[i * j] = ph[i] * (j - 1);
        }
    }
}

ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

int main()
{
    sieve();
    int n; scanf("%d", &n);
    int s = 0;
    for (int i = 2; i <= n; ++i)
        s += ph[i];
    ll u = s , v = n - (n % 2 == 0);
    if (!v) v = 1;
    ll d = gcd(u, v);
    u /= d; v /= d;
    printf("%lld/%lld\n", u, v);
    return 0;
}
