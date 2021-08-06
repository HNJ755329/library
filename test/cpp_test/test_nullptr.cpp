#include <bits/stdc++.h>
using namespace std;

int main()
{
    char *f;
    f = nullptr;
    char *g;
    g = NULL;

    // C++11からはNULLでなくてnullptrの使用が推奨されている．

    if(f){
        cout << "f is true" << endl;
    }
    if(!f){
        cout << "f is false" << endl;
    }

    if(g){
        cout << "g is true" << endl;
    }
    if(!g){
        cout << "g is false" << endl;
    }

    struct node
    {
        int cnt;
        int dep;
        node *ch[2];
        node() : cnt(0), dep(0), ch{nullptr, nullptr} {};
    };
    node *root;
    root = nullptr;
    if(root){
        cout << "root is not empty" << endl;
    }
    if(!root){
        cout << "root is empty" << endl;
    }
    root = new node;
    if(root){
        cout << root << endl;
        cout << "root is not empty" << endl;
    }
    if(!root){
        cout << "root is empty" << endl;
    }

    return 0;
}