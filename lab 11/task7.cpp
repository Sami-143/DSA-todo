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
        if (V[j] == V[pi]) {
            // Handle duplicates: Place equal elements in their correct positions
            i = i + 1;
            swap(V[i], V[j]);
        } else if (V[j] > V[pi]) {
            // Continue normal partitioning for elements greater than the pivot
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
    vector<int> retirementMonths = {3, 2, 5, 8, 3, 9, 10, 3, 3, 4, 11, 1};
    
    // Sorting with QuickSort that handles duplicates
    QuickSort(retirementMonths);

    // Print the sorted vector
    for (const auto& month : retirementMonths) {
        cout << month << " ";
    }

    return 0;
}
