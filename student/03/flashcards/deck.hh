/*
#############################################################################
# COMP.CS.115 Ohjelmointi 3: Rajapinnat / Programming 3: Interfaces         #
# Project: Opettelukortit / Flashcards                                      #
# File: deck.hh                                                             #
# Description: Declares the Deck class interface.                           #
#                                                                           #
# Notes: * Represents a collection of flashcards.                           #
#        * Stores card objects and field definitions.                       #
#        * Provides operations for printing, studying and copying cards.    #
#                                                                           #
# Author information:                                                       #
#                                                                           #
#############################################################################
*/

#ifndef DECK_HH
#define DECK_HH

#include "card.hh"

#include <memory>

using namespace std;

class Deck
{
public:
    /**
     * @brief Constructs a Deck object.
     * Initializes a deck with a name and field structure.
     *
     * @param deck_name Name of the deck
     * @param fields Field type identifiers
     */
    Deck(string deck_name, const Fields& fields);

    /**
     * @brief Destructs the Deck object.
     */
    ~Deck();

    /**
     * @brief Adds a new card to the deck.
     *
     * Called in command 'file' and 'add_card'.
     *
     * Creates and inserts a new card using provided field names
     * and definitions. Checks field-definition consistency.
     *
     * @param card_fields Card's field type identifiers
     * @param definitions Card's definitions
     * @return False if card_fields and definitions aren't equal in size,
     * true otherwise.
     */
    bool add_card(const Fields& card_fields,
                  const Fields& definitions);

    /**
     * @brief Adds an existing card to the deck.
     *
     * Called in command 'copy'.
     *
     * Checks that the card has all deck field types and the exact
     * same card doesn't already exist in the deck. Doesn't add the
     * card again if it already exists in the deck.
     *
     * @param card Card object to insert
     * @return False if the card doesn't have the all deck fields,
     * TRUE also if the card has already been added to the Deck,
     * true otherwise.
     */
    bool add_card(const shared_ptr<Card> card);

    /**
     * @brief Copies all Deck cards into another deck.
     *
     * Called in command 'copy'.
     *
     * Copies each card into the destination deck.
     *
     * @param destination Destination deck
     * @return False if card wasn't added into the deck,
     * true if it existed in the deck already,
     * true otherwise.
     */
    bool copy_cards(shared_ptr<Deck> destination);

    /**
     * @brief Fetches a new card to be studied.
     *
     * Called in command 'study'.
     *
     * Selects the next card in order of addition to be studied.
     *
     * @param cards_studied Number of cards studied so far
     * @return shared_ptr To the next card to be studied,
     * nullptr if no more Cards to be studied or over-indexing the Deck size.
     */
    shared_ptr<Card> get_next_study_card(unsigned int& cards_studied);

    /**
     * @brief Prints deck size, selected fields and all cards of the deck.
     * Displays all cards using only the selected requested_fields.
     *
     * Called in command 'overview'.
     *
     * @param requested_fields Fields to be printed
     * @return False if not all requested fields could be printed,
     * true otherwise.
     */
    bool print_deck(const Fields& requested_fields);

    /**
     * @brief Returns the field types of the deck.
     *
     * @return Shared pointer to deck fields
     */
    shared_ptr<Fields> get_fields();

    /**
     * @brief Returns the number of cards in the deck.
     *
     * @return Number of cards
     */
    size_t get_deck_size();

private:
    // Declare more attributes and/or methods here
};

#endif // DECK_HH
