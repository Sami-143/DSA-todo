#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
using namespace std;

int binary_search_recursive(vector<int>& arr, int s, int e, int key) {
    if (s > e) {
        return -1;  
    }

    int mid = (s + e) / 2;

    if (arr[mid] == key) {
        return mid;  
    } 
    else if (arr[mid] < key) {
        return binary_search_recursive(arr, mid + 1, e, key);
    } 
    else {
        return binary_search_recursive(arr, s, mid - 1, key);
    }
}

int main() {

    vector<int> large_data;
    for (int i = 0; i < 1000; ++i) {
        large_data.push_back(rand() % 10000);
    }
    sort(large_data.begin(), large_data.end());

    int key = large_data[rand() % large_data.size()]; 

    int index = binary_search_recursive(large_data, 0, large_data.size() - 1, key);

    if (index != -1) {
        cout << "Element " << key << " found at index " << index << endl;
    }
    else {
        cout << "Element " << key << " not found in the dataset" << endl;
    }

    return 0;
}
