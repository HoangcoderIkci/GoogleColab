#include <iostream>
#include <fstream>
#include <stdint.h>

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
    // control = 1;
    return true;
}

int main()
{
    std::ofstream file_output("D:\\CodeVsCode\\HoangCd\\Newcode\\ToanNghienCuu\\codeCreatePermutation\\output2.txt", std::ios::app);
    int arr[] = {1, 2, 3, 4, 5, 7, 8, 10, 11, 12, 13, 14};
    int size = sizeof(arr) / sizeof(arr[0]);
    int flag = 0;
    // int arr_support[] = {1, 14, 2};
    int arr_temp[15];
    uint8_t index_temp = 4;
    int so_luong_ban_dau = 2;
    int S_BOX[15] = {6, 9};
    S_BOX[index_temp] = 15;
    // so cho 5 giá trị đầu tiên
    int c = 0, count = 0;
    int distance = 1;
    uint8_t control = 0;
    do
    {
    start:
        flag = 1;
        for (int i = 0; i < index_temp - so_luong_ban_dau; i++)
        {
            S_BOX[so_luong_ban_dau + i] = arr[i];
        }
        // tao S_B0X
        S_BOX[index_temp] = 15;
        c = 1;
        for (int i = index_temp - so_luong_ban_dau; i < size; i++)
        {
            S_BOX[index_temp + c] = arr[i];
            c++;
        }
        for (int t = 1; t < 8; t++)
        {

            for (int i = 0; i < 15; i++)
            {
                c = S_BOX[i] ^ S_BOX[(i + t) % 15];
                // check xem da co c trong arr_temp chua
                for (int j = 0; j < i; j++)
                {
                    if (arr_temp[j] == c)
                    {
                        flag = 0;
                        break;
                    }
                }
                if (flag == 0)
                    break;
                arr_temp[i] = c;
            }
            // còn lần cuối
            if (flag == 0)
            {
                break;
            }
        }
        if (flag == 1)
        {
            ++count;
            for (int i = 0; i < 14; i++)
            {
                file_output << S_BOX[i] << " , ";
                // printf("%d , ", arr[i]);
            }
            file_output << S_BOX[14] << ".\n";
        }
        // // đảo 2 cái đầu cho nhau
        // c = S_BOX[0];
        // S_BOX[0] = S_BOX[1];
        // S_BOX[1] = c;
        // flag = 1;
        // // check lần 2
        // for (int t = 1; t < 8; t++)
        // {

        //     for (int i = 0; i < 15; i++)
        //     {
        //         c = S_BOX[i] ^ S_BOX[(i + t) % 15];
        //         // check xem da co c trong arr_temp chua
        //         for (int j = 0; j < i; j++)
        //         {
        //             if (arr_temp[j] == c)
        //             {
        //                 flag = 0;
        //                 break;
        //             }
        //         }
        //         if (flag == 0)
        //             break;
        //         arr_temp[i] = c;
        //     }
        //     // còn lần cuối
        //     if (flag == 0)
        //     {
        //         break;
        //     }
        // }
        // if (flag == 1)
        // {
        //     ++count;
        //     for (int i = 0; i < 14; i++)
        //     {
        //         file_output << S_BOX[i] << " , ";
        //         // printf("%d , ", S_BOX[i]);
        //     }
        //     file_output << S_BOX[14] << ".\n";
        //     // printf("\n");
        // }
        // c = S_BOX[0];
        // S_BOX[0] = S_BOX[1];
        // S_BOX[1] = c;
        index_temp ^= 8;
        //  control != 0 &&
        control ^= 1;
        if (control)
        {
            goto start;
        }
    } while (nextPermutation(arr, size));
    printf("%d\n", count);
    return 0;
}
