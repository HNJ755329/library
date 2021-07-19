#include <bits/stdc++.h>
#include "../../00_Library/template.hpp"
using namespace std;

void debug_out() { cerr << endl; } 
template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {cerr << " " << H; debug_out(T...);}
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)

vector<vector<int>> G(2,vector<int>(2,0));
vector<vector<int>> E;
void init(){
    for (int i = 0; i < 2; i++)
    {
        G[i][i] = 1;
    }
    E = G;
}

int main(){
    const int a = 10;
    int b = a;
    debug(a,b);
    b = 20;
    const int c = b;
    debug(a,b,c);
    init();
    debug(G);
    debug(E);
}