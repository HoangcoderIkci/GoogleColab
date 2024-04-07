#include <algorithm>
#include <iostream>
#include <vector>
#include <fstream>
#include <random>
#include <set>
#define SIZEPOLE 16
#define CHAR 2
#define DEGREE 4

using namespace std;
// const unsigned hsPole = 7; // x^2+x+1
// const unsigned hsPole = 283; // x8 + x4 + x3 + x + 1

const unsigned hsPole = 19; // {\displaystyle x^{8}+x^{7}+x^{6}+x+1}
vector<unsigned> S_BOX = {0, 6, 3, 5, 7, 1, 4, 2, 8, 11, 10, 12, 13, 15, 9, 14};

unsigned arrMultiple[SIZEPOLE][SIZEPOLE];
unsigned arrAddition[SIZEPOLE][SIZEPOLE];
unsigned arrInverseSubtraction[SIZEPOLE];
unsigned arrOppositeArray[SIZEPOLE];
vector<unsigned> arrExpr(SIZEPOLE);
//  ================== begin Code Matrix  =================================
typedef vector<vector<unsigned>> Matrix;

Matrix transpose(const Matrix &A)
{
    int rows = A.size();
    int cols = (rows > 0) ? A[0].size() : 0;

    Matrix B(cols, vector<unsigned>(rows)); // Chú ý rằng số hàng và cột đã được đảo ngược

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            B[j][i] = A[i][j];
        }
    }

    return B;
}
Matrix addMatrices(const Matrix &A, const Matrix &B)
{
    int rows = A.size();
    int cols = (rows > 0) ? A[0].size() : 0;

    if (rows != B.size() || cols != B[0].size())
    {
        cout << "Không thể cộng hai ma trận này vì kích thước của chúng không giống nhau!" << endl;
        return {};
    }

    Matrix C(rows, vector<unsigned>(cols, 0));
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            C[i][j] = arrAddition[A[i][j]][B[i][j]];
        }
    }
    return C;
}

Matrix subtractMatrices(const Matrix &A, const Matrix &B)
{
    int rows = A.size();
    int cols = (rows > 0) ? A[0].size() : 0;

    if (rows != B.size() || cols != B[0].size())
    {
        cout << "Không thể trừ hai ma trận này vì kích thước của chúng không giống nhau!" << endl;
        return {};
    }

    Matrix C(rows, vector<unsigned>(cols, 0));
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            C[i][j] = arrAddition[A[i][j]][arrOppositeArray[B[i][j]]];
        }
    }
    return C;
}
Matrix multiplyMatrices(const Matrix &A, const Matrix &B)
{
    int r1 = A.size();
    int c1 = (r1 > 0) ? A[0].size() : 0;

    int r2 = B.size();
    int c2 = (r2 > 0) ? B[0].size() : 0;

    if (c1 != r2)
    {
        cout << "Không thể nhân hai ma trận này!" << endl;
        return {}; // trả về ma trận rỗng nếu không thể nhân
    }

    Matrix C(r1, vector<unsigned>(c2, 0));
    unsigned temp = 0;
    for (int i = 0; i < r1; i++)
    {
        for (int j = 0; j < c2; j++)
        {
            for (int k = 0; k < c1; k++)
            {
                temp = arrMultiple[A[i][k]][B[k][j]];
                C[i][j] = arrAddition[C[i][j]][temp];
                // C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return C;
}
//  ================== End Code Matrix  =================================
void createArrayAdd()
{
    for (unsigned i = 0; i < SIZEPOLE; i++)
    {
        arrOppositeArray[i] = i;
        for (unsigned j = i; j < SIZEPOLE; j++)
        {
            arrAddition[i][j] = arrAddition[j][i] = i ^ j;
        }
    }
}
unsigned multipleTwoElement(unsigned a, unsigned b)
{
    if (a == 0 || b == 0)
        return 0;
    unsigned result = 0;
    unsigned temp = 1 << DEGREE;
    unsigned a_cp = 0;
    int k = 0, t;
    while (b != 0)
    {

        if (b & 0x1)
        {
            t = k;
            a_cp = a;
            while (t)
            {
                a_cp <<= 1;
                t--;
                if (a_cp & temp)
                {
                    a_cp ^= hsPole;
                }
            }
            result ^= a_cp;
        }
        k++;
        b >>= 1;
    }
    return result;
}
void createArrayMult()
{
    unsigned temp = 0;
    for (unsigned i = 0; i < SIZEPOLE; i++)
    {
        for (unsigned j = i; j < SIZEPOLE; j++)
        {
            temp = multipleTwoElement(i, j);
            // cout << i << "*" << j << " = " << temp << endl;
            arrMultiple[i][j] = temp;
            arrMultiple[j][i] = temp;
            if (temp == 1)
            {
                arrInverseSubtraction[i] = j;
                arrInverseSubtraction[j] = i;
            }
        }
    }
}
void createArrayExpr()
{
    arrExpr[0] = 1;
    arrExpr[1] = 2;
    for (unsigned i = 2; i < SIZEPOLE - 1; i++)
    {
        arrExpr[i] = arrMultiple[2][arrExpr[i - 1]];
    }
    arrExpr[SIZEPOLE - 1] = 0;
}
void printArray(int n = SIZEPOLE)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << arrMultiple[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << arrAddition[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    for (int j = 0; j < n; j++)
    {
        cout << arrInverseSubtraction[j] << " ";
    }
    cout << endl;
    for (int j = 0; j < n; j++)
    {
        cout << arrOppositeArray[j] << " ";
    }
    cout << endl;
}
void __startCreateMatrices()
{
    // createArrayAdd();
    createArrayMult();
    createArrayExpr();
}
bool isBeautiful(vector<unsigned> arr_index)
{
    vector<unsigned> S_box_temp;
    // S_box_temp.push_back(S_BOX[0]);
    for (auto x : arr_index)
    {
        S_box_temp.push_back(S_BOX[x]);
    }
    int b = 0;
    for (int i = 1; i < SIZEPOLE - 1; i++)
    {
        set<unsigned> temp;
        for (int j = 0; j < SIZEPOLE - 1; j++)
        {
            b = S_box_temp[j] ^ S_box_temp[(i + j) % (SIZEPOLE - 1)];
            temp.insert(b);
            if (temp.size() != j + 1)
                return false;
            // temp.push_back(b);
        }
    }
    return true;
}
int main()
{
    __startCreateMatrices();

    for (auto x : arrExpr)
    {
        cout << x << "  ";
        /* code */
    }
    vector<unsigned> arr_index = arrExpr;
    arr_index.pop_back();
    std::random_device rd;
    std::mt19937 generator(rd());

    // Hoán vị các phần tử trong vector
    for (int i = 0; i < 5; i++)
    {
        std::shuffle(S_BOX.begin(), S_BOX.end(), generator);
        if (isBeautiful(arr_index))
        {
            for (auto x : S_BOX)
            {
                cout << x << "  ";
                /* code */
            }
            cout << endl;
        }
    }

    // uint_fast16_t res[SIZEPOLE][SIZEPOLE];
    // int d = 0;
    // unsigned mx = 0;
    // int b = 0;
    // ofstream file_output("hvNghichDao2.txt", ios_base::app);
    // mx = 0;
    // for (int i = 0; i < SIZEPOLE; i++)
    // {
    //     S_BOX[i] = (i + 5) % SIZEPOLE;
    // }
    // for (int i = 0; i < SIZEPOLE; i++)
    // {
    //     for (int j = 0; j < SIZEPOLE; j++)
    //     {
    //         res[i][j] = 0;
    //     }
    // }

    // mx = 0;
    // int id = 0;
    // for (int i = 0; i < SIZEPOLE; i++)
    // {
    //     for (int j = 0; j < SIZEPOLE; j++)
    //     {
    //         file_output << "(" << i << "," << j << ") : ";
    //         b = S_BOX[arrMultiple[j][i]] ^ S_BOX[j];
    //         file_output << b << endl;
    //         res[i][b] += 1;
    //     }
    // }

    // for (int i = 0; i < SIZEPOLE; i++)
    // {
    //     for (int j = 0; j < SIZEPOLE; j++)
    //     {
    //         file_output << res[i][j] << "  ";
    //         if (res[i][j] > mx)
    //             mx = res[i][j];
    //         res[i][j] = 0;
    //     }
    //     file_output << endl;
    // }
    // file_output << mx << endl;
    // // arrDem[mx]++;

    // // for (int i = 0; i < 200; i++)
    // // {
    // //     if (arrDem[i])
    // //     {
    // //         file_output << i << " : " << arrDem[i] << endl;
    // //     }
    // // }
    // file_output.close();

    return 0;
}
