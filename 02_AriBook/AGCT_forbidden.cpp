#include <string>
#include <vector>
#include <iostream>
#include "../00_Library/template.hpp"

using namespace std;

int solve(int n, int k, string s){
    string AGCT = "AGCT";
    vector<vector<int> > dp(n+1,vector<int>(k,0));
    vector<vector<int> > next(k,vector<int>(4,0));
    
    // 前処理
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            string t = s.substr(0,i)+AGCT[j];
            while(s.substr(0,t.length())!=t){
                t = t.substr(1);
            }
            next[i][j] = t.length();
        }    
    }
    DBG(next)
    dp[0][0] = 1;
    for (int t = 0; t < n; t++)
    {
        // dp[t+1][i] = 0;
        for (int i = 0; i < k; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                int ti = next[i][j];
                if(ti==k) continue; 
                // 末尾がｋ個一致してる→Sが含まれてることと同じなので飛ばす。
                dp[t+1][ti] += dp[t][i];
            }
            
        }
        
    }
    int ret=0;
    DBG(dp)
    for (int i = 0; i < k; i++) ret += dp[n][i];
    return ret;    
}

int main(){
    int n=10;
    string s="ATGATGC";
    int k=s.length();
    cout << solve(n,k,s) << endl;
    return 0;
}