#include "list.hh"
#include <iostream>
#include <string>

using namespace std;

int main()
{
    List list;
    int input = 0;
    do
    {
        cout << "Input a list element: ";
        cin >> input;

        // Inserting even elements at the beginning and odd ones at the end
        if(input % 2 == 0)
        {
            list.insert_at_the_beginning(input);
        }
        else
        {
            list.insert_at_the_end(input);
        }

        // Printing the list
        list.print();
    } while(input != 0);

    // Removing the first and last elements and printing the resulting list
    list.remove_first();
    list.print();
    list.remove_last();
    list.print();

    return 0;
}
