#include<bits/stdc++.h>
#define ll long long
#define lson rt << 1
#define rson rt << 1 | 1
using namespace std;
const int MAXN = 2e5 + 7;
const int N = 2e5 + 1;
vector<int>p[MAXN], ft[MAXN];
int a[MAXN], n;
ll ans;
namespace segt
{
    ll sum[MAXN << 2], mx[MAXN << 2], lazy[MAXN << 2];
    void pushup(int rt)
    {
        sum[rt] = sum[lson] + sum[rson];
        mx[rt] = max(mx[lson], mx[rson]);
    }
    void build(int rt, int l, int r)
    {
        lazy[rt] = 0;
        if (l == r) {sum[rt] = mx[rt] = l; return;}
        int mid = (l + r) >> 1;
        build(lson, l, mid);
        build(rson, mid + 1, r);
        pushup(rt);
    }
    void upd(int rt, int l, int r, ll x) {mx[rt] = x; sum[rt] = x * (r - l + 1); lazy[rt] = x;}
    void pushdown(int rt, int l, int r)
    {
        if (!lazy[rt]) return;
        int mid = (l + r) >> 1;
        upd(lson, l, mid, lazy[rt]);
        upd(rson, mid + 1, r, lazy[rt]);
        lazy[rt] = 0;
    }
    void update(int rt, int l, int r, int L, int R, ll x)
    {
        if (L <= l && r <= R) {upd(rt, l, r, x); return;}
        int mid = (l + r) >> 1;
        pushdown(rt, l, r);
        if (L <= mid) update(lson, l, mid, L, R, x);
        if (mid <  R) update(rson, mid + 1, r, L, R, x);
        pushup(rt);
    }
    ll query(int rt, int l, int r, int L, int R)
    {
        if (L <= l && r <= R) return sum[rt];
        int mid = (l + r) >> 1; ll res = 0;
        pushdown(rt, l, r);
        if (L <= mid) res += query(lson, l, mid, L, R);
        if (mid <  R) res += query(rson, mid + 1, r, L, R);
        return res;
    }
    int gpos(int rt, int l, int r, ll x)
    {
        if (l == r) return l;
        pushdown(rt, l, r);
        int mid = (l + r) >> 1;
        if (mx[lson] > x) return gpos(lson, l, mid, x);
        else return gpos(rson, mid + 1, r, x);
    }   
    void print()
    {
        for (int i = 1; i <= n; i++) printf("%lld ", query(1, 1, n + 1, i, i));
        puts("");
    }
}
void alt(int l, int r, ll x, ll d)
{
    int L = l, R = min(r, segt::gpos(1, 1, n + 1, x) - 1);
    // printf(" alt:l = %d, r = %d, x = %lld\n", L, R, x);
    if (L > R) return;
    ll num = (x + 1) * (R - L + 1) - segt::query(1, 1, n + 1, L, R);
    // printf("num = %lld\n", num);
    ans += d * num;
    segt::update(1, 1, n + 1, L, R, x + 1);
    // segt::print();
}
void deal(int d)
{
    int sz = p[d].size();
    if (sz < 2) return;
    int l1 = p[d][1] + 1, r1 = p[d][sz - 2] - 1;
    int l2 = p[d][0] + 1, r2 = p[d][sz - 1] - 1;
    // printf("deal:d = %d, l1 = %d, r1 = %d, l2 = %d, r2 = %d\n", d, l1, r1, l2, r2);
    alt(l1, n, n, d);
    alt(l2, l1, r2, d);
    alt(1, l2, r1, d);
}
int main()
{
    for (int i = 1; i <= N; i++)
        for (int j = i; j <= N; j += i)
            ft[j].push_back(i);
    int T; scanf("%d", &T);
    while (T--)
    {
        ans = 0;
        scanf("%d", &n);
        for (int i = 1; i <= N; i++) p[i].clear();
        for (int i = 1; i <= n; i++) 
        {
            scanf("%d", &a[i]);
            for (int d : ft[a[i]]) p[d].push_back(i);
        }
        segt::build(1, 1, n + 1);
        for (int d = N; d >= 1; d--) deal(d);
        printf("%lld\n", ans);
    }
    return 0;
}