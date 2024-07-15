#include <map>
struct interval_manager {
  using T = long long int;
  std::map<T, T> st;
  interval_manager() = default;
  using const_iterator = typename std::map<T, T>::const_iterator;
  const_iterator begin() const { return st.begin(); }
  const_iterator end() const { return st.end(); }
  const_iterator lower_bound(T x) const {
    auto it = st.lower_bound(x);
    if (it == begin() || prev(it)->second <= x)
      return it;
    return prev(it);
  }
  const_iterator erase(const_iterator it) { return st.erase(it); }
  void erase(T l, T r) {
    if (l >= r)
      return;
    auto L = st.upper_bound(l);
    auto R = st.upper_bound(r);
    if (L != begin() && l <= prev(L)->second) {
      L--;
    }
    if (L == R) {
      return;
    }
    T nl = std::min(l, L->first);
    T nr = std::max(r, prev(R)->second);
    st.erase(L, R);
    if (nl < l)
      st[nl] = l;
    if (r < nr)
      st[r] = nr;
  }
  void intersect(T l, T r) {
    if (l >= r) {
      st.clear();
      return;
    }
    if (!empty())
      erase(begin()->first, l);
    if (!empty())
      erase(r, (--end())->second);
  }
  // add [l,r)
  void add_interval(T l, T r) {
    if (l >= r)
      return;
    auto itr = lower_bound(l);
    if (itr == end()) {
      st[l] = r;
      return;
    }
    if (itr->first < r) {
      T nl = std::min(l, itr->first);
      T nr = std::max(r, itr->second);
      itr = erase(itr);
      while (itr != end() && itr->first < nr) {
        nl = std::min(nl, itr->first);
        nr = std::max(nr, itr->second);
        itr = erase(itr);
      }
      st[nl] = nr;
    } else {
      st[l] = r;
    }
  }
  // use merge technique
  void merge(interval_manager &m) {
    if (st.size() < m.st.size()) {
      swap(st, m.st);
    }
    for (auto itr = m.begin(); itr != m.end(); itr++) {
      add_interval(itr->first, itr->second);
    }
  }
  // cut i [l,r) -> [l,i) [i,r)
  void cut(T i) {
    auto it = lower_bound(i);
    if (it == end())
      return;
    auto [x, y] = *it;
    if (x < i && i < y) {
      erase(it);
      st[x] = i;
      st[i] = y;
    }
  }
  bool empty() const { return st.empty(); }
  size_t size() const { return st.size(); }
  T length() const {
    T res = 0;
    for (auto itr = begin(); itr != end(); itr++) {
      res += itr->second - itr->first;
    }
    return res;
  }
};
