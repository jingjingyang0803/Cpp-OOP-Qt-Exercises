/*
#############################################################################
# COMP.CS.115 Ohjelmointi 3: Rajapinnat / Programming 3: Interfaces         #
# Project: Opettelukorttien paluu / Return of Flashcards                    #
# File: studywidget.hh                                                      #
# Description: Declares the StudyWidget class interface.                    #
#                                                                           #
# Notes: * Provides a widget for studying flashcards from a deck.           #
#        * Allows choosing front and back fields, flipping cards,           #
#          navigating between cards, and exiting study mode.                #
#        * Visual side cues are given with random colors.                   #
#                                                                           #
# Author information:                                                       #
#   Name: Jingjing Yang                                                     #
#   Email: jingjing.yang@tuni.fi                                            #
#############################################################################
*/

#ifndef STUDYWIDGET_HH
#define STUDYWIDGET_HH

#include "card.hh"
#include "deck.hh"

#include <QColor>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QWidget>
/**
 * @brief A widget for studying flashcards from a deck.
 *
 * This widget shows one card at a time and allows the user to:
 * - choose which field is shown on the front side
 * - choose which field is shown on the back side
 * - flip the current card
 * - move to the previous or next card
 * - exit study mode
 *
 * Visual side cues are given with random colors:
 * one color for the front side and another for the back side.
 */

class StudyWidget : public QWidget
{
    Q_OBJECT

  public:
    explicit StudyWidget(QWidget* parent = nullptr);

    // initialize study session with a deck
    void setStudyDeck(std::shared_ptr<Deck> deck, const std::string& front_field,
                      const std::string& back_field);

  signals:
    void exitRequested();

  private slots:
    void showPreviousCard();
    void showNextCard();
    void flipCard();
    void updateSelectedFields();

  private:
    void setupUi();
    void setupConnections();

    void updateView();
    void chooseRandomColors();
    void applySideColors();

    std::shared_ptr<Deck> deck_;
    std::string front_field_;
    std::string back_field_;

    unsigned int current_index_ = 0;
    bool showing_front_ = true;

    QLabel* card_label_;
    QLabel* progress_label_;

    QPushButton* last_button_;
    QPushButton* next_button_;
    QPushButton* flip_button_;
    QPushButton* exit_button_;

    QComboBox* front_field_box_;
    QComboBox* back_field_box_;

    Fields available_fields_;

    QColor front_color_;
    QColor back_color_;
};

#endif // STUDYWIDGET_HH