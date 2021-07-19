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

using ll = long long int;
using ull = unsigned long long int;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
inline void fast_io() { ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr); };
template<typename T, typename S> inline ostream& operator<<(ostream& os, const pair<T, S> p) { cout << "[" << p.first << ";" << p.second << "]"; return os; }
template<typename T> inline ostream& operator<<(ostream& os, const vector<T>& v) { for (auto el : v) os << el << " "; return os; }
template<typename T> inline vector<T> fetch_vec(int sz) { vector<T> ret(sz); for (auto& elem : ret) cin >> elem; return ret; }

int N;
string S;
vector<int> dir;

void input(){
    S = "BFFFFFFBBFFFFFFFBBBFF";
    N = S.size();
    dir.assign(N,0);
    for(int i=0;i<N;i++){
        if(S[i]=='F') dir[i]=1;
    }
}

// Kを固定した時の最小操作回数を求める。
// 解が存在しないのならば-1
// O(N^2) かかるのでNの大きさによってはTLE
// (N-K)*K/2 (ifの条件によって1/2かは変わる。全部trueなら1.期待値1/2)
// sigma_K (N-K)*K/2 = N(N+1)(N-1)/12 = O(N^3)
int calcOrder2(int const& K){
    vector<int> dirK=dir;
    int count=0;
    for(int i=0;i<(N-K+1);i++){
        // 裏向いている場合、その先のK個を裏返す。
        if(dirK[i]==0){
            for(int j=0;j<K;j++){
                dirK[i+j]^=1;
            }
            count++;
        }
    }
    if(accumulate(dirK.begin(),dirK.end(),0)!=N) return -1;
    else return count;
}

// O(N) の時間で計算できる。
int calc(int const& K){
    vector<int> f(N,0);
    int res=0;
    int sum=0;
    for(int i=0;i+K<=N;i++){
        if((dir[i]+sum)%2==0){
            // 先頭の牛が後ろを向いている。
            res++;
            f[i]=1;
        }
        sum += f[i];
        if(i-K+1>=0) sum -= f[i-K+1];
    }
    // 残りの牛が前を向いているかチュエック。
    for(int i=N-K+1;i<N;i++){
        if((dir[i]+sum)%2==0){
            return -1;
        }
        if(i-K+1>=0) sum -= f[i-K+1];
    }
    return res;

}

void solve(){
    int K=1;
    int M=N;
    for(int k=(N-1);k>0;k--){
        int m = calc(k);
        if(m>=0 && M>=m){
            M = m;
            K = k;
            // DBG(K)
            // DBG(M)
        }
    }
    DBG(K)
    DBG(M)
}

int main(){
    input();
    solve();
    return 0;
}
