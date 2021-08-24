# 高速ゼータ変換．高速メビウス変換

高速ゼータ変換，高速メビウス変換の解説.
Sの部分集合全体の和についての計算.

```math
g(S) = \sum_{T \in S} f(T)
```

fが既知のとき，gを求めるのが高速ゼータ変換.
逆にgが既知のときfを求めるのが高速メビウス変換.

自然に実装すれば計算量はO(4^n)やO(3^n)で計算できるが
高速ゼータ変換，高速メビウス変換では計算量がO(n2^n)で計算できる．

以下，実装．ただし，Sの部分集合全体について和をとるのか
Sを含む部分集合全体について和をとるのかで少し異なる．
本質的には同じだが分けて管理するほうが利用しやすいので分ける．

## 高速ゼータ変換

```math
g(S) = \sum_{T \in S} f(T)
```

```cpp
template <typename T>
vector<T> fast_zeta_transform_sos(const vector<T> &f)
{
    int n = f.size();
    vector<T> g = f;
    for (int i = 0; (1 << i) < n; ++i)
    {
        for (int bit = 0; bit < n; ++bit)
        {
            if ((bit >> i & 1))
            {
                g[bit] += g[bit ^ (1 << i)];
            }
        }
    }
    return g;
}
```


```math
g(S) = \sum_{S \in T} f(T)
```

```cpp
template <typename T>
vector<T> fast_zeta_transform(const vector<T> &f)
{
    int n = f.size();
    vector<T> g = f;
    for (int i = 0; (1 << i) < n; ++i)
    {
        for (int bit = 0; bit < n; ++bit)
        {
            if (!(bit >> i & 1))
            {
                g[bit] += g[bit | (1 << i)];
            }
        }
    }
    return g;
}
```
## 高速メビウス変換

```math
g(S) = \sum_{T \in S} f(T)
```

```cpp
template <typename T>
vector<T> fast_mobius_transform_sos(const vector<T> &g)
{
    int n = g.size();
    vector<T> f = g;
    for (int i = 0; (1 << i) < n; ++i)
    {
        for (int bit = 0; bit < n; ++bit)
        {
            if ((bit >> i & 1))
            {
                f[bit] -= f[bit ^ (1 << i)];
            }
        }
    }
    return f;
}
```

```math
g(S) = \sum_{S \in T} f(T)
```

```cpp
template <typename T>
vector<T> fast_mobius_transform(const vector<T> &g)
{
    int n = g.size();
    vector<T> f = g;
    for (int i = 0; (1 << i) < n; ++i)
    {
        for (int bit = 0; bit < n; ++bit)
        {
            if (!(bit >> i & 1))
            {
                f[bit] -= f[bit | (1 << i)];
            }
        }
    }
    return f;
}
```

## Reference

- [Tutorial on Zeta Transform, Mobius Transform and Subset Sum Convolution](https://codeforces.com/blog/entry/72488)
- [AtCoder頻出？貼るだけ高速ゼータ・メビウス変換＆約数拡張](https://habara-k.hatenadiary.jp/entry/2020/04/14/010237)
- [ゼータ変換・メビウス変換を理解する](https://qiita.com/convexineq/items/afc84dfb9ee4ec4a67d5)
