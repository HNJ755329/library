#include <bits/stdc++.h>
#include "template.hpp"
using namespace std;

int main()
{
    string a = "0123456789";
    int i = 5;
    string s = a.substr(0, i) + "#" + a.substr(i + 1);
    // [a,s]: 0123456789 01234#6789
    debug(a, s);
    i = 10;
    string t = a.substr(0, i) + "#" + a.substr(i);
    // [a,s]: 0123456789 0123456789# 
    debug(a, t);
}