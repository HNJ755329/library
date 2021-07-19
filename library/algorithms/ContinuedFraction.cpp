#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <numeric>
#include <iomanip>

using namespace std;
template<typename T, typename S> inline ostream& operator<<(ostream& os, const pair<T, S> p) { cout << "[" << p.first << ";" << p.second << "]"; return os; }
template<typename T> inline ostream& operator<<(ostream& os, const vector<T>& v) { for (auto el : v) os << el << " "; return os; }

// 実数を連分数に変換する。
vector<int> ContinuedFraction(double x,int n=1000){
    vector<int> CF;
    CF.push_back(floor(x));
    x = x - floor(x);

    while(x > 1e-6 && n>0){
        x = 1/x;
        // if(x>100) break;
        CF.push_back(floor(x));
        x = x - floor(x);
        n--;
    }
    return CF;
}

// 連分数を分数に変換する
// 深い階層から計算し直していってるのでダメ。
// 上から計算しないと・・・。
pair<unsigned long long,unsigned long long> MyCFtoFrac(vector<int> v){
    unsigned long long a=0,b=1;
    while(!v.empty()){
        int x = v.back();
        v.pop_back();
        swap(a,b);
        b = x*a+b;
        if(a>(1ULL<<60)|b>(1ULL<<60)){
            return make_pair(0,1);
        }
    }
    swap(a,b);
    return make_pair(a,b);
}

pair<unsigned long long,unsigned long long> CFtoFrac(vector<int> const& v){
    int n = v.size();
    vector<unsigned long long> q(n+1),p(n+1);
    p[0] = 1;
    q[0] = 0;
    p[1] = v[0];
    q[1] = 1;
    for(int i=2;i<=n;i++){
        p[i] = v[i-1]*p[i-1]+p[i-2];
        q[i] = v[i-1]*q[i-1]+q[i-2];
        if(p[i]>(1ULL<<60)|q[i]>(1ULL<<60)){
            return make_pair(p[i-1],q[i-1]);
        }
    }
    return make_pair(p.back(),q.back());
}

double CFtoDouble(vector<int> v){
    double a=0;
    while(!v.empty()){
        int x = v.back();
        v.pop_back();
        a = 1/(x+a);
    }
    a = 1/a;
    return a;
}

void test(){
    double x = 3.24568;
    auto V = ContinuedFraction(x);
    auto y = CFtoFrac(V);
    auto z = CFtoDouble(V);

    cout << fixed << setprecision(20) << x << endl;
    cout << fixed << setprecision(20) << V << endl;
    cout << fixed << setprecision(20) << y << endl;
    cout << fixed << setprecision(20) << z << endl;
}

int main()
{
    test();
    return 0;
}
