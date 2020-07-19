ans = 0
cur = 3
while True:
  print(ans)
  sum = 0
  for i in str(cur):
    fact = 1
    for j in range(int(i)):
      fact *= (j + 1)
    sum += fact
  if(sum == cur):
    ans += cur
  cur += 1


