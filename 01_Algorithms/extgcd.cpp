#include <iostream>
using namespace std;

int extgcd(int a, int b, int& x, int& y){
    int d=a;
    if(b!=0){
        d = extgcd(b,a%b,y,x);
        y -= (a/b)*x;
    }
    else
    {
        x=1;y=0;
    }
    
    return d;
}

int main()
{
    
    int x,y;
    int d = extgcd(49,23,x,y);
    cout << (d) << endl;
    cout << (x) << endl;
    cout << (y) << endl;
    return 0;
}
