#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
const double eps = 1e-9;

struct point
{
	double x, y;
};

point operator+(point a, point b) { return {a.x + b.x, a.y + b.y}; }
point operator-(point a, point b) { return {a.x - b.x, a.y - b.y}; }
point operator*(double t, point b) { return {t * b.x, t * b.y}; }
point operator/(point a, double t) { return {a.x / t, a.y / t}; }

double operator*(point a, point b) { return a.x * b.x + a.y * b.y; } // dot product
double operator%(point a, point b) { return a.x * b.y - a.y * b.x; } // cross product

bool operator<(point a, point b)
{ // lexicographical compare
	if (abs(a.x - b.x) > eps)
		return a.x < b.x;
	return a.y + eps < b.y;
}

std::ostream &operator<<(std::ostream &out, point a)
{ // for demplace_backugging
	return out << "(" << a.x << "," << a.y << ")";
}

double abs(point a) { return hypot(a.x, a.y); }
point perp(point a) { return {-a.y, a.x}; } // rotate 90 degrees counterclockwise
point normalize(point a) { return a / abs(a); }

double angle(point a, point b)
{ // angle between two vectors (0 to pi)
	double d = normalize(a) * normalize(b);
	return acos(std::max(-1.0, std::min(1.0, d)));
}

// counter clockwise
long long int ccw(point a, point b, point c)
{ // returns 1|0|-1 if c is left|straight|right of ab
	double res = (b - a) % (c - a);
	return abs(res) > eps ? (res > 0 ? 1 : -1) : 0;
}

bool on_segment(point p, point a, point b)
{
	return (a - p) * (b - p) < eps && ccw(a, b, p) == 0;
}

// point that has equal distance to a,b,c
point circumcenter(point a, point b, point c)
{
	b = b - a, c = c - a;
	return a + perp(c * c * b - b * b * c) / (b % c) / 2;
}

// center of incircle of triangle a,b,c
point incenter(point a, point b, point c)
{
	double u = abs(b - c), v = abs(c - a), w = abs(a - b);
	return (u * a + v * b + w * c) / (u + v + w);
}

// finds all lines tangent to two circles (p,r) and (q,s)
// first outer, then inner tangents; be careful with touching/intersecting circles!
void find_tangents(point p, double r, point q, double s, std::vector<std::pair<point, point>> &res)
{
	for (int inner : {0, 1, 2})
	{
		point v = q - p;
		double h = sqrt(v * v - (r - s) * (r - s));
		for (int sign : {-1, 1})
		{
			point n = normalize((r - s) * v + sign * h * perp(v));
			res.emplace_back(p + r * n, q + s * n);
		}
		s = -s;
	}
}