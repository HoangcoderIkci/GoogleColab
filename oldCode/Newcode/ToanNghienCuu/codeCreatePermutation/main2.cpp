#include <iostream>
#include <fstream>
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

int main()
{ // D:\CodeVsCode\HoangCd\Newcode\ToanNghienCuu\codeCreatePermutation
    std::ofstream file_output("D:\\CodeVsCode\\HoangCd\\Newcode\\ToanNghienCuu\\codeCreatePermutation\\output.txt");
    int n_temp = 4;
    int k_temp = (1 << n_temp) - 1;
    int arr[] = {1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 14};
    int size = sizeof(arr) / sizeof(arr[0]);
    int flag = 0;
    int arr_support[] = {2, 13};
    int arr_temp[k_temp];
    int index_test = 3;
    int idtemp = 0;
    // so cho 5 giá trị đầu tiên
    int so_luong_ban_dau = sizeof(arr_support) / sizeof(arr_support[0]);
    for (int i = 0; i < so_luong_ban_dau - 1; i++)
    {
        arr_temp[i] = arr_support[i] ^ arr_support[i + 1];
    }
    // arr_temp[so_luong_ban_dau - 1] = arr_support[0] ^ arr_support[so_luong_ban_dau - 1];
    int c = 0;
    int count = 0;
    do
    {
        // for (int i = so_luong_ban_dau - 1; i < 15; i++)
        // {
        //     arr_temp[i] = -1;
        // }

        flag = 1;
        // test cho phần tử đầu
        c = arr_support[so_luong_ban_dau - 1] ^ arr[0];
        // check xem da co c trong arr_temp chua
        for (int j = 0; j < so_luong_ban_dau - 1; j++)
        {
            if (arr_temp[j] == c)
            {
                flag = 0;
                break;
            }
        }
        if (flag == 0)
            continue;
        arr_temp[so_luong_ban_dau - 1] = c;
        // phần random 1
        for (int i = 0; i < index_test - so_luong_ban_dau - 1; i++)
        {
            c = arr[i] ^ arr[i + 1];
            // check xem da co c trong arr_temp chua
            for (int j = 0; j < so_luong_ban_dau + i; j++)
            {
                if (arr_temp[j] == c)
                {
                    flag = 0;
                    break;
                }
            }
            if (flag == 0)
                break;
            arr_temp[so_luong_ban_dau + i] = c;
        }
        if (flag == 0)
            continue;
        // còn lần cuối của random1
        c = arr[index_test - so_luong_ban_dau - 1] ^ k_temp;
        for (int j = 0; j < index_test - 1; j++)
        {
            if (arr_temp[j] == c)
            {
                flag = 0;
                break;
            }
        }
        if (flag == 0)
            continue;
        arr_temp[index_test - 1] = c;
        // tai số 15
        c = k_temp ^ arr[index_test - so_luong_ban_dau];
        for (int j = 0; j < index_test; j++)
        {
            if (arr_temp[j] == c)
            {
                flag = 0;
                break;
            }
        }
        if (flag == 0)
            continue;
        arr_temp[index_test] = c;
        // phần còn lại random2
        for (int i = index_test + 1; i < k_temp - 1; i++)
        {
            idtemp = i - 1 - so_luong_ban_dau;
            c = arr[idtemp] ^ arr[idtemp + 1];
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
            // if (i == 10)
            // {
            //     printf("\n");
            // }
            arr_temp[i] = c;
        }
        if (flag == 0)
            continue;
        // còn phẩn tử cuối cùng
        c = arr[size - 1] ^ arr_support[0];
        for (int j = 0; j < k_temp - 1; j++)
        {
            if (arr_temp[j] == c)
            {
                flag = 0;
                break;
            }
        }
        if (flag)
        {
            for (int i = 0; i < so_luong_ban_dau; i++)
            {
                file_output << arr_support[i] << " , ";
            }

            for (int i = 0; i < index_test - so_luong_ban_dau; i++)
            {
                file_output << arr[i] << " , ";
                // printf("%d , ", arr[i]);
            }
            file_output << k_temp << " , ";
            for (int i = index_test - so_luong_ban_dau; i < size - 1; i++)
            {
                file_output << arr[i] << " , ";
                // printf("%d , ", arr[i]);
            }
            file_output << arr[size - 1] << ".\n";
            // printf("\n");
            count++;
        }
    } while (nextPermutation(arr, size));
    printf("%d", count);
    return 0;
}
