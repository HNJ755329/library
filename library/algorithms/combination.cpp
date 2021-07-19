#include <iostream>
using namespace std;

long long combidb[5000][5000];
long long mod = 1e9+7;

long long combination(int const& n, int const& k){
  if(combidb[n][k] != 0) return combidb[n][k];
  if(n==k) return 1;
  if(k==0) return 1;
  if(k==1) return n;
  return combidb[n][k] = (combination(n-1,k)%mod + combination(n-1,k-1)%mod)%mod;
}

int main(){
  int k,K;
  k= 1;
  K = 100;
  cout << combination(4000,2000) << endl;
}