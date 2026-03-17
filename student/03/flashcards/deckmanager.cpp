/*
#############################################################################
# COMP.CS.115 Ohjelmointi 3: Rajapinnat / Programming 3: Interfaces         #
# Project: Opettelukortit / Flashcards                                      #
# File: deckmanager.cpp                                                     #
# Description: Implements DeckManager functionality.                        #
#                                                                           #
# Notes:                                                                    #
#                                                                           #
# Author information:                                                       #
#                                                                           #
#############################################################################
*/

#include "deckmanager.hh"
#include "utils.hh"

#include <iostream>
#include <iomanip>

const string PROMPT_FIELDS_PRINT = "Choose fields to print: ";
const string PROMPT_FIELDS_ANSWER = "Choose fields to answer: ";
const string PROMPT_TYPE_FIELDS = "Type all fields separated with spaces: ";
const string PROMPT_TYPE_DEFINITIONS = "Type all definitions line by line: ";

const string NO_DECKS = "No decks have been added.";
const string NO_CARDS = "No cards have been added.";

const string MESSAGE_STUDY_PROMPTS = "Prompts shown in: ";
const string MESSAGE_STUDY_ANSWERS = "Type answers in: ";
const string MESSAGE_STUDY_RESULT = "Final result of the study session: ";

const string FIELDS_PROMPT = "FIELDS> ";

DeckManager::DeckManager() {}

DeckManager::~DeckManager() {}

// Prints all deck names and the number of cards they contain.
void DeckManager::print_decks() const
{
    if ( decks_.empty() )
    {
        cout << NO_DECKS << endl;
        return;
    }

    for ( const auto& deck_pair : decks_ )
    {
        cout << "- " << deck_pair.first
             << " (" << deck_pair.second->get_deck_size()
             << " cards)" << endl;
    }
}

// Create and add the new deck with the provided name and fields
// Returns nullptr if a deck with the same name already exists,
// or if the provided fields are invalid (empty or contain empty fields),
// otherwise returns a pointer to the created deck.
shared_ptr<Deck> DeckManager::add_deck(string deck_name)
{
    // Check if a deck with the same name already exists
    if ( deck_exists(deck_name) )
    {
        return nullptr;
    }

    // Asks user to type fields that will initialize the deck fields.
    cout << PROMPT_TYPE_FIELDS << endl;
    cout << FIELDS_PROMPT;

    string input = "";
    getline(cin, input);
    cout << endl;

    // Split the input into fields and check for empty fields
    Fields input_fields = split(input, ' ');

    if ( input_fields.empty() || check_empty_fields(input_fields) )
    {
        return nullptr;
    }

    return add_deck(deck_name, input_fields);
}

// Creates a new empty deck.
// Initializes a deck with the given name and field structure.
shared_ptr<Deck> DeckManager::add_deck(string deck_name,
                                       const Fields &field_types)
{
    if ( deck_exists(deck_name) )
    {
        return nullptr;
    }

    shared_ptr<Deck> new_deck = make_shared<Deck>(deck_name, field_types);
    decks_[deck_name] = new_deck;
    return new_deck;
}

// Adds a new card to an existing deck.
// Prompts the user to fill out definitions for all field types of the deck.
// Accepts empty definitions.
// Returns false if deck doesn't exist, false if the card can't be
// added successfully to the deck, true otherwise.
bool DeckManager::add_card(string deck_name)
{
    if ( not deck_exists(deck_name) )
    {
        return false;
    }

    shared_ptr<Fields> deck_fields = get_deck_fields(deck_name);
    Fields definitions;

    cout << PROMPT_TYPE_DEFINITIONS << endl;

    for ( const string& field : *deck_fields )
    {
        cout << field << ": ";
        string definition = "";
        getline(cin, definition);
        definitions.push_back(definition);
    }

    cout << endl;

    return decks_.at(deck_name)->add_card(*deck_fields, definitions);
}

// Prints the deck name, size, and card information of a deck.
void DeckManager::overview(const string& deck_name)
{
    // Check if the deck exists before proceeding with the overview.
    if (not deck_exists(deck_name))
    {
        return;
    }

    Fields requested_fields;

    // Ask the user for fields to print
    ask_fields(deck_name, PROMPT_FIELDS_PRINT, requested_fields, true);

    shared_ptr<Deck> deck = decks_.at(deck_name);

    // Handle the case when user inputted nonexisting fields
    if (not deck->print_deck(requested_fields))
    {
        cout << "Error: Incorrect field information." << endl;
    }
}

/**
 * @brief Copies all cards from the source deck into the destination deck.
 *
 * If the destination deck does not exist, it is created using the same
 * field structure as the source deck. Cards are copied without duplication.
 *
 * @param source_deck_name Name of the source deck
 * @param destination_deck_name Name of the destination deck
 * @return false if the source deck does not exist,
 *         false if both decks exist and their fields do not match,
 *         false if the destination deck could not be created or cards
 *         could not be copied, true otherwise
 */
bool DeckManager::copy(string source_deck_name,
                       string destination_deck_name)
{
    if ( not deck_exists(source_deck_name) )
    {
        return false;
    }

    shared_ptr<Deck> source = decks_.at(source_deck_name);
    shared_ptr<Fields> source_fields = source->get_fields();

    shared_ptr<Deck> destination = nullptr;

    if ( not deck_exists(destination_deck_name) )
    {
        destination = add_deck(destination_deck_name, *source_fields);

        if ( destination == nullptr )
        {
            return false;
        }
    }
    else
    {
        destination = decks_.at(destination_deck_name);

        if ( not fields_match(*source_fields, *(destination->get_fields())) )
        {
            return false;
        }
    }

    return source->copy_cards(destination);
}

bool DeckManager::run_study(const string &deck_name)
{

}

bool DeckManager::deck_exists(const string &deck_name) const
{
    return decks_.find(deck_name) != decks_.end();
}

shared_ptr<Fields> DeckManager::get_deck_fields(const string &deck_name) const
{
    if ( not deck_exists(deck_name) )
    {
        return nullptr;
    }

    return decks_.at(deck_name)->get_fields();
}

void DeckManager::ask_fields(const string& deck_name,
                             const string& prompt_message,
                             Fields& input_fields,
                             bool allow_all) const
{
    if ( not deck_exists(deck_name) )
    {
        return;
    }

    shared_ptr<Fields> deck_fields = get_deck_fields(deck_name);

    cout << prompt_message << endl;

    for (const string& field : *deck_fields)
    {
        cout << field << " ";
    }

    if (allow_all)
    {
        cout << "or all";
    }

    cout << endl << FIELDS_PROMPT;

    string input = "";
    getline(cin, input);

    cout << endl;

    input_fields = split(input, ' ');

    if (allow_all and input_fields.size() == 1 and input_fields.at(0) == "all")
    {
        input_fields = *deck_fields;
    }
}

