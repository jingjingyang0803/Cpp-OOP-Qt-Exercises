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

void DeckManager::print_decks() const
{

}

shared_ptr<Deck> DeckManager::add_deck(string deck_name)
{

}

shared_ptr<Deck> DeckManager::add_deck(string deck_name,
                                       const Fields &field_types)
{

}

bool DeckManager::add_card(string deck_name)
{

}

void DeckManager::overview(const string& deck_name)
{

}

bool DeckManager::copy(string source_deck_name,
                       string destination_deck_name)
{

}

bool DeckManager::run_study(const string &deck_name)
{

}

bool DeckManager::deck_exists(const string &deck_name) const
{

}

shared_ptr<Fields> DeckManager::get_deck_fields(const string &deck_name) const
{

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

