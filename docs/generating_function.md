# 母関数から数列を復元する(Atcoder ABC198F)

- [Atcoder ABC198F - Cube](https://atcoder.jp/contests/abc198/tasks/abc198_f)をうけての記事．
- [F - Cube 解説](https://atcoder.jp/contests/abc198/editorial/986)によると[OEIS/A54473](https://oeis.org/A054473)が該当する答えらしい．
- n = 43までしか乗ってないしG.f.(Generating function)しかわからない．
- 母関数から数列を復元して行列累乗で第n項の係数を求める．
- 解説解法３の補間的な内容である.
- Bostan-Moriのアルゴリズムを追記(2021/5/10)

## サンプル S = 50 (n = 44)の確認．

まずこの数列でいいのか簡易的に確認する．
とりあえず母関数を$x = 0$の周りでテーラー展開すれば良い．
pythonを使ったコードと結果を以下に載せる．

```python
from sympy import *

x = Symbol('x')                  # 文字'x'を変数xとして定義
print(series((3*x**6+x**5+x**4+1)/((1-x**4)*(1-x**3)**2*(1-x**2)**2*(1-x)), x, 0, 51))
# 1 + x + 3*x**2 + 5*x**3 + 10*x**4 + 15*x**5 + 29*x**6 + 41*x**7 + 68*x**8 + 98*x**9 + 147*x**10 + 202*x**11 + 291*x**12 + 386*x**13 + 528*x**14 + 688*x**15 + 906*x**16 + 1151*x**17 + 1480*x**18 + 1841*x**19 + 2310*x**20 + 2833*x**21 + 3484*x**22 + 4207*x**23 + 5099*x**24 + 6076*x**25 + 7259*x**26 + 8562*x**27 + 10104*x**28 + 11796*x**29 + 13785*x**30 + 15948*x**31 + 18462*x**32 + 21201*x**33 + 24339*x**34 + 27747*x**35 + 31633*x**36 + 35827*x**37 + 40572*x**38 + 45695*x**39 + 51436*x**40 + 57618*x**41 + 64520*x**42 + 71918*x**43 + 80132*x**44 + 88934*x**45 + 98640*x**46 + 109018*x**47 + 120429*x**48 + 132587*x**49 + 145899*x**50 + O(x**51)
```

$x^{44}$の係数が$80132$であり，サンプルの数値と一致するのでよさそう．

- [[Pythonによる科学・技術計算] テイラー展開, 数式, sympy](https://qiita.com/sci_Haru/items/33b8e36655f20f7f3c12)

## 母関数から数列の一般項を求める．

```math
\sum a_n x^n =  \frac{3x^6+x^5+x^4+1}{(1-x^4)(1-x^3)^2(1-x^2)^2(1-x)} \\
\sum a_n x^n ((1-x^4)(1-x^3)^2(1-x^2)^2(1-x)) = 3x^6+x^5+x^4+1 \\
\sum a_n x^n (x^{15} - x^{14} - 2x^{13} + 2x^{11} + 4x^{10} - x^9 - 3x^8 - 3x^7 \\
 - x^6 + 4x^5 + 2x^4 - 2x^2 - x + 1) = 3x^6+x^5+x^4+1
```

- 母関数の分母を展開して，両辺に掛ける．
- $x^n$の係数を求める．

分母の展開はpythonもしくはwolfram alphaを使う．決して手で計算しては行けない．間違えるので．

```python
from sympy import *
x = Symbol('x')
print(series(((1-x**4)*(1-x**3)**2*(1-x**2)**2*(1-x)), x, 0, 16))
# x**15 - x**14 - 2*x**13 + 2*x**11 + 4*x**10 - x**9 - 3*x**8 - 3*x**7 - x**6 + 4*x**5 + 2*x**4 - 2*x**2 - x + 1
```

- [wolfram alpha](https://www.wolframalpha.com/input/?i=%281-x%5E4%29%281-x%5E3%29%5E2%281-x%5E2%29%5E2%281-x%29&lang=ja)

$n >= 15$について$x^n$の係数を比較して以下$a_{n}$の漸化式を得る．分母を展開した形とほぼ同じなことに注意．

```math
a_{n-15} - a_{n-14} -2a_{n-13} +2a_{n-11}+4a_{n-10}-a_{n-9}
-3a_{n-8}-3a_{n-7} \\
-a_{n-6}+4a_{n-5}+2a_{n-4}-2a_{n-2}-a_{n-1}+a_{n} = 0
```

$n < 15$についても係数比較で$a_n$を出すこともできるが，めんどうなので既に求めたテーラー展開，OEISの数値等をそのまま使えばいい．母関数の分子は計算に直接関与しない．

## 行列累乗で数列の一般項を計算する．

ここで

```math
a_n = \sum_{k=1}^{15} c_k a_{n-k}
```

とすると，

```math
A = \begin{pmatrix}
c_{1} & c_{2} & \cdots & c_{14} &  c_{15} \\
1 & 0 & \cdots & 0 & 0\\
0 & 1 & \cdots & 0 & 0\\
\vdots &   & \ddots & & \vdots\\
0 & 0 & \cdots  & 1 & 0
\end{pmatrix}
```

として

```math
\begin{align}
\left(
\begin{matrix} 
a_n \\ 
a_{n-1} \\
\vdots \\
a_{n-14}
\end{matrix} 
\right)
&=A
\left(
\begin{matrix} 
a_{n-1} \\ 
a_{n-2} \\
\vdots \\
a_{n-15}
\end{matrix} 
\right) 
=A^{2}
\left(
\begin{matrix} 
a_{n-2} \\ 
a_{n-3} \\
\vdots \\
a_{n-16}
\end{matrix} 
\right) 
= \cdots\\

&=A^{n-14}
\left(
\begin{matrix} 
a_{14} \\ 
a_{13} \\
\vdots \\
a_{0}
\end{matrix} 
\right) \\
\end{align}
```

が成り立つ．あとはこれを実装するだけだが符号と添字がややこしいので注意．テストは欠かせない．

```cpp:main.cpp
#include <atcoder/modint>
using modint = atcoder::modint998244353;

modint solve(long long S)
{
    // S = 6 を N = 0 にあてる．
    long long N = S - 6;
    // Matrixライブラリを適当に引っ張ってくる．
    // https://ei1333.github.io/luzhiled/snippets/math/matrix.html
    // 15*15行列
    Matrix<modint> A(15);
    for (int i = 0; i + 1 < 15; i++)
    {
        A[i + 1][i] = 1;
    }
    // a_n = a_{n-1} + ... - a_{n-15}
    A[0][0] = 1; //a_{n-1}の係数
    A[0][1] = 2; //a_{n-2}の係数
    A[0][2] = 0; //a_{n-3}の係数
    A[0][3] = -2; //a_{n-4}の係数
    A[0][4] = -4; //a_{n-5}の係数
    A[0][5] = 1; //a_{n-6}の係数
    A[0][6] = 3; //a_{n-7}の係数
    A[0][7] = 3; //a_{n-8}の係数
    A[0][8] = 1; //a_{n-9}の係数
    A[0][9] = -4; //a_{n-10}の係数
    A[0][10] = -2; //a_{n-11}の係数
    A[0][11] = 0; //a_{n-12}の係数
    A[0][12] = 2; //a_{n-13}の係数
    A[0][13] = 1; //a_{n-14}の係数
    A[0][14] = -1; //a_{n-15}の係数

    // 縦ベクトル
    Matrix<modint> B(15, 1);
    B[0][0] = 528; // a_14
    B[1][0] = 386; // a_13
    B[2][0] = 291; // a_12
    B[3][0] = 202; // a_11
    B[4][0] = 147; // a_10
    B[5][0] = 98; // a_9
    B[6][0] = 68; // a_8
    B[7][0] = 41; // a_7
    B[8][0] = 29; // a_6
    B[9][0] = 15; // a_5
    B[10][0] = 10; // a_4
    B[11][0] = 5; // a_3
    B[12][0] = 3; // a_2
    B[13][0] = 1; // a_1
    B[14][0] = 1; // a_0
    
    if (N <= 14)
    {
        return B[14 - N][0];
    }
    else
    {
        A ^= (N - 14);
        A *= B;
        return A[0][0];
    }
}
```

横ベクトルで表現する場合は転地されるので注意．（やっぱ横ベクトルの方が自然なんかなぁ．．．）

### 計算量

K*K行列のN乗は$O(K^3logN)$で求められる．
$K = 15$なのでこのままで間に合うが，Kが大きい時は,きたまさ法$O(K^2logN)$をつかえばよい．

## Bostan-Mori のアルゴリズム

2021/05/10に追記．

[x^N]P(x)/Q(x) を O(logN) で求められる．
かなり綺麗な再帰で書けて感動した．
詳細は自分が書くより天才たちが残した記述のほうがわかりやすいのでそちらを参照．

### アルゴリズム

- [線形漸化式を満たす数列の N 項目を計算するアルゴリズム](http://q.c.titech.ac.jp/docs/progs/polynomial_division.html)

### 参照

- [線形漸化的数列のN項目の計算](https://qiita.com/ryuhe1/items/da5acbcce4ac1911f47a)
- [[多項式・形式的べき級数]（３）線形漸化式と形式的べき級数](https://maspypy.com/%e5%a4%9a%e9%a0%85%e5%bc%8f%e3%83%bb%e5%bd%a2%e5%bc%8f%e7%9a%84%e3%81%b9%e3%81%8d%e7%b4%9a%e6%95%b0%ef%bc%88%ef%bc%93%ef%bc%89%e7%b7%9a%e5%bd%a2%e6%bc%b8%e5%8c%96%e5%bc%8f%e3%81%a8%e5%bd%a2%e5%bc%8f)

### 実装

```cpp:bostan-mori.cpp
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
```

```cpp:main.cpp
#include "bostan-mori.cpp"
modint solve(long long S)
{
    vector<modint> P, Q;
    P = {1, 0, 0, 0, 1, 1, 3};
    Q = {1};
    Q = atcoder::convolution<modint>(Q, {1, -1});
    Q = atcoder::convolution<modint>(Q, {1, 0, -1});
    Q = atcoder::convolution<modint>(Q, {1, 0, -1});
    Q = atcoder::convolution<modint>(Q, {1, 0, 0, -1});
    Q = atcoder::convolution<modint>(Q, {1, 0, 0, -1});
    Q = atcoder::convolution<modint>(Q, {1, 0, 0, 0, -1});
    long long N = S - 6;
    return bostan_mori(N, P, Q);
}
```

以上．
