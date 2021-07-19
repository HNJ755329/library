#include <bits/stdc++.h>
using namespace std;

int main()
{
    cout << fixed << setprecision(40);
    cout << "long double\n";
    long double lr;
    for (int i = 0; i < 18; i++)
    {
        lr = pow(10, i);
        lr = nextafter(lr, INFINITY);
        cout << i << " " << lr << endl;
        lr *= -1;
        cout << i << " " << lr << endl;
        lr = abs(lr);
        cout << i << " " << lr << endl;
    }
}