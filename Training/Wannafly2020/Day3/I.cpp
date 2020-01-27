#include<bits/stdc++.h>
#define ldb long double
#define db double
using namespace std;

#define MAX 1000000007
#define LL __int128
const int N = 50005;

LL a[N], m[N];

LL gcd(LL a,LL b){
    return b? gcd(b, a % b) : a;
}

void extend_Euclid(LL a, LL b, LL &x, LL &y){
    if(b == 0){
        x = 1;
        y = 0;
        return;
    }
    extend_Euclid(b, a % b, x, y);
    LL tmp = x;
    x = y;
    y = tmp - (a / b) * y;
}

LL Inv(LL a, LL b){
    LL d = gcd(a, b);
    if(d != 1) return -1;
    LL x, y;
    extend_Euclid(a, b, x, y);
    return (x % b + b) % b;
}

bool merge(LL a1, LL m1, LL a2, LL m2, LL &a3, LL &m3){
    LL d = gcd(m1, m2);
    LL c = a2 - a1;
    if(c % d) return false;
    c = (c % m2 + m2) % m2;
    m1 /= d;
    m2 /= d;
    c /= d;
    c *= Inv(m1, m2);
    c %= m2;
    c *= m1 * d;
    c += a1;
    m3 = m1 * m2 * d;
    a3 = (c % m3 + m3) % m3;
    return true;
}

LL CRT(LL a[], LL m[], int n){
    LL a1 = a[1];
    LL m1 = m[1];
    for(int i=2; i<=n; i++){
        LL a2 = a[i];
        LL m2 = m[i];
        LL m3, a3;
        if(!merge(a1, m1, a2, m2, a3, m3))
            return -1;
        a1 = a3;
        m1 = m3;
    }
    return (a1 % m1 + m1) % m1;
}
db f[105][105][105];
int main()
{
    f[2][2][1] = 0.5;
    f[2][1][1] = 1;
    f[2][1][2] = 0;
    for (int i = 3; i <= 15; i++)
        for (int j = 1; j <= i; j++)
            for (int k = 1; k <= i - j + 1; k++)
            {
                if (k == 1)
                {
                    if (j == 1) f[i][j][k] = f[i - 1][1][i - 1];
                    else 
                    {
                        db part1 = 1.0 / j * f[i - 1][j - 2][i - j + 2] + (1 - 1.0 / j) * f[i - 1][j - 2][1];
                        db part2 = 1.0 / j * f[i - 1][j - 1][i - j + 1] + (1 - 1.0 / j) * f[i - 1][j - 1][1];
                        if (i == j) f[i][j][k] = part1;
                        else if (j == 2) f[i][j][k] = part2;
                        else f[i][j][k] = min(part1, part2);
                    }
                }
                else
                {
                    if (j == 1) 
                    {
                        if (k == 2) f[i][j][k] = f[i - 1][1][k - 1];
                        else if (k == i - j + 1) f[i][j][k] = f[i - 1][1][k - 2];
                        else f[i][j][k] = min(f[i - 1][1][k - 2], f[i - 1][1][k - 1]);
                    }
                    else
                    {
                        db part1 = f[i - 1][j - 2][k];
                        db part2 = f[i - 1][j - 1][k - 1];
                        db part3 = f[i - 1][j - 1][k];
                        db part4 = f[i - 1][1][k - 1];
                        if (j == i - 1) 
                        {
                            if (j == 2) f[i][j][k] = part4;
                            else f[i][j][k] = part1;
                        }
                        else if (k == i - j + 1) f[i][j][k] = part2;
                        else 
                        {
                            if (j == 2) if (j == 2) f[i][j][k] = min(min(part4, part2), part3);
                            f[i][j][k] = min(min(part1, part2), part3);
                        }
                    }
                }
            }
    //for (int i = 2; i <= 15; i++) printf("%.6lf\n", f[i][i][1]);
    int n; scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%lld%lld", &a[i], &m[i]);
    LL ans = CRT(a, m, n);
    if (ans == -1 || ans < 2) puts("error");
    else 
    {
        if (ans <= 15) printf("%.6lf\n", f[ans][ans][1]);
        else puts("0.000000");
    }
    return 0;
}