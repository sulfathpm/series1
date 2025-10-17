s=input('enter a list of numbers(comma sep): ')
s=list(map(int,s.split(',')))
even=[x for x in s if x%2==0]
print(even)