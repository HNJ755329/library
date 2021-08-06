#include <iostream>
#include <vector>
using namespace std;

template <int char_size, int base>
struct Trie
{
    struct Node
    {                           // 頂点を
        vector<int> next;       // 子の頂点番号を格納。存在しなければ-1
        vector<int> accept;     // 末端がこの頂点になる文字列の str_id を保存
        int c;                  // base からの間隔をint型で表現したもの
        int common;             // いくつの文字列がこの頂点を共有しているか
        vector<long long int> common_char; //文字cを含む子孫の数
        Node(int c_) : c(c_), common(0)
        {
            next.assign(char_size, -1);
            common_char.assign(char_size, 0);
        }
    };
    vector<Node> nodes; // trie 木本体
    int root;           // 根
    Trie() : root(0)
    {
        // 初期化。はじめは根しか無い
        nodes.push_back(Node(root));
    }

    void insert(const string &word, int word_id)
    { // 単語:str と 単語の番号: str_id
        int node_id = 0;
        for (int i = 0; i < (int)word.size(); i++)
        {
            int c = (int)(word[i] - base);
            int &next_id = nodes[node_id].next[c];
            if (next_id == -1)
            { // 次の頂点が存在しなければ追加
                next_id = (int)nodes.size();
                nodes.push_back(Node(c));
            }
            ++nodes[node_id].common;
            node_id = next_id;
        }
        ++nodes[node_id].common;
        nodes[node_id].accept.push_back(word_id); // 単語の終端なので、頂点に番号を入れておく
    }
    void insert(const string &word) { insert(word, nodes[0].common); }

    // 単語とprefixの検索. indexを返す
    int search(const string &word)
    {
        int node_id = 0;
        for (int i = 0; i < (int)word.size(); i++)
        {
            int c = (int)(word[i] - base);
            int &next_id = nodes[node_id].next[c];
            if (next_id == -1)
            { // 次の頂点が存在しなければ終了
                return -1;
            }
            node_id = next_id;
        }
        // return (prefix) ? true : nodes[node_id].accept.size() > 0; // 最後の頂点が受理状態か確認
        return node_id;
    }

    void fill_common_char()
    {
        for (int node_id = (int)nodes.size() - 1; node_id >= 0; node_id--)
        {
            Node &node = nodes[node_id];
            for (int c = 0; c < 26; c++)
            {
                int next_id = node.next[c];
                if (next_id == -1)
                    continue;
                Node &next_node = nodes[next_id];
                for (int d = 0; d < 26; d++)
                {
                    node.common_char[d] += next_node.common_char[d];
                }
            }
            // 全ての子孫はcを含む
            if (node.c != -1)
                node.common_char[node.c] = node.common;
        }
    }
};

int main()
{
    return 0;
}