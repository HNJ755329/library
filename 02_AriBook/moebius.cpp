#include <vector>
#include <map>
#include <iostream>
#include <algorithm>

using namespace std;

template< int mod >
struct ModInt {
  int x;
  ModInt() : x(0) {}
  ModInt(int64_t y) : x(y >= 0 ? y % mod : (mod - (-y) % mod) % mod) {}
  ModInt &operator+=(const ModInt &p) {
    if((x += p.x) >= mod) x -= mod;
    return *this;
  }

  ModInt &operator-=(const ModInt &p) {
    if((x += mod - p.x) >= mod) x -= mod;
    return *this;
  }

  ModInt &operator*=(const ModInt &p) {
    x = (int) (1LL * x * p.x % mod);
    return *this;
  }

  ModInt &operator/=(const ModInt &p) {
    *this *= p.inverse();
    return *this;
  }

  ModInt operator-() const { return ModInt(-x); }
  ModInt operator+(const ModInt &p) const { return ModInt(*this) += p; }
  ModInt operator-(const ModInt &p) const { return ModInt(*this) -= p; }
  ModInt operator*(const ModInt &p) const { return ModInt(*this) *= p; }
  ModInt operator/(const ModInt &p) const { return ModInt(*this) /= p; }
  bool operator==(const ModInt &p) const { return x == p.x; }
  bool operator!=(const ModInt &p) const { return x != p.x; }
  ModInt inverse() const {
    int a = x, b = mod, u = 1, v = 0, t;
    while(b > 0) {
      t = a / b;
      swap(a -= t * b, b);
      swap(u -= t * v, v);
    }
    return ModInt(u);
  }

  ModInt pow(int64_t n) const {
    ModInt ret(1), mul(x);
    while(n > 0) {
      if(n & 1) ret *= mul;
      mul *= mul;
      n >>= 1;
    }
    return ret;
  }

  friend ostream &operator<<(ostream &os, const ModInt &p) {
    return os << p.x;
  }

  friend istream &operator>>(istream &is, ModInt &a) {
    int64_t t;
    is >> t;
    a = ModInt< mod >(t);
    return (is);
  }

  static int get_mod() { return mod; }
};
const long long int mod = 10009;
using modint = ModInt< mod >;

template< typename T >
T mod_pow(T x, T n, const T &p) {
  T ret = 1;
  while(n > 0) {
    if(n & 1) (ret *= x) %= p;
    (x *= x) %= p;
    n >>= 1;
  }
  return ret;
}


int N;

void input(){
    N = 2;
}

map<int, int> moebius(int n){
    map<int,int> res;
    vector<int> primes;
    for (int i = 2; i*i <= n; i++)
    {
        if(n%i==0){
            primes.push_back(i);
            while(n%i==0) n /= i;
        }
    }
    if(n!=1) primes.push_back(n);

    int m=primes.size();
    // m個の約数から任意の数だけ選ぶ。bit全探索
    // moebius(a^2) = 0 なので素因数についてだけ求めれば良い。
    for (int bit = 0; bit < (1<<m); bit++)
    {
        int mu=1,d=1;
        for (int j = 0; j < m; j++)
        {
            if(bit>>j & 1){
                mu *= -1;
                d *= primes[j];
            }
        }        
        res[d] = mu;
    }
    return res;    
}

// 約数列挙
vector< int64_t > divisor(int64_t n) {
  vector< int64_t > ret;
  for(int64_t i = 1; i * i <= n; i++) {
    if(n % i == 0) {
      ret.push_back(i);
      if(i * i != n) ret.push_back(n / i);
    }
  }
  sort(begin(ret), end(ret));
  return (ret);
}

void solve(int N=N){
    auto mo = moebius(N);
    modint ans=0;
    auto d = divisor(N); 
    for(auto p:d) ans += mod_pow<int>(26,p,mod)*mo[N/p];
    cout << ans << endl;    
}

int main(){
    input();
    solve(4);
    return 0;
}
