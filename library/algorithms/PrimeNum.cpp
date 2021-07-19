#include <iostream>
#include <vector>

using namespace std;
template<typename T> inline ostream& operator<<(ostream& os, const vector<T>& v) { for (auto el : v) cout << el << " "; return os; }

vector<bool> IsPrime;
vector<int> Prime;

void sieve(int max){
    if(max+1 > IsPrime.size()){     // resizeで要素数が減らないように
        IsPrime.resize(max+1,true); // IsPrimeに必要な要素数を確保
    } 
    IsPrime[0] = false; // 0は素数ではない
    IsPrime[1] = false; // 1は素数ではない

    for(int i=2; i<=max; ++i) // 0からmaxまで調べる
        if(IsPrime[i]) // iが素数ならば
        {
            for(int j=2; i*j<=max; ++j) // (max以下の)iの倍数は
            IsPrime[i*j] = false;      // 素数ではない
            Prime.emplace_back(i);
        }
}

int main()
{
    int M = 100000;
    sieve(M);
    cout << (Prime.size()) << endl;
    cout << (Prime) << endl;
}
