#include <map>
#include <vector>
namespace number_theory
{
    template <typename T>
    T euler_phi(T n)
    {
        T ret = n;
        for (T i = 2; i * i <= n; i++)
        {
            if (n % i == 0)
            {
                ret -= ret / i;
                while (n % i == 0)
                    n /= i;
            }
        }
        if (n > 1)
            ret -= ret / n;
        return ret;
    }

    template <typename T>
    T extgcd(T a, T b, T &x, T &y)
    {
        T d = a;
        if (b != 0)
        {
            d = extgcd(b, a % b, y, x);
            y -= (a / b) * x;
        }
        else
        {
            x = 1;
            y = 0;
        }
        return d;
    }

    template <typename T>
    std::map<T, int> moebius(T n)
    {
        std::map<T, int> res;
        std::vector<T> primes;
        for (T i = 2; i * i <= n; i++)
        {
            if (n % i == 0)
            {
                primes.push_back(i);
                while (n % i == 0)
                    n /= i;
            }
        }
        if (n != 1)
            primes.push_back(n);

        int m = primes.size();
        // m個の約数から任意の数だけ選ぶ。bit全探索
        // moebius(a^2) = 0 なので素因数についてだけ求めれば良い。
        for (int bit = 0; bit < (1 << m); bit++)
        {
            int mu = 1, d = 1;
            for (int j = 0; j < m; j++)
            {
                if (bit >> j & 1)
                {
                    mu *= -1;
                    d *= primes[j];
                }
            }
            res[d] = mu;
        }
        return res;
    }

    // 約数列挙
    template <typename T>
    std::vector<T> divisor(T n)
    {
        std::vector<T> ret;
        for (T i = 1; i * i <= n; i++)
        {
            if (n % i == 0)
            {
                ret.push_back(i);
                if (i * i != n)
                    ret.push_back(n / i);
            }
        }
        std::sort(begin(ret), end(ret));
        return (ret);
    }
}
