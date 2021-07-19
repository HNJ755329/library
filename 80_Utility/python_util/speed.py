import timeit


# test用関数
def main():
    for i in range(10):
        print(i)
    s = [x for x in range(10) if x % 2 == 0]
    print(s)

t = timeit.Timer('main()')
t.timeit(number=1)
