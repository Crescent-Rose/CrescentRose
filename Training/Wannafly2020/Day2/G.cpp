#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
const int N = 1e5;
struct point{
    long long x, y;
    int sig;
    point(long long x = 0, long long y = 0, int sig = 0) :x(x),y(y), sig(sig) {
    }
}a[N];
int n, m;
point operator-(point a, point b){
    return point(a.x - b.x, a.y - b.y);
}
long long operator*(point a, point b) {
    return a.x * b.y - a.y * b.x;
}
long long cross(point a, point b, point c) {
    return (b - a) * (c - a);
}
bool operator==(point a, point b) {
    return a.x == b.x && a.y == b.y;
}
bool operator!=(point a, point b) {
    return a.x != b.x || a.y != b.y;
}
vector<point> convex(vector<point>& p){//返回凸包 keep_same_line设定是否保留三点共线
    vector<point> a = p;
    vector<point> d;
    sort(a.begin(), a.end(), [](const point&a, const point&b) {
        if (a.y == b.y) return a.x < b.x;
        return a.y < b.y;
    });
    int n = a.size();
    while (n>1&&a[n - 1]==a[n - 2])n--, a.pop_back();
    int tot=1;
    d.push_back(a[0]);
    for (int i=1;i < n;i++)
        if (a[i]!=a[i-1]){
            while (tot>=2&&cross(d[tot-2],d[tot-1],a[i])<=0)tot--, d.pop_back();
            d.push_back(a[i]);
            tot ++;
        }
    if (n>1) {
        int len = tot;
        ++tot;
        d.push_back(a[n - 2]);
        for (int i=n-3;i >= 0;i--)
            if (a[i]!=a[i+1]){
                while (len!=tot&&cross(d[tot-2],d[tot-1],a[i])<=0)tot--, d.pop_back();
                ++tot;
                d.push_back(a[i]);
            }
    }
    while (d[d.size() - 1] == d[0]) d.pop_back();
    return d;
}
vector<pair<int, int> > ans[2];
bool be(int x) {
    return x > n;
}
long long area(point a, point b, point c) {
    return abs(cross(a, b, c));
}
bool in(point a, point b, point c, point d) {
    return a != d && b != d && c != d && area(a, b, c) == area(a, b, d) + area(a, c, d) + area(b, c, d);
}
void work(point w, point v1, point v2) {
    for (int i = 1; i <= n + m; i ++)
        if (be(a[i].sig) == be(w.sig)  && in(w, v1, v2, a[i])) {
            ans[be(a[i].sig)].push_back(make_pair(a[i].sig - be(a[i].sig) *n, w.sig - be(w.sig) * n));
            work(v1, a[i], w);
            work(v2, a[i], w);
            work(a[i], v1,v2);
            return;
        }
    for (int i = 1; i <= n + m; i ++)
        if (in(w, v1, v2, a[i])) {
            ans[be(a[i].sig)].push_back(make_pair(a[i].sig - be(a[i].sig) *n, v1.sig - be(v1.sig) * n));
            work(a[i], v1, v2);
            work(w, a[i], v1);
            work(w, a[i], v2);
            return;
        }
}
int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n + m; i++){
        int x, y;
        scanf("%d %d", &x, &y);
        a[i] = point(x, y, i);
    }
    bool haveans = 1;
    while (1) {
        vector<point> d;
        for (int i = 1; i <= n + m ; i ++)
            if (a[i].sig)
                d.push_back(a[i]);
        vector<point> w = convex(d);
        if (w.size() == 1) break;
        int sum = 0;
        int st = -1, en = -1;
        for (int i = 0; i < w.size(); i ++){
            sum += (be(w[i].sig) != be(w[(i + 1) % w.size()].sig));
            if (be(w[i].sig) != be(w[(i + 1) % w.size()].sig)) {
                if (sum == 1)
                    st = i;
                else
                    en = i;
            }
        }
        if (sum > 2) {
            haveans = 0;
            break;
        }
        if (sum == 2) {
            for (int i = st + 1; i < en; i ++) {
                work(w[st], w[i], w[i + 1]);
                ans[be(w[i].sig)].push_back(make_pair(w[i].sig - be(w[i].sig) * n, w[i + 1].sig - be(w[i + 1].sig) * n));

            }
            for (int i = (en + 1) % w.size(); i != st; i = (i + 1) % w.size()) {
                work(w[en], w[i], w[(i + 1) % w.size()]);
                ans[be(w[i].sig)].push_back(make_pair(w[i].sig - be(w[i].sig) * n, w[(i + 1)%w.size()].sig - be(w[(i + 1)%w.size()].sig) * n));
            }
            break;
        } else {
            ans[be(w[0].sig)].push_back(make_pair(w[0].sig - be(w[0].sig) * n, w[1].sig - be(w[1].sig) * n));
            a[w[0].sig].sig = 0;
        }
    }
    if (!haveans) {
        puts("Poor Quailty");
        return 0;
    }
    for (auto u:ans[0])
        printf("%d %d\n", u.first, u.second);
    for (auto u:ans[1])
        printf("%d %d\n", u.first, u.second);
    return 0;
}