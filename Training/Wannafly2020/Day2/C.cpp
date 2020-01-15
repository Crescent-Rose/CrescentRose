#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 1e5 + 10;
const long long maxn = 1ll << 59;
struct node{
    int son[2];
    int sum;
}tri[N * 62];
int n, tot;
void ins(int s, long long v, long long step) {
    tri[s].sum ++;
    if (step == 0 ) return;
    bool sig = ((v & step) > 0);
    if (!tri[s].son[sig])
        tri[s].son[sig] =  ++ tot;
    ins(tri[s].son[sig],v, step >> 1);
}
int get(int s, long long v, long long step, long long now) {
    if (!tri[s].sum) return 0;
    long long last = step * 2;
    if (!last) last = 1;
    if (v / last != now / last)
        return tri[s].sum * (v / last < now / last);
    if (step == 0) return 0;
    return get(tri[s].son[0], v, step >> 1, now) + get(tri[s].son[1], v ^ step, step >> 1, now ^ step);
}
int main() {
    scanf("%d", &n);
    long long all = 0;
    tot = 1;
    for (int i= 1; i <= n; i ++) {
        long long x;
        scanf("%lld", &x);
        all ^= x;
        ins(1, x, maxn);
        printf("%d\n", get(1, all, maxn, 0));
    }
    return 0;
}