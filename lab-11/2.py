i, k = 10, 0
while i < 100:
    if i % 2 != 0:
        print(f"Нечетное число:{i}")
        k += 1
    i += 1
print(f'Общее кол-во двухзначных: {k}')
