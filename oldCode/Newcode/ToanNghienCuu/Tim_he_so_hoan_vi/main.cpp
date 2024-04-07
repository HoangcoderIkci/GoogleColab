#include <algorithm>
#include <iostream>
#include <vector>
#include <fstream>
#include <random>
#define SIZEPOLE 16
#define CHAR 2
#define DEGREE 4
using namespace std;
// const uint32_t hsPole = 7; // x^2+x+1
const uint32_t hsPole = 19; // x8 + x4 + x3 + x + 1
// const uint32_t hsPole = 11; // x^4 + x + 1
// vector<uint32_t> S_BOX =  {0,7,1,3,2,4,5,6};
// vector<uint32_t> S_BOX = {13, 11, 14, 8, 12, 10, 15, 9, 4, 2, 7, 1, 5, 3, 6, 0};
vector<uint32_t> S_BOX = {0x63,
                          0x7C,
                          0x77,
                          0x7B,
                          0xF2,
                          0x6B,
                          0x6F,
                          0xC5,
                          0x30,
                          0x01,
                          0x67,
                          0x2B,
                          0xFE,
                          0xD7,
                          0xAB,
                          0x76,
                          0xCA,
                          0x82,
                          0xC9,
                          0x7D,
                          0xFA,
                          0x59,
                          0x47,
                          0xF0,
                          0xAD,
                          0xD4,
                          0xA2,
                          0xAF,
                          0x9C,
                          0xA4,
                          0x72,
                          0xC0,
                          0xB7,
                          0xFD,
                          0x93,
                          0x26,
                          0x36,
                          0x3F,
                          0xF7,
                          0xCC,
                          0x34,
                          0xA5,
                          0xE5,
                          0xF1,
                          0x71,
                          0xD8,
                          0x31,
                          0x15,
                          0x04,
                          0xC7,
                          0x23,
                          0xC3,
                          0x18,
                          0x96,
                          0x05,
                          0x9A,
                          0x07,
                          0x12,
                          0x80,
                          0xE2,
                          0xEB,
                          0x27,
                          0xB2,
                          0x75,
                          0x09,
                          0x83,
                          0x2C,
                          0x1A,
                          0x1B,
                          0x6E,
                          0x5A,
                          0xA0,
                          0x52,
                          0x3B,
                          0xD6,
                          0xB3,
                          0x29,
                          0xE3,
                          0x2F,
                          0x84,
                          0x53,
                          0xD1,
                          0x00,
                          0xED,
                          0x20,
                          0xFC,
                          0xB1,
                          0x5B,
                          0x6A,
                          0xCB,
                          0xBE,
                          0x39,
                          0x4A,
                          0x4C,
                          0x58,
                          0xCF,
                          0xD0,
                          0xEF,
                          0xAA,
                          0xFB,
                          0x43,
                          0x4D,
                          0x33,
                          0x85,
                          0x45,
                          0xF9,
                          0x02,
                          0x7F,
                          0x50,
                          0x3C,
                          0x9F,
                          0xA8,
                          0x51,
                          0xA3,
                          0x40,
                          0x8F,
                          0x92,
                          0x9D,
                          0x38,
                          0xF5,
                          0xBC,
                          0xB6,
                          0xDA,
                          0x21,
                          0x10,
                          0xFF,
                          0xF3,
                          0xD2,
                          0xCD,
                          0x0C,
                          0x13,
                          0xEC,
                          0x5F,
                          0x97,
                          0x44,
                          0x17,
                          0xC4,
                          0xA7,
                          0x7E,
                          0x3D,
                          0x64,
                          0x5D,
                          0x19,
                          0x73,
                          0x60,
                          0x81,
                          0x4F,
                          0xDC,
                          0x22,
                          0x2A,
                          0x90,
                          0x88,
                          0x46,
                          0xEE,
                          0xB8,
                          0x14,
                          0xDE,
                          0x5E,
                          0x0B,
                          0xDB,
                          0xE0,
                          0x32,
                          0x3A,
                          0x0A,
                          0x49,
                          0x06,
                          0x24,
                          0x5C,
                          0xC2,
                          0xD3,
                          0xAC,
                          0x62,
                          0x91,
                          0x95,
                          0xE4,
                          0x79,
                          0xE7,
                          0xC8,
                          0x37,
                          0x6D,
                          0x8D,
                          0xD5,
                          0x4E,
                          0xA9,
                          0x6C,
                          0x56,
                          0xF4,
                          0xEA,
                          0x65,
                          0x7A,
                          0xAE,
                          0x08,
                          0xBA,
                          0x78,
                          0x25,
                          0x2E,
                          0x1C,
                          0xA6,
                          0xB4,
                          0xC6,
                          0xE8,
                          0xDD,
                          0x74,
                          0x1F,
                          0x4B,
                          0xBD,
                          0x8B,
                          0x8A,
                          0x70,
                          0x3E,
                          0xB5,
                          0x66,
                          0x48,
                          0x03,
                          0xF6,
                          0x0E,
                          0x61,
                          0x35,
                          0x57,
                          0xB9,
                          0x86,
                          0xC1,
                          0x1D,
                          0x9E,
                          0xE1,
                          0xF8,
                          0x98,
                          0x11,
                          0x69,
                          0xD9,
                          0x8E,
                          0x94,
                          0x9B,
                          0x1E,
                          0x87,
                          0xE9,
                          0xCE,
                          0x55,
                          0x28,
                          0xDF,
                          0x8C,
                          0xA1,
                          0x89,
                          0x0D,
                          0xBF,
                          0xE6,
                          0x42,
                          0x68,
                          0x41,
                          0x99,
                          0x2D,
                          0x0F,
                          0xB0,
                          0x54,
                          0xBB,
                          0x16};

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
    uint32_t S_BOX_temp[SIZEPOLE] = {0};
    uint32_t S_BOX_inv[SIZEPOLE] = {0}; // D:\CodeVsCode\HoangCd\Newcode\ToanNghienCuu\Tim_he_so_hoan_vi\input.txt
    ifstream file("D:\\CodeVsCode\\HoangCd\\Newcode\\ToanNghienCuu\\Tim_he_so_hoan_vi\\input.txt");
    std::vector<std::vector<int>> arrays;
    std::vector<int> array;
    int number;
    char comma;
    while (file >> number >> comma)
    {
        array.push_back(number);

        if (comma == ',')
        {
            continue;
        }
        else
        {
            arrays.push_back(array);
            array.clear();
        }
    }

    // In ra mảng
    for (const auto &arr : arrays)
    {
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
        printf("|||");
    }

    // for (int i = 0; i < SIZEPOLE; i++)
    // {
    //     S_BOX_inv[S_BOX[i]] = i;
    // }

    file.close();
    // file_output.close();
    return 0;
}
