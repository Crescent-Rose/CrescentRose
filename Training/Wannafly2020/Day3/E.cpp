#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 501;
bool a[N][N], tag[N][N];
int n, m;
int main() {
    int T;
    scanf("%d", &T);
    while (T --) {
        scanf("%d %d", &n, &m);
        for (int i = 1; i <= n ; i ++) {
            for (int j = 1; j <= m; j ++) {
                char c;
                scanf(" %c", &c);
                a[i][j] = c - '0';
                tag[i][j] = 0;
            }
        }
        bool sig = 0;
        for (int i = n; i >= 1; i --)
            for (int j = m; j >= 1; j --) {
                if (tag[i][j]) {
                    a[i][j] ^= 1;
                    tag[i -1][j] ^= 1;
                    tag[i -1][j - 1] ^= 1;
                    tag[i][j - 1] ^= 1;
                }
                sig ^= a[i][j];
                if (a[i][j]) {
                    tag[i -1][j] ^= 1;
                    tag[i -1][j - 1] ^= 1;
                    tag[i][j - 1] ^= 1;
                }
            }
        sig?puts("call"):puts("aoligei");
    }
    return 0;
}