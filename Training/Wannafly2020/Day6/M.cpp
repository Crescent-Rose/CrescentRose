#include<bits/stdc++.h>
using namespace std;
const int MAXN = 107;
const int MAXM = 17; 
vector<int>vec[MAXN][MAXM];
set<int>ACpro[MAXN];
int haveAC[MAXM], ACnum[MAXM], subnum[MAXN];
int ans[MAXN];
int main()
{
    int n, m, W; scanf("%d%d%d", &n, &m, &W);
    for (int i = 1, x, y, c; i <= W; i++)
    {
        scanf("%d%d%d", &x, &y, &c);
        vec[x][y].push_back(c);
        if (c == 1) 
        {
            ACpro[x].insert(y);
            haveAC[y] = 1;
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++) subnum[i] += vec[i][j].size();
        for (int x : ACpro[i]) ACnum[x]++;
    }
    

    for (int i = 1; i <= n; i++)
    {
        if (!subnum[i]) {ans[i] = 998244353; continue;} // Rule 1
        if (!ACpro[i].size()) {ans[i] = 1000000; continue;} // Rule 2
        if (ACpro[i].size() == m) {ans[i] = 0; continue;} // Rule 3
        for (int j = 1; j <= m; j++) if (ACpro[i].find(j) == ACpro[i].end()) 
        {
            if (haveAC[j])
            {
                ans[i] += 20; // Rule 4
                if (ACnum[j] >= n / 2) ans[i] += 10; // Rule 5
            }
        }
        for (int j = 1; j <= m; j++)
        {
            int maxK = 0;
            int K = 0;
            for (int k = 0; k < vec[i][j].size(); k++)
            { // Rule 6
                int c = vec[i][j][k];
                if (c == 1) 
                {
                    maxK = max(maxK, K);
                    K = 0;
                }
                else K++;
            }
            maxK = max(maxK, K);
            ans[i] += maxK * maxK;
            if (ACpro[i].find(j) == ACpro[i].end()) ans[i] += maxK * maxK; // Rule 7
        }
    }
    for (int i = 1; i <= n; i++) printf("%d\n", ans[i]);
    return 0;
}