#include <bits/stdc++.h>
using namespace std;

int main()
{
    vector<int> A = {11, 235, 45, 6};
    sort(A.begin(), A.end(), [](int a, int b)
         { return a < b; });
    for(auto a:A) cout << a << ' ';
    cout << endl;

    sort(A.begin(), A.end(), [](int a, int b)
         { return a > b; });
    for(auto a:A) cout << a << ' ';
    cout << endl;

    return 0;
}