def lychrel(n):
  for i in range(50):
    n += int(str(n)[::-1])
    if(str(n) == str(n)[::-1]):
      return False
  return True
    

ans = 0
for i in range(10000): #0 included?
  if(lychrel(i)):
    ans += 1
  
print(ans)
  
