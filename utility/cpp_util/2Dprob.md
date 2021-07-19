# 【C++】平面図形問題を解く。
競技プログラミングにおいて平面問題を解く際のテンプレートを用意した。
需要があれば数学的な解説を図形付きで載せたい。
とりあえずは、自分用にまとめておく。

## 0.下準備
structを使ってpointを自分で定義する。
classを使ってもよい。その場合はメンバ変数をpublicにするとやりやすい。

```cpp
#include <bits/stdc++.h>
#define FOR(i, m, n) for(int i = m;i < n;i++)

const double eps = 1e-9;
const double eps = 1e-9;

struct point { double x, y; };
point  operator+(point a,  point b) { return {a.x+b.x, a.y+b.y}; }
point  operator-(point a,  point b) { return {a.x-b.x, a.y-b.y}; }
point  operator*(double t, point b) { return {t*b.x, t*b.y}; }
point  operator/(point a, double t) { return {a.x/t, a.y/t}; }
double operator*(point a,  point b) { return a.x*b.x + a.y*b.y; } // dot product
double operator%(point a,  point b) { return a.x*b.y - a.y*b.x; } // cross product
bool operator<(point a, point b) { // lexicographical compare
	if (abs(a.x-b.x) > eps) return a.x < b.x;
	return a.y + eps < b.y;
}
ostream &operator<<(ostream &out, point a) { // for demplace_backugging
	return out << "(" << a.x << "," << a.y << ")";
}
```
ベクトルの和、差、内積、外積を、各演算子をオーバーロードすることにより定義する。
各点を`double`で表現しているので比較をするときには注意が必要。
`a.x != b.x`の気持ちで`abs(a.x-b.x) > eps`を使用している。
`0.1*100 != 10.0`が`true`になるのと同じ理由。詳しくは省略。
## 1.基本的な演算

```cpp
double abs(point a) { return hypot(a.x,a.y); }
point perp(point a) { return {-a.y,a.x}; } // rotate 90 degrees counterclockwise
point normalize(point a) { return a/abs(a); }
 
double angle(point a, point b) { // angle between two vectors (0 to pi)
	double d = normalize(a)*normalize(b);
	return acos(max(-1.0,min(1.0,d)));
}
 
ll ccw(point a, point b, point c) { // returns 1|0|-1 if ac is left|straight|right of ab
	double res = (b-a)%(c-a);
	return abs(res) > eps ? (res > 0 ? 1 : -1) : 0;
}

// 線分AB上に点ｐがあるか判定。
bool on_segment(point p, point a, point b) {
	return (a-p)*(b-p) < eps && ccw(a,b,p) == 0;
}
```

## 2.外心

```cpp
// point that has equal distance to a,b,c
point circumcenter(point a, point b, point c) {
	b = b-a, c = c-a;
	return a + perp(c*c*b - b*b*c)/(b%c)/2;
}
```
日本語で解説してる記事は見当たらなかった。3次元の場合はwikipedia(英語版)に解説あり。
https://en.wikipedia.org/wiki/Circumscribed_circle
需要があれば詳しく解説したい。

## 3.内心
```cpp
// center of incircle of triangle a,b,c
point incenter(point a, point b, point c) {
	double u = abs(b-c), v = abs(c-a), w = abs(a-b);
	return (u*a + v*b + w*c) / (u + v + w);
}
```
内心の公式でググれば、なぜこうなるかはわかる。

## 4.2円に接する直線と円との交点
```cpp
// finds all lines tangent to two circles (p,r) and (q,s)
// first outer, then inner tangents; be careful with touching/intersecting circles!
void find_tangents(point p, double r, point q, double s, vector<pair<point,point>> &res) {
	FOR(inner,0,2) {
		point v = q-p;
		double h = sqrt(v*v - (r-s)*(r-s));
		for (ll sign: {-1,1}) {
			point n = normalize((r-s)*v + sign*h*perp(v));
			res.emplace_back(p+r*n, q+s*n);
		}
		s = -s;
	}
}
```
円が2つ離れているとき、共通外接線2本と共通内接線2本が存在する。
それぞれの接線と円との交点を計算する。
図形付きで解説したいけど、図形書くのめんどくさい。
どこかにいい感じのソフトないかなぁ。

以上。
# 参考文献
[Circumscribed circle - wikipedia](https://en.wikipedia.org/wiki/Circumscribed_circle)