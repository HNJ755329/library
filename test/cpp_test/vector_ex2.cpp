#include <bits/stdc++.h>
#include <queue>
using namespace std;
template<typename T> inline ostream& operator<<(ostream& os, const vector<T>& v) { for (auto el : v) cout << el << " "; return os; }

// vectorの特徴:末尾への挿入・削除のみ高速	
int main(){
  std::vector<int> X;
  X.push_back(58);
  X.push_back(9);
  X.push_back(2);
  X.push_back(6);
  X.push_back(13);
  X.push_back(96);

  std::sort(X.begin(),X.end());
  for(int i=0;i<X.size();i++){
    std::cout << "X.at(" << i << ") : " << X.at(i) << std::endl;
  }
  std::cout << std::boolalpha;
  std::cout << "binary_search of X in 13:" << std::binary_search(X.begin(),X.end(),13) << std::endl;
  std::cout << "binary_search of X in  1:" << std::binary_search(X.begin(),X.end(),1) << std::endl;
  std::cout << "binary_search of X in  8:" << std::binary_search(X.begin(),X.end(),8) << std::endl;

  std::vector<int>::iterator it = std::find(X.begin(), X.end(), 13);
  int index = std::distance(X.begin(), it);
  std::cout << index << std::endl;
  X.erase(it);
  std::cout << X << std::endl;
  while(next_permutation(X.begin(),X.end())){
    cout << X << endl;
  }
  
  return 0;
  
}