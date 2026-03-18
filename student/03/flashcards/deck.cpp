/*
#############################################################################
# COMP.CS.115 Ohjelmointi 3: Rajapinnat / Programming 3: Interfaces         #
# Project: Opettelukortit / Flashcards                                      #
# File: deck.cpp                                                            #
# Description: Implements the Deck class functionality.                     #
#                                                                           #
# Author information:                                                       #
# - Name: Jingjing Yang                                                     #
# - Student number: 154016843                                               #
# - Gitlab user name: ptjiya                                                #
# - Tuni email: jingjing.yang@tuni.fi                                       #
#############################################################################
*/

#include "deck.hh"

#include <iostream>

const string MESSAGE_NO_CARDS = "No cards have been added.";

Deck::Deck(string deck_name, const Fields& fields) :
    name_(deck_name), deck_fields_(make_shared<Fields>(fields))
{
}

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
    if ( not card->has_fields(*deck_fields_) )
    {
        return false;
    }

    for ( const auto& existing_card : cards_ )
    {
        // Ignore duplicates when the same card is copied into the deck.
        if ( *existing_card == *card )
        {
            return true;
        }
    }

    cards_.push_back(card);
    return true;
}

bool Deck::copy_cards(shared_ptr<Deck> destination) const
{
    for ( const auto& card : cards_ )
    {
        if ( not destination->add_card(card) )
        {
            return false;
        }
    }

    return true;
}

shared_ptr<Card> Deck::get_next_study_card(unsigned int& cards_studied)
{
    if ( cards_studied >= cards_.size() )
    {
        return nullptr;
    }

    // Cards are returned in insertion order, one at a time.
    shared_ptr<Card> next_card = cards_.at(cards_studied);
    ++cards_studied;
    return next_card;
}

bool Deck::print_deck(const Fields &requested_fields) const
{
    if (cards_.empty())
    {
        cout << MESSAGE_NO_CARDS << endl;
        return true;
    }

    // Printing is allowed only if all requested fields belong to the deck.
    if ( not fields_overlap(*deck_fields_, requested_fields) )
    {
        return false;
    }

    cout << name_ << " (" << cards_.size() << " cards)" << endl << endl;

    cout << "   |";
    for (const string& field : requested_fields)
    {
        cout << " " << field << " |";
    }
    cout << endl;

    // Print each card using the selected field order.
    for (const auto& card : cards_)
    {
        if (not card->print_card(requested_fields))
        {
            return false;
        }
    }

    return true;
}
shared_ptr<Fields> Deck::get_fields() const
{
    return deck_fields_;
}

size_t Deck::get_deck_size() const
{
    return cards_.size();
}


