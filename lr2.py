s1=input('enter string1:')
s2=input('enter string2:')

print(s2[0]+s1[1:]+" "+s1[0]+s2[1:])

clr=input('enter clrs:').split(',')
print(list(clr))
print(clr[::2])