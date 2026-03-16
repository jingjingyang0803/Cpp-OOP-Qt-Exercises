/*
#############################################################################
# COMP.CS.115 Ohjelmointi 3: Rajapinnat / Programming 3: Interfaces         #
# Project: Opettelukortit / Flashcards                                      #
# File: card.hh                                                             #
# Description: Declares the Card class interface.                           #
#                                                                           #
# Notes: * Represents a single flashcard.                                   #
#        * Stores definitions mapped to named fields.                       #
#        * Provides answer checking and prompt retrieval.                   #
#                                                                           #
# Author information:                                                       #
#                                                                           #
#############################################################################
*/

#ifndef CARD_HH
#define CARD_HH

#include "utils.hh"

#include <string>

using namespace std;

class Card
{
public:
    /**
     * @brief Constructs a Card object.
     *
     * Initializes an empty card with a unique ID.
     */
    Card();

    /**
     * @brief Destructs the Card object.
     */
    ~Card();

    /**
     * @brief Assigns definitions to card field types.
     *
     * Stores provided definitions for the given field types.
     * Overwrites previous definitions of the same field type.
     *
     * Called in commands 'file' and 'add_card'.
     *
     * @param field_types Field type identifiers
     * @param definitions Field definitions
     * @return False if field_types and definitions are't equal size,
     * true otherwise.
     */
    bool add_new_definitions(const Fields& field_types,
                             const Fields& definitions);

    /**
     * @brief Checks if the card contains the specified fields.
     *
     * Called in the command 'copy' to check if the card has
     * the fields of a deck.
     *
     * @param fields Field identifiers
     * @return True if all fields exist in the card, false otherwise
     */
    bool has_fields(const Fields& fields) const;

    /**
     * @brief Fetches definitions of chosen field types
     *
     * Called in the command 'study'
     *
     * @param requested_fields Requested definition field types
     * @param return_definitions Output of requested definitions for prompts
     * @return True if all requested fields existed,
     * false otherwise.
     */
    bool get_definitions(const Fields& requested_fields,
                         Fields& return_definitions);

    /**
     * @brief Checks study answers against stored definitions.
     *
     * Called in command 'study'.
     *
     * Compares user answers with correct values and updates
     * the accumulated study result.
     *
     * User gets 0-1 points per card.
     * If there are multiple fields to be checked, the 1 point is divided
     * between them.
     *
     * @param answer_fields Fields to be checked
     * @param answers User-provided answers
     * @return result Study result [0-1] points
     */
    double check_answers(const Fields& answer_fields,
                         const Fields& answers) const;

    /**
     * @brief Prints the card ID and requested field definitions.
     *
     * Called in command 'overview'.
     *
     * @param print_fields Fields to be printed
     * @return False if the requested fields existed,
     * false otherwise.
     */
    bool print_card(const Fields& print_fields) const;

    /**
     * @brief Compares two cards by ID.
     *
     * @param other Card to compare against
     * @return True if both cards have the same ID, false otherwise.
     */
    bool operator==(const Card& other) const;

private:
    static unsigned int NEXT_ID;
    unsigned int ID_;

    // Declare more attributes and/or methods here
};

#endif // CARD_HH
