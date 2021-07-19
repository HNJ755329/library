#include <bits/stdc++.h>
using namespace std;

int main(){
  int a,b;
  a = 451;
  b = 670;
  cout << a << setw(15) << " = "  << (bitset<10>(a)) << endl;
  cout << b << setw(15) << " = " << (bitset<10>(b)) << endl;
  cout << a << " and " << b << setw(7) << " = " << bitset<10>(a&b) << endl;
  cout << a << " or  " << b << setw(7) << " = " << bitset<10>(a|b) << endl;
  cout << a << " xor " << b << setw(7) << " = " << bitset<10>(a^b) << endl;

  cout << boolalpha << endl;
  cout << (a&(1<<7)) << endl;
  if(a&(1<<7)) cout << "true" << endl;

  for(int i = 0;i<10;i++){
    cout << bitset<10>((1<<i)) << endl;
  }

  for(int i = 0;i<10;i++){
    cout << bitset<10>(~(1<<i)) << endl;
  }
  // c に含まれるフラグの数
  int c;
  c |= 1 << 8;
  cout << c << setw(15) << " = "  << (bitset<32>(c)) << endl;
  c |= 1 << 5;
  cout << c << setw(15) << " = "  << (bitset<32>(c)) << endl;
  c |= 1 << 2;
  cout << c << setw(15) << " = "  << (bitset<32>(c)) << endl;
  c &= ~(1 << 5);
  cout << c << setw(15) << " = "  << (bitset<32>(c)) << endl;
  c = 0;
  cout << c << setw(15) << " = "  << (bitset<32>(c)) << endl;
  c -= 1;
  cout << c << setw(15) << " = "  << (bitset<32>(c)) << endl;
  c &= ~(1 << 5);
  cout << c << setw(15) << " = "  << (bitset<32>(c)) << endl;

  cout << __builtin_popcount(c) << endl;

  int n=9;
  for(int bit=0;bit<(1<<n);bit++){
    vector<int> S;
    for(int i=0;i<n;i++){
      if(bit&(1<<i)) S.push_back(i);
    }
    cout << bit << ": {";
    for(int i=0;i<(int)S.size();i++){
      cout << S[i] << ",";
    }
    cout << "} " << endl;

  }

  c =0;
  c |= 1 << 8;
  cout << c << setw(15) << " = "  << (bitset<32>(c)) << endl;
  c |= 1 << 5;
  cout << c << setw(15) << " = "  << (bitset<32>(c)) << endl;
  int d = c >> 1;
  cout << d << setw(15) << " = "  << (bitset<32>(d)) << endl;

  d <<= 1;
  cout << d << setw(15) << " = "  << (bitset<32>(d)) << endl;

  return 0;
}