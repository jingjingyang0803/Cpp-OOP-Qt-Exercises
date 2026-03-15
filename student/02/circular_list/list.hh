#ifndef LIST_HH
#define LIST_HH

#include <memory>

class List
{
public:
    // Constructor
    List();

    // Destructor: breaks the circle
    virtual ~List();

    // Inserts the given element at the beginning of the list.
    void insert_at_the_beginning(int i);

    // Inserts the given element at the end of the list.
    void insert_at_the_end(int i);

    // Removes the first element of the list.
    // If the list is empty, does nothing.
    void remove_first();

    // Removes the last element of the list.
    // If the list is empty, does nothing.
    void remove_last();

    // Prints the text "List elements:" and after that prints the elements
    // of the list, all in the same line, separated by an empty space.
    // If there are no elements in the list, prints the text "No elements".
    void print();

private:
    struct List_item
    {
        int data;
        std::shared_ptr<List_item> next;
    };
    std::shared_ptr<List_item> first_ = nullptr;
    std::shared_ptr<List_item> last_ = nullptr;
};

#endif // LIST_HH
