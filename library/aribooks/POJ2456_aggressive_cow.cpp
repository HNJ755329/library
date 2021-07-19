#include <bits/stdc++.h>

#ifdef __LOCAL
    #define DBG(X) cout << "File:" << __FILE__ << " Line:" << __LINE__ << " " <<#X << " = " << (X) << endl;
    #define SAY(X) cout << (X) << endl;
    #include <filesystem>
    namespace fs = std::filesystem;
#else
    #define DBG(X)
    #define SAY(X)
#endif

using namespace std;
 
inline void fast_io() { ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr); };
template<typename T, typename S> inline ostream& operator<<(ostream& os, const pair<T, S> p) { cout << "[" << p.first << ";" << p.second << "]"; return os; }
template<typename T> inline ostream& operator<<(ostream& os, const vector<T>& v) { for (auto el : v) os << el << " "; return os; }

int N,M;
vector<int> X;

void input(){
    N = 5;
    M = 3;
    X = {1,2,8,4,9};
    sort(X.begin(),X.end());
}

bool C(int const& d){
    int j=0;
    int count=1;
    for(int i=0;i<N;i++){
        if((X[i]-X[j])>=d){j=i;count++;}
        if(count>=M) return true;
    }
    return (count>=M);
}

void solve(){
    int lb=0;
    int ub=1e9;
    while(ub-lb>1){
        int mid=(lb+ub)/2;
        if(C(mid)) lb=mid;
        else ub=mid;
    }
    DBG(lb)
}

int main(){
    input();
    solve();
    return 0;
}
