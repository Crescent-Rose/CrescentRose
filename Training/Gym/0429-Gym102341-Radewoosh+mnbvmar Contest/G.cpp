#include<bits/stdc++.h>
using namespace std;
const int MAXN = 20;
unordered_map<string, int>col;
bool vis[MAXN + 2];
int color[MAXN + 1], sg[1 << MAXN][MAXN + 1], cnt[1 << MAXN];
void solve()
{
    int n, res = 0; cin >> n;
    for (int i = 1; i <= n; i++) vis[i] = 0;
    string s;
    for (int i = 1; i <= n; i++) cin >> s, color[i] = col[s];
    for (int i = 1; i <= n; i++)
    {
        if (color[i] == 2) vis[i] = 1;
        else if (color[i] == 3) 
        {
            vis[i] = 1;
            if (i > 1 && color[i - 1] == 1 && !vis[i - 1]) res ^= 1;
            if (i < n && color[i + 1] == 1) res ^= 1;
            vis[i - 1] = vis[i + 1] = 1;
        }
    }
    int x = 0, len = 0;
    vis[n + 1] = 1;
    for (int i = 1; i <= n + 1; i++)
    {
        if (vis[i]) res ^= sg[x][len], len = x = 0;
        else x = x * 2 + color[i], len++; 
    }
    cout << (res ? "First" : "Second") << '\n';
}
int main()
{
    ios::sync_with_stdio(false); cin.tie(0);
    col["II."] = col[".II"] = 0; col["III"] = 1; 
    col["I.I"] = 2; col[".I."] = 3; 
    for (int len = 1; len <= 20; len++)
        for (int s = 0; s < (1 << len); s++)
        {
            for (int i = 0, tmp; i < len; i++) 
            {
                if (s >> i & 1) 
                {
                    cnt[sg[s ^ (1 << i)][len]]++;
                    cnt[sg[s >> (i + 1)][len - (i + 1)] ^ sg[s & ((1 << i) - 1)][i]]++;
                }
                else
                {
                    tmp = 0;
                    if (i && (s >> (i - 1) & 1)) tmp ^= 1; 
                    if (i != len - 1 && (s >> (i + 1) & 1)) tmp ^= 1;
                    tmp ^= sg[s >> (i + 2)][max(0, len - (i + 2))];
                    if (i) tmp ^= sg[s & ((1 << (i - 1)) - 1)][max(0, i - 1)];
                    cnt[tmp]++;
                }
            }
            int v = 0; while (cnt[v]) v++; sg[s][len] = v; // get sg
            for (int i = 0, tmp; i < len; i++) // clear cnt
            {
                if (s >> i & 1) 
                {
                    cnt[sg[s ^ (1 << i)][len]]--;
                    cnt[sg[s >> (i + 1)][len - (i + 1)] ^ sg[s & ((1 << i) - 1)][i]]--;
                }
                else
                {
                    tmp = 0;
                    if (i && (s >> (i - 1) & 1)) tmp ^= 1; 
                    if (i != len - 1 && (s >> (i + 1) & 1)) tmp ^= 1;
                    tmp ^= sg[s >> (i + 2)][max(0, len - (i + 2))];
                    if (i) tmp ^= sg[s & ((1 << (i - 1)) - 1)][max(0, i - 1)];
                    cnt[tmp]--;
                }
            }
        }
    int T; cin >> T;
    while (T--) solve();
    return 0;
}