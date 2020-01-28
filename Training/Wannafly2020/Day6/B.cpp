#include<bits/stdc++.h>
#define pii pair<int, int>
#define fir first
#define sec second
using namespace std;
const int MAXN = 50 * 50 + 7;
const int MAXM = 507;
int n, m; 
vector<int>pt[MAXN];
pii edge[MAXM];
int col[MAXN], d[51], pre[MAXN], nxt[MAXN], cnt[MAXN];

int ecnt = 1, head[MAXN], vis[MAXN << 1];
struct node{int v, next;}e[MAXN << 1];
void add_edge(int u, int v)
{ 
    e[++ecnt] = {v, head[u]}; 
    vis[ecnt] = 0;
    head[u] = ecnt;
}
void add(int x, int y)
{
    if (x > y) swap(x, y);
    if (x + 1 == y || y % n + 1 == x) return;
    x = pt[x][cnt[x]++]; y = pt[y][cnt[y]++]; 
    add_edge(x, y); add_edge(y, x);
}
vector<int>s;
void dfs(int u)
{
    for (int &i = head[u]; i; i = e[i].next) 
    {
        if (vis[i] || vis[i ^ 1]) continue;
        vis[i] = vis[i ^ 1] = 1;
        int v = e[i].v;
        dfs(v);
    }
    if (!s.size() || col[u] != s[s.size() - 1]) s.push_back(col[u]);
}
int tot;
void G_init()
{
    for (int i = 1; i <= tot; i++) cnt[i] = head[i] = 0;
    ecnt = 1;
    for (int i = 1; i <= m; i++) add(edge[i].fir, edge[i].sec);
}
const int local = 1;
vector<vector<int> >ans;
int main()
{
    //if (local) freopen("sol.in", "r", stdin);
    int T; scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++) 
        {
            d[i] = 0, col[i] = i, pt[i].clear();
            pt[i].push_back(i);
        }
        for (int i = 1; i <= n; i++) pre[i] = i - 1, nxt[i] = i + 1; 
        pre[1] = n; nxt[n] = 1;
        for (int i = 1; i <= m; i++)
        {
            scanf("%d%d", &edge[i].fir, &edge[i].sec); 
            d[edge[i].fir]++; d[edge[i].sec]++;
        }
        tot = n;
        for (int i = 1; i <= n; i++)
            for (int j = 0, now = i; j < d[i] - 3; j++) 
            {
                pt[i].push_back(++tot); col[tot] = i;
                int nt = nxt[now];
                nxt[now] = tot; pre[tot] = now;
                nxt[tot] = nt; pre[nt] = tot; 
                now = tot;
            }
        ans.clear();
        G_init(); 
        for (int p = 1, cc = 1; cc <= tot; p = nxt[nxt[p]], cc += 2) add_edge(p, nxt[p]), add_edge(nxt[p], p);
        for (int i = 1; i <= tot; i++) if (head[i])
        {
            s.clear();
            dfs(i);
            s.pop_back(); ans.push_back(s);
        }
        G_init();
        for (int p = nxt[1], cc = 1; cc <= tot; p = nxt[nxt[p]], cc += 2) add_edge(p, nxt[p]), add_edge(nxt[p], p);
        for (int i = 1; i <= tot; i++) if (head[i])
        {
            s.clear();
            dfs(i);
            s.pop_back(); ans.push_back(s);
        }
        s.clear(); for (int i = 1; i <= n; i++) s.push_back(i);
        ans.push_back(s);
        printf("%d\n", (int)ans.size());
        for (auto vec : ans)
        {
            printf("%d", (int)vec.size());
            for (int x : vec) printf(" %d", x); puts("");
        }
    }
    return 0;
}