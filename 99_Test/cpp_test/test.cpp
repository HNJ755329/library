#include <bits/stdc++.h>
#include "template.hpp"
using namespace std;

int main()
{
    deque<int> dq;
    dq.push_front(1);
    dq.push_front(2);
    dq.back() += 10;
    cout << dq << endl;
    return 0;
}