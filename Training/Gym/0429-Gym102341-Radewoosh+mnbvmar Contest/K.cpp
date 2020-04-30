#include <bits/stdc++.h>
using namespace std;

const int N = 300005;

int f[N];
char s[N];

namespace LCT {

int ch[3][N], *ls = ch[0], *rs = ch[1], *fa = ch[2];
int val[N], tag[N];

inline int id(int x) { return rs[fa[x]] == x; }
inline int isr(int x) { return ch[id(x)][fa[x]] != x; }

void update(int p, int t) {
    val[p] += t;
    tag[p] += t;
}

void push_down(int p) {
    if (!tag[p]) return;
    if (ls[p]) update(ls[p], tag[p]);
    if (rs[p]) update(rs[p], tag[p]);
    tag[p] = 0;
}

void rot(int x) {
    int y = fa[x], z = fa[y], o = id(x), w = ch[!o][x];
    if (!isr(y)) ch[id(y)][z] = x; fa[x] = z;
    ch[!o][x] = y; fa[y] = x;
    ch[o][y] = w; if (w) fa[w] = y;
}

void splay(int x) {
    static int s[N], t, z; s[++t] = (z = x);
    while (!isr(z)) s[++t] = (z = fa[z]);
    while (t) push_down(s[t--]);
    for (int y; !isr(x); rot(x))
        if (!isr(y = fa[x])) rot(id(x)^id(y)?x:y);
}

void access(int x) {
    for (int y = 0; x; x = fa[y = x]) 
        splay(x), rs[x] = y;
}

void link(int x, int y) {
    //printf("Link %d %d\n", x, y);
    access(x);
    splay(x);
    fa[y] = x;
}

}

int main(void) {
    int q, n = 0; scanf("%d", &q);
    f[0] = -1;
    int last = 0;
    while (q--) {
        char t[4]; scanf("%s", t);
        if (t[0] == 'a') {
            char O[2]; scanf("%s", O);
            char o = ((O[0] - 'a') + last) % 26 + 'a';
            s[++n] = o;
            
            int p = f[n - 1];
            while (p != -1 && s[p + 1] != s[n]) p = f[p];
            ++p;
            //printf("%d %c %d\n", n, o, p);
            f[n] = p;
            LCT::link(p + 1, n + 1);
            LCT::access(n + 1); 
            LCT::splay(n + 1);
            LCT::update(n + 1, 1);

        }
        else {
            int k; scanf("%d", &k);
            k = (k - 1 + last) % n + 1;
            LCT::access(k + 1); LCT::splay(k + 1);
            printf("%d\n", last = LCT::val[k + 1]);
        }
    }
    return 0;
}