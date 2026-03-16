/*
#############################################################################
# COMP.CS.115 Ohjelmointi 3: Rajapinnat / Programming 3: Interfaces         #
# Project: Opettelukortit / Flashcards                                      #
#############################################################################
*
* Provide starting comment here including the following:
*
* Author information
* - Name:
* - Student number:
* - Gitlab user name:
* - Tuni email:
*
* Notes on the implementation choices:
*
* Additional notes:
*
* Documentation of the use of AI tools (tool name and application):
*
*/

#include "cli.hh"

#include <iostream>

using namespace std;

int main()
{
    cout << "[Flashcards]" << endl << endl;

    shared_ptr<Cli> cli = make_shared<Cli>();
    if ( not cli->run_program() )
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
