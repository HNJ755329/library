#include <bits/stdc++.h>
using namespace std;

// xを新たにコピーしてつかう。
// もとのｘが変化することはない。
// メモリを多くとる。
int func1(int x){
  x = x*2;
  return x;
}

// 因数のｘをそのままつかう。
// もとのｘに対して操作できる。メモリを節約できる。
int func2(int& x){
  x += 2;
  x += 2;
  x += 2;
  int y = x+1;
  return y;
}

// constつけてるのにｘを書き換えてるのでエラーになる。
// int func3(const int& x){
//   x = x*2;
//   return x;
// }


int main()
{
  int x,y,z;
  x = 100;
  y=z=0;
  printf("x:%d y:%d z :%d \n",x,y,z);
  y = func1(x);
  printf("x:%d y:%d z :%d \n",x,y,z);
  z = func2(x);
  printf("x:%d y:%d z :%d \n",x,y,z);
  // z = func3(x);
  // エラー

  return 0;
}