s=input('enter a string:')
vowel='aeiouAEIOU'
str11=[x for x in s if x not in vowel]
str1=set(str11)
print("".join(str1))

