#recursion gave stack overflow :(
#turns out I underestimated how giant these numbers are 
for i in range(1504170715041707, 0, -1):
  if(4503599627370517 % i == 0 and 1504170715041707 % i == 0):
    print(i)
    break

