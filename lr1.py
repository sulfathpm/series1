s=input('enter a string:')
print(s[0]+s[1:].replace(s[0],'$'))

print(s[-1]+s[1:-1]+s[0])