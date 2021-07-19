#include <deque>
#include <vector>
#include <iostream>
#ifdef __LOCAL
    #define DBG(X) cout << #X << " = " << (X) << endl;
    #define SAY(X) cout << (X) << endl;
#else
    #define DBG(X)
    #define SAY(X)
#endif

using namespace std;

template<typename T> inline ostream& operator<<(ostream& os, const vector<T>& v) { for (auto el : v) os << el << " "; return os; }
template<typename T> inline ostream& operator<<(ostream& os, const deque<T>& v) { for (auto el : v) os << el << " "; return os; }

vector<int> slide_min(vector<int> seq, int k){
    int n=seq.size();
    vector<int> res;
    deque<int> deq;
    for (int i = 0; i < n; i++)
    {
        DBG(i)
        DBG(deq)
        while(!deq.empty() && seq[deq.back()]>=seq[i]) deq.pop_back();
        deq.push_back(i);
        if(i-k+1>=0){
            res.push_back(seq[deq.front()]);
            if(deq.front()==(i-k+1)) deq.pop_front();
        }
    }
    return res;
}


vector<int> rev_slide_min(vector<int> seq, int k){
    int n=seq.size();
    vector<int> res;
    deque<int> deq;
    for (int i = n-1; i >= 0; i--)
    {
        DBG(i)
        DBG(deq)
        while(!deq.empty() && seq[deq.back()]>=seq[i]) deq.pop_back();
        deq.push_back(i);
        if(i+k-1<=n-1){
            res.push_back(seq[deq.front()]);
            if(deq.front()==(i+k-1)) deq.pop_front();
        }
    }
    return res;
}

int main()
{
    vector<int> seq={1,3,4,5,2};
    int k=3;
    auto res = rev_slide_min(seq,k);
    cout << res << endl;;

    return 0;
}
