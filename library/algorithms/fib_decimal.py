import decimal
import math
from functools import lru_cache

# フィボナッチ数列の少数表示を利用したフィボナッチ数列の求め方。

def fib_decimals(n):
    decimal.getcontext().prec = n*100
    a = decimal.Decimal(10**n)
    b = decimal.Decimal(100**n - 10**n -1)
    fib = a/b
    return fib

def N_fib(n):
    a = []
    x = decimal.Decimal(fib_decimals(n))
    while True:
        y = x*10**n
        x = y % 1
        a.append(int(y))
        if len(str(int(y))) >= n:
            break
    return a

def fibonacci(n):
    a = 1/math.sqrt(5)
    b = ((1+math.sqrt(5))/2)**n
    c = ((1-math.sqrt(5))/2)**n
    return int(a*(b-c) // 1)

@lru_cache(maxsize=1000)
def fib_def(n):
    if n == 1 or n == 2:
        return 1
    else:
        return fib_def(n-1) + fib_def(n-2)


if __name__ == "__main__":
    a = N_fib(20)
    n = int(len(a))
    b = [fibonacci(x) for x in range(1, n+1)]
    c = [fib_def(i) for i in range(1, n+1)]
    diff_ab = [a[i]-b[i] for i in range(n)]
    diff_bc = [b[i]-c[i] for i in range(n)]
    diff_ca = [c[i]-a[i] for i in range(n)]
    print(a)
    print(b)
    print(c)
    print(diff_ab.count(0))
    print(diff_bc.count(0))
    print(diff_ca.count(0))
    print(diff_ab)
    print(diff_bc)
    print(diff_ca)
     