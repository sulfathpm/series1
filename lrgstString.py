str1=input('enter list of string').split()
str1.sort(key=len)
print(str1[-1])