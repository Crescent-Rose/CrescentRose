#include <algorithm>
#include <cstdio>
#include <vector>
#include <cstring>
#include <cctype>
using namespace std;
const int N = 1e6 + 10;
const int S = 22;
int T;
char s[N];
bool f[N * 4 * 2];
int a[N * 2][2];
struct node{
    int fail[1], son[26], len;
    void clear(){
        memset(fail, 0, sizeof(fail));
        memset(son, 0, sizeof(son));
        len = 0;
    }
}tri[N * 2];
int lst[N], L, n, l[N * 2], cnt, r[N * 2];
void clear() {
    while (L) {
        tri[L].clear();
        L --;
    }
    tri[0].clear();
    L = 1;
    lst[0] = 1;
}
int add(int last, int c) {
    static int v, u, up, up1;
    v = ++L;
    u = last;
    tri[v].len = tri[u].len + 1;
    for (;u&&!tri[u].son[c];u=tri[u].fail[0]) tri[u].son[c] = v;
    if (!u) tri[v].fail[0] = 1;
    else {
        up = tri[u].son[c];
        if (tri[up].len == tri[u].len + 1) tri[v].fail[0] = up;
        else {
            up1 = ++ L;
            tri[up1] = tri[up];
            tri[up1].len = tri[u].len + 1;
            tri[up].fail[0] = tri[v].fail[0] = up1;
            for (;u&&tri[u].son[c]== up; u = tri[u].fail[0]) tri[u].son[c] = up1;
        }
    }
    return v;
}
namespace IO {
    const int BUF_SIZE = 1 << 15;
    char in_buf[BUF_SIZE], out_buf[BUF_SIZE];
    char *p_in_buf = in_buf + BUF_SIZE;
    char *p_out_buf = out_buf;
    inline char get_char() {
        if (p_in_buf == in_buf + BUF_SIZE) {
            fread(in_buf, 1, BUF_SIZE, stdin), p_in_buf = in_buf;
        }
        return *(p_in_buf++);
    }
    inline void put_char(char x) {
        if (p_out_buf == out_buf + BUF_SIZE) {
            fwrite(out_buf, 1, BUF_SIZE, stdout), p_out_buf = out_buf;
        }
        *(p_out_buf++) = x;
    }
    inline void flush() {
        if (p_out_buf != out_buf) {
            fwrite(out_buf, 1, p_out_buf - out_buf, stdout);p_out_buf = out_buf;
        }
    }
}
#define getchar() IO::get_char()
#define putchar(x) IO::put_char(x)
inline int getint() {
    int x = 0;
    char c = getchar();
    while (c <= 32) c = getchar();
    while (c > 32) x = x * 10 + c - 48, c = getchar();
    return x;
}
inline int getint(char &c) {
    int x = 0;
    c = getchar();
    while (!isdigit(c)) c = getchar();
    while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
    return x;
}
template <class T>
inline void _putint(T x) {
    return x ? _putint(x / 10), putchar(48 + x % 10), void() : void();
}
template <class T>
inline void putint(T x) {
    return x == 0 ? putchar('0'), void() : _putint(x), void();
}
inline void getline(char *s) {
    char c = getchar();
    while (c == '\n') c = getchar();
    while (c != '\n') *(s++) = c, c = getchar();
    *s = 0;
}
inline void getstring(char * s) {
    while (!((s[0] = getchar()) >= 'a' && s[0] <= 'z'));
    while (1) {
        s ++;
        s[0] = getchar();
        if (s[0] > 'z' || s[0] < 'a') {
            s[0] = 0;
            return;
        }
    }
}
int ans[N];
int main() {
   // freopen("input", "r", stdin);
    //int T = 5;
    T = getint();
    //for (int i = 1; i <= 1e6; i ++) s[i] = 'a';
    while (T --) {
        getstring(s + 1);
        clear();
        n = strlen(s + 1);
        for (int i = 1; i <= n; i ++)
            lst[i] = add(lst[i - 1], s[i] -= 'a'), ans[i] = max(tri[tri[lst[i]].fail[0]].len, ans[i - 1]);
        cnt = 0;
        bool have_zero = 1;
        int c = -1;
        for (int i = 1; i <= n; i ++) {
            if (s[i] != c && c != -1) {
                have_zero = 0;
            } else
                c = s[i];
            !have_zero?printf("%d%c", ans[i] + 1, " \n" [i ==n]):printf("0%c"," \n"[i == n]);
        }
    }
    return 0;
}