/*
#############################################################################
# COMP.CS.115 Ohjelmointi 3: Rajapinnat / Programming 3: Interfaces         #
# Project: Opettelukortit / Flashcards                                      #
# File: card.cpp                                                            #
# Description: Implements Card class functionality.                         #
#                                                                           #
# Author information:                                                       #
# - Name: Jingjing Yang                                                     #
# - Student number: 154016843                                               #
# - Gitlab user name: ptjiya                                                #
# - Tuni email: jingjing.yang@tuni.fi                                       #
#############################################################################
*/

#include "card.hh"
#include <iostream>

unsigned int Card::NEXT_ID = 1;

Card::Card() :
    ID_(NEXT_ID++)  // Assign a unique ID to each card
{

}

bool Card::add_new_definitions(const Fields &field_types,
                               const Fields &definitions)
{
    if ( field_types.size() != definitions.size() )
    {
        return false;
    }

    for ( size_t i = 0; i < field_types.size(); ++i )
    {
        // Map each field type to its corresponding definition
        definitions_[field_types.at(i)] = definitions.at(i);
    }

    return true;
}

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

bool Card::get_definitions(const Fields &requested_fields,
                           Fields &return_definitions) const
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
    if ( answer_fields.size() != answers.size() || answer_fields.empty() )
    {
        return 0.0;
    }

    // Each field contributes equally to the total score
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

        // Empty correct answers are treated as always correct
        if ( correct_answer.empty() || correct_answer == user_answer )
        {
            result += points_per_field;
        }
    }

    return result;
}

bool Card::print_card(const Fields& print_fields) const
{
    Fields definitions;

    // Validate requested fields before printing
    if ( !get_definitions(print_fields, definitions) )
    {
        return false;
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