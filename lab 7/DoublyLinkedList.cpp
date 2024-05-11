#include <iostream>
using namespace std;
template <typename T>
class DoublyLinkedList
{
private:
    struct Node
    {
        T data;
        Node *prev;
        Node *next;

        Node(T value) : data(value), prev(nullptr), next(nullptr) {}
    };

    Node *head;
    Node *tail;

public:
    class Iterator
    {
    private:
        Node *current;

    public:
        Iterator(Node *node) : current(node) {}

        Iterator &operator++()
        {
            if (current)
            {
                current = current->next;
            }
            return *this;
        }

        Iterator &operator--()
        {
            if (current)
            {
                current = current->prev;
            }
            return *this;
        }

        bool operator==(const Iterator &other) const
        {
            return current == other.current;
        }

        bool operator!=(const Iterator &other) const
        {
            return !(*this == other);
        }

        T &operator*()
        {
            return current->data;
        }

        // Declare Iterator as a friend to access private members of Node
        friend class DoublyLinkedList;
    };

    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    Iterator begin()
    {
        return Iterator(head);
    }

    Iterator end()
    {
        return Iterator(nullptr);
    }

    bool Empty() const
    {
        return head == nullptr;
    }

    void insertAt(Iterator place, T val)
    {
        Node *newNode = new Node(val);
        Node *currentNode = place.current;
        if (currentNode)
        {
            newNode->prev = currentNode->prev;
            newNode->next = currentNode;
            if (currentNode->prev)
            {
                currentNode->prev->next = newNode;
            }
            else
            {
                head = newNode;
            }
            currentNode->prev = newNode;
        }
    }

    void insertAtAfter(Iterator place, T val)
    {
        insertAt(++place, val);
    }

    void insertAtBefore(Iterator place, T val)
    {
        insertAt(place, val);
    }

    void InsertAtFront(T val)
    {
        Node *newNode = new Node(val);
        newNode->next = head;
        if (head)
            head->prev = newNode;
        head = newNode;
        if (!tail)
            tail = newNode;
    }

    void InsertAtTail(T val)
    {
        Node *newNode = new Node(val);
        newNode->prev = tail;
        if (tail)
        {
            tail->next = newNode;
        }
        tail = newNode;
        if (!head)
        {
            head = newNode;
        }
    }

    void RemoveAt(Iterator place)
    {
        Node *currentNode = place.current;
        if (currentNode)
        {
            if (currentNode->prev)
            {
                currentNode->prev->next = currentNode->next;
            }
            else
            {
                head = currentNode->next;
            }
            if (currentNode->next)
            {
                currentNode->next->prev = currentNode->prev;
            }
            if (currentNode == tail)
            {
                tail = currentNode->prev;
            }
            delete currentNode;
        }
    }

    void Splice(Iterator place, DoublyLinkedList &newList)
    {
        if (newList.Empty() || place.current == nullptr)
        {
            return;
        }

        Node *newHead = newList.head;
        Node *newTail = newList.tail;
        Node *givenPrev = place.current->prev;

        if (givenPrev)
        {
            givenPrev->next = newHead;
        }
        else
        {
            head = newHead;
        }

        newHead->prev = givenPrev;
        place.current->prev = newTail;
        newTail->next = place.current;
        if (place.current == tail)
        {
            tail = newTail;
        }

        newList.head = nullptr;
        newList.tail = nullptr;
    }
};

int main()
{
    DoublyLinkedList<int> myList;

    myList.InsertAtFront(10);
    myList.InsertAtFront(2);
    myList.InsertAtFront(12);
    myList.InsertAtTail(4);
    myList.InsertAtTail(5);



    cout << " First List of the elements are : ";
    for (auto it = myList.begin(); it != myList.end(); ++it)
    {
        cout << *it << " ";
    }
    cout << endl;

    DoublyLinkedList<int>::Iterator iteratorToRemove = myList.begin();
    ++iteratorToRemove;
    myList.RemoveAt(iteratorToRemove);

    // Print updated list elements
    cout << "Updated list elements: ";
    for (auto it = myList.begin(); it != myList.end(); ++it)
    {
        cout << *it << " ";
    }
    cout << endl;

    DoublyLinkedList<int> anotherList;
    anotherList.InsertAtFront(89);
    anotherList.InsertAtFront(26);
    anotherList.InsertAtFront(22);
    cout << endl<<endl;
    cout << "2nd list elements are : ";
    for (auto it = anotherList.begin(); it != anotherList.end(); ++it)
    {
        cout << *it << " ";
    }
    cout << endl;

    myList.Splice(++myList.begin(), anotherList);
    cout << endl<<endl;
    cout << "After Splicing: ";
    for (auto it = myList.begin(); it != myList.end(); ++it)
    {
        cout << *it << " ";
    }
    cout << endl<<endl;

    return 0;
}
