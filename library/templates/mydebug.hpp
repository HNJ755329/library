#include <iostream>
#ifdef __DEBUG__
    void debug_out() { std::cerr << "\n";} 
    template <typename Head, typename... Tail>
    void debug_out(Head H, Tail... T) {std::cerr << H << " "; debug_out(T...);}
    #define debug(...) std::cerr << "[" << #__VA_ARGS__ << "]:\n" , debug_out(__VA_ARGS__)
#else
    #define debug(...) 
#endif

