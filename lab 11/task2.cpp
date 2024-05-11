#include <iostream>
#include <vector>
#include <queue>
using namespace std;


template<class T>
class Compare {
public:
    bool operator()(const T& a, const T& b) {
        return a >= b;
    }
};

template<class T>
void Heapsort(vector<T>& V) {
    // Create a max heap
    priority_queue<T, vector<T>, Compare<T>> PQ;

    // Push elements from the vector into the max heap
    for (int vi = 0; vi < V.size(); vi++) {
        PQ.push(V[vi]);
    }

    // Clear the previous vector
    V.clear();

    // Pop elements from the max heap and add to the vector in reverse order
    while (!PQ.empty()) {
        V.push_back(PQ.top());
        PQ.pop();
    }
}

int main() {
    vector<int> V = { 9, 9, 9, 8, 9, 8, 8, 8, 9, 8, 9, 8, 8, 2, 9 };

    try {
        // Call the Heapsort function
        Heapsort(V);

        // Print the sorted vector
        for (const auto& val : V) {
            cout << val << " ";  // Note: cout is now used directly without std::
        }
    }
    catch (const std::exception& e) {
        cerr << "Exception: " << e.what() << endl;
    }

    return 0;
}