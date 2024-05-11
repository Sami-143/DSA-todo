
#include <iostream>
#include <vector>
#include <algorithm> // for std::swap
using namespace std;

template <typename T>
bool SwappingAllTheWay(vector<T>& V) {
    bool ChangeHappen = false;
    for (int i = 0; i < V.size() - 1; ++i) {
        if (V[i] > V[i + 1]) {
            swap(V[i], V[i + 1]);
            ChangeHappen = true;
        }
    }
    return ChangeHappen;
}

template <typename T>
void BubbleSort(vector<T>& V) {
    while (SwappingAllTheWay(V)) {
        // No need to print the state of the vector in each iteration
    }
}

int main() {
    // Example usage:
    vector<int> myVector = {5, 3, 8, 2, 1};

    // Call the BubbleSort function to sort the vector
    BubbleSort(myVector);

    // Print the sorted vector
    cout << "Sorted Vector: ";
    for (const auto& element : myVector) {
        cout << element << " ";
    }
    cout << endl;

    return 0;
}