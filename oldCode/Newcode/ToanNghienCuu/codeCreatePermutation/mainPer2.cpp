#include <iostream>
using namespace std;

// Hàm để in một hoán vị
void printPermutation(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// Hàm đệ quy để tạo hoán vị
void permute(int arr[], int start, int end)
{
    if (start == end)
    {
        printPermutation(arr, end + 1);
    }
    else
    {
        for (int i = start; i <= end; i++)
        {
            // Đổi chỗ phần tử hiện tại với phần tử tại vị trí start
            swap(arr[start], arr[i]);
            // Gọi đệ quy cho phần còn lại
            permute(arr, start + 1, end);
            // Quay lại (backtrack)
            swap(arr[start], arr[i]);
        }
    }
}

int main()
{
    int nums[] = {1, 2, 3};                 // Tập hợp cần liệt kê hoán vị
    int n = sizeof(nums) / sizeof(nums[0]); // Tính kích thước của mảng
    permute(nums, 0, n - 1);                // Gọi hàm liệt kê hoán vị
    return 0;
}
