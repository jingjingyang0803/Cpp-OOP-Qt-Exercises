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

bool Deck::add_card(const Fields &card_fields, const Fields &definitions)
{

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

bool Deck::print_deck(const Fields &requested_fields)
{

}

shared_ptr<Fields> Deck::get_fields()
{

}

size_t Deck::get_deck_size()
{

}


