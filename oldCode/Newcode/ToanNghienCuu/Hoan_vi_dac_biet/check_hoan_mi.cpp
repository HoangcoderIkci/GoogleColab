#include <iostream>
#include <fstream>
#include <cstdint>
#define U8 uint8_t
#define U16 uint8_t
void mySwap(int *a, int *b)
{
    int temp = *b;
    *b = *a;
    *a = temp;
}
void myReverse(int *begin, int *end)
{
    end--;
    while (begin < end)
    {
        mySwap(begin, end);
        begin++;
        end--;
    }
}
bool nextPermutation(int *arr, int size)
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
    // mySwap(&arr[i - 1], &arr[j]);
    int temp = arr[j];
    arr[j] = arr[i - 1];
    arr[i - 1] = temp;
    // Bước 4: Đảo ngược phần còn lại sau i-1
    myReverse(arr + i, arr + size);
    return true;
}
bool checkHoanMi(U8 *S_BOX, int sizeField)
{
    int size_temp = sizeField - 1;
    U8 val = 0;
    // U8 flag = 0;
    for (int t = 1; t < (sizeField - 2) >> 1; t++)
    {
        U8 res[sizeField] = {};
        for (int i = 0; i < sizeField - 1; i++)
        {
            val = S_BOX[i] ^ S_BOX[(i + t) % size_temp];
            // flag = 1;
            for (int j = 0; j < i; j++)
            {
                if (val == res[j])
                    return false;
            }
            res[i] = val;
        }
    }
    return true;
}
int main()
{
    U8 SIZEPOLE = 1 << 5;
    U8 SBOX[] = {1, 30, 24, 19, 28, 25, 13, 4, 10, 17, 29, 7, 21, 23, 22, 8, 16, 3, 31, 6, 11, 15, 5, 20, 9, 14, 27, 12, 26, 18, 2};
    int lst1[] = {5, 6, 9, 11, 12, 14, 15, 16, 18, 20, 26, 27};
    U8 size1 = sizeof(lst1) / sizeof(lst1[0]);
    U8 lst2[] = {16, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29};
    U8 flag = 1, flag2;
    while (flag)
    {
        flag = nextPermutation(lst1, size1);
        for (int i = 0; i < size1; i++)
        {
            SBOX[lst2[i]] = lst1[i];
        }
        flag2 = checkHoanMi(SBOX, SIZEPOLE);
        if (flag2)
        {

            for (int i = 0; i < SIZEPOLE - 1; i++)
            {
                printf("%u ,", SBOX[i]);
            }
            printf("\n");
        }
    }
    return 0;
}
