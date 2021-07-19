# Floor Sum

ACLのfloor sumを(たぶん)理解したのでまとめる.
記号はACLに準じる.

## 問題文

$\mathrm{floorsum}(n,m,a,b) = \sum_{i=0}^{n-1} \lfloor(a\times i+b)/m \rfloor$ をもとめよ.

https://atcoder.jp/contests/practice2/tasks/practice2_c

### 解説

$a \geq m, b \geq m$のとき、$a = q_am + r_a, b = q_bm + r_b (0 \leq r_a, r_b < m)$
と表せて

```math
\begin{aligned}
\mathrm{floorsum}(n,m,a,b) &= \sum_{i=0}^{n-1} \lfloor(a\times i+b)/m \rfloor \\
&=  \sum_{i=0}^{n-1} (q_a\times i+q_b) + \sum_{i=0}^{n-1} \lfloor(r_a\times i+r_b)/m \rfloor \\
&= n(n-1)q_a/2 + nq_b + \mathrm{floorsum}(n,m,r_a,r_b)
\end{aligned}
```

であるので,$0 \leq a, b < m$に帰着できる.
以下$0 \leq a, b < m$とする.

$y_{max} = \lfloor (na+b)/m \rfloor$とおく.
$a, b < m$よりfloor_sumは初項0、公差1以下の数列の和で表せる.

```math
\begin{aligned}
\mathrm{floorsum}(n,m,a,b) &= \sum_{i=0}^{n} \lfloor(a\times i+b)/m \rfloor - y_{max} \\
&= 0 + 0 + 1 + 1 + 2 + 2 + \cdots  + y_{max} - y_{max}
\end{aligned}
```

それぞれの数が何個足されてるか分かればfloor_sumが求められる.
それを求めるために、$k_l$を$\lfloor (ak_l + b)/m \rfloor = l$となる最小の自然数とする.以下を満たす.

```math
l \leq (ak_l+b)/m \\
(ml-b)/a \leq k_l
```

このうちの最小の自然数なので$k_l = \lceil(ml-b)/a \rceil$.
この$k_l$を用いてfloor_sum中の自然数$l (1 \leq l < y_{max})$の個数は $(k_{l+1}-1 - k_l + 1) = (k_{l+1}-k_{l})$ 個, 自然数$y_{max}$の個数は $(n-k_{y_{max}})$個と表せる.(自然数$l$は1個以上あり,自然数$y_{max}$は0個以上あることに注意.)
floor_sumを次のように書き直せる.

```math
\begin{aligned}
\mathrm{floorsum}(n,m,a,b) &= \sum_{i=0}^{n-1} \lfloor(a\times i+b)/m \rfloor \\
&= (k_2-k_1) + 2(k_3-k_2) + \cdots + y_{max}(n-k_{y_{max}}) \\
&= -k_1 - k_2 - \cdots -k_{y_{max}} + y_{max}n \\
&= (n-k_1) + (n - k_2) + \cdots + (n - k_{y_{max}})
\end{aligned}
```

ここで,簡単のためACLに従い$x_{max} = my_{max}-b$ とおく.

```math
\begin{aligned}
n - k_l &= n - \lceil(ml-b)/a \rceil = \lfloor (na-ml+b)/a \rfloor \\
&= \lfloor (m(y_{max}-l) + (na-x_{max}))/a \rfloor \\
\end{aligned}

```

また, $y_{max} = \lfloor (na+b)/m \rfloor$より

```math
y_{max} \leq (na+b)/m < (y_{max}+1) \\
my_{max} \leq (na+b) < m(y_{max}+1) \\
0 \leq na-x_{max} < m
```

である.よって

```math
\begin{aligned}
na-x_{max} &= \lfloor(na-x_{max})/a \rfloor a + (na-x_{max})\%a \\
 &= (n-\lceil x_{max}/a \rceil )a + (a-x_{max}\%a)\%a
\end{aligned}
```

と表せるので

```math
n - k_l = (n-\lceil x_{max}/a \rceil ) + \lfloor (m(y_{max}-l) + (a-x_{max}\%a)\%a)/a \rfloor
```

したがって

```math
\begin{aligned}
\mathrm{floorsum}(n,m,a,b) &= \sum_{l=1}^{y_{max}} (n-k_l) \\
&= (n-\lceil x_{max}/a \rceil ) y_{max} + \sum_{l=0}^{y_{max}-1} \lfloor (ml + (a-x_{max}\%a)\%a)/a \rfloor \\
&= (n-\lceil x_{max}/a \rceil ) y_{max} + \mathrm{floorsum}(y_{max},a,m,(a-x_{max}\%a)\%a)
\end{aligned}
```

このようにfloor_sumを再帰的に計算できる.
あとはコードに落とすだけ.

```cpp
long long floor_sum(long long n, long long m, long long a, long long b) {
    long long ans = 0;
    if (a >= m) {
        ans += (n - 1) * n * (a / m) / 2;
        a %= m;
    }
    if (b >= m) {
        ans += n * (b / m);
        b %= m;
    }

    long long y_max = (a * n + b) / m, x_max = (y_max * m - b);
    if (y_max == 0) return ans;
    ans += (n - (x_max + a - 1) / a) * y_max;
    ans += floor_sum(y_max, a, m, (a - x_max % a) % a);
    return ans;
}
```

解説で用いた、floor,ceilの操作について補題で示す.

## 補題

xは整数,yは実数とする.次が成り立つ.

```math
x-\lceil y \rceil = \lfloor x - y \rfloor
```

### 証明

$\lfloor x - y \rfloor = k$とおくと次が成り立つ.

```math
k \leq (x-y) < (k+1) \\
k-x \leq -y < (k+1)-x \\
x-k-1 < y \leq x-k \\
```

これは $\lceil y \rceil = x - k$ を表している.

## 時間計算量

ユークリッドの互除法と同じく$a,m$を互いに余りを取り交換し合いながら計算するので, $O(\log a + \log m)$

## 参考

- [Time complexity of Euclid's Algorithm](https://stackoverflow.com/questions/3980416/time-complexity-of-euclids-algorithm)
