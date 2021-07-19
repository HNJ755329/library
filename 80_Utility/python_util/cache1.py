"""
決定的キャッシュ。これによって再帰的な関数をメモ化する。
ただし複数の引数をとる場合はさらに複雑化する。cache2を参照。
"""


def memoize(function):
    """Memoize the call to single-argument function"""
    call_cache = {}

    def memoized(*argument):
        try:
            return call_cache[argument]
        except KeyError:
            return call_cache.setdefault(argument, function(*argument))
        print(call_cache) 
    return memoized

# --- 再帰的な関数（ここではフィボナッチ数列）をmemoize化する。デコレーターをつけるだけの簡単な操作---


class Fib():
    @memoize
    def fibonacci(self, n):
        if n < 2:
            return 1
        else:
            return self.fibonacci(n-1) + self.fibonacci(n-2)


def main():
    f = Fib()
    print(f.fibonacci(10))

main()
