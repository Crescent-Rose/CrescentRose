#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 1e4;
bool bz[N];
int n, T, a, b, c, d;
//a ぱ籵 b 吤嗎 c 陸當 d 吤嗎陸當
int workmx(int a, int b, int c, int d) {
    int sum = 0;
    for (int i = 1; i <= n; i ++)
        if (bz[i]) {
            if (c || d) {
                if (c) {
                    c --;
                    sum ++;
                } else {
                    d --;
                    c ++;
                }
            } else
                if (a) {
                    a --;
                    sum ++;
                } else
                    if (b) {
                        b --;
                        a ++;
                    }
        } else {
            if (c || d) {
                if (d) {
                    d --;
                    c ++;
                }
            } else
                if (b) {
                    b --;
                    a ++;
                }
        }
    return sum;
}
//a ぱ籵 b 吤嗎 c 陸當 d 吤嗎陸當
int workmn(int a, int b, int c, int d) {
    int sum = 0;
    for (int i = 1; i <= n; i ++)
        if (bz[i]) {
            if (c || d) {
                if (d) {
                    d --;
                    c ++;
                } else {
                    c --;
                    sum ++;
                }
            } else
            if (b) {
                b --;
                a ++;
            } else
            if (a) {
                a --;
                sum ++;
            }
        } else {
            if (c || d) {
                if (!c) {
                    d --;
                    c ++;
                }
            } else
                if (!a && b) {
                    b --;
                    a ++;
                }
        }
    return sum;
}
int main() {
    int T;
    scanf("%d", &T);
    while (T --) {
        scanf("%d %d %d %d %d", &n, &a, &b, &c, &d);
        for (int i = 1; i <= n; i ++) {
            char c;
            scanf(" %c", &c);
            bz[i] = c - '0';
        }
        printf("%d %d\n", workmx(a, b, c, d), workmn(a, b, c, d));
    }
}