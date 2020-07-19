#I think the upper bound is just 10^(n + 1) <- technically it can be higher but we're working with 5 here so it can't add up that much

ans = 0

for i in range(10, 1000000):
  sum = 0
  for j in str(i):
    sum += pow(int(j), 5)
  if(sum == i):
    print(i)
    ans += i

print(ans)
  
  
