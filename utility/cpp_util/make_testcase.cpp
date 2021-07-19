#include <bits/stdc++.h>
using namespace std;

using ll = long long int;
using ull = unsigned long long int;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;


inline void fast_io() { ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr); };
template<typename T> inline T sign(T x) { return T(x > 0) - T(x < 0); }
template<typename T, typename S> inline ostream& operator<<(ostream& os, const pair<T, S> p) { cout << "[" << p.first << ";" << p.second << "]"; return os; }
template<typename T> inline ostream& operator<<(ostream& os, const vector<T>& v) { for (auto el : v) cout << el << " "; return os; }
template<typename T> inline T fetch() { T ret; cin >> ret; return ret; }
template<typename T> inline vector<T> fetch_vec(int sz) { vector<T> ret(sz); for (auto& elem : ret) cin >> elem; return ret; }

void deleteNl(std::string &targetStr)
{
    const char CR = '\r';
    const char LF = '\n';
    std::string destStr;
    for (std::string::const_iterator it = targetStr.begin(); it != targetStr.end(); ++it) {
        if (*it != CR && *it != LF) {
            destStr += *it;
        }
    }
    targetStr = destStr;
}


int fetch_testcase(string const& filename, vector<int> &vec_input){
    std::ifstream ifs(filename);
    std::string str;
    if (ifs.fail())
    {
        std::cerr << "!Failure" << std::endl;
        return -1;
    }
    
    while(getline(ifs, str,' ')){
        deleteNl(str);
        if(str=="") continue;
        else vec_input.push_back(stoi(str));
    }
    return 0;
}

void save_testcase(string const& filename, vector<int> const& output_vec){
    ofstream outputfile(filename);
    for(auto elem:output_vec){
        outputfile << elem << " ";
    }
    outputfile << endl;
}

int main()
{
    // vector<int> output_vec={2,3,5,7};
    // save_testcase("testcase.txt", output_vec);

    vector<int> input_vec;
    fetch_testcase("testcase.txt", input_vec);
    cout << input_vec << endl;
    vector<int>::iterator itr = input_vec.begin();
    int N = *itr; itr++;
    int a[10];
    for(int i=0;i<N;i++){
        a[i] = *itr;
        itr++;
    }

    cout << N << endl;
    for(int i=0;i<N;i++){
        cout << i << " : " << a[i] << endl;
    }
}
