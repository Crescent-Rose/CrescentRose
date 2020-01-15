#include <algorithm>
#include <cstdio>
#include <vector>
#include <stack>
#define tag tag233
using namespace std;
const int N = 2e5 + 10;
bool havetag[N * 4];
int tag[N * 4];
struct node{
    int son[2];
    int sum;
}f[N * 200];
struct node1 {
    int sig, l, r, k;
}q[N];
int tot;
int n, m;
int a[N], b[N * 4];
void downb(int l, int r, int s) {
    if (!f[s].sum && l != r) {
        f[f[s].son[0]].sum = f[f[s].son[1]].sum = 0;
    }
}
void ins(int l, int r, int s, int ll, int sum) {
    downb(l, r, s);
    f[s].sum += sum;
    if (l == r) return;
    if (b[(l + r) / 2] >= ll) {
        if (!f[s].son[0]) f[s].son[0] = ++ tot;
        ins(l, (l  + r) / 2, f[s].son[0], ll, sum);
    } else {
        if (!f[s].son[1]) f[s].son[1] = ++tot;
        ins((l + r) / 2 + 1, r, f[s].son[1], ll, sum);
    }
}
void build(int l, int r, int s) {
    for (int i = l ; i <= r; i ++)
        ins(1, b[0], s, a[i], 1);
    if (l == r) return;
    build(l, (l + r) / 2, s + s);
    build((l + r) / 2 + 1, r, s + s + 1);
}
vector<int> st;
int get_bigger_and_kill(int l, int r, int s, int ll) {
    downb(l, r, s);
    if (b[r] <= ll || !f[s].sum) return 0;
    if (ll < b[l]) {
        int tmp = f[s].sum;
        f[s].sum = 0;
        return tmp;
    }
    int x = get_bigger_and_kill(l, (l + r) / 2, f[s].son[0], ll) + get_bigger_and_kill((l + r) / 2 + 1, r, f[s].son[1], ll);
    f[s].sum = f[f[s].son[0]].sum + f[f[s].son[1]].sum;
    return x;
}
void down(int l, int r, int s) {
    if (havetag[s]) {
        int v = get_bigger_and_kill(1, b[0], s, tag[s]);
        if (v)ins(1, b[0], s, tag[s], v);
        if (l != r && v) {
            if (!havetag[s+s] || tag[s+s] > tag[s])
                tag[s+s]=tag[s], havetag[s+s] = 1;
            if (!havetag[s+s+1] || tag[s+s+1] > tag[s])
                tag[s+s+1]=tag[s], havetag[s+s+1] = 1;
        }
        havetag[s] = 0;
    }
}
int all = 0;
vector<pair<int, int> > d;
void search(int l, int r, int s, int ll) {
    downb(l, r, s);
    if (b[r] <= ll || !f[s].sum) return;
    if (l == r) {
        d.push_back(make_pair(b[l], f[s].sum));
        all += f[s].sum;
        return;
    }
    search(l, (l + r) / 2, f[s].son[0], ll);
    search((l+r) / 2 + 1, r, f[s].son[1], ll);
}
void change(int l, int r, int s, int ll, int rr, int v) {
    down(l, r, s);
    if (r < ll || rr < l) return;
    if (ll <= l && r <= rr) {
        d.clear();
        all = 0;
        search(1, b[0], s, v);
        for (auto u:d) {
            for (auto v:st)
                ins(1, b[0], v, u.first, -u.second);
        }
        if (all)
            for (auto w:st)
                ins(1, b[0], w, v, all);
        if (all) {
            havetag[s] = 1;
            tag[s] = v;
        }
        return;
    }

    st.push_back(s);
    change(l, (l + r) / 2, s + s, ll, rr, v);
    change((l + r) / 2 + 1, r, s + s + 1, ll, rr, v);
    st.pop_back();
}
void get(int l, int r, int s, int ll, int rr) {
    down(l, r, s);
    if (r < ll || rr < l) return;
    if (ll <= l && r <= rr) {
        st.push_back(s);
        return;
    }
    get(l, (l + r) / 2, s + s, ll, rr);
    get((l + r) /2 + 1, r, s + s + 1, ll, rr);
}
int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n ; i ++)
        scanf("%d", &a[i]), b[++b[0]] = a[i];
    for (int i = 1; i <= m ; i ++) {
        scanf("%d %d %d %d", &q[i].sig, &q[i].l, &q[i].r, &q[i].k);
        if (q[i].sig == 1) {
            b[++b[0]] = q[i].k;
        }
    }
    sort(b + 1, b + b[0] + 1);
    int x = b[0];
    b[0] = 1;
    for (int i = 2; i <= x; i ++)
        if (b[i] != b[b[0]])
            b[++b[0]] = b[i];
    tot = n * 4;
    build(1, n, 1);
    for (int i = 1; i <= m; i ++)
        if (q[i].sig == 1){
            change(1, n, 1, q[i].l, q[i].r, q[i].k);
        } else {
            st.clear();
            get(1, n ,1, q[i].l, q[i].r);
            int l = 1, r = b[0];
            while (l != r) {
                int sum = 0;
                for (auto u :st) {
                    downb(l, r, u);
                    sum += f[f[u].son[0]].sum;
                }
                if (sum >= q[i].k) {
                    for (int i =0 ;i < st.size(); i ++)
                        st[i] = f[st[i]].son[0];
                    r = (l + r ) / 2;
                } else {
                    for (int i =0 ;i < st.size(); i ++)
                        st[i] = f[st[i]].son[1];
                    q[i].k -= sum;
                    l = (l + r) / 2 + 1;
                }
            }
            st.clear();
            printf("%d\n", b[l]);
        }
    return 0;
}