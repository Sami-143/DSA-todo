#include <iostream>
#include <stack>
#include <queue>
#include <stdexcept> // Include the <stdexcept> header for exceptions
using namespace std;

class MyQueue {
    stack<int> s1;

public:
    void Push(int x) {
        s1.push(x);
    }

    int pop() {
        if (s1.empty()) {
            cout << "Queue is already empty" << endl;
            return -1; // Return a sentinel value to indicate the error
        }
        int x = s1.top();
        s1.pop();
        if(s1.empty())
        {
            return x;
        }
        int top_value = pop();
        s1.push(x);
        return top_value;
    }

    bool empty() {
        return s1.empty();
    }
};

int main() {
    MyQueue q;
    q.Push(1);
    q.Push(2);
    q.Push(3);
    q.Push(4);
    q.Push(5);

    cout << q.pop() << endl;
    q.Push(6);
    cout << q.pop() << endl;
    cout << q.pop() << endl;

    cout << q.pop() << endl;
    cout << q.pop() << endl;
    cout << q.pop() << endl;
    cout << q.pop() << endl;

    return 0;
}


