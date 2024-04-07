#include <iostream>

int main()
{
    int arr[] = {2, 13, 1, 15, 4, 3, 5, 6, 12, 8, 9, 11, 14, 7, 10};
    int arr_temp[15];
    int c = 0;
    int distance = 2;
    for (int i = 0; i < 15; i++)
    {
        c = arr[i] ^ arr[(i + distance) % 15];
        for (int j = 0; j < i; j++)
        {
            if (c == arr_temp[j])
                return 0;
        }
        arr_temp[i] = c;
    }
    // c = arr[14] ^ arr[0];
    // for (int j = 0; j < 13; j++)
    // {
    //     if (c == arr_temp[j])
    //         return 0;
    // }
    printf("win\n");
    return 0;
}