#include <bits/stdc++.h>

class Segment_tree{
  private:
    int N;
    int C;
    std::vector<int> L;
    std::vector<int> S;
    std::vector<int> A;
    // セグメント木のデータ
    std::map<int, double> vx, vy;
    std::map<int, double> ang;
    // 角度の変化を調べるため、現在の角度を保存しておく
    std::map<int, double> prv;
  public:
    Segment_tree(int const& n, int const& c, std::vector<int> l,std::vector<int> s,std::vector<int> a);
    void init(int const& k, int const& l, int const& r);
    void setN(int const& n){N=n;}
    void setC(int const& c){C=c;}
    void setL(std::vector<int> l){L=l;} 
    void setS(std::vector<int> s){S=s;} 
    void setA(std::vector<int> a){A=a;}
    void setAllattrib(int const& n, int const& c, std::vector<int> l,std::vector<int> s,std::vector<int> a);
    void change(int const& s, double const& a, int const& v, int const& l, int const& r);
    void solve();
};

// コンストラクタ
Segment_tree::Segment_tree(int const& n, int const& c, std::vector<int> l,std::vector<int> s,std::vector<int> a){
  setAllattrib(n,c,l,s,a);
  init(0,0,n);
}

void Segment_tree::setAllattrib(int const& n, int const& c, std::vector<int> l,std::vector<int> s,std::vector<int> a){
  setN(n);
  setC(c);
  setL(l); 
  setS(s); 
  setA(a);      
}

// セグメント木の初期化
// k は節点の番号、[l, r)区間に対応
void Segment_tree::init(int const& k, int const& l, int const& r){
  ang[k] = vx[k] = 0.0;
  if(r-l==1) vy[k] = L[l];
  else{
    int chl = 2*k+1, chr = 2*k+2;
    Segment_tree::init(chl,l,(l+r)/2);
    Segment_tree::init(chr,(l+r)/2,r);
    vy[k] = vy[chl] + vy[chr];
  }
}

void Segment_tree::change(int const& s, double const& a, int const& v, int const& l, int const& r){
  if(s<=l) return ;
  else if (s < r)
  {
    int chl = 2*v+1, chr = 2*v+2;
    int m = (l+r)/2;
    Segment_tree::change(s,a,chl,l,m);
    Segment_tree::change(s,a,chr,m,r);
    if (s<=m) ang[v] += a;
    double s = sin(ang[v]), c = cos(ang[v]);
    vx[v] = vx[chl] + (c*vx[chr]-s*vy[chr]);  
    vy[v] = vy[chl] + (s*vx[chr]+c*vy[chr]);
  }
  
}

void Segment_tree::solve(){
  for(int i = 1;i<N;i++) prv[i] = M_PI;
  for(int i = 0;i<C;i++){
    int s = S[i];
    double a = A[i]/360.0*2*M_PI;
    change(s,a-prv[s],0,0,N);
    prv[s] = a;
    std::cout << vx[0] << " " << vy[0] << std::endl;
  }
}

int main(){
  int N = 3;
  int C = 2;
  std::vector<int> L = {5,5,5};
  std::vector<int> S = {1,2};
  std::vector<int> A = {270,90};
  Segment_tree s(N,C,L,S,A);
  std::cout<<std::fixed<<std::setprecision(10);
  s.solve();
}
