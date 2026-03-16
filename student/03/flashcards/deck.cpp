/*
#############################################################################
# COMP.CS.115 Ohjelmointi 3: Rajapinnat / Programming 3: Interfaces         #
# Project: Opettelukortit / Flashcards                                      #
# File: deck.cpp                                                            #
# Description: Implements the Deck class functionality.                     #
#                                                                           #
# Notes:                                                                    #
#                                                                           #
# Author information:                                                       #
#                                                                           #
#############################################################################
*/

#include "deck.hh"

#include <iostream>

const string NO_CARDS = "No cards have been added.";

Deck::Deck(string deck_name, const Fields& fields) :
    name_(deck_name), deck_fields_(make_shared<Fields>(fields))
{

}

Deck::~Deck()
{

}

// Adds a new card to the deck.
bool Deck::add_card(const Fields &card_fields, const Fields &definitions)
{
    if ( card_fields.size() != definitions.size() )
    {
        return false;
    }

    shared_ptr<Card> new_card = make_shared<Card>();

    if ( not new_card->add_new_definitions(card_fields, definitions) )
    {
        return false;
    }

    cards_.push_back(new_card);
    return true;
}

bool Deck::add_card(shared_ptr<Card> card)
{

}

bool Deck::copy_cards(shared_ptr<Deck> destination)
{

}

shared_ptr<Card> Deck::get_next_study_card(unsigned int& cards_studied)
{

}

// Prints deck size, selected fields and all cards of the deck.
bool Deck::print_deck(const Fields &requested_fields)
{
    // Handle the case when there are no cards in the deck.
    if (cards_.empty())
    {
        cout << NO_CARDS << endl;
        return true;
    }

    // Print the deck name and the number of cards in the deck.
    cout << name_ << " (" << cards_.size() << " cards)" << endl << endl;

    // Print the header with requested fields.
    cout << "   |";
    for (const string& field : requested_fields)
    {
        cout << " " << field << " |";
    }
    cout << endl;


    // Displays all cards using only the selected requested_fields.
    for (const auto& card : cards_)
    {
        if (not card->print_card(requested_fields))
        {
            return false;
        }
    }

    return true;
}

// Returns the field types of the deck.
shared_ptr<Fields> Deck::get_fields()
{
    return deck_fields_;
}

// Returns the number of cards in the deck.
size_t Deck::get_deck_size()
{
    return cards_.size();
}


