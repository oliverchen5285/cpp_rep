#ok pure brute force works

def digit_sum(n):
  ans = 0
  for i in str(n):
    ans += int(i)
  return ans

ans = 0
for i in range(100):
  for j in range(100):
    ans = max(ans, digit_sum(i**j))

print(ans)
