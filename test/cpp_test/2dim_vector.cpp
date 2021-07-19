#include <bits/stdc++.h>
using namespace std;

double EPS = 1e-10;

// 誤差を考慮して足し算を行う。
double add(double const& a, double const& b){
    if(abs(a+b)<EPS*(abs(a)+abs(b))) return 0;
    return a+b;
}

struct Point{
    double x,y;
    Point(){}
    Point(double x, double y): x(x), y(y) {}
    Point operator + (Point p){
        return Point(add(x,p.x),add(y,p.y));
    }
    Point operator - (Point p){
        return Point(add(x,-p.x),add(y,-p.y));
    }
    Point operator * (double d){
        return Point(x*d, y*d);
    }
    double dot(Point p){
        return add(x*p.x,y*p.y);
    }
    double det(Point p){
        return add(x*p.y,-y*p.x);
    }
};

int main(){
    Point p1(1,2),p2(2,4);
    cout << (p1.dot(p2)) << endl;    
}