#include <iostream>
#include <vector>
using namespace std;

void generateSubarrays(const vector<int>& arr, vector<int>& current, vector<vector<int>>& result, int index = 0) {
    if (index == arr.size()) {
        result.push_back(current);
        return;
    }

    generateSubarrays(arr, current, result, index + 1); // Exclude the current element
    current.push_back(arr[index]);
    generateSubarrays(arr, current, result, index + 1); // Include the current element
    current.pop_back(); // Backtrack
}

vector<vector<int>> generateAllSubarrays(const vector<int>& arr) {
    vector<vector<int>> result;
    vector<int> current;
    generateSubarrays(arr, current, result);
    return result;
}

int main() {
    vector<int> input1 = {1, 2, 3};
    vector<int> input2 = {1, 2};

    vector<vector<int>> output1 = generateAllSubarrays(input1);
    vector<vector<int>> output2 = generateAllSubarrays(input2);

    // Print the results
    for (const auto& subarray : output1) {
        for (int num : subarray) {
            cout << num << " ";
        }
        cout << endl;
    }

    cout << endl;

    for (const auto& subarray : output2) {
        for (int num : subarray) {
            cout << num << " ";
        }
        cout << endl;
    }

    return 0;
}
