#include <bits/stdc++.h>
using namespace std;

int main()
{
    deque<int> dq;
    dq.push_front(1);
    dq.push_front(2);
    dq.back() += 10;
    for(auto x:dq) cout << x << endl;
    return 0;
}