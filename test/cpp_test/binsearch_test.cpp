#include <bits/stdc++.h>
using namespace std;

void debug_out() { cerr << endl; } 
template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {cerr << " " << H; debug_out(T...);}
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)

int main(){
    vector<int> v = {2,2,5,5,8,9,15};
    debug("lower_bound");
    auto itr = lower_bound(v.begin(),v.end(),5);
    debug(*itr);
    debug(itr-v.begin());
    debug(v.end()-itr);

    itr = lower_bound(v.begin(),v.end(),20);
    debug(*itr);
    debug(itr-v.begin());
    debug(v.end()-itr);


    debug("upper_bound");
    itr = upper_bound(v.begin(),v.end(),5);
    debug(*itr);
    debug(itr-v.begin());
    debug(v.end()-itr);

    itr = upper_bound(v.begin(),v.end(),2);
    debug(*itr);
    debug(itr-v.begin());
    debug(v.end()-itr);

}