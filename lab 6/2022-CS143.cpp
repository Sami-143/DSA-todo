#include <iostream>
using namespace std;

class node
{
public:
    int data;
    node *next;
    node(int value)
    {
        data = value;
        next = nullptr;
    }
};

void Insert_AT_Tail(node *&head, int val)
{
    node *n = new node(val);

    if (head == nullptr)
    {
        head = n;
        return;
    }
    node *temp = head;
    while (temp->next != nullptr)
    {
        temp = temp->next;
    }
    temp->next = n;
}
void Insert_AT_Head(node *&head, int val)
{
    node *n = new node(val);
    n->next = head;
    head = n;
}

int search_At_Middle(node *&head)
{
    if (head == nullptr)
    {
        return -1;
    }

    int node_counter = 0;
    node *oneStep = head;
    node *twoStep = head;

    while (twoStep != nullptr && twoStep->next != nullptr)
    {
        oneStep = oneStep->next;
        twoStep = twoStep->next->next;
        node_counter++;
    }

    return node_counter;
}

void insertAtMiddle(node *&head, int val)
{
    node *curr = new node(val);
    int node_counter = 0;
    node *temp = head;
    while (temp != nullptr)
    {
        node_counter++;
        temp = temp->next;
    }
    temp = head;
    int mid = node_counter / 2;

    for (int i = 0; i < mid; i++)
    {
        temp = temp->next;
    }
    node *next_node = temp->next;
    temp->next = curr;
    curr->next = next_node;
}

void insert_After(node *&head, int val)
{
    node *curr = new node(val);
    node *temp = head;
    while (temp != nullptr)
    {
        temp = temp->next;
    }
    node *next_node = temp->next;
    temp->next = curr;
    curr->next = next_node;
}

// This function is used to delte the middle element in the Linked List
void removeMiddle(node *&head)
{
    if (head == nullptr || head->next == nullptr)
    {
        return;
    }

    int counter = 0;
    node *temp = head;
    node *prev_ptr = nullptr;

    while (temp != nullptr)
    {
        counter++;
        temp = temp->next;
    }

    temp = head;
    int mid = counter / 2;

    for (int i = 0; i < mid; i++)
    {
        prev_ptr = temp;
        temp = temp->next;
    }

    prev_ptr->next = temp->next;
    delete temp;
}

bool isEmpty(node *&head)
{
    node *temp = head;
    if (head == nullptr)
    {
        return true;
    }
    return false;
}

bool search(node *&head, int key)
{
    node *temp = head;
    while (temp->next != NULL)
    {
        if (temp->data == key)
        {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

void deletionAtHead(node *&head)
{
    node *todelete = head;
    head = head->next;
    delete todelete;
}

void deletion(node *&head, int val)
{
    if (head == nullptr)
    {
        return;
    }
    if (head->next == nullptr)
    {
        deletionAtHead(head);
        return;
    }
    node *temp = head;

    while (temp->next->data != val)
    {
        temp = temp->next;
    }
    node *todelete = temp->next;
    temp->next = temp->next->next;
    delete todelete;
}

void deleteAtTail(node *&head)
{
    node *temp = head;
    if (temp == nullptr)
    {
        return;
    }
    while (temp->next->next != NULL)
    {
        temp = temp->next;
    }

    delete temp->next;
    temp->next = nullptr;
}

bool isCircularLinkedList(node *head)
{
    node *temp = head;
    if (temp == nullptr)
    {
        return false;
    }
    while (temp->next != nullptr)
    {
        temp = temp->next;
        if (temp->next == head)
        {
            return true;
        }
    }
    return false;
}

node *reverse(node *&head)
{
    node *prevptr = NULL;
    node *currptr = head;
    node *nextptr;

    while (currptr != NULL)
    {
        nextptr = currptr->next;
        currptr->next = prevptr;
        prevptr = currptr;
        currptr = nextptr;
    }
    return prevptr;

}

node *reverseRecursive(node *&head)
{
    if (head == NULL || head->next == NULL)
    {
        return head;
    }
    node *newhead = reverseRecursive(head->next);
    head= head->next->next;
    head->next = NULL;

    return newhead;
}

void display(node *&head)
{
    node *temp = head;
    while (temp != NULL)
    {
        cout << temp->data << "->";
        temp = temp->next;
    }
    cout << "NULL" << endl;
}

int main()
{

    node *head = NULL;
    Insert_AT_Tail(head, 1);
    Insert_AT_Tail(head, 2);
    Insert_AT_Tail(head, 3);
    Insert_AT_Tail(head, 4);
    Insert_AT_Tail(head, 5);
    // Insert_AT_Head(head,6);

    display(head);

    deleteAtTail(head);
    display(head);
    if(isEmpty(head))
    {
        cout<<"link list is empty"<<endl;
    }

    cout<<search(head,3)<<endl;
    deletion(head,2);
    deletionAtHead(head);
    display(head);
    cout<<search_At_Middle(head);

    cout<<isCircularLinkedList(head);
    return 0;
}


//GET HEAD AND TAIL
// #include <iostream>
// using namespace std;

// template <typename T>
// class node {
// public:
//     T data;
//     node<T>* next;

//     node(T value) {
//         data = value;
//         next = nullptr;
//     }
// };

// template <typename T>
// bool isEmpty(node<T>* head) {
//     return head == nullptr;
// }

// template <typename T>
// void display(node<T>* head) {
//     node<T>* temp = head;
//     while (temp != nullptr) {
//         cout << temp->data << "->";
//         temp = temp->next;
//     }
//     cout << "NULL" << endl;
// }

// template <typename T>
// T GetFront(node<T>* head) {
//     if (head == nullptr) {
//         return T();
//     }
//     return head->data;
// }

// template <typename T>
// T GetTail(node<T>* head) {
//     if (head == nullptr) {
//         return T();
//     }

//     node<T>* temp = head;
//     while (temp->next != nullptr) {
//         temp = temp->next;
//     }
//     return temp->data;
// }

// int main() {
//     node<int>* intHead = nullptr;
//     Insert_AT_Tail(intHead, 1);
//     Insert_AT_Tail(intHead, 2);
//     Insert_AT_Tail(intHead, 3);
//     Insert_AT_Tail(intHead, 4);
//     Insert_AT_Tail(intHead, 5);

//     display(intHead);

//     if (isEmpty(intHead)) {
//         cout << "Integer linked list is empty" << endl;
//     } else {
//         int intFrontValue = GetFront(intHead);
//         int intTailValue = GetTail(intHead);

//         cout << "Integer Front Value: " << intFrontValue << endl;
//         cout << "Integer Tail Value: " << intTailValue << endl;
//     }

//     node<double>* doubleHead = nullptr;
//     Insert_AT_Tail(doubleHead, 1.1);
//     Insert_AT_Tail(doubleHead, 2.2);
//     Insert_AT_Tail(doubleHead, 3.3);
//     Insert_AT_Tail(doubleHead, 4.4);
//     Insert_AT_Tail(doubleHead, 5.5);

//     display(doubleHead);

//     if (isEmpty(doubleHead)) {
//         cout << "Double linked list is empty" << endl;
//     } else {
//         double doubleFrontValue = GetFront(doubleHead);
//         double doubleTailValue = GetTail(doubleHead);

//         cout << "Double Front Value: " << doubleFrontValue << endl;
//         cout << "Double Tail Value: " << doubleTailValue << endl;
//     }

//     return 0;
// }

//INSERT BEFORE AND AFTER

// #include <iostream>
// using namespace std;

// class node
// {
// public:
//     int data;
//     node *next;
//     node(int value)
//     {
//         data = value;
//         next = nullptr;
//     }
// };

// class LinkedList
// {
// private:
//     node *head;

// public:
//     LinkedList()
//     {
//         head = nullptr;
//     }
//     void insertAfter(int val, int key)
//     {
//         node *new_node = new node(val);
//         node *temp = head;

//         while (temp != nullptr)
//         {
//             if (temp->data == key)
//             {
//                 new_node->next = temp->next;
//                 temp->next = new_node;
//                 return;
//             }
//             temp = temp->next;
//         }
//     }
//     void insertBefore(int val, int key)
//     {
//         node *new_node = new node(val);

//         if (head && head->data == key)
//         {
//             new_node->next = head;
//             head = new_node;
//             return;
//         }

//         node *temp = head;

//         while (temp && temp->next != NULL)
//         {
//             if (temp->next->data == key)
//             {
//                 new_node->next = temp->next;
//                 temp->next = new_node;
//                 return;
//             }
//             temp = temp->next;
//         }
//     }

//     void append(int data)
//     {
//         node *new_node = new node(data);

//         if (!head)
//         {
//             head = new_node;
//             return;
//         }

//         node *temp = head;
//         while (temp->next)
//         {
//             temp = temp->next;
//         }
//         temp->next = new_node;
//     }

//     void display()
//     {
//         node *temp = head;
//         while (temp != nullptr)
//         {
//             cout << temp->data << " => ";
//             temp = temp->next;
//         }
//         cout << "nullptr" << endl;
//     }
// };

// int main()
// {

//     LinkedList linked_list;
//     linked_list.append(1);
//     linked_list.append(5);
//     linked_list.append(6);
//     linked_list.append(9);
//     linked_list.append(-50);
//     linked_list.append(75);

//     linked_list.display();
//     linked_list.insertAfter(9, 35);
//     linked_list.display();
//     linked_list.insertBefore(35, 9);
//     linked_list.display();

//     return 0;
// }



// #include <iostream>
// using namespace std;
// template <typename T>
// class LinkedList
// {
// private:
//     class node
//     {
//         T data;
//         node *next;
//         node(T value)
//         {
//             data = value;
//             next = nullptr; 
//         }
//     };

//     node *head;
//     node *tail;

// public:
//     LinkedList()
//     {
//         head = nullptr;
//         tail = nullptr;
//     }

//     void append(T value)
//     {
//         node *newNode = new node(value);
//         if (tail == nullptr)
//         {
//             head = tail = newNode;
//         }
//         else
//         {
//             tail->next = newNode;
//             tail = newNode;
//         }
//     }

//     T removeFront()
//     {
//         if (head == nullptr)
//         {
//             cout<<"Queue is empty"<<endl;
//         }
//         T data = head->data;
//         node *temp = head;
//         head = head->next;
//         delete temp;
//         if (head == nullptr)
//         {
//             tail = nullptr;
//         }
//         return data;
//     }

//     bool isEmpty()
//     {
//         return head == nullptr;
//     }
// };

// template <typename T>
// class Queue
// {
// private:
//     LinkedList<T> list;

// public:
//     Queue() {}

//     void Enqueue(T value)
//     {
//         list.append(value);
//     }

//     T Dequeue()
//     {
//         return list.removeFront();
//     }

//     bool IsEmpty()
//     {
//         return list.isEmpty();
//     }
// };

// int main()
// {
//     Queue<int> queue;

//     queue.Enqueue(1);
//     queue.Enqueue(2);
//     queue.Enqueue(3);

//     while (!queue.IsEmpty())
//     {
//         cout << queue.Dequeue() << " ";
//     }

//     cout << endl;

//     return 0;
// }



// #include <iostream>
// using namespace std;

// template <typename T>
// class node
// {
// public:
//     T data;
//     node<T> *next;
//     node(T value)
//     {
//         data = value;
//         next = nullptr;
//     }
// };

// template <typename T>
// class LinkedList
// {
// public:
//     node<T> *head;  

//     LinkedList()
//     {
//         head = nullptr;
//     }

//     void AddToFront(T value)
//     {
//         node<T> *newNode = new node<T>(value);
//         newNode->next = head;
//         head = newNode;
//     }

//     T RemoveFront()
//     {
//         if (IsEmpty())
//         {
//             cout << "List is empty. Cannot remove." << endl;
//             return T();
//         }
//         node<T> *temp = head;
//         T value = temp->data;
//         head = head->next;
//         delete temp;
//         return value;
//     }

//     bool IsEmpty()
//     {
//         return head == nullptr;
//     }
// };

// template <typename T>
// class Stack
// {
// private:
//     LinkedList<T> S;

// public:
//     Stack() {}

//     void Push(T value)
//     {
//         S.AddToFront(value);
//     }

//     T Pop()
//     {
//         if (!IsEmpty())
//         {
//             return S.RemoveFront();
//         }
//         else
//         {
//             cout << "Stack is empty. Cannot pop." << endl;
//             return T();  
//         }
//     }

//     bool IsEmpty()
//     {
//         return S.IsEmpty();
//     }
// };

// int main()
// {
//     Stack<int> intStack;
//     intStack.Push(1);
//     intStack.Push(2);
//     intStack.Push(3);

//     cout << "Is stack empty? " << intStack.IsEmpty() << endl;
//     int poppedValue = intStack.Pop();
//     cout << "Popped value: " << poppedValue << endl;
//     cout << "Is stack empty? " << intStack.IsEmpty() << endl;
//     return 0;
// }

