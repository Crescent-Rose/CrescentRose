#include <bits/stdc++.h>
using namespace std;

int m[2001][2001], a[2001][2001], cnt, maxcnt;

int query(int x, int y) {
    int& d = m[x][y];
    if (!d) {
        printf("? %d %d\n", x, y);
        fflush(stdout);
        //d = a[x][y];
        scanf("%d", &d);
        cnt++;
        assert(cnt <= maxcnt);
    }
    return d;
}

void answer(int x, int y) {
    printf("! %d %d\n", x, y);
    //printf("%d\n", cnt);
    fflush(stdout);
    exit(0);
}

int xx = -1, yy = -1, vv = -1;

void solve(int x1, int y1, int x2, int y2, int n) {
    if (x1 == x2 && y1 == y2)
        answer(x1, y1);
    else if (x2 - x1 > y2 - y1) {
        int x = (x2 + x1) >> 1, y = -1, v = -1;
        for (int j = y1; j <= y2; ++j)
            if (query(x, j) > v)
                v = m[x][j], y = j;
        for (int i = max(x1, x - 1); i <= min(x + 1, x2); ++i)
            for (int j = max(y1, y - 1); j <= min(y + 1, y2); ++j)
                if (query(i, j) > vv)
                    vv = m[i][j], xx = i, yy = j;
        if (xx == x)
            answer(xx, yy);
        else if (xx < x)
            solve(x1, y1, x - 1, y2, n);
        else 
            solve(x + 1, y1, x2, y2, n);        
    }
    else {
        int y = (y1 + y2) >> 1, x = -1, v = -1;
        for (int i = x1; i <= x2; ++i)
            if (query(i, y) > v)
                v = m[i][y], x = i;
        for (int i = max(x1, x - 1); i <= min(x + 1, x2); ++i)
            for (int j = max(y1, y - 1); j <= min(y + 1, y2); ++j)
                if (query(i, j) > vv)
                    vv = m[i][j], xx = i, yy = j;
        if (yy == y)
            answer(xx, yy);
        else if (yy < y)
            solve(x1, y1, x2, y - 1, n);
        else 
            solve(x1, y + 1, x2, y2, n);
    }
}

int main(void) {
    int n; scanf("%d", &n);
    maxcnt = 3 * n + 210;
    /*
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            scanf("%d\n", &a[i][j]);
    //*/
    solve(1, 1, n, n, n);
    return 0;
}