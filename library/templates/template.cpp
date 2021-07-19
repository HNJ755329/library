#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <deque>
#include <queue>
#include <stack>
#include <set>
#include <random>
#include <string>
#include "./mydebug.cpp"
#include "./myconst.cpp"

static std::mt19937 _g(time(nullptr)); 
inline long long int randint(long long int a, long long int b) { long long int w = (_g() << 31LL) ^ _g(); return a + w % (b - a + 1); }
inline void fast_io() { std::ios_base::sync_with_stdio(false); std::cin.tie(nullptr); std::cout.tie(nullptr); };
template<typename T, typename S> inline std::ostream& operator<<(std::ostream& os, const std::pair<T, S> p) { std::cout << "[" << p.first << ";" << p.second << "]"; return os; }
template<typename T, typename S> inline std::ostream& operator<<(std::ostream& os, const std::map<T, S> p) { for (auto el : p) std::cout << "[" << el.first << ";" << el.second << "]"; return os; }
template<typename T, typename S> inline std::ostream& operator<<(std::ostream& os, const std::unordered_map<T, S> p) { for (auto el : p) std::cout << "[" << el.first << ";" << el.second << "]"; return os; }
template<typename T> inline std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) { for (auto el : v) std::cout << el << " "; return os; }
template<typename T> inline std::ostream& operator<<(std::ostream& os, const std::vector<std::vector<T>>& v) { for (auto el : v) std::cout << el << "\n"; return os; }
template<typename T> inline std::ostream& operator<<(std::ostream& os, const std::deque<T>& v) { for (auto el : v) std::cout << el << " "; return os; }
template<typename T> inline std::ostream& operator<<(std::ostream& os, const std::queue<T>& v) { for (auto el : v) std::cout << el << " "; return os; }
template<typename T> inline std::ostream& operator<<(std::ostream& os, const std::stack<T>& v) { for (auto el : v) std::cout << el << " "; return os; }
template<typename T> inline std::ostream& operator<<(std::ostream& os, const std::set<T>& v) { for (auto el : v) std::cout << el << " "; return os; }
template<typename T> inline std::ostream& operator<<(std::ostream& os, const std::multiset<T>& v) { for (auto el : v) std::cout << el << " "; return os; }
template<typename T> inline std::istream& operator>>(std::istream&is, std::vector<T> &vec) {for (T &x : vec) is >> x;return is;}
template<typename T> inline std::vector<T> fetch_vec(int sz) { std::vector<T> ret(sz); for (auto& elem : ret) std::cin >> elem; return ret; }
template<class T> inline bool chmax(T &a, const T &b) { if (a<b) { a=b; return 1; } return 0; }
template<class T> inline bool chmin(T &a, const T &b) { if (b<a) { a=b; return 1; } return 0; }
#include <atcoder/modint>
inline std::ostream &operator<<(std::ostream &os, const atcoder::modint1000000007 &x){std::cout << x.val(); return os; }
inline std::ostream &operator<<(std::ostream &os, const  atcoder::modint998244353 &x){std::cout << x.val(); return os; }
