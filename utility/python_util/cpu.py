import pstats
import cProfile

"""
コードのマイクロプロファイリングを行う。
"""

# テスト用の関数を定義


def main():
    for i in range(10):
        print(i)
    s = [x for x in range(10) if x % 2 == 0]
    print(s)


def medium():
    for i in range(10**3):
        print("a")

# ---ここからプロファイリング---
cProfile.run('main()', 'stats')
stats = pstats.Stats('stats')
stats.total_calls
stats.sort_stats('time').print_stats(1)

#  stats.print_callees('medium')
