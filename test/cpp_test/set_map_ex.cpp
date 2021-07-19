#include <bits/stdc++.h>
#include <queue>

int main(){
  // set について
  std::set<int> s;
  s.insert(5);
  s.insert(8);
  s.insert(9);

  std::cout << std::boolalpha;
  std::cout << "s.size() :" << s.size() << std::endl;
  std::cout << "s.max_size() :" << s.max_size() << std::endl;
  std::cout << "s.empty() :" << s.empty() << std::endl;

  std::set<int>::iterator itr;
  for(itr=s.begin();itr!=s.end();itr++){
    printf("Element of set : %d \n", *itr);
  }
  std::set<int> t;
  t.insert(41);
  t.insert(20);
  s.operator=(t);

  std::cout << std::boolalpha;
  std::cout << "s.size() :" << s.size() << std::endl;
  std::cout << "s.max_size() :" << s.max_size() << std::endl;
  std::cout << "s.empty() :" << s.empty() << std::endl;

  for(itr=s.begin();itr!=s.end();itr++){
    printf("Element of set : %d \n", *itr);
  }

  // map について
  std::map<int,std::string> m;
  // 値の設定の仕方は以下のどちらでも良い。
  std::cout << "m.size() :" << m.size() << std::endl;

  m[10] = "test";
  m.insert(std::make_pair(1,"ttt"));

  std::cout << std::boolalpha;
  std::cout << "m.size() :" << m.size() << std::endl;
  std::cout << "m.max_size() :" << m.max_size() << std::endl;
  std::cout << "m.empty() :" << m.empty() << std::endl;

  std::cout << m[10] << std::endl;
  for(std::map<int,std::string>::iterator ite=m.begin();ite!=m.end();ite++){
    // printf("%d %s \n",ite->first, ite->second.c_str());
    std::cout << "Element of map :" << ite->first << " : " << ite->second << std::endl;
  }

  for(const auto& [key,value]:m){
    std::cout << key << value << std::endl;
  }
  // debug でも集合やマップの中身を見れるのでそんなに全要素を見たい欲求はない。
  return 0;
}