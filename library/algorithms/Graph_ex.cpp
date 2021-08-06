#include <bits/stdc++.h>

using namespace std;
using ll = long long int;
using pii = pair<int, int>;
// ダイクストラ法：単一始点最短経路問題（負の閉路がない場合）, O(E * logV)
// ベルマンフォード法：単一始点最短経路問題（負の閉路がある場合）, O(V*E)
// ワーシャルフロイド法：全点対最短経路問題, O(V^3)

class Graph{
    private:
        //  number of vertices
        int V;
        // In a weighted graph, we need to store vertex and weight.
        unordered_map<int,unordered_map<int,int> > edge;
    public:
        Graph(int x):V(x){REP(i,V) add_edge(i,i,0);}
        int get_vertex(){return V;}
        void add_edge(int x, int y, int cost=1){
            edge[x][y] = cost;
            // edge[y][x] = cost;
        };
        auto get_edge(){return edge;}
        auto get_edge(int x, int y){
            try{return edge.at(x).at(y);}
            catch(...){return INF;}
            }

        // source から各点までの最短距離を出力する。
        vector<int> Dijkstra(int source){
            vector<int> dist(V,INF);
            dist[source]=0;
            priority_queue<pii,vector<pii>, greater<pii>> pque;
            pque.push(make_pair(0,source));
            while(!pque.empty()){
                // 最短距離を進んでるものから取り出していく。
                // priority_queueのお陰でlogEに収まってる。
                auto now = pque.top();
                pque.pop();
                int x = now.second;
                int costs = now.first;
                if(dist[x] < costs) continue;
                // unorderd_map<int,int> to 
                // to.first is sink of x
                // to.second is cost x->to.first
                for(auto to:edge[x]){
                    if(dist[to.first] > dist[x]+to.second){
                        dist[to.first] = dist[x]+to.second;
                        pque.push(make_pair(dist[to.first], to.first));
                    }
                }

            }
            return dist;
        }
        void Warshall_Floyd(){
            for (int i = 0; i < V; i++) for (int j = 0; j < V; j++) for (int k = 0; k < V; k++)
                add_edge(i, j, min(get_edge(i,j),get_edge(i,k)+get_edge(k,j)));
        }

};

int main() {

    int V,E,r;
    cin >> V >> E >> r;
    Graph G(V);

    for (int i = 0; i < E; i++)
    {
        int s,t,d;
        cin >> s >> t >> d;
        G.add_edge(s,t,d);
    }

    cout << G.Dijkstra(r);
    // Warshall FloydはO(V^3)なのでVの大きさを見てから使うか決める。
    // Vが1e3ぐらい小さくないと使えない。
    // G.Warshall_Floyd();
    // cout << G.get_edge()[r] << endl;
}