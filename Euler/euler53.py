def fact_to(n, r):
  ans = 1
  for i in range(n, r, -1):
    ans *= i
  return ans

def comb(n, r):
  ans = 1
  return fact_to(n, max(r, n-r)) / fact_to(min(r, n-r), 1)

def comb_selections():
  ans = 0
  for i in range(23, 101):
    for j in range(1, i//2 + 1):
      if(comb(i, j) > 1000000):
        ans += 1
        print(i, j)
        if(j*2 != i):
          ans += 1
        
  return ans

print(comb_selections())
