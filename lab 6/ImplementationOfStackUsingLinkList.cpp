#include <iostream>
using namespace std;

template <typename T>
class node
{
public:
    T data;
    node<T> *next;
    node(T value)
    {
        data = value;
        next = nullptr;
    }
};

template <typename T>
class LinkedList
{
public:
    node<T> *head;  

    LinkedList()
    {
        head = nullptr;
    }

    void AddToFront(T value)
    {
        node<T> *newNode = new node<T>(value);
        newNode->next = head;
        head = newNode;
    }

    T RemoveFront()
    {
        if (IsEmpty())
        {
            cout << "List is empty. Cannot remove." << endl;
            return T();
        }
        node<T> *temp = head;
        T value = temp->data;
        head = head->next;
        delete temp;
        return value;
    }

    bool IsEmpty()
    {
        return head == nullptr;
    }
};

template <typename T>
class Stack
{
private:
    LinkedList<T> S;

public:
    Stack() {}

    void Push(T value)
    {
        S.AddToFront(value);
    }

    T Pop()
    {
        if (!IsEmpty())
        {
            return S.RemoveFront();
        }
        else
        {
            cout << "Stack is empty. Cannot pop." << endl;
            return T();  
        }
    }

    bool IsEmpty()
    {
        return S.IsEmpty();
    }
};

int main()
{
    Stack<int> intStack;
    intStack.Push(1);
    intStack.Push(2);
    intStack.Push(3);

    cout << "Is stack empty? " << intStack.IsEmpty() << endl;
    int poppedValue = intStack.Pop();
    cout << "Popped value: " << poppedValue << endl;
    cout << "Is stack empty? " << intStack.IsEmpty() << endl;
    return 0;
}
