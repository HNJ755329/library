#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;
using pdd=pair<double,double>;
double INF = 2e9;

bool cmp_y(pdd a, pdd b){
    return a.second < b.second;
}

// Time complexity: O(nlogn)
double closest_pair(vector<pdd> a){
    int n=a.size();
    if(n<=1) return INF;
    int m=n/2;
    // vectorを2つに分けるときいいやり方がないか。
    vector<pdd> al,ar;
    for (int i = 0; i < n; i++)
    {
        if(i<m) al.push_back(a[i]);
        else ar.push_back(a[i]);
    }
    double d = min(closest_pair(al),closest_pair(ar));
    double x = a[m].first;
    sort(a.begin(),a.end(),cmp_y);
    vector<pdd> closest_x;
    for (int i = 0; i < n; i++)
    {
        if(abs(a[i].first-x)>=d) continue;
        for (int j = 0; j < closest_x.size(); j++)
        {
            double dx = a[i].first-closest_x[closest_x.size()-j-1].first;
            double dy = a[i].second-closest_x[closest_x.size()-j-1].second;
            if(dy>=d) break;
            d = min(d,sqrt(dx*dx+dy*dy));
        }
        closest_x.push_back(a[i]);
    }    
    return d;
}

int main(){
    int n = 5;
    vector<int> x = {0,6,43,39,189};
    vector<int> y = {2,67,71,107,140};
    vector<pdd> A;
    for (int i = 0; i < n; i++) A.push_back({x[i],y[i]});
    sort(A.begin(),A.end());
    double d = closest_pair(A);
    cout << d << endl;
    return 0;
}