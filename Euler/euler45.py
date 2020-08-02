def tri(n):
  return (n*(n + 1))/2

def pent(n):
  return (n*(3*n - 1))/2

def hex(n):
  return n*(2*n - 1)

tri_index, pent_index, hex_index = 285 + 1, 165 + 1, 143 + 1
tri_cur, pent_cur, hex_cur = tri(tri_index), pent(pent_index), hex(hex_index)

while True:
  if(tri_cur == pent_cur and pent_cur == hex_cur):
    print(tri_cur)
    break
  if(tri_cur <= pent_cur and tri_cur <= hex_cur):
    tri_index += 1
    tri_cur = tri(tri_index)
  elif(pent_cur <= tri_cur and pent_cur <= hex_cur):
    pent_index += 1
    pent_cur = pent(pent_index)
  else:
    hex_index += 1
    hex_cur = hex(hex_index)


