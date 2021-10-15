#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
const double eps = 1e-9;

bool eq(double x, double y) { return abs(x - y) <= eps; }
bool eq(int x, int y) { return abs(x - y) == 0; }
bool eq(long long int x, long long int y) { return abs(x - y) == 0; }

template <typename _Tp>
struct point
{
	_Tp x, y;
	point() : x(0), y(0){};
	point(_Tp x, _Tp y) : x(x), y(y){};

	point &operator+=(const point &rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	point &operator-=(const point &rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}
	friend point operator*(_Tp t, const point &rhs) { return {t * rhs.x, t * rhs.y}; }
	friend point operator/(const point &lhs, _Tp t) { return {lhs.x / t, lhs.y / t}; }
	friend _Tp operator*(const point &lhs, const point &rhs) { return lhs.x * rhs.x + lhs.y * rhs.y; } // dot product
	friend _Tp operator%(const point &lhs, const point &rhs) { return lhs.x * rhs.y - lhs.y * rhs.x; } // cross product
	friend point operator+(const point &lhs, const point &rhs) { return point(lhs) += rhs; }
	friend point operator-(const point &lhs, const point &rhs) { return point(lhs) -= rhs; }
	friend bool operator==(const point &lhs, const point &rhs) { return lhs.x == rhs.x && lhs.y == rhs.y; }
	friend bool operator!=(const point &lhs, const point &rhs) { return lhs.x != rhs.x || lhs.y != rhs.y; }
	friend bool operator<(const point &lhs, const point &rhs)
	{
		if (!eq(lhs.x, rhs.x))
			return lhs.x < rhs.x;
		return lhs.y + eps < rhs.y;
	}
	friend std::ostream &operator<<(std::ostream &out, const point &rhs) { return out << "(" << rhs.x << "," << rhs.y << ")"; }
};

template <typename _Tp>
using Points = std::vector<_Tp>;
template <typename _Tp>
using Polygon = std::vector<point<_Tp>>;

template <typename _Tp>
double abs(point<_Tp> a) { return hypot(a.x, a.y); }

template <typename _Tp>
point<_Tp> perp(point<_Tp> a) { return {-a.y, a.x}; } // rotate 90 degrees counterclockwise

template <typename _Tp>
point<_Tp> normalize(point<_Tp> a) { return a / abs(a); }

template <typename _Tp, typename _Up>
_Up angle(point<_Tp> a, point<_Tp> b)
{ // angle between two vectors (0 to pi)
	_Up d = normalize(a) * normalize(b);
	return acos(std::max(_Up(-1), std::min(_Up(1), d)));
}

// counter clockwise
template <typename _Tp, typename _Up>
long long int ccw(point<_Tp> a, point<_Tp> b, point<_Tp> c)
{ // returns 1|0|-1 if c is left|straight|right of ab
	_Up res = (b - a) % (c - a);
	return abs(res) > eps ? (res > 0 ? 1 : -1) : 0;
}

template <typename _Tp>
bool on_segment(point<_Tp> p, point<_Tp> a, point<_Tp> b)
{
	return (a - p) * (b - p) < eps && ccw(a, b, p) == 0;
}

// point that has equal distance to a,b,c
template <typename _Tp>
point<_Tp> circumcenter(point<_Tp> a, point<_Tp> b, point<_Tp> c)
{
	b = b - a, c = c - a;
	return a + perp(c * c * b - b * b * c) / (b % c) / 2;
}

// center of incircle of triangle a,b,c
template <typename _Tp>
point<_Tp> incenter(point<_Tp> a, point<_Tp> b, point<_Tp> c)
{
	double u = abs(b - c), v = abs(c - a), w = abs(a - b);
	return (u * a + v * b + w * c) / (u + v + w);
}

// finds all lines tangent to two circles (p,r) and (q,s)
// first outer, then inner tangents; be careful with touching/intersecting circles!
template <typename _Tp>
void find_tangents(point<_Tp> p, double r, point<_Tp> q, double s, std::vector<std::pair<point<_Tp>, point<_Tp>>> &res)
{
	for (int inner : {0, 1, 2})
	{
		point<_Tp> v = q - p;
		double h = sqrt(v * v - (r - s) * (r - s));
		for (int sign : {-1, 1})
		{
			point<_Tp> n = normalize((r - s) * v + sign * h * perp(v));
			res.emplace_back(p + r * n, q + s * n);
		}
		s = -s;
	}
}

template <typename _Tp>
Polygon<_Tp> convex_hull(Polygon<_Tp> &p)
{
	int n = p.size();
	if (n <= 2)
	{
		return p;
	}
	int k = 0;
	sort(p.begin(), p.end());
	Polygon<_Tp> hull(2 * n);
	for (int i = 0; i < n; i++)
	{
		while (k > 1 && (hull[k - 1] - hull[k - 2]) % (p[i] - hull[k - 1]) < eps)
		{
			k--;
		}
		hull[k++] = p[i];
	}
	for (int i = n - 2, t = k; i >= 0; --i)
	{
		while (k > t && (hull[k - 1] - hull[k - 2]) % (p[i] - hull[k - 1]) < eps)
		{
			k--;
		}
		hull[k++] = p[i];
	}
	hull.resize(k - 1);
	return hull;
}

// 多角形の面積を求める
template <typename _Tp>
_Tp PolygonArea(const Polygon<_Tp> &p)
{
	_Tp res = 0;
	int n = p.size();
	for (int i = 0; i < n - 1; i++)
	{
		res += (p[i] % p[i + 1]);
	}
	res += (p[n - 1] % p[0]);
	return res * 0.5;
}

template <typename _Tp>
_Tp PolygonArea2(const Polygon<_Tp> &p)
{
	_Tp res = 0;
	int n = p.size();
	for (int i = 0; i < n - 1; i++)
	{
		res += (p[i] % p[i + 1]);
	}
	res += (p[n - 1] % p[0]);
	return res;
}