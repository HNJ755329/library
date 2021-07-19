#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

class Union{
  private:
    int N;
    std::map<int,int> parent;
    std::map<int,int> rank;
  public:
    Union(int const& n=100);
    int find_root(int const& x);
    void unite(int x, int y);
    bool same(int const& x, int const& y);
};

// 初期化
// コンストラクタ
Union::Union(int const& n){
  N = n;
  for(int i=0;i<n;i++){
    parent[i]=i;
    rank[i]=0;
  }
}

// 木の根を求める
int Union::find_root(int const& x){
  if(x >= N) return N;
  if(parent[x]==x){
    return x;
  } else {
    return parent[x] = find_root(parent[x]);
  }
}

// x と y の属する集合を合併
void Union::unite(int x, int y){
  x = find_root(x);
  y = find_root(y);
  if(x == y) return;
  if(rank[x] < rank[y]){
    parent[x] = y;
  } else {
    parent[y] = x;
    if(rank[x] == rank[y]) rank[x]++;
  }
}

// x と y が同じ集合に属するか否か。
bool Union::same(int const& x, int const& y){
  return (Union::find_root(x) == Union::find_root(y));
}


// 別の形のunion find
struct UnionFind {
  std::vector<int> data;
 
  UnionFind(int sz) {
    data.assign(sz, -1);
  }
 
  bool unite(int x, int y) {
    x = find(x), y = find(y);
    if(x == y) return (false);
    if(data[x] > data[y]) std::swap(x, y);
    data[x] += data[y];
    data[y] = x;
    return (true);
  }
 
  int find(int k) {
    if(data[k] < 0) return (k);
    return (data[k] = find(data[k]));
  }
 
  int size(int k) {
    return (-data[find(k)]);
  }

  bool same(int i, int j){
    return find(i)==find(j);
  }
};

int main(){
  Union u(10);
  u.unite(0,1);
  u.unite(1,2);
  u.unite(2,3);
  u.unite(2,4);
  u.unite(5,6);
  u.unite(5,7);
  u.unite(6,8);
  u.unite(6,9);
  std::cout << std::boolalpha;
  std::cout << u.same(1,3) << std::endl;
  std::cout << u.same(6,7) << std::endl;
  std::cout << u.same(1,8) << std::endl;

  Union v(5);
  v.unite(0,1);
  v.unite(2,3);
  v.unite(3,4);
  std::cout << std::boolalpha;
  std::cout << v.same(1,3) << std::endl;
  std::cout << v.same(2,4) << std::endl;
  std::cout << v.same(0,5) << std::endl;
  std::cout << v.same(0,8) << std::endl;

  return 0;
}