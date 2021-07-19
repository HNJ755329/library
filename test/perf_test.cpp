#include <bits/stdc++.h>
using ull = unsigned long long int;
using namespace std;
// perf 用に重い処理を実装する。


ull Fib(int const& n){
    if(n==1|n==2) return 1;
    else return Fib(n-1) + Fib(n-2);    
}

// memo化
ull FibDB[10000];
ull Fib_m(int const& n){
    if(FibDB[n]) return FibDB[n];
    if(n==1|n==2) return FibDB[n] = 1;
    else return FibDB[n] = Fib_m(n-1) + Fib_m(n-2);
}

int heavy_do(){
    for(int i=0;i<1e5;i++){
        cout << i*i << endl;
    }
    return 0;
}


int main()
{
    for(int i=1;i<40;i++){
        cout << i << " : " << Fib(i) << endl;
    }

    for(int i=1;i<40;i++){
        cout << i << " : " << Fib_m(i) << endl;
    }
    heavy_do();
    return 0;
}
