#include<iostream>
#include <vector>
#include <cstdlib>

using namespace std;

template<class T>
int Partition(vector<T> &V, int left, int right, int pi) {
    int i = left - 1;
    int j = left;

    swap(V[pi], V[right]); // Move pivot element to the end
    pi = right;
    int range = right - left;

    while (j < range) {
        if (V[j] >= V[pi]) {
            i = i + 1;
            swap(V[i], V[j]);
        }
        j++;
    }

    swap(V[i + 1], V[pi]);
    return i + 1;
}

template<class T>
void QuickSortRec(vector<T> &V, int si, int ei) {
    if (si >= ei) {
        return; // The size of the range is just one... So no need to do anything
    }

    int pi = (rand() % (ei - si + 1)) + si; // Generating a random index between si to ei
    pi = Partition(V, si, ei, pi);

    QuickSortRec(V, si, pi - 1);
    QuickSortRec(V, pi + 1, ei);
}

template<class T>
void QuickSort(vector<T> &V) {
    QuickSortRec(V, 0, V.size() - 1);
}

int main() {
    // Example usage:
    vector<int> myVector = {4, 2, 7, 1, 9, 3};
    QuickSort(myVector);

    // Print the sorted vector
    for (const auto& element : myVector) {
        cout << element << " ";
    }

    return 0;
}
