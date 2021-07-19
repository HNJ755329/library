#include <iostream>
#include <algorithm>
#include <cmath>
#include <iomanip>      // std::setprecision

#ifdef __LOCAL
    #define DBG(X) cout << "File:" << __FILE__ << " Line:" << __LINE__ << " " <<#X << " = " << (X) << endl;
    #define SAY(X) cout << (X) << endl;
#else
    #define DBG(X)
    #define SAY(X)
#endif

using namespace std;

int main()
{
    int X=2;
    double upper=X;
    double lower=0;
    double middl;
    cout << std::setprecision(100); 
    for(int i=0;i<1000;i++){
        middl = (upper+lower)/2;
        if(X*X<middl*middl*middl) upper=middl;
        else lower=middl;
    }
    DBG(upper);
    DBG(lower);
    DBG(middl);
    DBG(sqrt(X));
    DBG(sqrt(X)-middl)
    DBG(pow(2,101/100))
}
