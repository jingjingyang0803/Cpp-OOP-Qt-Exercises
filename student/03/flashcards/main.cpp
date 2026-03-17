/*
#############################################################################
# COMP.CS.115 Ohjelmointi 3: Rajapinnat / Programming 3: Interfaces         #
# Project: Opettelukortit / Flashcards                                      #
#############################################################################
*
* Provide starting comment here including the following:
*
* Author information
* - Name: Jingjing Yang
* - Student number: 154016843
* - Gitlab user name: ptjiya
* - Tuni email: jingjing.yang@tuni.fi
*
* Notes on the implementation choices:
* - The program is structured using three main classes:
*   Card, Deck and DeckManager.
* - Smart pointers (shared_ptr) are used to manage Card objects,
*   since a card can belong to multiple decks.
* - STL containers such as vector and map are used for storing data.
* - The logic is separated from the CLI by using DeckManager
*   as an abstraction layer.
*
* Additional notes:
* - The program follows object-oriented design principles.
* - Cards are stored in insertion order.
* - Duplicate cards are prevented within a single deck.
*
* Documentation of the use of AI tools (tool name and application):
* - ChatGPT (OpenAI) was used extensively during the project.
* - It was used to:
*   - explain the assignment requirements
*   - suggest program structure
*   - generate and refine parts of the implementation
*   - write and improve comments
*   - propose commit messages
*   - help create unit tests and documentation
* - The generated code and text were reviewed and tested
*   during the project work.
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
