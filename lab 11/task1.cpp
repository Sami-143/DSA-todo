#include <queue>
#include <vector>
#include <iostream>
#include <stdlib.h>
using namespace std;


int main()
{
    // Examplo 1 (Internally you can safely assume "priority queue" a heap data structures).
    priority_queue<int> PQ;
    PQ.push(20);
    PQ.push(30);
    PQ.push(40);
    PQ.push(10);
    PQ.push(5);
    while (!PQ.empty())
    {
        cout << PQ.top() << " ";
        PQ.pop();
    }

    return 0;
}