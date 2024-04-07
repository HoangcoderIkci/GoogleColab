#include <algorithm>
#include <iostream>
#include <vector>
#include <fstream>
#include <random>
#define SIZEPOLE 16
#define CHAR 2
#define DEGREE 4
using namespace std;
#define U32 uint32_t
// const uint32_t hsPole = 7; // x^2+x+1
const uint32_t hsPole = 19; // x8 + x4 + x3 + x + 1

uint32_t arrMultiple[SIZEPOLE][SIZEPOLE];
uint32_t ArrayInverseElements[SIZEPOLE];
uint32_t ArrayPowerSupport[SIZEPOLE];
int ArrayPower[SIZEPOLE][SIZEPOLE]; // Giả sử kích thước tối đa là SIZEPOLE x SIZEPOLE
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

void createArrayPower()
{
    ArrayPowerSupport[0] = 1;
    int temp = 2;
    for (int idx1 = 1; idx1 < SIZEPOLE; idx1++)
    {
        ArrayPowerSupport[idx1] = temp;
        temp = arrMultiple[2][temp];
    }

    for (int i = 0; i < SIZEPOLE; i++)
    {
        ArrayPower[0][i] = 0;
        ArrayPower[1][i] = 1;
        ArrayPower[2][i] = ArrayPowerSupport[i];
    }

    for (int idx1 = 3; idx1 < SIZEPOLE; idx1++)
    {
        temp = idx1;
        ArrayPower[idx1][0] = 1;
        ArrayPower[idx1][1] = temp;
        // Tìm vị trí của temp trong ArrayPowerSupport
        int index_temp = -1;
        for (int i = 0; i < SIZEPOLE; i++)
        {
            if (ArrayPowerSupport[i] == temp)
            {
                index_temp = i;
                break;
            }
        }
        if (index_temp == -1)
            continue; // Nếu không tìm thấy temp trong ArrayPowerSupport

        for (int idx2 = 2; idx2 < SIZEPOLE; idx2++)
        {
            temp = (idx2 * index_temp) % (SIZEPOLE - 1);
            ArrayPower[idx1][idx2] = ArrayPowerSupport[temp];
        }
    }
}
void __startCreateArrays()
{
    createArrayMult();
    createArrayPower();
}
void findCoefficients(U32 *sBox)
{
    uint32_t A = 0;
    uint32_t c;
    uint32_t nghich_j;
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
            A ^= arrMultiple[c][sBox[j]];
        }
        if (A)
        {
            printf("%x*y^%d +", A, i);
        }
        // printf("%x\\cdot y^{%d} + ", A, i);
        // cout << i << " : " << A << endl;
    }
    printf("|||\n");
}
void sap_xep_lai_hs_theo_pow(U32 *arr, U32 *S_BOX_inv)
{
    for (int i = 1; i < SIZEPOLE; i++)
    {
        S_BOX_inv[ArrayPowerSupport[i]] = arr[i];
    }
}
void printfArrray(U32 *arr, int size)
{
    for (size_t i = 0; i < size; i++)
    {
        printf("%u,", arr[i]);
    }
    printf("\n");
}
int main()
{
    __startCreateArrays();
    // tạo nghịch đảo S-BOX
    // uint32_t vec_support[SIZEPOLE] = {2, 4, 8, 3, 6, 12, 11, 5, 10, 7, 14, 15, 13, 9, 1};
    uint32_t S_BOX_inv[SIZEPOLE] = {}; // D:\CodeVsCode\HoangCd\Newcode\ToanNghienCuu\Tim_he_so_hoan_vi\input.txt

    // In ra mảng
    // uint32_t arr[] = {0, 1, 16, 17, 13, 12, 29, 28, 14, 15, 30, 31, 3, 2, 19, 18, 27, 26, 11, 10, 22, 23, 6, 7, 21, 20, 5, 4, 24, 25, 8, 9};
    uint32_t arr[SIZEPOLE] = {0, 1, 14, 8, 5, 15, 6, 15 - 2, 10, 9, 11, 7, 3, 2, 12, 4};
    sap_xep_lai_hs_theo_pow(arr, S_BOX_inv);
    findCoefficients(S_BOX_inv);
    // U32 b = 1, c, a;
    // for (b = 1; b < SIZEPOLE - 1; b++)
    // {
    //     printf("#########################################\n");
    //     printf("b = %u\n", b);
    //     for (c = 1; c < SIZEPOLE - 2; c++)
    //     {
    //         if (b == c)
    //             continue;
    //         printf("====================================\n");
    //         printf("c = %u\n", c);
    //         a = b ^ c;
    //         arr[1] = b;
    //         arr[2] = 7 ^ b;
    //         arr[3] = a;
    //         arr[6] = 7 ^ a;
    //         arr[5] = 7 ^ c;
    //         arr[7] = c;
    //         sap_xep_lai_hs_theo_pow(arr, S_BOX_inv);
    //         findCoefficients(S_BOX_inv);
    //     }
    // }

    return 0;
}
