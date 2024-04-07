#include <iostream>
#include <chrono>
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
{
    int arr[] = {1, 2, 3, 4, 6, 7, 8, 9, 10};
    int size = sizeof(arr) / sizeof(arr[0]);
    // Bắt đầu đo thời gian
    auto start = std::chrono::high_resolution_clock::now();
    do
    {
        // for (int i = 0; i < size; ++i)
        // {
        //     std::cout << arr[i] << " ";
        // }
        // std::cout << "\n";
    } while (nextPermutation(arr, size));
    // Kết thúc đo thời gian
    auto end = std::chrono::high_resolution_clock::now();

    // Tính toán thời gian thực thi
    std::chrono::duration<double> duration = end - start;

    // In ra thời gian thực thi (đơn vị: giây)
    std::cout << "Thời gian thực thi: " << duration.count() << " giây" << std::endl;
    return 0;
}
