import math
x = abs(int(input('Введите значение x: ')))
a = x // 1000
b = x % 1000 // 100
c = x % 100 // 10
d = x % 10
sum = (math.cos(a)+math.cos(b)+math.cos(c)+math.cos(d))
print('Цифры введенного числа x:',a,b,c,d)
print('Сумма косинусов цифр числа x: ',sum)