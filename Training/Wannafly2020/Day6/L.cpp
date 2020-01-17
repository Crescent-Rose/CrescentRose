#include<bits/stdc++.h>
using namespace std;
const int MAXN = 107;
char mp[MAXN][MAXN];
struct node{int x, y, d;};
int dis[MAXN][MAXN], vis[MAXN][MAXN];
int dx[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};
int px[8] = {-1, 0, 0, 1, 1, 0, 0, -1};
int py[8] = {0, 1, 1, 0, 0, -1, -1, 0};
int n, m;
bool check(int x, int y)
{
    return (x >= 1 && x <= n && y >= 1 && y <= m && mp[x][y] != 'X');
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf(" %s", mp[i] + 1);
    queue<node>q;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            dis[i][j] = -1;
            if (mp[i][j] == 'M') q.push({i, j, 0});
        }
    while (q.size())
    {
        node u = q.front(); q.pop();
        if (vis[u.x][u.y]) continue;
        dis[u.x][u.y] = u.d; vis[u.x][u.y] = 1;
        for (int k = 0; k < 8; k++)
        {
            int nx = u.x + dx[k], ny = u.y + dy[k];
            if (vis[nx][ny]) continue;
            if (check(u.x + px[k], u.y + py[k]) && check(nx, ny))
            {
                q.push({nx, ny, u.d + 1});
            }
        }
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            printf("%d%c", dis[i][j], " \n"[j == m]);
    return 0;
}