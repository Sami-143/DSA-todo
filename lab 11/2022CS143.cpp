#include <chrono>  // Add this header for high_resolution_clock
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <fstream>

using namespace std;
using namespace std::chrono;  // Add this for high_resolution_clock
// Function to print the elements of the vector
template <typename T>
void Vector_Print(const vector<T> &V)
{
    for (const auto &element : V)
    {
        cout << element << " ";
    }
    cout << endl
         << endl
         << endl;
}

template <typename T>
class Compare
{
public:
    bool operator()(const T &a, const T &b)
    {
        return a >= b;
    }
};

// HeapSort
template <typename T>
void Heapify(vector<T> &arr, int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
    {
        largest = left;
    }

    if (right < n && arr[right] > arr[largest])
    {
        largest = right;
    }

    if (largest != i)
    {
        swap(arr[i], arr[largest]);
        Heapify(arr, n, largest);
    }
}
template <typename T>
void HeapSort(vector<T> &arr)
{
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; i--)
    {
        Heapify(arr, n, i);
    }

    for (int i = n - 1; i >= 0; i--)
    {
        swap(arr[0], arr[i]);
        Heapify(arr, i, 0);
    }
}

// MergeSort
template <typename T>
void Merge(vector<T> &arr, int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<T> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
    {
        L[i] = arr[l + i];
    }
    for (int j = 0; j < n2; j++)
    {
        R[j] = arr[m + 1 + j];
    }

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

template <typename T>
void MergeSort(vector<T> &arr, int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;

        MergeSort(arr, l, m);
        MergeSort(arr, m + 1, r);

        Merge(arr, l, m, r);
    }
}

// Quicksort
template <typename T>
int Partition(vector<T> &arr, int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return i + 1;
}

template <typename T>
void QuickSort(vector<T> &arr, int low, int high)
{
    if (low < high)
    {
        int pi = Partition(arr, low, high);

        QuickSort(arr, low, pi - 1);
        QuickSort(arr, pi + 1, high);
    }
}

// BubbleSort
template <class T>
bool SwappingAllTheWay(vector<T> &V)
{
    bool ChangeHappen = false;
    for (int i = 0; i < V.size() - 1; ++i)
    {
        if (V[i] > V[i + 1])
        {
            swap(V[i], V[i + 1]);
            ChangeHappen = true;
        }
    }
    return ChangeHappen;
}

template <class T>
void BubbleSort(vector<T> &V)
{
    while (SwappingAllTheWay(V))
    {
    }
}

// SelectionSort
template <class T>
int FindMinRange(vector<T> &V, int si, int ei)
{
    int mi = si;
    for (int i = si + 1; i <= ei; i++)
    {
        if (V[mi] > V[i])
        {
            mi = i;
        }
    }
    return mi;
}

template <typename T>
void SelectionSort(vector<T> &V)
{
    for (int i = 0; i < V.size() - 1; i++)
    {
        int mi = FindMinRange(V, i, V.size() - 1);
        swap(V[i], V[mi]);
    }
}

void createRandomFile(string fn, int Size, int RN = 100)
{
     ofstream Writer(fn);
     for (int i = 0; i < Size * 1024 * 1024; i++)
    {
         Writer << rand() % RN << " ";
       
    }
    
}

template <typename T>
void LoadData(string filename, vector<T> &arr)
{
    ifstream file(filename);
    int value;
    while (file >> value)
    {
        arr.push_back(value);
    }
    file.close();
    
}


int main()
{
    // Example usage
    vector<int> data = {9, 9, 9, 8, 9, 8, 8, 8, 9, 8, 9, 8, 8, 2, 9};

    cout << "Original Data: " << endl;
    Vector_Print(data);


    createRandomFile("random_data.txt", data.size()); // You can adjust the file name and size

    
    LoadData("random_data.txt", data);// Call LoadData to load data from the file into the vector
    auto start = high_resolution_clock::now();
    HeapSort(data);  // Replace with the sorting function you want to measure
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl;

    // Heapsort
    HeapSort(data);
    cout << "After Heapsort: " << endl;
    Vector_Print(data);

    // MergeSort
    MergeSort(data, 0, data.size() - 1);
    cout << "After MergeSort: " << endl;
    Vector_Print(data);

    // Quicksort
    QuickSort(data, 0, data.size() - 1);
    cout << "After Quicksort: " << endl;
    Vector_Print(data);

    // BubbleSort
    BubbleSort(data);
    cout << "After BubbleSort: " << endl;
    Vector_Print(data);

    // SelectionSort
    SelectionSort(data);
    cout << "After SelectionSort: " << endl;
    Vector_Print(data);

    return 0;
}
