#include<bits/stdc++.h>
using namespace std;
multiset<int>s;
char a[20];
int sum[1 << 20];
void deal(int m)
{
	for (int sta = 0; sta < (1 << m); sta++)
	{
		int tot = a[m]; 
		for (int j = 0; j < m; j++) if (sta >> j & 1) tot += a[j];
		s.erase(s.find(tot));
	}
}
int main()
{
	int n; scanf("%d", &n);
	for (int i = 0; i < (1 << n); i++) 
	{
		int x; scanf("%d", &x);
		s.insert(x);
	}
	s.erase(s.find(0));
	a[0] = *s.begin(); s.erase(s.find(a[0]));
	if (n == 1) 
	{
		printf("%c\n", a[0]);
		return 0;
	}
	a[1] = *s.begin(); s.erase(s.find(a[1])); s.erase(s.find(a[0] + a[1]));
	if (n == 2)
	{
		printf("%c%c\n", a[0], a[1]);
		return 0;
	}
	for (int i = 2; i < n; i++)
	{
		a[i] = *s.begin();
		deal(i);
	}
	for (int i = 0; i < n; i++) printf("%c", a[i]);
	return 0;
}