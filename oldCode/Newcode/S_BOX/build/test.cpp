#include <algorithm>
#include <thread>
#include <functional>
#include <chrono> // Thêm thư viện này để sử dụng std::chrono
#define MAX 1000000
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
vector<unsigned> S_BOX = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

unsigned arrMultiple[SIZEPOLE][SIZEPOLE];
// unsigned arrAddition[SIZEPOLE][SIZEPOLE];
// unsigned arrInverseSubtraction[SIZEPOLE];
// unsigned arrOppositeArray[SIZEPOLE];
unsigned arrExpr[SIZEPOLE];
//  ================== begin Code Matrix  =================================

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
            arrMultiple[i][j] = temp;
            arrMultiple[j][i] = temp;
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

void __startCreateMatrices()
{
    createArrayMult();
    createArrayExpr();
}

bool nextPermutation(unsigned arr[], int size = SIZEPOLE - 1)
{
    int i = size - 2;
    unsigned temp;
    int start, end;
    while (i >= 0 && arr[i] >= arr[i + 1])
    {
        i--;
    }

    if (i < 0)
    {
        return false;
    }

    int j = size - 1;
    while (arr[j] <= arr[i])
    {
        j--;
    }
    temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
    //////
    start = i + 1;
    end = size - 1;
    while (start < end)
    {
        temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
    return true;
}
void isBeautiful(vector<unsigned> S_BOX_int)
{
    // std::ofstream outputFile(filename, std::ios::app);
    // vector<unsigned> S_box_temp;
    // S_box_temp.push_back(S_BOX[0]);
    // for (auto x : arr_index)
    // {
    //     S_box_temp.push_back(S_BOX[x]);
    // }
    unsigned *S_box_temp = new unsigned[SIZEPOLE - 1];
    for (int i = 0; i < SIZEPOLE - 1; i++)
        S_box_temp[i] = S_BOX_int[i];
    int b = 0;
    bool check = true;
    for (int dem = 0; dem < MAX; dem++)
    {
        for (int i = 1; i < SIZEPOLE - 1; i++)
        {
            set<unsigned> temp;
            for (int j = 0; j < SIZEPOLE - 1; j++)
            {
                b = S_box_temp[j] ^ S_box_temp[(i + j) % (SIZEPOLE - 1)];
                temp.insert(b);
                if (temp.size() != j + 1)
                {
                    // check = false;
                    i = SIZEPOLE;
                    check = false;
                    break;
                }

                // temp.push_back(b);
            }
        }
        if (check)
        {
            for (size_t ii = 0; ii < SIZEPOLE - 1; ii++)
            {
                cout << S_box_temp[ii] << " , ";
                /* code */
            }
            cout << endl;
        }
        check = true;
        nextPermutation(S_box_temp);
    }
    delete[] S_box_temp;
}
int main()
{
    // vector<vector<int>> v;
    __startCreateMatrices();
    for (size_t i = 0; i < SIZEPOLE; i++)
    {
        cout << arrExpr[i] << " ";
    }
    cout << endl;
    cout << "================================================================ bat dau \n";
    vector<unsigned> temp{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    // isBeautiful(temp);
    //   temp = S_BOX;
    auto v_cp = temp;
    vector<std::thread> threads;
    for (int k = 0; k < 3; ++k)
    {
        v_cp.erase(v_cp.begin() + k);
        temp = v_cp;
        for (size_t i = 0; i < 15; i++)
        {
            int t = temp[0];
            temp[0] = temp[i];
            temp[i] = t;
            // for (auto x : temp)
            //     cout << x << " ";
            // cout << endl;
            threads.emplace_back(isBeautiful, temp);
            // for (size_t j = 1; j < 15; j++)
            // {
            //     t = temp[1];
            //     temp[1] = temp[j];
            //     temp[j] = t;
            //     threads.emplace_back(isBeautiful, temp);
            //}
            // threads.emplace_back(isBeautiful, temp);
        }
        // Thêm lại phần tử tại vị trí i
        v_cp.insert(v_cp.begin() + k, k);
    }
    for (std::thread &t : threads)
    {
        t.join();
    }
    cout << endl;
    return 0;
}