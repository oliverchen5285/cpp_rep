def fib_index():
  index = 1
  a = 1
  b = 1
  while True:
    if(len(str(a)) >= 1000):
      return index
    a, b = b, a
    a += b
    index += 1

print(fib_index())
