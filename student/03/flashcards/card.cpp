/*
#############################################################################
# COMP.CS.115 Ohjelmointi 3: Rajapinnat / Programming 3: Interfaces         #
# Project: Opettelukortit / Flashcards                                      #
# File: card.cpp                                                            #
# Description: Implements Card class functionality.                         #
#                                                                           #
# Notes:                                                                    #
#                                                                           #
# Author information:                                                       #
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

Card::~Card()
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

double Card::check_answers(const Fields& answer_fields,
                           const Fields& answers) const
{

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

