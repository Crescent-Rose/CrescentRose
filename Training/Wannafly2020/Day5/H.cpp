#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll a[4][4];
ll cal()
{
    ll res = 0;
    res += a[1][1] * (a[2][2] * a[3][3] - a[2][3] * a[3][2]);
    res -= a[1][2] * (a[2][1] * a[3][3] - a[2][3] * a[3][1]);
    res += a[1][3] * (a[2][2] * a[3][2] - a[2][2] * a[3][1]);
    return res;
}
ll ans[4][4];
int main()
{
    
    a[1][1] = 1e6; a[1][2] = 1e6; a[1][3] = 0;
    a[2][1] = -1e6; a[2][2] = 0; a[2][3] = 1e6;
    a[3][1] = 0; a[3][2] = -1e6; a[3][3] = -1e6;
    ll now = 1e18;
    for (int dx1 = 0; dx1 <= 10; dx1++)
        for (int dx2 = 0; dx2 <= 10; dx2++)
            for (int dy1 = 0; dy1 <= 10; dy1++)
                for (int dy2 = 0; dy2 <= 10; dy2++)
                    for (int dz1 = 0; dz1 <= 10; dz1++)
                        for (int dz2 = 0; dz2 <= 10; dz2++)
                        {
                            a[1][1] -= dx1; a[1][2] -= dx2;
                            a[2][1] += dy1; a[2][3] -= dy2;
                            a[3][2] += dz1; a[3][3] += dz2;
                            ll temp = abs(cal()); 
                            if (temp < now && temp) 
                            {
                                now = temp;
                                for (int i = 1; i <= 3; i++)
                                    for (int j = 1; j <= 3; j++)   
                                        ans[i][j] = a[i][j];
                            }
                            a[1][1] += dx1; a[1][2] += dx2;
                            a[2][1] -= dy1; a[2][3] += dy2;
                            a[3][2] -= dz1; a[3][3] -= dz2;
                        }
    //printf("det = %lld\n", now);
    for (int i = 1; i <= 3; i++)
        for (int j = 1; j <= 3; j++)
            printf("%lld%c", ans[i][j], " \n"[j == 3]);
    return 0;
}
