# 何乗しても後ろに同じ数が来る数。無限にある。
# 2乗して同じ数がくるなら何乗しても同じ。
# 一桁目が5もしくは6の2パターンある。
# 自己同次形
a = 6 # a = 5
N = 100 # 求める桁数
n = 0
for _ in range(N):
    for i in range(1,10):
        x = a + i*10**(len(str(a))+n)
        if x*(x-1) % 10**len(str(x)) == 0:
            a = x
            n = 0
            break
        if i == 9:
            n += 1
    print(len(str(a)),"桁:",a)