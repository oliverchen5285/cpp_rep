#I'm just gonna use python :I

n = 1
for i in range(100):
  n *= (i + 1)

sum = 0
for i in str(n):
  sum += int(i)

print(sum)
