#include <vector>
#include <algorithm>

// max c * x s.t. A*x <= b, x >= 0
// Duality:
// min b * y s.t. tA*y >= c, y >= 0
template <typename _Tp>
struct Simplex
{
private:
    using Arr = std::vector<_Tp>;
    using Mat = std::vector<std::vector<_Tp>>;
    int *index;
    _Tp **a;
    int row, column, L;
    _Tp EPS = 1e-9;

    void Set(const Mat &A, const Arr &b, const Arr &c)
    {
        infinity = none = false;
        row = A.size(), column = A[0].size() + 1;
        index = new int[row + column];
        int i, j;
        for (i = 0; i < row + column; i++)
            index[i] = i;
        L = row;
        a = new _Tp *[row + 2];
        for (i = 0; i < row + 2; i++)
            a[i] = new _Tp[column + 1];
        for (i = 0; i < row; i++)
        {
            for (j = 0; j < column - 1; j++)
                a[i][j] = -A[i][j];
            a[i][column - 1] = 1;
            a[i][column] = b[i];
            if (a[L][column] > a[i][column])
                L = i;
        }
        for (j = 0; j < column - 1; j++)
            a[row][j] = c[j];
        a[row + 1][column - 1] = -1;
    }

    void solve()
    {
        int E, i, j;
        int *ls = new int[column + 2];
        for (E = column - 1;;)
        {
            if (L < row)
            {
                std::swap(index[E], index[L + column]);
                a[L][E] = 1 / a[L][E];
                int prv = column + 1;
                for (j = 0; j < column + 1; j++)
                {
                    if (j != E)
                    {
                        a[L][j] *= -a[L][E];
                        if (abs(a[L][j]) > EPS)
                            ls[prv] = j, prv = j;
                    }
                }
                ls[prv] = column + 1;
                for (i = 0; i < row + 2; i++)
                {
                    if (abs(a[i][E]) < EPS || i == L)
                        continue;
                    for (j = ls[column + 1]; j < column + 1; j = ls[j])
                    {
                        a[i][j] += a[i][E] * a[L][j];
                    }
                    a[i][E] *= a[L][E];
                }
            }
            E = -1;
            // double pre = EPS;
            for (j = 0; j < column; j++)
            {
                if (E < 0 || index[E] > index[j])
                {
                    if (a[row + 1][j] > EPS || (abs(a[row + 1][j]) < EPS && a[row][j] > EPS))
                        E = j;
                    // if(a[row + 1][j] > pre) E = j, pre = a[row + 1][j];
                    // else if(abs(a[row + 1][j]) < EPS && a[row][j] > pre) E = j, pre = a[row][j];
                }
            }
            if (E < 0)
                break;
            L = -1;
            for (i = 0; i < row; i++)
            {
                if (a[i][E] < -EPS)
                {
                    if (L < 0)
                        L = i;
                    else if (a[L][column] / a[L][E] - a[i][column] / a[i][E] < -EPS)
                        L = i;
                    else if (a[L][column] / a[L][E] - a[i][column] / a[i][E] < EPS && index[L] > index[i])
                        L = i;
                    // if(L < 0 || a[L][column] / a[L][E] - a[i][column] / a[i][E] < EPS) L = i;
                }
            }
            if (L < 0)
            {
                infinity = true;
                return;
            }
        }
        if (a[row + 1][column] < -EPS)
        {
            none = true;
            return;
        }
        x.assign(column - 1, 0);
        for (i = 0; i < row; i++)
        {
            if (index[column + i] < column - 1)
                x[index[column + i]] = a[i][column];
        }
        ans = a[row][column];
    }

public:
    bool infinity, none;
    _Tp ans;
    Arr x;
    Simplex(const Mat &A, const Arr &b, const Arr &c)
    {
        Set(A, b, c);
        solve();
    }
};