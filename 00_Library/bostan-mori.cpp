#include <atcoder/convolution>
#include <vector>

template <class T>
std::vector<T> _odd(std::vector<T> P)
{
    std::vector<T> R;
    for (int i = 0; i < P.size(); i++)
    {
        if (i % 2)
        {
            R.push_back(P[i]);
        }
    }
    return R;
}

template <class T>
std::vector<T> _even(std::vector<T> P)
{
    std::vector<T> R;
    for (int i = 0; i < P.size(); i++)
    {
        if (i % 2 == 0)
        {
            R.push_back(P[i]);
        }
    }
    return R;
}

template <class S, class T>
T bostan_mori(S N, std::vector<T> P, std::vector<T> Q)
{
    if (N == 0)
    {
        return P[0] / Q[0];
    }
    std::vector<T> QQ(Q.size(), 0);
    for (int i = 0; i < Q.size(); i++)
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
        return bostan_mori((N - 1) / 2, _odd(U), _even(V));
    }
    else
    {
        return bostan_mori(N / 2, _even(U), _even(V));
    }
}