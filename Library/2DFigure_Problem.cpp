#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
double eps=1e-9;
template<typename T, typename S> inline ostream& operator<<(ostream& os, const pair<T, S> p) { cout << "[" << p.first << ";" << p.second << "]"; return os; }
template<typename T> inline ostream& operator<<(ostream& os, const vector<T>& v) { for (auto el : v) os << el << " "; return os; }

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
 
double abs(point a) { return hypot(a.x,a.y); }
point perp(point a) { return {-a.y,a.x}; } // rotate 90 degrees counterclockwise
point normalize(point a) { return a/abs(a); }
 
double angle(point a, point b) { // angle between two vectors (0 to pi)
	double d = normalize(a)*normalize(b);
	return acos(max(-1.0,min(1.0,d)));
}
 
long long ccw(point a, point b, point c) { // returns 1|0|-1 if ac is left|straight|right of ab
	double res = (b-a)%(c-a);
	return abs(res) > eps ? (res > 0 ? 1 : -1) : 0;
}

// 線分AB上に点ｐがあるか判定。
bool on_segment(point p, point a, point b) {
	return (a-p)*(b-p) < eps && ccw(a,b,p) == 0;
}
 
// point that has equal distance to a,b,c
// 外心の中心点
point circumcenter(point a, point b, point c) {
	b = b-a, c = c-a;
	return a + perp(c*c*b - b*b*c)/(b%c)/2;
}
 
// center of incircle of triangle a,b,c
point incenter(point a, point b, point c) {
	double u = abs(b-c), v = abs(c-a), w = abs(a-b);
	return (u*a + v*b + w*c) / (u + v + w);
}
 
// finds all lines tangent to two circles (p,r) and (q,s)
// first outer, then inner tangents; be careful with touching/intersecting circles!
void find_tangents(point p, double r, point q, double s, vector<pair<point,point>> &res) {
	for(int inner=0;inner<2;inner++) {
		point v = q-p;
		double h = sqrt(v*v - (r-s)*(r-s));
		for (long long sign: {-1,1}) {
			point n = normalize((r-s)*v + sign*h*perp(v));
			res.emplace_back(p+r*n, q+s*n);
		}
		s = -s;
	}
}
 
double needed_radius(vector<point> &a, point p) {
	double res = 0;
	for (point q: a) res = max(res, abs(p-q));
	return res;
}
 
int main() {
	
	long long n; cin >> n;
	vector<point> a(n);
	for (int i = 0; i < n; i++)
	{
		cin >> a[i].x >> a[i].y;
	}
		
	// cout << circumcenter(a[0],a[1],a[2]) << endl;
	// cout << incenter(a[0],a[1],a[2]) << endl;

	vector<pair<point,point>> res;
	find_tangents(a[0], 0.25, a[1], 0.25, res);
	cout << res << endl;
}