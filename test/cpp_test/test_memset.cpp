#include <bits/stdc++.h>
using namespace std;

int main()
{
     int memo[10][10];
     memset(memo, -1, sizeof(memo));
     for (int i = 0; i < 10; i++)
     {
          for (int j = 0; j < 10; j++)
          {
               cout << memo[i][j];
          }
          cout << endl;
     }
     return 0;
}