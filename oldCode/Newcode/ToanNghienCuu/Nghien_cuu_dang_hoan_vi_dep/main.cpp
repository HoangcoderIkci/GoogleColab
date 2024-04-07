#include <algorithm>
#include <iostream>
#include <vector>
#include <fstream>
#include <random>
#include <numeric>
#include <map>
#define CHAR 2
#define DEGREE 3
#define SIZEPOLE 8
using namespace std;
#define limit (1 << DEGREE) - 1
#define myRegister(x) (((x << 1) ^ (x >> DEGREE - 1)) & limit)
// const uint32_t hsPole = 7; // x^2+x+1
// uint32_t hsPole = 0x11d; // x8 + x4 + x3 + x + 1
// uint32_t hsPole = 19; // x^4 + x + 1
uint32_t hsPole = 11; // x^3 + x + 1

// uint32_t S_BOX[256] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 256, 253, 255, 254};
uint32_t arrMultiple[SIZEPOLE][SIZEPOLE];
uint32_t arrInverseSubtraction[SIZEPOLE];
// uint32_t S_BOX[] = {0xee, 0xfc, 0xdd, 0x11, 0xcf, 0x6e, 0x31, 0x16, 0xfb, 0xc4, 0xfa, 0xda, 0x23, 0xc5, 0x04, 0x4d,
// 0xe9, 0x77, 0xf0, 0xdb, 0x93, 0x2e, 0x99, 0xba, 0x17, 0x36, 0xf1, 0xbb, 0x14, 0xcd, 0x5f, 0xc1,
//     0xf9, 0x18, 0x65, 0x5a, 0xe2, 0x5c, 0xef, 0x21, 0x81, 0x1c, 0x3c, 0x42, 0x8b, 0x01, 0x8e, 0x4f,
//     0x05, 0x84, 0x02, 0xae, 0xe3, 0x6a, 0x8f, 0xa0, 0x06, 0x0b, 0xed, 0x98, 0x7f, 0xd4, 0xd3, 0x1f,
//     0xeb, 0x34, 0x2c, 0x51, 0xea, 0xc8, 0x48, 0xab, 0xf2, 0x2a, 0x68, 0xa2, 0xfd, 0x3a, 0xce, 0xcc,
//     0xb5, 0x70, 0x0e, 0x56, 0x08, 0x0c, 0x76, 0x12, 0xbf, 0x72, 0x13, 0x47, 0x9c, 0xb7, 0x5d, 0x87,
//     0x15, 0xa1, 0x96, 0x29, 0x10, 0x7b, 0x9a, 0xc7, 0xf3, 0x91, 0x78, 0x6f, 0x9d, 0x9e, 0xb2, 0xb1,
//     0x32, 0x75, 0x19, 0x3d, 0xff, 0x35, 0x8a, 0x7e, 0x6d, 0x54, 0xc6, 0x80, 0xc3, 0xbd, 0x0d, 0x57,
//     0xdf, 0xf5, 0x24, 0xa9, 0x3e, 0xa8, 0x43, 0xc9, 0xd7, 0x79, 0xd6, 0xf6, 0x7c, 0x22, 0xb9, 0x03,
//     0xe0, 0x0f, 0xec, 0xde, 0x7a, 0x94, 0xb0, 0xbc, 0xdc, 0xe8, 0x28, 0x50, 0x4e, 0x33, 0x0a, 0x4a,
//     0xa7, 0x97, 0x60, 0x73, 0x1e, 0x00, 0x62, 0x44, 0x1a, 0xb8, 0x38, 0x82, 0x64, 0x9f, 0x26, 0x41,
//     0xad, 0x45, 0x46, 0x92, 0x27, 0x5e, 0x55, 0x2f, 0x8c, 0xa3, 0xa5, 0x7d, 0x69, 0xd5, 0x95, 0x3b,
//     0x07, 0x58, 0xb3, 0x40, 0x86, 0xac, 0x1d, 0xf7, 0x30, 0x37, 0x6b, 0xe4, 0x88, 0xd9, 0xe7, 0x89,
//     0xe1, 0x1b, 0x83, 0x49, 0x4c, 0x3f, 0xf8, 0xfe, 0x8d, 0x53, 0xaa, 0x90, 0xca, 0xd8, 0x85, 0x61,
//     0x20, 0x71, 0x67, 0xa4, 0x2d, 0x2b, 0x09, 0x5b, 0xcb, 0x9b, 0x25, 0xd0, 0xbe, 0xe5, 0x6c, 0x52,
//     0x59, 0xa6, 0x74, 0xd2, 0xe6, 0xf4, 0xb4, 0xc0, 0xd1, 0x66, 0xaf, 0xc2, 0x39, 0x4b, 0x63, 0xb6
// }
// ;
uint32_t S_BOX[] = {0, 1, 2, 3, 4, 5, 6, 7};
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
    cout << "createArrayMult" << endl;
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
                arrInverseSubtraction[i] = j;
                arrInverseSubtraction[j] = i;
            }
        }
    }
}

void __startCreateMatrices()
{
    createArrayMult();
}
int findGCD(const std::vector<int> &vec)
{
    int result = vec[0];
    for (int i = 1; i < vec.size(); i++)
    {
        result = std::gcd(result, vec[i]);

        // Nếu UCLN là 1, không cần tìm tiếp
        if (result == 1)
        {
            break;
        }
    }
    return result;
}
bool Tim_he_so_hoan_vi(const vector<uint32_t> &MyS_BOX, ofstream &file_output, int luot, map<vector<unsigned>, int> &vec_he_so_hoan_vi)
{
    uint_fast16_t res[SIZEPOLE][SIZEPOLE];
    uint32_t A = 0;
    uint32_t c;
    uint32_t nghich_j;
    bool check = true;
    vector<uint32_t> v_temp;
    file_output << MyS_BOX[0] << " + ";
    for (int i = 1; i < SIZEPOLE - 1; i++)
    {
        A = 0;
        for (int j = 1; j < SIZEPOLE; j++)
        {
            c = 1;
            nghich_j = arrInverseSubtraction[j];
            for (int k = 0; k < i; k++)
            {
                c = arrMultiple[c][nghich_j];
            }
            A ^= arrMultiple[c][MyS_BOX[j]];
        }
        if (A)
        {
            file_output << A << "x^" << i << " + ";
            // gcd_val = gcd(gcd_val, i);
            v_temp.push_back(i);
        }
    }
    vec_he_so_hoan_vi[v_temp]++;
    file_output << endl;
    uint32_t template_elem = v_temp[0];
    uint8_t flag;
    uint32_t elem2, elem;
    for (int i = 1; i < v_temp.size(); i++)
    {
        elem = v_temp[i];
        flag = 0;
        elem2 = myRegister(elem);
        while (elem2 != elem)
        {
            if (elem2 == template_elem)
            {
                flag = 1;
                break;
            }
            elem2 = myRegister(elem2);
        }

        // elem /= gcd_val;
        // while (elem % 2 == 0)
        // {
        //     elem = elem >> 1;
        // }
        if (flag != 1)
        {
            file_output << "Hoan vi xấu!!! " << luot << endl;
            return false;
        }
    }
    file_output << "Hoan vi dep !!! " << luot << endl;
    return true;
}
void mySwap(uint32_t *a, uint32_t *b)
{
    uint32_t temp = *b;
    *b = *a;
    *a = temp;
}
void myReverse(uint32_t *begin, uint32_t *end)
{
    end--;
    while (begin < end)
    {
        mySwap(begin, end);
        begin++;
        end--;
    }
}
bool nextPermutation(uint32_t *arr, uint32_t size)
{
    // Bước 1: Tìm phần tử a[i-1] không tuân thủ thứ tự giảm dần từ phải sang trái
    int i = size - 1;
    while (i > 0 && arr[i - 1] >= arr[i])
    {
        i--;
    }
    // Nếu không tìm thấy, đây là hoán vị cuối cùng. Sắp xếp lại và trả về false.
    if (i <= 0)
    {
        myReverse(arr, arr + size);
        return false;
    }

    // Bước 2: Tìm phần tử a[j] lớn hơn a[i-1]
    int j = size - 1;
    while (arr[j] <= arr[i - 1])
    {
        j--;
    }

    // Bước 3: Đổi chỗ a[i-1] và a[j]
    // swap(&arr[i - 1], &arr[j]);
    uint32_t temp = arr[j];
    arr[j] = arr[i - 1];
    arr[i - 1] = temp;
    // Bước 4: Đảo ngược phần còn lại sau i-1
    myReverse(arr + i, arr + size);
    return true;
}
int main()
{
    // cout << multipleTwoElement(1, 2);
    __startCreateMatrices();
    // printArray();
    cout << "bat dau dau nhe  \n"
         << endl;
    uint_fast16_t res[SIZEPOLE][SIZEPOLE];
    int arrDem[200];
    for (int i = 0; i < 200; i++)
    {
        arrDem[i] = 0;
    }
    int d = 0;
    uint32_t mx = 0;
    int b = 0;
    ofstream file_output("D:\\CodeVsCode\\HoangCd\\Newcode\\ToanNghienCuu\\Nghien_cuu_dang_hoan_vi_dep\\tabledatbiet1113.txt", ios_base::out);
    //  for (int i = 0; i < SIZEPOLE; i++)
    //  {
    //      S_BOX[i] = i;
    //  }
    for (int i = 0; i < SIZEPOLE; i++)
    {
        for (int j = 0; j < SIZEPOLE; j++)
        {
            res[i][j] = 0;
        }
    }
    // S_BOX = {6, 1, 7, 0, 5, 2, 4, 3};
    //  vector<uint32_t> polehs{11, 13};
    bool check = true;
    int dem_so_luong_hv_dep = 0;
    int luot = 1;
    int arrtempIndex[] = {0, 2, 4, 3, 6, 7, 5, 1};
    map<vector<unsigned>, int> vec_he_so_hoan_vi;
    do
    {
        // file_output << "\n\n============================\n";
        // file_output << " luot so sanh " << luot << endl;
        // cout << dd << endl;
        // for (auto elem : S_BOX)
        // {
        //     file_output << elem << ", ";
        // }
        // file_output << endl;
        mx = 0;
        // b=0;
        for (int i = 2; i < SIZEPOLE; i++)
        {
            for (int j = 0; j < SIZEPOLE; j++)
            {
                b = S_BOX[arrMultiple[j][i]] ^ S_BOX[j];
                // file_output << b << endl;
                //  b = arrAddition[][arrOppositeArray[]];
                res[i][b] += 1;
            }
        }
        for (int i = 2; i < SIZEPOLE; i++)
        {
            for (int j = 0; j < SIZEPOLE; j++)
            {
                // file_output << res[i][j] << "  ";
                if (res[i][j] > mx)
                    mx = res[i][j];
                res[i][j] = 0;
            }
            // file_output << endl;
        }
        printf("%d ,", mx);
        if (mx == 1)
        {
            for (auto x : arrtempIndex)
            {
                file_output << S_BOX[x] << " ";
            }
            file_output << endl;
            // return 0;
        }
        // arrDem[mx]++;
        //  file_output << "max : " << mx << endl;
        //   if (mx == 1)
        //   {
        //       check = Tim_he_so_hoan_vi(S_BOX, file_output, luot++, vec_he_so_hoan_vi);
        //       if (check)
        //       {
        //           dem_so_luong_hv_dep++;
        //       }
        //   }

    } while (nextPermutation(S_BOX, SIZEPOLE));
    // file_output << "dem_so_luong_hv_dep: " << dem_so_luong_hv_dep << endl;
    // for (auto elem : vec_he_so_hoan_vi)
    // {
    //     for (auto v : elem.first)
    //     {
    //         file_output << v << " ";
    //     }
    //     file_output << "   :   " << elem.second << endl;
    // }
    cout << "end program" << endl;
    // for (int i = 0; i < 30; i++)
    // {
    //     if (arrDem[i] != 0)
    //         file_output << i << ":" << arrDem[i] << endl;
    // }

    file_output.close();
    return 0;
}
