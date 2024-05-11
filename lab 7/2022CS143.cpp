#include <iostream>
using namespace std;

class node
{
public:
    int data;
    node *next;
    node *prev;

    node(int value)
    {
        data = value;
        next = nullptr;
        prev = nullptr;
    }
};

class DoublyLinkedList
{
public:
    node *head;
    node *tail;
    DoublyLinkedList()
    {
        head = nullptr;
        tail = nullptr;
    }

    // Forward Iterator
    class ForwardIterator
    {
        node *iter;

    public:
        ForwardIterator(node *n)
        {
            iter = n;
        }

        node *operator++()
        {
            return iter = iter->next;
        }

        node *operator--()
        {
            return iter = iter->prev;
        }

        bool operator!=(const ForwardIterator &other)
        {
            return iter != other.iter;
        }

        bool operator==(const ForwardIterator &other)
        {
            return iter == other.iter;
        }

        int operator*()
        {
            return iter->data;
        }
    };

    // Reverse Iterator
    class Reverse_Iterator
    {
        node *iter;

    public:
        Reverse_Iterator(node *n)
        {
            iter = n;
        }

        node *operator++()
        {
            return iter = iter->prev;
        }

        bool operator==(const Reverse_Iterator &other)
        {
            return iter == other.iter;
        }

        bool operator!=(const Reverse_Iterator &other)
        {
            return iter != other.iter;
        }

        int operator*()
        {
            return iter->data;
        }
    };

    // General Iterator
    class General_Iterator
    {
        node *iter;

    public:
        General_Iterator(node *n)
        {
            iter = n;
        }

        node *operator++()
        {
            return iter = iter->next;
        }

        node *operator--()
        {
            return iter = iter->prev;
        }

        bool operator==(const General_Iterator &other)
        {
            return iter == other.iter;
        }

        bool operator!=(const General_Iterator &other)
        {
            return iter != other.iter;
        }

        int operator*()
        {
            return iter->data;
        }
    };

    // Begin and End functions for each iterator
    ForwardIterator fbegin()
    {
        return ForwardIterator(head);
    }

    ForwardIterator fend()
    {
        return ForwardIterator(nullptr);
    }

    Reverse_Iterator Rbegin()
    {
        return Reverse_Iterator(tail);
    }

    Reverse_Iterator Rend()
    {
        return Reverse_Iterator(nullptr);
    }

    General_Iterator Gbegin()
    {
        return General_Iterator(head);
    }

    General_Iterator Gend()
    {
        return General_Iterator(nullptr);
    }

    void push_back(int val)
    {
        node *temp = new node(val);
        if (!head)
        {
            head = temp;
            tail = temp;
        }
        else
        {
            tail->next = temp;
            temp->prev = tail;
            tail = temp;
        }
    }

    bool isempty()
    {
        return head == nullptr;
    }

    void insert_At_Front(int val)
    {
        node *temp = new node(val);
        if (head == nullptr)
        {
            head = temp;
            tail = temp;
        }
        else
        {
            temp->next = head;
            head->prev = temp;
            head = temp;
        }
    }

    void insert_At_Tail(int val)
    {
        node *temp = new node(val);
        if (head == nullptr)
        {
            head = temp;
            tail = temp;
        }
        else
        {
            temp->prev = tail;
            tail->next = temp;
            tail = temp;
        }
    }
};

int main()
{
    DoublyLinkedList l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);

    // Forward Iterator
    for (DoublyLinkedList::ForwardIterator i = l.fbegin(); i != l.fend(); ++i)
    {
        cout << *i << " ";
    }
    cout << endl;

    // Reverse Iterator
    for (DoublyLinkedList::Reverse_Iterator i = l.Rbegin(); i != l.Rend(); ++i)
    {
        cout << *i << " ";
    }
    cout << endl;

    // General Iterator
    for (DoublyLinkedList::General_Iterator i = l.Gbegin(); i != l.Gend(); ++i)
    {
        cout << *i << " ";
    }
    cout << endl;

    return 0;
}




//Leet Code tasks
// Merging the two Arrays
// class Solution {
// public:
//     ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
//         ListNode* p1 = list1;
//         ListNode* p2 = list2;

//         ListNode* dummyNode = new ListNode(-1);
//         ListNode* p3 = dummyNode;

//         while(p1!=NULL && p2!=NULL)
//         {
//             if(p1->val < p2->val)
//             {
//                 p3->next = p1;
//                 p1 = p1->next;
//             }
//             else
//             {
//                 p3->next = p2;
//                 p2 = p2->next;
//             }
//             p3 = p3->next;
//         }

//         while(p1 != NULL)
//     {
//         p3 ->next = p1;
//         p1 = p1 ->next;
//         p3 = p3 ->next;
//     }

//     while(p2 != NULL)
//     {
//         p3 ->next = p2;
//         p2 = p2 ->next;
//         p3 = p3 ->next;
//     }
//     return dummyNode->next;
//     }
// };

// class Solution {
// public:
//     ListNode* removeNthFromEnd(ListNode* head, int n) {
//         ListNode* fast_ptr = head;
//         ListNode* slow_ptr = head;
//         for (int i = 0; i < n; i++)
//         {
//             fast_ptr = fast_ptr->next;
//         }
//         if (fast_ptr == nullptr)
//         {
//             return head->next;
//         }
//         while (fast_ptr->next != nullptr)
//         {
//             fast_ptr = fast_ptr->next;
//             slow_ptr = slow_ptr->next;
//         }
//         slow_ptr->next = slow_ptr->next->next;
//         return head;
//     }
// };

// Part 3

// class Solution {
// public:
//     ListNode* swapPairs(ListNode* head) {
//         ListNode* cur = head;
//         while (cur && cur->next)
//         {
//             swap(cur->val, cur->next->val);
//             cur = cur->next->next;
//         }
//         return head;
//     }
// };

// Part 4

// class Solution {
// public:
//     ListNode* reverseBetween(ListNode* head, int left, int right) {
//         if (left == right || head == nullptr)
//         {
//             return head;
//         }
//         ListNode* newNode = new ListNode;
//         newNode->next = head;
//         ListNode* previous = newNode;
//         for (int i = 0; i < left - 1; i++)
//         {
//             previous = previous->next;
//         }
//         ListNode* current = previous->next;
//         for (int i = 0; i < (right - left); i++)
//         {
//             ListNode* forward = current->next;
//             current->next = forward->next;
//             forward->next = previous->next;
//             previous->next = forward;
//         }
//         return newNode->next;
//     }
// };


//Part 5

// class MyLinkedList {
// private:
//     struct Node {
//         int val;
//         Node* next;

//         Node(int value) : val(value), next(nullptr) {}
//     };

//     Node* head;

// public:
//     MyLinkedList() : head(nullptr) {}

//     int get(int index) {
//         if (index < 0 || head == nullptr) {
//             return -1;  // Index out of range or empty list
//         }

//         Node* current = head;
//         for (int i = 0; i < index && current != nullptr; ++i) {
//             current = current->next;
//         }

//         return (current != nullptr) ? current->val : -1;  // Return value at index or -1 if not found
//     }

//     void addAtHead(int val) {
//         Node* newNode = new Node(val);
//         newNode->next = head;
//         head = newNode;
//     }

//     void addAtTail(int val) {
//         Node* newNode = new Node(val);
//         if (head == nullptr) {
//             head = newNode;
//             return;
//         }

//         Node* current = head;
//         while (current->next != nullptr) {
//             current = current->next;
//         }

//         current->next = newNode;
//     }

//     void addAtIndex(int index, int val) {
//         if (index < 0) {
//             addAtHead(val);  // Insert at the head if the index is negative
//             return;
//         }

//         Node* newNode = new Node(val);

//         if (index == 0) {
//             newNode->next = head;
//             head = newNode;
//             return;
//         }

//         Node* current = head;
//         for (int i = 0; i < index - 1 && current != nullptr; ++i) {
//             current = current->next;
//         }

//         if (current == nullptr) {
//             return;  // Index out of range
//         }

//         newNode->next = current->next;
//         current->next = newNode;
//     }

//     void deleteAtIndex(int index) {
//         if (index < 0 || head == nullptr) {
//             return;  // Index out of range or empty list
//         }

//         if (index == 0) {
//             Node* temp = head;
//             head = head->next;
//             delete temp;
//             return;
//         }

//         Node* current = head;
//         for (int i = 0; i < index - 1 && current != nullptr; ++i) {
//             current = current->next;
//         }

//         if (current == nullptr || current->next == nullptr) {
//             return;  // Index out of range
//         }

//         Node* temp = current->next;
//         current->next = current->next->next;
//         delete temp;
//     }
// };

