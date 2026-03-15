#include "list.hh"
#include <iostream>

using namespace std;

List::List() :
    first_(nullptr),
    last_(nullptr)
{
}

// Destructor: breaks the circle
List::~List()
{
    if(first_ == nullptr)
    {
        return;
    }

    // Break the circle first, otherwise shared_ptr reference counts
    // would never go to zero.
    last_->next = nullptr;

    // After the circle is broken, the chain is an ordinary one-way list.
    // Removing our own shared_ptrs is enough to free all nodes.
    first_ = nullptr;
    last_ = nullptr;
}

// Inserts the given element at the beginning of the list.
void List::insert_at_the_beginning(int i)
{
    shared_ptr<List_item> new_item = make_shared<List_item>();
    new_item->data = i;

    if(first_ == nullptr)
    {
        first_ = new_item;
        last_ = new_item;
        new_item->next = new_item;  // circular
    }
    else
    {
        new_item->next = first_;
        first_ = new_item;
        last_->next = first_;       // keep circular
    }
}

// Inserts the given element at the end of the list.
void List::insert_at_the_end(int i)
{
    shared_ptr<List_item> new_item = make_shared<List_item>();
    new_item->data = i;

    if(first_ == nullptr)
    {
        first_ = new_item;
        last_ = new_item;
        new_item->next = new_item;  // circular
    }
    else
    {
        new_item->next = first_;
        last_->next = new_item;
        last_ = new_item;
    }
}

// Removes the first element of the list.
// If the list is empty, does nothing.
void List::remove_first()
{
    if(first_ == nullptr)
    {
        return;
    }

    // Only one element
    if(first_ == last_)
    {
        first_->next = nullptr;  // break self-loop
        first_ = nullptr;
        last_ = nullptr;
    }
    else
    {
        shared_ptr<List_item> old_first = first_;
        first_ = first_->next;
        last_->next = first_;    // keep circular
        old_first->next = nullptr; // detach removed node
    }
}

// Removes the last element of the list.
// If the list is empty, does nothing.
void List::remove_last()
{
    if(first_ == nullptr)
    {
        return;
    }

    // Only one element
    if(first_ == last_)
    {
        first_->next = nullptr;  // break self-loop
        first_ = nullptr;
        last_ = nullptr;
        return;
    }

    shared_ptr<List_item> current = first_;

    // Find the node before last_
    while(current->next != last_)
    {
        current = current->next;
    }

    current->next = first_;
    last_->next = nullptr;   // detach removed node
    last_ = current;
}

// Prints the text "List elements:" and after that prints the elements
// of the list, all in the same line, separated by an empty space.
// If there are no elements in the list, prints the text "No elements".
void List::print()
{
    if(first_ == nullptr)
    {
        cout << "No elements" << endl;
        return;
    }

    cout << "List elements:";

    shared_ptr<List_item> current = first_;

    do
    {
        cout << " " << current->data;
        current = current->next;
    }
    while(current != first_);

    cout << endl;
}