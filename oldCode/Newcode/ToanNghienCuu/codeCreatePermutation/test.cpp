#include <iostream>
#include <fstream>
#include <vector>

int main()
{
    std::ifstream file("D:\\CodeVsCode\\HoangCd\\Newcode\\ToanNghienCuu\\codeCreatePermutation\\input.txt"); // Thay "ten_file.txt" bằng đường dẫn tới file của bạn

    if (!file.is_open())
    {
        std::cout << "Không thể mở file." << std::endl;
        return 1;
    }

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
        for (int num : arr)
        {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }

    file.close();
    std::cout << "end\n";
    return 0;
}