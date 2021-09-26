<<<<<<< HEAD
# 高速ゼータ変換/高速メビウス変換
=======
# 高速ゼータ変換．高速メビウス変換
>>>>>>> dev

高速ゼータ変換，高速メビウス変換の解説.
Sの部分集合全体の和についての計算.

<<<<<<< HEAD
![formula](https://render.githubusercontent.com/render/math?math=g(S)%20%3D%20\sum_{T%20\subset%20S}f(T))
=======
```math
g(S) = \sum_{T \in S} f(T)
```
>>>>>>> dev

fが既知のとき，gを求めるのが高速ゼータ変換.
逆にgが既知のときfを求めるのが高速メビウス変換.

<<<<<<< HEAD
自然に実装すれば計算量はO(4^n)やO(3^n)で計算できるが，
高速ゼータ変換/高速メビウス変換を用いれば計算量がO(n*2^n)で計算できる．

以下実装．ただし，Sの部分集合全体について和をとるのか
Sを含む集合全体について和をとるのかで少し異なる．
本質的には同じだが分けて管理するほうが利用しやすいので分けてコードを書く．

## 高速ゼータ変換

Sの部分集合全体についての和．

![formula](https://render.githubusercontent.com/render/math?math=g(S)%20%3D%20\sum_{T%20\subset%20S}f(T))
=======
自然に実装すれば計算量はO(4^n)やO(3^n)で計算できるが
高速ゼータ変換，高速メビウス変換では計算量がO(n2^n)で計算できる．

以下，実装．ただし，Sの部分集合全体について和をとるのか
Sを含む部分集合全体について和をとるのかで少し異なる．
本質的には同じだが分けて管理するほうが利用しやすいので分ける．

## 高速ゼータ変換

```math
g(S) = \sum_{T \in S} f(T)
```
>>>>>>> dev

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

<<<<<<< HEAD
Sを含む集合全体の和．

![formula](https://render.githubusercontent.com/render/math?math=g(S)%20%3D%20\sum_{S%20\subset%20T}f(T))

=======

```math
g(S) = \sum_{S \in T} f(T)
```
>>>>>>> dev

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

<<<<<<< HEAD
Sの部分集合全体についての和．

![formula](https://render.githubusercontent.com/render/math?math=g(S)%20%3D%20\sum_{T%20\subset%20S}f(T))
=======
```math
g(S) = \sum_{T \in S} f(T)
```
>>>>>>> dev

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

<<<<<<< HEAD
Sを含む集合全体の和．

![formula](https://render.githubusercontent.com/render/math?math=g(S)%20%3D%20\sum_{S%20\subset%20T}f(T))

=======
```math
g(S) = \sum_{S \in T} f(T)
```
>>>>>>> dev

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
