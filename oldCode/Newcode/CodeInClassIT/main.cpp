#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

// Hàm kiểm tra sự lặp lại của phần tử trong mảng 2 chiều
bool hasDuplicates(const vector<vector<int>>& matrix) {
    unordered_map<int, bool> seen;
    for (const auto& row : matrix) {
        for (int val : row) {
            if (seen.find(val) != seen.end()) {
                return true; // Phát hiện lặp lại
            }
            seen[val] = true;
        }
    }
    return false;
}

// Hàm tính trọng số cho mỗi hàng
int rowWeight(const vector<int>& row) {
    unordered_map<int, int> count;
    int maxFrequency = 0;
    for (int val : row) {
        maxFrequency = max(maxFrequency, ++count[val]);
    }
    return maxFrequency;
}
bool compare(const vector<int>& a, const vector<int>& b){
    return rowWeight(a) < rowWeight(b);
}
// Hàm sắp xếp các hàng theo trọng số tăng dần
void sortByRowWeight(vector<vector<int>>& matrix) {
    sort(matrix.begin(), matrix.end(), compare);
}

int main() {
    vector<vector<int>> matrix = {{1, 2, 2,1,2}, {1,1,1,3,4}, {3,4,5,6,6},{2,2,1,2,2}};

    if (!hasDuplicates(matrix)) {
        cout << "Không có phần tử lặp lại trong mảng." << endl;
        return 0;
    }

    sortByRowWeight(matrix);

    cout << "Mảng sau khi sắp xếp: " << endl;
    for (const auto& row : matrix) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }

    return 0;
}
