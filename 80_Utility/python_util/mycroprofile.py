"""
@profileを定義された関数の前につけることによって
その関数のスピードテストを実行できる。
"""
import tempfile
import cProfile
import pstats


def profile(column='time', list=5):
    def _profile(function):
        def __profile(*args, **kw):
            s = tempfile.mktemp()
            profiler = cProfile.Profile()
            profiler.runcall(function, *args, **kw)
            profiler.dump_stats(s)
            p = pstats.Stats(s)
            p.sort_stats(column).print_stats(list)
        return __profile
    return _profile

# ---以下テスト用---


@profile('time', 5)
def main():
    for i in range(10):
        print(i)
    s = [x for x in range(10) if x % 2 == 0]
    print(s)


def medium():
    for _ in range(10):
        print("a")

main()
medium()
