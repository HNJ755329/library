#include <atcoder/convolution>
#include <vector>

struct bostan_mori
{
    template <class T>
    std::vector<T> _odd(const std::vector<T> &P)
    {
        std::vector<T> R;
        for (size_t i = 0; i < P.size(); i++)
        {
            if (i % 2)
            {
                R.push_back(P[i]);
            }
        }
        return R;
    }

    template <class T>
    std::vector<T> _even(const std::vector<T> &P)
    {
        std::vector<T> R;
        for (size_t i = 0; i < P.size(); i++)
        {
            if (i % 2 == 0)
            {
                R.push_back(P[i]);
            }
        }
        return R;
    }

    template <class S, class T>
    T solve(const S &N, const std::vector<T> &P, const std::vector<T> &Q)
    {
        if (N == 0)
        {
            return P[0] / Q[0];
        }
        std::vector<T> QQ(Q.size(), 0);
        for (size_t i = 0; i < Q.size(); i++)
        {
            if (i % 2)
            {
                QQ[i] = -Q[i];
            }
            else
            {
                QQ[i] = Q[i];
            }
        }
        auto U = atcoder::convolution<T>(P, QQ);
        auto V = atcoder::convolution<T>(Q, QQ);
        if (N % 2)
        {
            return solve((N - 1) / 2, _odd(U), _even(V));
        }
        else
        {
            return solve(N / 2, _even(U), _even(V));
        }
    }
};