/*
#############################################################################
# COMP.CS.115 Ohjelmointi 3: Rajapinnat / Programming 3: Interfaces         #
# Project: Opettelukortit / Flashcards                                      #
# File: cli.hh                                                              #
# Description: Declares the command line interface of the program.          #
#                                                                           #
# Notes: * Handles user input and calls for commands.                       #
#        * Connects user commands to Deckmanager functionalities.           #
#                                                                           #
# Student's don't touch this file.                                          #
#                                                                           #
#############################################################################
*/

#ifndef CLI_HH
#define CLI_HH

#include "deckmanager.hh"

#include <string>
#include <memory>
#include <map>
#include <vector>

using namespace std;

/**
 * @brief Alias for command parameter list.
 */
using PARAMS = vector<string>;

class Cli;

/**
 * @brief Represents a single Cli command.
 *
 * Stores the command name, required number of parameters,
 * and a pointer to the corresponding Cli member function.
 */
struct Command {

    /** Name of the command as entered by the user */
    string name;

    /** Types of parameters expected (including command name) */
    PARAMS params;

    /**
     * Pointer to the Cli member function that implements the command.
     * If nullptr, the command does not execute a function (e.g. quit).
     */
    void (Cli::*function)(PARAMS);

    /**
     * @brief Comparison operator for ordering commands.
     * @param other Another Command to compare against
     * @return True if this command is ordered before the other
     */
    bool operator< (const Command& other) const
    {
        return name < other.name;
    }
};

/**
 * @brief Command-line interface for the station system.
 *
 * Handles user input, command parsing, and delegates operations
 * to the underlying Deckmanager.
 */
class Cli
{
public:
    /**
     * @brief Constructs a Cli object.
     */
    Cli();

    /**
     * @brief Deconstructs a Cli object.
     */
    ~Cli();

    /**
     * @brief Prints help information for all available commands.
     * Lists all supported commands and their usage.
     *
     * @param params as follows:
     *    params.at(0) command
     */
    void command_help(PARAMS params);

    /**
     * @brief Runs the main program loop.
     *
     * Reads user commands, validates them, and executes
     * the corresponding actions until termination.
     *
     * @return True on normal termination, false on error
     */
    bool run_program();

    /**
     * @brief Reads one deck from a file.
     *
     * Reads Deck, Field and Card data from an input file
     * and stores them by calling DeckManager.
     *
     * @param params as follows:
     *    params.at(0) command
     *    params.at(1) input file name
     */
    void command_file(PARAMS params);

    /**
     * @brief Prints all existing decks.
     *
     * @param params as follows:
     *    params.at(0) command
     */
    void command_decks(PARAMS params);

    /**
     * @brief Prints all cards of a deck.
     * Prompts the user to select which fields should be displayed.
     *
     * @param params as follows:
     *    params.at(0) command
     *    params.at(1) deck name
     */
    void command_overview(PARAMS params);

    /**
     * @brief Creates a new deck.
     * Prompts the user to define deck fields and creates an empty deck.
     *
     * @param params as follows:
     *    params.at(0) command
     *    params.at(1) new deck name
     */
    void command_create(PARAMS params);

    /**
     * @brief Copies an existing deck.
     * Copies all cards from source deck to destination deck.
     *
     * @param params as follows:
     *    params.at(0) command
     *    params.at(1) source deck name
     *    params.at(2) destination deck name
     */
    void command_copy(PARAMS params);

    /**
     * @brief Adds a new card to a deck.
     * Prompts the user to enter definitions for each field of the deck.
     *
     * @param params as follows:
     *    params.at(0) command
     *    params.at(1) deck name
     */
    void command_add_card(PARAMS params);

    /**
     * @brief Starts an interactive study session.
     * Prompts the user to choose which fields to show and which to answer,
     * then iterates through all cards and checks user input.
     *
     * @param params as follows:
     *    params.at(0) command
     *    params.at(1) deck name
     */
    void command_study(PARAMS params);

private:
    /**
     * @brief Shared pointer to the DeckManager object.
     */
    shared_ptr<DeckManager> manager_;

    /**
     * @brief Map of command strings to command definitions.
     *
     * Used for command lookup, parameter validation,
     * and function calls. Add more keywords for quicker Cli usage, if
     * you'd like.
     */
    const map<string, Command> COMMANDS = {
        {"help", {"help", {"command"}, &Cli::command_help}},

        // File reading command
        {"file", {"file", {"command", "file name"}, &Cli::command_file}},

        // Commands related to decks
        {"decks", {"decks", {"command"}, &Cli::command_decks}},
        {"overview", {"overview", {"command", "deck name"}, &Cli::command_overview}},
        {"create", {"create", {"command", "deck name"}, &Cli::command_create}},
        {"copy", {"copy", {"command", "deck name", "deck name"}, &Cli::command_copy}},

        // Commands related to cards
        {"add_card", {"add_card", {"command", "deck name"}, &Cli::command_add_card}},

        // Study command
        {"study", {"study", {"command", "deck name"}, &Cli::command_study}},

        // Quitting the program
        {"quit", {"quit", {"command"}, nullptr}}
    };

    /**
     * @brief Validates existence of a deck.
     * @param deck_name Name of the deck
     * @return True if deck exists, false otherwise.
     */
    bool validate_deck(const string& deck_name) const;

    /**
     * @brief Reads a deck definition file.
     *
     * Parses the file header, field names, and all cards.
     * Checks for inconsitencies in the input file.
     *
     * @param file_name Name of the file to read
     * @return True if file was successfully read, false otherwise.
     */
    bool read_file(const string& file_name);


    /**
     * @brief Reads file header line.
     *
     * Extracts deck name and number of fields.
     *
     * @param file Input file stream
     * @param deck_name Output deck name
     * @param field_count Output field count
     * @return True on success, false otherwise.
     */
    bool read_file_header(ifstream& file_object,
                          string& deck_name,
                          size_t& field_count);

    /**
     * @brief Reads second header line.
     *
     * Extracts field names.
     *
     * @param file Input file stream
     * @param expected_count Expected number of fields
     * @param field_names Output field list
     * @return True on success, false otherwise.
     */
    bool read_field_names(ifstream& file_object,
                          size_t expected_count,
                          Fields& field_names);

    /**
     * @brief Reads all cards from file.
     *
     * @param file Input file stream
     * @param deck_name Pointer to the Deck
     * @param field_names Field definitions
     * @param card_count Output number of successfully read cards
     */
    void read_cards(ifstream& file_object,
                    shared_ptr<Deck> deck,
                    const Fields& field_names,
                    unsigned int& card_count);
};


#endif // CLI_HH
