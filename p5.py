n=input('enter a list:')
n=list(map(int,n.split()))
x=int(input('x=?'))
bigno=[i for i in n if i>x]
print(bigno)