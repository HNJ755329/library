#include <bits/stdc++.h>
template<typename T, typename S> inline ostream& operator<<(ostream& os, const pair<T, S> p) { cout << "[" << p.first << ";" << p.second << "]"; return os; }
template<typename T> inline ostream& operator<<(ostream& os, const vector<T>& v) { for (auto el : v) cout << el << " "; return os; }

int main(){
  int a,b;
  vector<int> v={1,2,3,3,3,4,56,6,7,7,8};
  a = 1;
  b = 2;
  auto min = std::min_element(v.begin(), v.end());
  auto max = std::max_element(v.begin(), v.end());
  int sum = std::accumulate(v.begin(), v.end(), 0);
  cout << v << endl;
  *(min+1)+=10;
  cout << "min : " << *(min+1) << endl;
  cout << "max : " << *(max-1) << endl;
  cout << "sum : " << sum << endl;
  v.erase(max-1);

  cout << v << endl;
}