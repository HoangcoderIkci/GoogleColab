#include <algorithm>
#include <iostream>
#include <vector>
#include <fstream>
#define SIZEPOLE 256
#define CHAR 2
#define DEGREE 8

using namespace std;
// const unsigned hsPole = 7; // x^2+x+1
// const unsigned hsPole = 283; // x8 + x4 + x3 + x + 1

unsigned hsPole = 19; // {\displaystyle x^{8}+x^{7}+x^{6}+x+1}
unsigned S_BOXAES[SIZEPOLE] = {0x63,
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

unsigned S_BOX[SIZEPOLE] =
    {0xfc, 0xee, 0xdd, 0x11, 0xcf, 0x6e, 0x31, 0x16, 0xfb, 0xc4, 0xfa, 0xda, 0x23, 0xc5, 0x04, 0x4d,
     0xe9, 0x77, 0xf0, 0xdb, 0x93, 0x2e, 0x99, 0xba, 0x17, 0x36, 0xf1, 0xbb, 0x14, 0xcd, 0x5f, 0xc1,
     0xf9, 0x18, 0x65, 0x5a, 0xe2, 0x5c, 0xef, 0x21, 0x81, 0x1c, 0x3c, 0x42, 0x8b, 0x01, 0x8e, 0x4f,
     0x05, 0x84, 0x02, 0xae, 0xe3, 0x6a, 0x8f, 0xa0, 0x06, 0x0b, 0xed, 0x98, 0x7f, 0xd4, 0xd3, 0x1f,
     0xeb, 0x34, 0x2c, 0x51, 0xea, 0xc8, 0x48, 0xab, 0xf2, 0x2a, 0x68, 0xa2, 0xfd, 0x3a, 0xce, 0xcc,
     0xb5, 0x70, 0x0e, 0x56, 0x08, 0x0c, 0x76, 0x12, 0xbf, 0x72, 0x13, 0x47, 0x9c, 0xb7, 0x5d, 0x87,
     0x15, 0xa1, 0x96, 0x29, 0x10, 0x7b, 0x9a, 0xc7, 0xf3, 0x91, 0x78, 0x6f, 0x9d, 0x9e, 0xb2, 0xb1,
     0x32, 0x75, 0x19, 0x3d, 0xff, 0x35, 0x8a, 0x7e, 0x6d, 0x54, 0xc6, 0x80, 0xc3, 0xbd, 0x0d, 0x57,
     0xdf, 0xf5, 0x24, 0xa9, 0x3e, 0xa8, 0x43, 0xc9, 0xd7, 0x79, 0xd6, 0xf6, 0x7c, 0x22, 0xb9, 0x03,
     0xe0, 0x0f, 0xec, 0xde, 0x7a, 0x94, 0xb0, 0xbc, 0xdc, 0xe8, 0x28, 0x50, 0x4e, 0x33, 0x0a, 0x4a,
     0xa7, 0x97, 0x60, 0x73, 0x1e, 0x00, 0x62, 0x44, 0x1a, 0xb8, 0x38, 0x82, 0x64, 0x9f, 0x26, 0x41,
     0xad, 0x45, 0x46, 0x92, 0x27, 0x5e, 0x55, 0x2f, 0x8c, 0xa3, 0xa5, 0x7d, 0x69, 0xd5, 0x95, 0x3b,
     0x07, 0x58, 0xb3, 0x40, 0x86, 0xac, 0x1d, 0xf7, 0x30, 0x37, 0x6b, 0xe4, 0x88, 0xd9, 0xe7, 0x89,
     0xe1, 0x1b, 0x83, 0x49, 0x4c, 0x3f, 0xf8, 0xfe, 0x8d, 0x53, 0xaa, 0x90, 0xca, 0xd8, 0x85, 0x61,
     0x20, 0x71, 0x67, 0xa4, 0x2d, 0x2b, 0x09, 0x5b, 0xcb, 0x9b, 0x25, 0xd0, 0xbe, 0xe5, 0x6c, 0x52,
     0x59, 0xa6, 0x74, 0xd2, 0xe6, 0xf4, 0xb4, 0xc0, 0xd1, 0x66, 0xaf, 0xc2, 0x39, 0x4b, 0x63, 0xb6};
// unsigned S_BOX[SIZEPOLE] = {0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76, 0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0, 0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15, 0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75, 0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84, 0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf, 0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8, 0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2, 0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73, 0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb, 0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79, 0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08, 0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a, 0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e, 0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf, 0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16};

unsigned arrMultiple[SIZEPOLE][SIZEPOLE];
unsigned ArrayInverseElements[SIZEPOLE];
unsigned arrOppositeArray[SIZEPOLE];

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
    unsigned res[SIZEPOLE][SIZEPOLE];
    unsigned mx = 0;
    int b = 0;
    vector<unsigned> arr_mx(SIZEPOLE);
    ofstream file_output("D:\\CodeVsCode\\HoangCd\\Newcode\\ToanNghienCuu\\Kuzni_nghien_cuu_rieng\\output11.txt");
    mx = 0;
    for (int i = 0; i < SIZEPOLE; i++)
    {
        for (int j = 0; j < SIZEPOLE; j++)
        {
            res[i][j] = 0;
        }
    }
    vector<unsigned> vec_hs = {0b100011011, 0b100011101, 0b100101011, 0b100101101, 0b100111001, 0b100111111, 0b101001101, 0b101011111, 0b101100011, 0b101100101, 0b101101001, 0b101110001, 0b101110111, 0b101111011, 0b110000111, 0b110001011, 0b110001101, 0b110011111, 0b110100011, 0b110101001, 0b110110001, 0b110111101, 0b111000011, 0b111001111, 0b111010111, 0b111011101, 0b111100111, 0b111110011, 0b111110101, 0b111111001};
    // vector<unsigned> vec_hs = {283};
    cout << vec_hs.size() << endl;
    //  x8 + x4 + x3 + x + 1)
    vector<unsigned> arrMx(SIZEPOLE);
    vector<unsigned> ArrTemp;
    for (auto lhs : vec_hs)
    {
        hsPole = lhs;
        // hsPole = 19;
        mx = 0;
        __startCreateMatrices();
        file_output << "\n\n===================================================================================================\n\n";
        file_output << "Lượt nghiên cứu ứng với hs : " << hsPole << "\n";
        printf("Số hex là: %x  ", hsPole);
        // cout << "nghien cuu " << endl;
        for (int i = 2; i < SIZEPOLE; i++)
        {
            for (int j = 0; j < SIZEPOLE; j++)
            {
                b = S_BOXAES[arrMultiple[j][i]] ^ S_BOXAES[j];
                res[i][b] += 1;
                // file_output << "(" << i << "," << j << " : " << b << endl;
            }
        }
        for (int i = 2; i < SIZEPOLE; i++)
        {
            for (int j = 0; j < SIZEPOLE; j++)
            {
                // file_output << res[i][j] << "  ";
                // arr_mx[res[i][j]] += 1;
                if (res[i][j] > mx)
                    mx = res[i][j];
                res[i][j] = 0;
            }
            // file_output << endl;
        }
        file_output << "mx = ";
        file_output << mx << endl;
        arrMx[mx]++;
        printf(" %d \n", mx);
        ArrTemp.push_back(mx);
        // for (int i = 0; i < SIZEPOLE; i++)
        // {
        //     if (arr_mx[i] != 0)
        //         file_output << i << " : " << arr_mx[i] << endl;
        // }
    }
    for (int i = 1; i < SIZEPOLE; i++)
        if (arrMx[i] != 0)
            file_output << "mx = " << i << " : " << arrMx[i] << endl;
    file_output.close();
    for (int i = 0; i < 15; i++)
    {
        printf(" %x &", vec_hs[i]);
    }
    printf("\n");
    for (int i = 0; i < 15; i++)
    {
        printf(" %d &", ArrTemp[i]);
    }
    printf("\n");
    for (int i = 15; i < 30; i++)
    {
        printf(" %x &", vec_hs[i]);
    }
    printf("\n");
    for (int i = 15; i < 30; i++)
    {
        printf(" %d &", ArrTemp[i]);
    }
    printf("\n");

    return 0;
}
