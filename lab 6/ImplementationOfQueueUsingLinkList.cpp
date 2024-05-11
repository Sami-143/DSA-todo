#include <iostream>
using namespace std;

template <typename T>
class LinkedList
{
public:  // Make the node class and its members public
    class Node
    {
    public:
        T data;
        Node *next;

        Node(T value)
        {
            data = value;
            next = nullptr;
        }
    };

private:
    Node *head;
    Node *tail;

public:
    LinkedList()
    {
        head = nullptr;
        tail = nullptr;
    }

    void append(T value)
    {
        Node *newNode = new Node(value);
        if (tail == nullptr)
        {
            head = tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
    }

    T removeFront()
    {
        if (head == nullptr)
        {
            cout << "Queue is empty" << endl;
            return T();  // Return a default value for T (assuming T has a default constructor)
        }
        T data = head->data;
        Node *temp = head;
        head = head->next;
        delete temp;
        if (head == nullptr)
        {
            tail = nullptr;
        }
        return data;
    }

    bool isEmpty()
    {
        return head == nullptr;
    }
};

template <typename T>
class Queue
{
private:
    LinkedList<T> list;

public:
    Queue() {}

    void Enqueue(T value)
    {
        list.append(value);
    }

    T Dequeue()
    {
        return list.removeFront();
    }

    bool IsEmpty()
    {
        return list.isEmpty();
    }
};

int main()
{
    Queue<int> queue;

    queue.Enqueue(1);
    queue.Enqueue(2);
    queue.Enqueue(3);

    while (!queue.IsEmpty())
    {
        cout << queue.Dequeue() << " ";
    }

    cout << endl;

    return 0;
}
