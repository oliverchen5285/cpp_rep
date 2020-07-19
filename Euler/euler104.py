def pan(a): #return true if number is pan
  if(len(a) < 9):
    return False
  nums = list(range(1, 10))
  for i in range(0, 9):
    if(int(a[i]) in nums):
      nums.remove(int(a[i]))
    else:
      return False
  nums = list(range(1, 10))
  for i in range(len(a)-9, len(a)):
    if(int(a[i]) in nums):
      nums.remove(int(a[i]))
    else:
      return False
  return True

def pan_fib(): #returns index of 1st fib number that satisfies pan()
  index = 1
  a = 1
  b = 0
  while(True):
    c = a
    a += b
    b = c
    print(a)
    if(pan(str(a))):
      return index
    index += 1

    
print(pan_fib())		
'''	
print(pan("123456789"))
print(pan("1983523235239587239487384723084723412830562834628939469283569897324"))
print(pan("1"))	
'''
