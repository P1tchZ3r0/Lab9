import random as r
A = [[r.randint(1,100),r.randint(1,100),r.randint(1,100)],
     [r.randint(1,100),r.randint(1,100),r.randint(1,100)],
     [r.randint(1,100),r.randint(1,100),r.randint(1,100)]]
print('Полученная матрица А:')
print(A[0])
print(A[1])
print(A[2])
print('Главная диагональ матрицы А:')
B = [A[0][0],A[1][1],A[2][2]]
print(B)
print('Побочная диагональ матрицы А:')
C = [A[0][2],A[1][1],A[2][0]]
print(C)