#include <string>
#include <iostream>

using namespace std;
using ull = unsigned long long int;
const ull MASK30 = (1UL << 30) - 1;
const ull MASK31 = (1UL << 31) - 1;
const ull MOD = (1UL << 61) - 1;
const ull MASK61 = MOD;
const ull base = 1e9 + 7;

// mod = 2^64だと衝突が起こりやすい。
// （少なくともコンテストでは衝突するようなサンプルが高い確率で含まれる。）
// mod = 2^61-1とする。素数かつ数が大きいので衝突が起こりにくい。
// baseもできるだけランダムにとる。

//mod 2^61-1を計算する関数
ull CalcMod(ull x)
{
    ull xu = x >> 61;
    ull xd = x & MASK61;
    ull res = xu + xd;
    if (res >= MOD)
        res -= MOD;
    return res;
}

//a*b mod 2^61-1を返す関数(最後にModを取る)
ull Mul(ull a, ull b)
{
    ull au = a >> 31;
    ull ad = a & MASK31;
    ull bu = b >> 31;
    ull bd = b & MASK31;
    ull mid = ad * bu + au * bd;
    ull midu = mid >> 30;
    ull midd = mid & MASK30;
    return CalcMod(au * bu * 2 + midu + (midd << 31) + ad * bd);
}

// aはbに含まれているか？
bool contain(string a, string b)
{
    int al = a.length(), bl = b.length();
    if (al > bl)
        return false;
    ull t = 1;
    for (int i = 0; i < al; i++)
    {
        t = Mul(t, base);
    }

    ull ah = 0, bh = 0;
    for (int i = 0; i < al; i++)
        ah = CalcMod(Mul(ah, base) + a[i]);
    for (int i = 0; i < al; i++)
        bh = CalcMod(Mul(bh, base) + b[i]);

    for (int i = 0; i + al <= bl; i++)
    {
        if (ah == bh)
            return true;
        if (i + al < bl)
            bh = CalcMod(Mul(bh, base) + b[i + al] + MOD - Mul(b[i], t));
    }
    return false;
}

int main()
{
    string s, t;
    cout << contain(s, t);
}