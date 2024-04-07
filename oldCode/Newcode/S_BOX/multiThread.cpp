// #include <iostream>
// #include <algorithm>
// #include <vector>
// #include <thread>
// #include <functional>
// #include <chrono> // Thêm thư viện này để sử dụng std::chrono
// #define MAX 100000000
// using namespace std;
// using namespace std::chrono;

// void my_next_permutation(std::vector<int> &arr)
// {
//     int c = 0;
//     while (c++ < MAX / 20)
//     {
//         next_permutation(arr.begin(), arr.end());
//     }
//     cout << c << endl;
// }
// void all_next_permutation(std::vector<int> &arr)
// {
//     int c = 0;
//     while (c++ < MAX)
//     {
//         next_permutation(arr.begin(), arr.end());
//     }
//     cout << c << endl;
// }
// int main()
// {
//     std::vector<int> v1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
//     std::vector<int> v2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
//     std::vector<int> v3 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
//     std::vector<int> v4 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
//     std::vector<int> v5 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
//     std::vector<int> v6 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
//     std::vector<int> v7 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
//     std::vector<int> v8 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
//     std::vector<int> v9 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
//     std::vector<int> v10 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};

//     std::vector<int> v11 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
//     std::vector<int> v12 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
//     std::vector<int> v13 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
//     std::vector<int> v14 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
//     std::vector<int> v15 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
//     std::vector<int> v16 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
//     std::vector<int> v17 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
//     std::vector<int> v18 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
//     std::vector<int> v19 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
//     std::vector<int> v20 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
//     // std::vector<int> v2 = {2, 1, 3, 4, 5, 6, 7, 8};
//     // std::vector<int> v3 = {3, 1, 2, 4, 5, 6, 7, 8};
//     // std::vector<int> v4 = {4, 1, 2, 3, 5, 6, 7, 8};
//     // std::vector<int> v5 = {5, 1, 2, 3, 4, 6, 7, 8};
//     // std::vector<int> v6 = {6, 1, 2, 3, 4, 5, 7, 8};
//     // std::vector<int> v7 = {7, 1, 2, 3, 4, 5, 6, 8};
//     // std::vector<int> v8 = {8, 1, 2, 3, 4, 5, 6, 7};
//     vector<vector<int>> All_vec = {v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20};

//     // Bắt đầu 100 luồng
//     std::vector<std::thread> threads;
//     auto start_time = high_resolution_clock::now(); // Đánh dấu thời gian bắt đầu
//     for (int i = 0; i < 100; ++i)
//     {
//         threads.emplace_back(my_next_permutation, std::ref(All_vec[i]));
//     }
//     // cout << "Start" << endl;
//     //  Đợi cho tất cả các luồng hoàn thành
//     for (std::thread &t : threads)
//     {
//         t.join();
//     }
//     // all_next_permutation(ref(v1));
//     auto end_time = high_resolution_clock::now(); // Đánh dấu thời gian kết thúc
//     auto duration = duration_cast<seconds>(end_time - start_time);

//     std::cout << "All threads have completed in " << duration.count() << " milliseconds.\n";

//     return 0;
// }

#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <mutex>

// std::mutex fileMutex; // Mutex để đảm bảo đồng bộ khi ghi vào file

void writeToFile(const std::string &filename, const std::vector<int> &data)
{
    // std::lock_guard<std::mutex> lock(fileMutex); // Lock mutex để đảm bảo chỉ có một thread được phép ghi vào file
    std::ofstream outputFile(filename, std::ios::app);

    if (outputFile.is_open())
    {
        for (const auto &value : data)
        {
            outputFile << value << ' ';
        }
        outputFile.close();
        std::cout << "Data written to file: " << filename << std::endl;
    }
    else
    {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}

int main()
{
    std::vector<int> data{1, 2, 3, 4, 5};

    // Tạo và bắt đầu các thread
    std::thread thread1(writeToFile, "file1.txt", data);
    std::thread thread2(writeToFile, "file2.txt", data);
    std::thread thread3(writeToFile, "file3.txt", data);

    // Chờ cho các thread kết thúc
    thread1.join();
    thread2.join();
    thread3.join();

    return 0;
}
