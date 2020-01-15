#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#define N 100001
using namespace std;

typedef double dbl;
const dbl pi = acos(-1), eps = 1e-8;
int sgn(dbl f) { return f < -eps ? -1 : f > eps; }

double read_dbl() { double d; scanf("%lf", &d); return d; }

struct vec { dbl x, y; };
vec operator+(vec v1, vec v2) { return { v1.x + v2.x, v1.y + v2.y }; }
vec operator-(vec v1, vec v2) { return { v1.x - v2.x, v1.y - v2.y }; }
dbl operator*(vec v1, vec v2) { return v1.x * v2.x + v1.y * v2.y; }
dbl operator^(vec v1, vec v2) { return v1.x * v2.y - v1.y * v2.x; }
vec operator*(vec v, dbl k) { return { v.x * k, v.y * k }; }
vec operator/(vec v, dbl k) { return { v.x / k, v.y / k }; }
bool operator<(vec v1, vec v2) { return v1.x == v2.x ? v1.y < v2.y : v1.x < v2.x; }
bool operator==(vec v1, vec v2) { return sgn(v1.x - v2.x) == 0 && sgn(v1.y - v2.y) == 0; }

dbl dot(vec v0, vec v1, vec v2) { return (v1 - v0) * (v2 - v0); }
dbl crx(vec v0, vec v1, vec v2) { return (v1 - v0) ^ (v2 - v0); }
dbl len(vec v) { return hypot(v.x, v.y); }
dbl len2(vec v) { return v * v; }
vec t90(vec v) { return { v.y, -v.x }; }
vec unif(vec v) { return v / len(v); }

int convex_hull(vec* p, int n, vec* c) {
    sort(p + 1, p + n + 1);
    n = unique(p + 1, p + n + 1) - p - 1;
    int m = 0;
    c[1] = p[++m];
    for (int i = 1; i <= n; ++i) {
        while (m > 1 && sgn(crx(c[m - 1], c[m], p[i])) != 1) m--;
        c[++m] = p[i];
    }
    int t = m;
    for (int i = n - 1; i; --i) {
        while (m > t && sgn(crx(c[m - 1], c[m], p[i])) != 1) m--;
        c[++m] = p[i];
    }
    if (m > 1) m--;
    c[m + 1] = c[1];

    return m;
}

struct cir { vec o; dbl r; };

bool cptan(cir c, vec p, vec& p1, vec& p2) {
    dbl x = (p - c.o) * (p - c.o), y = x - c.r * c.r;
    if (y < eps) return false;
    vec o = (p - c.o) * (c.r * c.r / x);
    vec d = t90((p - c.o) * (-c.r * sqrt(y) / x));
    o = o + c.o; p1 = o +d; p2 = o - d;
    return true;
}

bool ccetan(cir c1, cir c2, vec& p11, vec& p12, vec& p21, vec& p22) {
    if (!sgn(c1.r - c2.r)) {
        vec v = t90(unif(c1.o - c2.o) * c1.r);
        p11 = c1.o + v; p12 = c1.o - v;
        p21 = c2.o + v; p22 = c2.o - v;
        return true;
    }
    else {
        vec p = (c2.o * c1.r - c1.o * c2.r) / (c1.r - c2.r);
        if (cptan(c1, p, p11, p12) && cptan(c2, p, p21, p22))
            return true;
        return false;
    }
}

dbl arc(cir c, vec p1, vec p2) {
    dbl res, w = crx(c.o, p1, p2);
    dbl l1 = len(p1 - c.o), l2 = len(p2 - c.o);
    if (sgn(w) == 0)
        res = c.r * pi;
    else if (sgn(w) > 0) {
        res = c.r * acos(((p1 - c.o) * (p2 - c.o)) / (l1 * l2));
    }
    else {
        res = c.r * (2 * pi - acos(-((p1 - c.o) * (p2 - c.o)) / (l1 * l2)));
    }
    return res;
}

bool contain(cir c1, cir c2) {
    if (c1.r < c2.r) return false;
    if (sgn(len2(c1.o - c2.o) + (c2.r - c1.r)*(c2.r - c1.r)) <= 0) return true;
    return false;
}

bool oncir(cir c, vec p) { return !sgn((p - c.o)*(p - c.o) - c.r*c.r); }

cir cs[N]; bool del[N];

vec pv[N], cv[N];

int k0;

bool chk(const vector<int>& idx, vec p) {
    for (int i : idx) if (len(cs[i].o - p) < cs[i].r - eps)
        return false;
    return true;
}

int main() {
    //fn();
    //freopen("2.in", "r", stdin);
    //FILE* fans = fopen("9.out", "r");
    int T; scanf("%d", &T);
    while (T--) {
        int k; scanf("%d", &k); k0 = k;
        for (int i = 1; i <= k; ++i) del[i] = false;
        for (int i = 1; i <= k; ++i) {
            cs[i].o.x = read_dbl();
            cs[i].o.y = read_dbl();
            cs[i].r = read_dbl();
        }
        for (int i = 1; i <= k; ++i)
            for (int j = i + 1; j <= k; ++j) {
                bool f1 = contain(cs[i], cs[j]);
                bool f2 = contain(cs[j], cs[i]);
                if (f1 && f2) del[i] = 1;
                else {
                    if (f1) del[j] = 1;
                    if (f2) del[i] = 1;
                }
            }
        vector<int> idx;
        for (int i = 1; i <= k; ++i)
            if (!del[i]) idx.push_back(i);
        double res;
        if (idx.size() == 1) {
            res = (2 * pi * cs[idx[0]].r);
        }
        else {
            k = idx.size();
            int n = 0;
            for (int i = 0; i != k; ++i) {
                for (int j = i + 1; j < k; ++j) {
                    vec p11, p12, p21, p22;
                    if (!ccetan(cs[idx[i]], cs[idx[j]], p11, p12, p21, p22))
                        continue;
                    if (chk(idx, p11)) pv[++n] = p11;
                    if (chk(idx, p12)) pv[++n] = p12;
                    if (chk(idx, p21)) pv[++n] = p21;
                    if (chk(idx, p22)) pv[++n] = p22;
                }
            }
            int m = convex_hull(pv, n, cv); cv[m + 2] = cv[2];

            dbl sum = 0;
            for (int i = 1; i <= m; ++i) {
                bool ff = false;
                cir cc;
                for (int j : idx) {
                    cc = cs[j];
                    if (oncir(cc, cv[i]) && oncir(cc, cv[i + 1])) {
                        ff = true;
                        break;
                    }
                }
                if (ff)
                    sum += arc(cc, cv[i], cv[i + 1]);
                else
                    sum += len(cv[i + 1] - cv[i]);
            }
            res = sum;
        }
//        double ans;
//        fscanf(fans, "%lf", &ans);
        printf("%.10f\n", (double)(res));
    }
    return 0;
}
