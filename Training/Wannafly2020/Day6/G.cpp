#include <algorithm>
#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;
const int N = 1e4;
priority_queue<int>q;
int n, T;
int a[N];
vector<int >g[N];
int du[N], d[N];
void add(int x, int y){
    du[y] ++;
    g[x].push_back(y);
}
int main() {
    scanf("%d", &T);
    while (T --) {
        scanf("%d", &n);
        int mx = 0;
        for (int i = 1; i <= n ;i ++) {
            scanf("%d", &a[i]);
            if (a[i] == -1) a[i] = mx + 1;
            mx = max(mx, a[i]);
        }
        memset(du, 0, sizeof(du));
        for (int i = 1; i <= n; i ++)
            for (int j = i + 1; j <= n; j++)
                if (a[i] < a[j] || (a[i] == a[j] && i > j))
                    add(i, j);
                else
                    add(j, i);
        for (int i = 1; i <= n; i++)
            if (!du[i])
                q.push(-i);
        d[0] = 0;
        while (!q.empty()) {
            int x = -q.top();
            q.pop();
            d[x] = ++d[0];
            for (auto u:g[x])
                if (!(--du[u]))
                    q.push(-u);
        }
        for (int i= 1; i <= n; i ++)
            printf("%d%c", d[i], " \n"[i ==n]);
        for (int i = 1; i <= n; i ++)
            g[i].clear();
    }
    return 0;
}