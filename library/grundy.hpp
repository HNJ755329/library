#include <set>
#include <vector>

template <typename T, typename U>
U grundyNumber(T pos)
{
  std::vector<T> next; // = { posから遷移できる全ての座標 };
  std::set<U> s;     // 集合を用意します
  for (T x : next) s.insert(grundyNumber(x)); //遷移先のgrundy numberを集合に追加します
  //集合sに含まれない非負の整数の中で最小値を、このposのgrundy numberとします
  U res = 0;
  while (s.find(res) != s.end()) res++;
  return res;
}