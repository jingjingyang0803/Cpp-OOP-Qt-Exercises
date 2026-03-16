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

bool Card::add_new_definitions(const Fields &field_types,
                               const Fields &definitions)
{

}

bool Card::has_fields(const Fields &fields) const
{

}

bool Card::get_definitions(const Fields &requested_fields,
                           Fields &return_definitions)
{

}

double Card::check_answers(const Fields& answer_fields,
                           const Fields& answers) const
{

}

bool Card::print_card(const Fields& print_fields) const
{

}

bool Card::operator==(const Card &other) const
{
    return ID_ == other.ID_;
}

