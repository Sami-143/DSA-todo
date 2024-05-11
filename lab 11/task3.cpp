#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

// Function to initialize the vector with random values
void Randomized_Init(vector<int> &V)
{
    for (int i = 0; i < V.size(); i++)
    {
        V[i] = rand() % 100;
    }
}

// Function to print the elements of the vector
void Vector_Print(const vector<int> &V)
{
    for (int i = 0; i < V.size(); i++)
    {
        cout << V[i] << " ";
    }
    cout << endl
         << endl
         << endl;
}

// HeapSort
void Heapify(vector<int> &arr, int n, int i)
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

void HeapSort(vector<int> &arr)
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
void Merge(vector<int> &arr, int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<int> L(n1), R(n2);

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

void MergeSort(vector<int> &arr, int l, int r)
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
int Partition(vector<int> &arr, int low, int high)
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

void QuickSort(vector<int> &arr, int low, int high)
{
    if (low < high)
    {
        int pi = Partition(arr, low, high);

        QuickSort(arr, low, pi - 1);
        QuickSort(arr, pi + 1, high);
    }
}

int main()
{
    // Example usage
    vector<int> Values(20);
    Randomized_Init(Values);

    cout << "Before Sorting...: " << endl;
    Vector_Print(Values);

    // Uncomment and use the sorting algorithm you want
    // HeapSort(Values);
    // MergeSort(Values, 0, Values.size() - 1);
    // QuickSort(Values, 0, Values.size() - 1);

    cout << "After Sorting...: " << endl;
    Vector_Print(Values);

    return 0;
}
