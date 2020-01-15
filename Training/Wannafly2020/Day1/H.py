T = int(input())
prime = []
for i in range(500):
    u = i + 1
    tag = 1
    for j in range(u):
        if j > 1 and u % j == 0:
           tag = 0
    if tag == 1:
        prime.append(u)
while T > 0:
    T -= 1
    n, k =input().split(' ')
    n = int(n)
    k = int(k)
    ans = 1
    for i in prime:
        if (i * k > n): 
            break
        ans *= i
    print(ans * k)