#include <vector>
#include <atcoder/maxflow.hpp>

// https://theory-and-me.hatenablog.com/entry/2020/03/17/180157

// V. Kolmogorov and R. Zabih. What energy functions can be minimized via graph cuts? IEEE Transweraction on Pattern Analysis and Machine Intelligence, 26(2):147–159, 2004.
// http://www.cs.cornell.edu/~rdz/Papers/KZ-PAMI04.pdf
template <typename T>
struct MinimizedViaGraphCuts
{
    int n;
    atcoder::mf_graph<T> g;
    T answer;
    int s, t;
    MinimizedViaGraphCuts() : n(0) {}
    MinimizedViaGraphCuts(int _n) : n(_n)
    {
        assert(_n > 0);
        atcoder::mf_graph<T> _g(_n + 2);
        g = _g;
        s = _n;
        t = _n + 1;
        answer = T(0);
    }
    bool is_submodular(const std::vector<T> &p) { return p.at(0b00) + p.at(0b11) <= p.at(0b01) + p.at(0b10); }

    // xi=0のときのコストがC0,
    // xi=1のときのコストがC1
    void addF1(int i, T C0, T C1)
    {
        if (C0 <= C1)
        {
            answer += C0;
            g.add_edge(s, i, C1 - C0);
        }
        else
        {
            answer += C1;
            g.add_edge(i, t, C0 - C1);
        }
    }

    // xi=0,xj=0のときのコストがEij[0b00],
    // xi=0,xj=1のときのコストがEij[0b01],
    // xi=1,xj=0のときのコストがEij[0b10],
    // xi=1,xj=1のときのコストがEij[0b11],
    void addF2(int i, int j, const std::vector<T> &Eij)
    {
        assert(Eij.size() == 4);
        assert(is_submodular(Eij));
        T A = Eij.at(0b00);
        T B = Eij.at(0b01);
        T C = Eij.at(0b10);
        T D = Eij.at(0b11);
        answer += A;
        addF1(i, 0, C - A);
        addF1(j, 0, D - C);
        g.add_edge(i, j, B + C - A - D);
    }

    T solve()
    {
        answer += g.flow(s, t);
        return answer;
    }
};