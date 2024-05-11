#include <iostream>
#include <stdexcept> // Include the <stdexcept> header for std::runtime_error
using namespace std;

template<typename T>
class DynamicStack {
private:
    T* stackArray;
    int top;
    int capacity;

public:
    DynamicStack(int initialCapacity = 10) {
        capacity = initialCapacity;
        stackArray = new T[capacity];
        top = -1;
    }

    ~DynamicStack() {
        delete[] stackArray;
    }

    bool isEmpty() {
        return top == -1;
    }

    bool isFull() {
        return top == capacity - 1;
    }

    void push(T item) { // Change the parameter type to T
        if (isFull()) {
            // If the stack is full, double its capacity
            int newCapacity = capacity * 2;
            T* newStack = new T[newCapacity];

            for (int i = 0; i <= top; i++) {
                newStack[i] = stackArray[i];
            }

            delete[] stackArray;
            stackArray = newStack;
            capacity = newCapacity;
        }

        stackArray[++top] = item;
    }

    T pop() {
        if (!isEmpty()) {
            return stackArray[top--];
        } else {
            throw runtime_error("Stack is empty. Cannot pop."); // Throw a std::runtime_error
        }
    }

    T peek() {
        if (!isEmpty()) {
            return stackArray[top];
        } else {
            throw runtime_error("Stack is empty. Cannot peek."); // Throw a std::runtime_error
        }
    }

    int size() {
        return top + 1;
    }
};

int main() {
    DynamicStack<int> stack; // Specify the template type as 'int'

    stack.push(1);
    stack.push(2);
    stack.push(3);

    cout << "Stack Size: " << stack.size() << endl;
    cout << "Top Element: " << stack.peek() << endl;

    int poppedItem = stack.pop();
    cout << "Popped Element: " << poppedItem << endl;
    cout << "Stack Size after Pop: " << stack.size() << endl;

    return 0;
}