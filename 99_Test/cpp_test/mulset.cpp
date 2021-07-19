#include <bits/stdc++.h>
#include "../../00_Library/template.hpp"
using namespace std;

void debug_out() { cerr << endl; } 
template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {cerr << " " << H; debug_out(T...);}
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)

int main(){
    multiset<int> se;
    se.insert(-1);
    se.insert(-10);
    se.insert(-50);
    se.insert(-100);
    debug(*se.begin());
    debug(*se.rbegin());
    debug(*--se.end());
    return 0;
}