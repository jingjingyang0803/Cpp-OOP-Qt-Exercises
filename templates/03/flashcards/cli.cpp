/*
#############################################################################
# COMP.CS.115 Ohjelmointi 3: Rajapinnat / Programming 3: Interfaces         #
# Project: Opettelukortit / Flashcards                                      #
# File: cli.cpp                                                             #
# Description: Implements the command line interface logic.                 #
#                                                                           #
# Notes: * Responsible for command execution and user interaction.          #
#        * Performs input validation and file handling.                     #
#        * Delegates deck operations to DeckManager.                        #
#                                                                           #
# Student's don't touch this file.                                          #
#                                                                           #
#############################################################################
*/

#include "cli.hh"
#include "utils.hh"

#include <iostream>
#include <fstream>

// Iterate header line
const unsigned int DECK_NAME = 0;
const unsigned int FIELDS_COUNT = 1;
const unsigned int HEADER_SIZE = 2;

const string ERROR_FILE = "Error: Unable to open file.";
const string ERROR_FILE_HEADER = "Error: Erroneous file header.";
const string ERROR_FILE_CARD = "Error: Erroneous card in file.";
const string ERROR_PARAMETERS = "Error: Incorrect amount of parameters for command ";

const string ERROR_ADD_DECK = "Error: Error in adding the deck.";
const string ERROR_DECK_NOT_FOUND = "Error: Incorrect deck information.";
const string ERROR_FIELDS = "Error: Incorrect field information.";
const string ERROR_ADD_CARD = "Error: Error in adding the card.";
const string ERROR_FIELDS_DONT_MATCH = "Error: Deck fields don't match";

const string MESSAGE_ADD_DECK = "New deck added: ";
const string MESSAGE_CARDS_ADDED = "New cards added: ";
const string MESSAGE_CARD_ADDED = "Card added to deck ";
const string MESSAGE_DECK_COPIED = "Deck copied successfully.";

const string CLI_PROMPT = "CLI> ";

const string COMMAND_HELP =
    "file <file_name>              Reads a deck from a file\n"
    "decks                         Print all decks\n"
    "overview <deck>               Print all cards of a deck\n"
    "study <deck>                  Study cards of a deck\n\n"

    "create <deck>                 Create a new deck\n"
    "copy <source> <destination>   Copy source deck into destination deck\n\n"

    "add_card <deck>               Add a new card to the deck\n"

    "quit                          Terminate the program\n";

Cli::Cli() {}

Cli::~Cli() {}

void Cli::command_help(PARAMS )
{
    cout << COMMAND_HELP << endl;
}

bool Cli::run_program()
{
    manager_ = make_shared<DeckManager>();

    while (true)
    {
        cout << CLI_PROMPT;
        string command_line;
        getline(cin, command_line);
        cout << endl;

        vector<string> command_split = split(command_line, ' ');

        string command = command_split.at(0);

        if ( COMMANDS.find(command) == COMMANDS.end() )
        {
            cout <<  "Command " << command << " not found." << endl << endl;
            continue;
        }

        if ( COMMANDS.at(command).params.size() != command_split.size() )
        {
            cout << ERROR_PARAMETERS << command << "." << endl << endl;
            continue;
        }

        if ( COMMANDS.at(command).function != nullptr )
        {
            (this->*COMMANDS.at(command).function)(command_split);
        }
        else
        {
            break;
        }
        cout << endl;
    }

    return true;
}

void Cli::command_file(PARAMS params)
{
    read_file(params.at(1));
}

void Cli::command_decks(PARAMS)
{
    manager_->print_decks();
}

void Cli::command_overview(PARAMS params)
{
    string deck_name = params.at(1);

    if ( not validate_deck(deck_name) )
    {
        return;
    }

    manager_->overview(deck_name);
}

void Cli::command_create(PARAMS params)
{
    if ( manager_->deck_exists(params.at(1)) )
    {
        cout << ERROR_ADD_DECK << endl;
        return;
    }

    if ( not manager_->add_deck(params.at(1)) )
    {
        cout << endl << ERROR_ADD_DECK << endl;
        return;
    }

    cout << endl << MESSAGE_ADD_DECK << params.at(1) << endl;
}

void Cli::command_copy(PARAMS params)
{
    if ( not validate_deck(params.at(1)) )
    {
        return;
    }

    if ( not manager_->copy(params.at(1),
                               params.at(2)) )
    {
        cout << ERROR_FIELDS_DONT_MATCH << endl;
        return;
    }
    cout << MESSAGE_DECK_COPIED << endl;
}

void Cli::command_add_card(PARAMS params)
{
    if ( not validate_deck(params.at(1)) )
    {
        return;
    }

    if ( not manager_->add_card(params.at(1)) )
    {
        cout << ERROR_ADD_CARD << endl;
    }
    else
    {
        cout << MESSAGE_CARD_ADDED << params.at(1) << endl;
    }
}

void Cli::command_study(PARAMS params)
{
    const string& deck_name = params.at(1);

    if ( not validate_deck(deck_name) )
    {
        return;
    }

    if ( not manager_->run_study(deck_name) )
    {
        cout << ERROR_FIELDS << endl;
        return;
    }

}

bool Cli::validate_deck(const string &deck_name) const
{
    if ( not manager_->deck_exists(deck_name) )
    {
        cout << ERROR_DECK_NOT_FOUND << endl;
        return false;
    }
    return true;
}

bool Cli::read_file(const string &file_name)
{
    ifstream file_object(file_name);
    if ( not file_object )
    {
        cout << ERROR_FILE << endl;
        return false;
    }

    string deck_name = "";
    size_t field_count = 0;
    Fields field_names;
    unsigned int card_count = 0;

    if (not read_file_header(file_object, deck_name, field_count))
    {
        file_object.close();
        return false;
    }

    if (not read_field_names(file_object, field_count, field_names))
    {
        file_object.close();
        return false;
    }

    shared_ptr<Deck> new_deck = manager_->add_deck(deck_name, field_names);
    if ( not new_deck )
    {
        cout << ERROR_ADD_DECK << endl;
        file_object.close();
        return false;
    }

    read_cards(file_object, new_deck, field_names, card_count);

    cout << MESSAGE_ADD_DECK << deck_name << endl;
    cout << MESSAGE_CARDS_ADDED << card_count << endl;

    return true;
}

bool Cli::read_file_header(ifstream &file_object,
                           string &deck_name,
                           size_t &field_count)
{
    string header_line = "";
    getline(file_object, header_line);
    vector<string> split_header = split(header_line, ';');

    if ( split_header.size() != HEADER_SIZE or
         split_header.at(DECK_NAME).empty() or
         split_header.at(FIELDS_COUNT).empty() or
         not is_number(split_header.at(FIELDS_COUNT)) )
    {
        cout << ERROR_FILE_HEADER << endl;
        file_object.close();
        return false;
    }

    deck_name = split_header.at(DECK_NAME);
    field_count = stoi(split_header.at(FIELDS_COUNT));
    return true;
}

bool Cli::read_field_names(ifstream &file_object,
                           size_t expected_count,
                           Fields &field_names)
{
    string field_line = "";
    getline(file_object, field_line);
    field_names = split(field_line, ';');

    if ( field_names.size() != expected_count or
         check_empty_fields(field_names) )
    {
        cout << ERROR_FILE_HEADER << endl;
        file_object.close();
        return false;
    }
    return true;
}

void Cli::read_cards(ifstream &file,
                     shared_ptr<Deck> deck,
                     const Fields &field_names,
                     unsigned int &card_count)
{
    string card_line = "";
    card_count = 0;

    while (getline(file, card_line))
    {
        vector<string> split_line = split(card_line, ';');

        if (split_line.size() != field_names.size())
        {
            cout << ERROR_FILE_CARD << endl;
            continue;
        }

        if (not deck->add_card(field_names, split_line))
        {
            cout << ERROR_FILE_CARD << endl;
            continue;
        }
        ++card_count;
    }
}

