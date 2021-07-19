#include<iostream>
#include<algorithm>
#include<string>
#include<vector>

template<typename T> inline std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) { for (auto el : v) std::cout << el << " "; return os; }

template<typename T>
std::vector<int> z_algorithm(const T &s) {
    std::vector<int> ans(s.size());
    ans[0] = s.size();
    int i = 1, j = 0;
    while (i < (int)s.size()) {
        while (i + j < (int)s.size() && s[j] == s[i + j]) ++j;
        ans[i] = j;
        if (!j) {
            ++i;
            continue;
        }
        int k = 1;
        while (i + k < (int)s.size() && k + ans[k] < j) ans[i + k] = ans[k], ++k;
        i += k;
        j -= k;
    }
    return ans;
}

// https://www.youtube.com/watch?v=f6ct5PQHqM0
template<typename T>
std::vector<int> zalgo(const T &str) {
    int n = str.size();
    std::vector<int> a(n, 0);
    int from = -1, last = -1;
    for(int i = 1;i < n;i++){
        int &same = a[i];
        if(from != -1){
            same = std::min(a[i-from], last - i);
            same = std::max(0, same);
        }
        while(i + same < str.size() && str[same] == str[i+same]) same++;
        if(last < i+same){
            last = i + same;
            from = i;
        }
    }
    a[0] = n;
    return a;
}

int main()
{
    // vector<int> T={1,2,2,3,1,5,4,2,1,1,2,2,3,2,1,1,3};
    std::string s="aabbaabbaabbaaabbb";
    // DBG(z_algorithm(T));
    std::cout << z_algorithm(s) << std::endl;
    std::cout << zalgo(s);
    return 0;
}
