/*
#############################################################################
# COMP.CS.115 Ohjelmointi 3: Rajapinnat / Programming 3: Interfaces         #
# Project: Opettelukortit / Flashcards                                      #
# File: card.cpp                                                            #
# Description: Implements Card class functionality.                         #
#                                                                           #
# The Card class represents a single flashcard containing multiple          #
# field definitions (e.g., translations between languages). It provides     #
# functionality for storing definitions, retrieving them, printing card     #
# content, and checking user answers during study sessions.                 #                                                        #                                             #
#                                                                           #
# Notes:                                                                    #
# - Each card has a unique ID.                                              #
# - Definitions are stored by field type.                                   #
# - Used by Deck and DeckManager classes.                                   #
#                                                                           #
# Author information:                                                       #
# - Name: Jingjing Yang                                                     #
# - Student number: 154016843                                               #
# - Gitlab user name: ptjiya                                                #
# - Tuni email: jingjing.yang@tuni.fi                                       #
#                                                                           #
#############################################################################
*/

#include "card.hh"
#include <iostream>

unsigned int Card::NEXT_ID = 1;

Card::Card() :
    ID_(NEXT_ID++)
{

}


// Assigns definitions to card field types.
bool Card::add_new_definitions(const Fields &field_types,
                               const Fields &definitions)
{
    if ( field_types.size() != definitions.size() )
    {
        return false;
    }

    for ( size_t i = 0; i < field_types.size(); ++i )
    {
        definitions_[field_types.at(i)] = definitions.at(i);
    }

    return true;
}

// Checks if the card contains the specified fields.
bool Card::has_fields(const Fields& fields) const
{
    for ( const string& field : fields )
    {
        if ( definitions_.find(field) == definitions_.end() )
        {
            return false;
        }
    }

    return true;
}

// Fetches definitions of chosen field types
bool Card::get_definitions(const Fields &requested_fields,
                           Fields &return_definitions)
{
    return_definitions.clear();

    for (const string& field : requested_fields)
    {
        auto it = definitions_.find(field);

        if (it == definitions_.end())
        {
            return false;
        }

        return_definitions.push_back(it->second);
    }

    return true;
}

/**
 * @brief Checks user answers against stored definitions.
 *
 * Compares the given answers with the correct definitions of the card.
 * Each card yields a score between 0 and 1.
 * If multiple fields are checked, the score is divided equally between them.
 *
 * If a correct definition is empty, the user receives full points for
 * that field regardless of the answer.
 *
 * @param answer_fields Fields that are being checked
 * @param answers User-provided answers corresponding to the fields
 * @return Score between 0 and 1 for this card
 */
double Card::check_answers(const Fields& answer_fields,
                           const Fields& answers) const
{
    if ( answer_fields.size() != answers.size() || answer_fields.empty() )
    {
        return 0.0;
    }

    double points_per_field = 1.0 / answer_fields.size();
    double result = 0.0;

    for ( size_t i = 0; i < answer_fields.size(); ++i )
    {
        auto it = definitions_.find(answer_fields.at(i));

        if ( it == definitions_.end() )
        {
            return 0.0;
        }

        const string& correct_answer = it->second;
        const string& user_answer = answers.at(i);

        if ( correct_answer.empty() || correct_answer == user_answer )
        {
            result += points_per_field;
        }
    }

    return result;
}

// Prints the card ID and requested field definitions.
bool Card::print_card(const Fields& print_fields) const
{
    Fields definitions;

    // Check if all requested fields exist and gather their definitions.

    for (const string& field : print_fields)
    {
        // can't call non-const get_definitions in a const function,
        // so we manually retrieve definitions here
        auto it = definitions_.find(field);

        if (it == definitions_.end())
        {
            return false;
        }

        definitions.push_back(it->second);
    }

    cout << " " << ID_ << " |";

    for (const string& def : definitions)
    {
        cout << " " << def << " |";
    }

    cout << endl;

    return true;
}

bool Card::operator==(const Card &other) const
{
    return ID_ == other.ID_;
}

