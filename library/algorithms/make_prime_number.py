#!/usr/bin/
# prime number
import math
def printNth(n, N, plist):
    print(n,"th prime number is ", plist[n-1])

def isPrimeNum(p, N, plist):
    if p > N:
        print(p,"is too large!")
    else:
        if p in plist:
            print(p,"is prime number")
        else:
            print(p,"is composite number")

def setOfPrimeNumbers(N):
    plist = list()
    X = set(range(2, N))
    while len(X) > 0:
        p = min(X)
        plist.append(p)
        X = set(X) - set([x for x in X if x%p == 0])
    return plist

def main(N):
    plist = setOfPrimeNumbers(N)
    sum = 1
    for i in range(len(plist)):
        p = 1/(1-(1/plist[i])**(2))
        sum *= p
        print("p/(p-1) is :",plist[i],":",p)
    print("sum is ",sum)

if __name__ == "__main__":
    main(11000)
    print(math.pi**2/6)