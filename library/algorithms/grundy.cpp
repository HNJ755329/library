#include <set>
#include <iostream>
#include <vector>

using namespace std;
struct position{};

int grundyNumber(position pos){
  vector<position> next;// = { posから遷移できる全ての座標 };
  set<int> s; // 集合を用意します
  for(position x : next)
    s.insert( grundyNumber(x) ); //遷移先のgrundy numberを集合に追加します
  //集合sに含まれない非負の整数の中で最小値を、このposのgrundy numberとします
  int res = 0;
  while( s.find(res)!=s.end() ) res++;
  return res;
}

int main(){
    return 0;
}
