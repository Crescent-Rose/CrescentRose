#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n; scanf("%d", &n);
    printf("%d\n", n);
    for (int i = 1; i < n; i++) printf("%d %d\n", -i, i + 1);
    printf("%d %d\n", -n, -n);
    return 0;
}