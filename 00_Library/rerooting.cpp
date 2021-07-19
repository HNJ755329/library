#include <vector>

template<typename M>
class ReRooting {
public:
    using T = typename M::T;
    using U = typename M::U;
    struct Node {
        int to, rev;
        U val;
        Node(int u, int v, U val) : to(u), rev(v), val(val) {};
    };
    int n;
    std::vector<std::vector<Node>> G;
    std::vector<std::vector<T>> dpl, dpr;
    std::vector<int> l, r;

    explicit ReRooting(int n) : n(n), G(n), dpl(n), dpr(n), l(n), r(n) {};

    void add_edge(int u, int v, const U &x) {
        G[u].emplace_back(v, G[v].size(), x);
        G[v].emplace_back(u, G[u].size()-1, x);
    }
    void add_edge(int u, int v, const U &x, const U &y) {
        G[u].emplace_back(v, G[v].size(), x);
        G[v].emplace_back(u, G[u].size()-1, y);
    }

    T dfs(int i, int par){
        while(l[i] != par && l[i] < (int)G[i].size()){
            auto &e = G[i][l[i]];
            dpl[i][l[i] + 1] = M::f(dpl[i][l[i]], M::g(dfs(e.to, e.rev), e.val));
            ++l[i];
        }
        while(r[i] != par && r[i] >= 0){
            auto &e = G[i][r[i]];
            dpr[i][r[i]] = M::f(dpr[i][r[i] + 1], M::g(dfs(e.to, e.rev), e.val));
            --r[i];
        }
        if(par < 0) return dpr[i].front();
        return M::f(dpl[i][par], dpr[i][par+1]);
    }

    std::vector<T> solve(){
        for (int i = 0; i < n; ++i) {
            dpl[i].assign(G[i].size()+1, M::e());
            dpr[i].assign(G[i].size()+1, M::e());
            l[i] = 0;
            r[i] = (int)G[i].size() - 1;
        }
        std::vector<T> ans(n);
        for (int i = 0; i < n; ++i) {
            ans[i] = dfs(i, -1);
        }
        return ans;
    }
};

// 問題によってMの中身を書き換える。
// この問題では{求める総数、子ノードの数}をデータとして持つ。
// struct M {
//     using T = pair<int, int>;
//     using U = int;
//     // 親ノードaと子どもノードbから新たに親ノードを求める式
//     static T f(T a, T b) { return {a.first*b.first, a.second+b.second}; }
//     // 子どものノードを親のノードに足す前処理的な。
//     static T g(T a, U b) { return {a.first, a.second+b}; }
//     // 単位元。初期値。子どものないノードが持つ値。
//     static T e() { return {1, 0}; }
// };

// // いわゆる全方位木DP
// // https://atcoder.jp/contests/abc160/submissions/11289071
// int main() {
//     int n;
//     cin >> n;
//     ReRooting<M> G(n);
//     for (int i = 0; i < n-1; ++i) {
//         int a, b;
//         scanf("%d %d", &a, &b);
//         a--; b--;
//         G.add_edge(a, b, 1);
//     }
//     auto ans = G.solve();
//     for (int i = 0; i < n; ++i) {
//         printf("%d\n", ans[i].first.val);
//     }
//     return 0;
// }
