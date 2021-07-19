#include <bits/stdc++.h>
using namespace std;

int main(){
  auto v = std::map<int,std::pair<int,int>>{{1,{0,9}},{2,{10,3}},{3,{1,4}},{4,{2,9}},{5,{3,-1}}};
  auto result = *std::min_element(v.cbegin(), v.cend(), [](const auto& lhs, const auto& rhs) {
          return lhs.second.second < rhs.second.second;    
      });
  std::cout << result.first << std::endl; // 5
}