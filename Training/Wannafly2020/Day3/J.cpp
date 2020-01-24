#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
const int N = 1e6;
pair<int, int> f[N];
char s[N];
int q, n;
void Lyndon_depress(char *s, int n){//f[i].first 存的是i开始的Lyndon分解串的第一个串的长度，f[i].second存的是这类串的个数
    memset(f, 0, sizeof(f));
    for (int i = 0; i < n; i ++)
        if (!f[i].first) {
            int j = i + 1, k = i;
            while (j < n && s[j] >= s[k]) {
                if (s[j] > s[k])
                    k = i;
                else
                    k ++;
                j ++;
            }
            int ii = i;
            int sum = (k - i) / (j - k) + 1;
            while (ii <= k) {
                f[ii].first = j - k;
                f[ii].second = sum --;
                ii += j - k;
            }
        }
}
int main() {
    scanf("%s %d", s, &q);
    n = strlen(s);
    Lyndon_depress(s, n);
    while (q --) {
        int l, k;
        scanf("%d %d", &l, &k);
        l --;
        if (f[l].second < k) {
            printf("%d %d\n", l +1, f[l].first + l);
        }else if (f[l].second % k == 0) {
            if (f[l].second * f[l].first == n - l){
                int tmp = f[l].second / k;
                printf("%d %d\n", l + 1, l + tmp * f[l].first);
            } else {
                int tmp = f[l].second / k;
                int r = l + f[l].second * f[l].first;
                printf("%d %d\n", r - tmp * f[l].first + 1, n);
            }
        } else {
            int tmp = f[l].second / k + 1;
            printf("%d %d\n", l + 1, l + tmp * f[l].first);
        }
    }
    return 0;
}