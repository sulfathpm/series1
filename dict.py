d1={1:20,2:30,4:45}
print(d1.items())
print(d1.keys)
print(d1.values)
print(d1)
d2={2:24,5:67,1:22}
d1.update(d2)
print(d1)
print(sorted(d2))
print(sorted(d1,reverse=True))
key=int(input('enter key to search:'))
print('key exist:',key in d1)

invert={v:k for k,v in d1.items()}
print(invert)