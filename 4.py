import math
x = int(input())
a = x // 1000
b = x % 1000 // 100
c = x % 100 // 10
d = x % 10
sum=(math.cos(a)+math.cos(b)+math.cos(c)+math.cos(d))
print(a,b,c,d)
print(sum)