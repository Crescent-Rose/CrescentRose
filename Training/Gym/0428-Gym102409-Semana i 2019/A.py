x = 1
for i in range(50):
	x = x * 10
T = int(input())
for case in range(T):
	a, b, c = map(int, input().split(' '))
	res = (a * x + b * x) // c
	s1 = str(res // x)
	s2 = str(res % x)
	if len(s2) > 50:
		assert(False)
	while len(s2) < 50:
		s2 = '0' + s2
	print(s1 + "." + s2)