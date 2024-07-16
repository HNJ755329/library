#include <algorithm>
#include <vector>

using G = std::vector<std::vector<int>>;

struct LowLink {
  int n;
  const G g;
  std::vector<int> used, ord, low;
  std::vector<int> articulation;
  std::vector<std::pair<int, int>> bridge;
  std::vector<int> dfsOrd;
  std::vector<int> parent;

  LowLink(const G &g) : n(g.size()), g(g) {}

  int dfs(int cur, int k, int par) {
    used[cur] = true;
    ord[cur] = k++;
    low[cur] = ord[cur];
    parent[cur] = par;
    dfsOrd.push_back(cur);
    bool is_articulation = false;
    int cntChildren = 0;
    for (const int &to : g[cur]) {
      if (!used[to]) {
        ++cntChildren;
        k = dfs(to, k, cur);
        low[cur] = std::min(low[cur], low[to]);
        // (par != -1)&& low[to] >= ord[cur];
        // is_articulation |= ~par && low[to] >= ord[cur];
        if (par != -1)
          is_articulation |= low[to] >= ord[cur];
        if (ord[cur] < low[to])
          bridge.emplace_back(std::minmax(cur, to));
      } else if (to != par) {
      }
      if (par == -1)
        is_articulation |= cntChildren > 1;
      if (is_articulation)
        articulation.push_back(cur);
    }
    return k;
  }

  virtual void build() {
    used.assign(n, 0);
    ord.assign(n, 0);
    low.assign(n, 0);
    parent.assign(n, 0);
    dfsOrd.clear();
    int k = 0;
    for (int i = 0; i < n; i++) {
      if (!used[i])
        k = dfs(i, k, -1);
    }
  }
};

struct blockCutTree {
  LowLink lw;
  int n;
  G bctree;
  int num_bcc;
  std::vector<std::vector<int>> bctree_adj;
  std::vector<int> low;

  blockCutTree(const G &g) : n(g.size()), lw(g) {}

  void build() {
    lw.build();
    low = lw.low;

    num_bcc = 0;
    // must be lowlink dfsOrder
    for (const int &cur : lw.dfsOrd) {
      int par = lw.parent[cur];
      if (par == -1) {
        continue;
      }
      if (low[cur] < lw.ord[par]) {
        low[cur] = low[par];
        bctree_adj[low[cur]].push_back(cur);
      } else {
        low[cur] = num_bcc;
        bctree_adj.push_back(std::vector<int>());
        bctree_adj[num_bcc].push_back(cur);
        bctree_adj[num_bcc].push_back(par);
        num_bcc++;
      }
    }

    bctree.resize(n + num_bcc);
    for (int i = 0; i < num_bcc; i++) {
      for (int x : bctree_adj[i]) {
        bctree[x].push_back(n + i);
        bctree[n + i].push_back(x);
      }
    }
  }
};
