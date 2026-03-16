/*
#############################################################################
# COMP.CS.115 Ohjelmointi 3: Rajapinnat / Programming 3: Interfaces         #
# Project: Opettelukortit / Flashcards                                      #
# File: deckmanager.hh                                                      #
# Description: Declares the DeckManager class interface.                    #
#                                                                           #
# Notes: * Manages multiple decks.                                          #
#        * Provides operations for creating, combining and studying decks.  #
#        * Acts as an abstraction layer between CLI and Deck objects.       #
#                                                                           #
# Author information:                                                       #
#                                                                           #
#############################################################################
*/

#ifndef DECKMANAGER_HH
#define DECKMANAGER_HH

#include "deck.hh"
#include <memory>

class DeckManager
{
public:
    /**
     * @brief Constructs a DeckManager object.
     *
     * Initializes an empty deck container.
     */
    DeckManager();

    /**
     * @brief Deconstructs the DeckManager object.
     */
    ~DeckManager();

    /**
     * @brief Prints all deck names and the number of cards they contain.
     *
     * Called in command 'decks'.
     */
    void print_decks() const;

    /**
     * @brief Creates a new empty deck.
     *
     * Called in command 'create'.
     *
     * Asks user to type fields that will initialize the deck fields.
     *
     * @param deck_name Deck name
     * @return Pointer to the deck if it was created successfully,
     * nullptr otherwise.
     */
    shared_ptr<Deck> add_deck(string deck_name);

    /**
     * @brief Creates a new empty deck.
     * Initializes a deck with the given name and field structure.
     *
     * Called in command 'file'.
     *
     * @param deck_name Deck name
     * @param field_names Field type identifiers
     * @return shared_ptr to the created deck,
     * nullptr if a deck with the same name already existed.
     */
    shared_ptr<Deck> add_deck(string deck_name,
                              const Fields& field_types);

    /**
     * @brief Adds a new card to an existing deck.
     *
     * Called in command 'add_card'.
     *
     * Prompts the user to fill out definitions for all field types of the deck.
     * Accepts empty definitions.
     *
     * @param deck_name Deck name
     * @return False if deck doesn't exist, false if the card can't be
     * added successfully to the deck, true otherwise.
     */
    bool add_card(string deck_name);

    /**
     * @brief Prints the deck name, size, and card information of a deck.
     *
     * Called in command 'overview'.
     *
     * Prints deck information and all cards. Prompts user to choose the
     * fields for which definitions are printed.
     *
     * @param deck_name Deck name
     */
    void overview(const string& deck_name);

    /**
     * @brief Copies all cards from the source deck into the destination deck.
     * Creates the destination deck if it does not exist.
     *
     * Called in command 'copy'.
     *
     * @param source_deck_name Name of the source deck
     * @param destination_deck_name Name of the destination deck
     * @return False if source deck doesn't exist,
     * False if both decks exist and their fields don't match,
     * False if destination deck couldn't been initialized or cards could not
     * been copied to it, true otherwise.
     */
    bool copy(string source_deck_name,
              string destination_deck_name);

    /**
     * @brief Runs a study session.
     *
     * Called by command 'study'.
     *
     * Iterates through all cards, prompts the user for field selection,
     * collects user answers and checks their correctness.
     *
     * @param deck_name Name of the studied deck
     * @return False if user requests nonexisting fields,
     * true otherwise.
     */
    bool run_study(const string& deck_name);

    /**
     * @brief Checks if a deck exists.
     *
     * @param deck_name Deck name
     * @return True if the deck exists,
     * false otherwise.
     */
    bool deck_exists(const string& deck_name) const;

private:
    // Declare more attributes and/or methods here

    /**
     * @brief returns Deck fields
     *
     * Interface in template code but not mandatory to use. Changes allowed.
     *
     * @param deck_name Deck name
     * @return Pointer to Deck fields if successful,
     * nullptr if the Deck didn't exist
     */
    shared_ptr<Fields> get_deck_fields(const string& deck_name) const;

    /**
     * @brief Prompts the user to select fields.
     *
     * Prints available fields and reads user selected fields.
     * Doesn't check the validity of the field selection.
     *
     * Provided in template code but not mandatory to use. Changes allowed.
     *
     * @param deck_name Name of the deck
     * @param prompt_message Prompt that is printed
     * @param input_fields Output vector containing user selected fields
     * @param allow_all Whether "all" is allowed as input
     */
    void ask_fields(const string& deck_name,
                    const string& prompt_message,
                    Fields& input_fields,
                    bool allow_all = true) const;

};

#endif // DECKMANAGER_HH
