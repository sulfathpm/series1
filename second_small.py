s=input('enter a list of numbers:')
s=list(map(int,s.split()))
s.sort()
print(s[1])