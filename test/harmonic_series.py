f = 100
n = 8

print(f)
for v in range(n - 1):
    f *= (v + 2) / (v + 1)
    print(f)
