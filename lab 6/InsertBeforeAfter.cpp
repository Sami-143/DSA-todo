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

class LinkedList
{
private:
    node *head;

public:
    LinkedList()
    {
        head = nullptr;
    }
    void insertAfter(int val, int key)
    {
        node *new_node = new node(val);
        node *temp = head;

        while (temp != nullptr)
        {
            if (temp->data == key)
            {
                new_node->next = temp->next;
                temp->next = new_node;
                return;
            }
            temp = temp->next;
        }
    }
    void insertBefore(int val, int key)
    {
        node *new_node = new node(val);

        if (head && head->data == key)
        {
            new_node->next = head;
            head = new_node;
            return;
        }

        node *temp = head;

        while (temp && temp->next != NULL)
        {
            if (temp->next->data == key)
            {
                new_node->next = temp->next;
                temp->next = new_node;
                return;
            }
            temp = temp->next;
        }
    }

    void append(int data)
    {
        node *new_node = new node(data);

        if (!head)
        {
            head = new_node;
            return;
        }

        node *temp = head;
        while (temp->next)
        {
            temp = temp->next;
        }
        temp->next = new_node;
    }

    void display()
    {
        node *temp = head;
        while (temp != nullptr)
        {
            cout << temp->data << " => ";
            temp = temp->next;
        }
        cout << "nullptr" << endl;
    }
};

int main()
{

    LinkedList linked_list;
    linked_list.append(1);
    linked_list.append(5);
    linked_list.append(6);
    linked_list.append(9);
    linked_list.append(-50);
    linked_list.append(75);

    linked_list.display();
    linked_list.insertAfter(9, 35);
    linked_list.display();
    linked_list.insertBefore(35, 9);
    linked_list.display();

    return 0;
}