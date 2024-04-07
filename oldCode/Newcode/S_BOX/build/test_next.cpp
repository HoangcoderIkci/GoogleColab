#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
using namespace std;
// Hàm đảo ngược mảng từ start đến end
void reverse(int arr[], int start, int end)
{
    while (start < end)
    {
        std::swap(arr[start], arr[end]);
        start++;
        end--;
    }
}

// Hàm sinh hoán vị kế tiếp của mảng arr với kích thước size

int main()
{
    const int size = 5;
    int arr[size] = {1, 2, 3, 4, 5};

    // Đo thời gian cho việc sử dụng next_permutation
    auto start_time_next_permutation = std::chrono::high_resolution_clock::now();

    do
    {
        // Thực hiện công việc với hoán vị tại đây
    } while (std::next_permutation(arr, arr + size));

    auto end_time_next_permutation = std::chrono::high_resolution_clock::now();
    auto duration_next_permutation = std::chrono::duration_cast<std::chrono::milliseconds>(end_time_next_permutation - start_time_next_permutation);

    // Đo thời gian cho việc sử dụng nextPermutation
    auto start_time_custom_permutation = std::chrono::high_resolution_clock::now();

    do
    {
        // Thực hiện công việc với hoán vị tại đây
        for (size_t i = 0; i < size; i++)
        {
            cout << arr[i] << " ";
            /* code */
        }
        cout << endl;

    } while (nextPermutation(arr, size));

    auto end_time_custom_permutation = std::chrono::high_resolution_clock::now();
    auto duration_custom_permutation = std::chrono::duration_cast<std::chrono::milliseconds>(end_time_custom_permutation - start_time_custom_permutation);

    std::cout << "Thời gian sử dụng next_permutation: " << duration_next_permutation.count() << " milliseconds\n";
    std::cout << "Thời gian sử dụng nextPermutation: " << duration_custom_permutation.count() << " milliseconds\n";

    return 0;
}
