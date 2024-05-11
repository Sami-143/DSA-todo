#include <iostream>
#include <vector>
using namespace std;

template<class T>
bool FindMinRange(vector<T>& V, int si, int ei) {
    int mi = si;
    for (int i = si + 1; i <= ei; i++) {
        if (V[mi] > V[i]) {
            mi = i;
        }
    }
    return mi;
}

template<class T>
void SelectionSort(vector<T>& V) {
    for (int i = 0; i < V.size() - 1; i++) {
        int mi = FindMinRange(V, i, V.size() - 1);
        swap(V[i], V[mi]);
    }
}

template<class T>
void Vector_Print(const vector<T>& V) {
    for (int i = 0; i < V.size(); i++) {
        cout << V[i] << " ";
    }
    cout << endl << endl << endl;
}

int main() {
    vector<int> Values = {4, 2, 7, 1, 9, 3, 5};
    
    Vector_Print(Values);
    SelectionSort(Values);

    Vector_Print(Values);

    return 0;
}
