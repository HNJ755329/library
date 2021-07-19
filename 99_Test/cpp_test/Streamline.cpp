#include <bits/stdc++.h>
#include <queue>
// vectorの特徴:末尾への挿入・削除のみ高速
int main()
{
  int N, M;
  std::cin >> N >> M;
  if (N >= M)
  {
    std::cout << "0" << std::endl;
    return 0;
  }
  std::vector<int> X;
  for (int i = 0; i < M; i++)
  {
    int input;
    std::cin >> input;
    X.push_back(input);
  }
  std::sort(X.begin(), X.end());
  std::vector<int> Diff;
  for (int i = 0; i < M - 1; i++)
  {
    Diff.push_back(X[i + 1] - X[i]);
  }
  std::sort(Diff.begin(), Diff.end());
  int sum;
  sum = std::accumulate(Diff.begin(), Diff.end() - N + 1, 0);
  // map だと accumulate がないので, vector を使う。
  std::cout << sum << std::endl;
  return 0;
}