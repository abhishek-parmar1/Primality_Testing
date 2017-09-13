def primeOrNot(n):
    if(n==2):
        return 1
    if(n%2==0):
        return 0
    flag=0
    i=3
    while(i*i<=n):
        if(n%i==0):
            flag=1
            break
        i+=2
    if(flag==0):
        return 1
    else:
        return 0

def calPower(i,d):
    r=(2**1)%d
    for j in range(2,i):
       r= (r*2)%d
    return r

for i in range(30000000,300000000):
    if(primeOrNot(i)==1):
        print(i)
        d=i*i
        p=calPower(i,d)
        if(p==1):
            print("\n number is : "+i)
    
