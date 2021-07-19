"""
決定的キャッシュ。これによって再帰的な関数をメモ化する。
"""
from functools import lru_cache


# --- 再帰的な関数（ここではフィボナッチ数列）をmemoize化する。デコレーターをつけるだけの簡単な操作---
# ただしlru_cacheをつける関数の引数はhashableでなければならない。そうでない場合エラーとなる。

class Fib():
    @lru_cache(maxsize=1000)
    def fibonacci(self, n):
        if n < 2:
            return 1
        else:
            return self.fibonacci(n-1) + self.fibonacci(n-2)


def main():
    f = Fib()
    print(f.fibonacci(100))

main()
