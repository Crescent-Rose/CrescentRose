#include <iostream>

using namespace std;

int a[100001];

int main() {
    int n; scanf("%d", &n);
    int l = 1, r = n;
    for (int i = 1; i <= n; ++i) {
        if (i & 1) a[l++] = i;
        else a[r--] = i;
    }
    for (int i = 1; i <= n; ++i)
        printf("%d ", a[i]);
    return 0;
}
