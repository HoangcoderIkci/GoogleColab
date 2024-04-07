#include <algorithm>
#include <iostream>
#include <vector>
#include <fstream>
#include <random>
#define SIZEPOLE 32
#define CHAR 2
#define DEGREE 5
using namespace std;
// const uint32_t hsPole = 7; // x^2+x+1
const uint32_t hsPole = 37; // x8 + x4 + x3 + x + 1

uint32_t arrMultiple[SIZEPOLE][SIZEPOLE];
uint32_t ArrayInverseElements[SIZEPOLE];

uint32_t multipleTwoElement(uint32_t a, uint32_t b)
{
    if (a == 0 || b == 0)
        return 0;
    uint32_t result = 0;
    uint32_t temp = 1 << DEGREE;
    uint32_t a_cp = 0;
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
    uint32_t temp = 0;
    for (uint32_t i = 0; i < SIZEPOLE; i++)
    {
        for (uint32_t j = i; j < SIZEPOLE; j++)
        {
            temp = multipleTwoElement(i, j);
            // cout << i << "*" << j << " = " << temp << endl;
            arrMultiple[i][j] = temp;
            arrMultiple[j][i] = temp;
            if (temp == 1)
            {
                ArrayInverseElements[i] = j;
                ArrayInverseElements[j] = i;
            }
        }
    }
}
void __startCreateMatrices()
{
    createArrayMult();
}

int main()
{
    __startCreateMatrices();
    uint_fast16_t res[SIZEPOLE][SIZEPOLE];
    // ofstream file_output("hoanvi_out.txt");
    uint32_t A = 0;
    uint32_t c;
    uint32_t nghich_j;
    // tạo nghịch đảo S-BOX
    uint32_t vec_support[SIZEPOLE] = {2, 4, 8, 3, 6, 12, 11, 5, 10, 7, 14, 15, 13, 9, 1};
    uint32_t S_BOX_inv[SIZEPOLE] = {0, 1, 16, 17, 13, 12, 29, 28, 14, 15, 30, 31, 3, 2, 19, 18, 27, 26, 11, 10, 22, 23, 6, 7, 21, 20, 5, 4, 24, 25, 8, 9}; // D:\CodeVsCode\HoangCd\Newcode\ToanNghienCuu\Tim_he_so_hoan_vi\input.txt

    // In ra mảng
    uint32_t arr[] = {0, 1, 16, 17, 13, 12, 29, 28, 14, 15, 30, 31, 3, 2, 19, 18, 27, 26, 11, 10, 22, 23, 6, 7, 21, 20, 5, 4, 24, 25, 8, 9};
    for (int i = 0; i < SIZEPOLE - 1; i++)
    {
        S_BOX_inv[vec_support[i]] = arr[i];
    }
    // tìm hệ số
    // for (int i = 0; i < SIZEPOLE; i++)
    // {
    //     printf("%d, ", S_BOX_inv[i]);
    // }
    // printf("\n");
    for (int i = 1; i < SIZEPOLE - 1; i++)
    {
        A = 0;
        for (int j = 1; j < SIZEPOLE; j++)
        {
            c = 1;
            nghich_j = ArrayInverseElements[j];
            for (int k = 0; k < i; k++)
            {
                c = arrMultiple[c][nghich_j];
            }
            A ^= arrMultiple[c][S_BOX_inv[j]];
        }
        if (A)
        {
            // if (A & 0b1)
            // {
            //     if (A != 7 && A != 11 && A != 13 && A != 14)
            // }
            printf("%d,", i);
        }
        // printf("%x\\cdot y^{%d} + ", A, i);
        // cout << i << " : " << A << endl;
    }
    printf("|||\n");
    return 0;
}
