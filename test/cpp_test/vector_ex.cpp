#include <bits/stdc++.h>
#include <queue>

#ifdef __LOCAL
    #define DBG(X) cout << #X << " = " << (X) << endl;
    #define SAY(X) cout << (X) << endl;
#else
    #define DBG(X)
    #define SAY(X)
#endif

using namespace std;
template<typename T> inline ostream& operator<<(ostream& os, const vector<T>& v) { for (auto el : v) cout << el << " "; return os; }

// vectorの特徴:末尾への挿入・削除のみ高速	
int main(){
  vector<int> X;
  X.push_back(58);
  X.push_back(9);
  X.push_back(2);
  X.push_back(6);
  X.push_back(13);
  X.push_back(96);
  X.pop_back();
  X.pop_back();
  X[1] = 28;
  cout << boolalpha;

  DBG(X.size())
  DBG(X.max_size())
  DBG(X.empty())
  DBG(X.capacity())

  cout << "X" << endl;
  DBG(X.front())
  DBG(X.back())
  DBG(X)

  sort(X.begin(),X.end());
  cout << "X sorted" << endl;
  DBG(X.front())
  DBG(X.back())
  DBG(X)

  vector<int> Y;
  Y.push_back(76);
  Y.push_back(34);
  cout << "vector X の後ろに別の vector Y を追加"<< endl;
  // X.insert(X.end(), Y.begin(), Y.end());
  // insert でもできるけど copy 使ったほうがイイらしい。
  // サイズの大きい方に追加する。メモリの関係上。
  cout << Y << endl;
  if(X.size()>=Y.size()) copy(Y.begin(),Y.end(),back_inserter(X));
  else copy(X.begin(),X.end(),back_inserter(Y));
  cout << X << endl;
  vector<int>::iterator it;
  for(it=X.begin()+1;it!=X.end();it++){
    if(*it>1) break;
  }
  cout << (it==X.end()-1) << endl;
  cout << *(X.end()-1) << endl;
  cout << X[3/2+1] << endl;
  X.erase(X.end()-1);
  cout << X << endl;

  vector<vector<int>> Z;
  Z.assign(1,vector<int>(1,0));
  DBG(Z)
  DBG(Z.empty())
  Z[0].erase(Z[0].begin());
  DBG(Z)
  DBG(Z[0].empty())


  return 0;


}