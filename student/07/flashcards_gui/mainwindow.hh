/*
#############################################################################
# COMP.CS.115 Ohjelmointi 3: Rajapinnat / Programming 3: Interfaces         #
# Project: Opettelukorttien paluu / Return of Flashcards                    #
# File: mainwindow.hh                                                       #
# Description: Declares the MainWindow class interface.                     #
#                                                                           #
# Notes: * Provides the main application window for managing decks          #
#          and cards.                                                       #
#        * Allows loading, adding, removing, and editing decks and cards.   #
#        * Provides a study mode for flashcards.                            #
#                                                                           #
# Author information:                                                       #
#   Name: Jingjing Yang                                                     #
#   Email: jingjing.yang@tuni.fi                                            #
#############################################################################
*/

#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "deckmanager.hh"
#include "studywidget.hh"

#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QStackedWidget>
#include <QTableWidget>
#include <QWidget>

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    explicit MainWindow(QWidget* parent = nullptr);

  private:
    void setup_ui();
    void setup_connections();
    void setup_main_window();

    QHBoxLayout* create_top_bar();
    QWidget* create_left_panel();
    QWidget* create_right_panel();
    QHBoxLayout* create_bottom_bar();

  private slots:
    void loadFile();
    void addDeck();
    void removeDeck();
    void showDeckCards(const QString& deck_name);
    void addCard();
    void removeCard();
    void editCard();
    void startStudy();
    void enterStudyMode();
    void exitStudyMode();

  private:
    DeckManager deck_manager_;

    // application pages
    QStackedWidget* app_stack_;
    QWidget* main_page_;
    QWidget* study_page_;

    // top bar
    QLineEdit* file_edit_;

    // left panel
    QListWidget* deck_list_;
    QPushButton* add_deck_button_;
    QPushButton* remove_deck_button_;

    // right panel
    QLabel* selected_deck_label_;
    QTableWidget* card_table_;
    QPushButton* new_card_button_;
    QPushButton* edit_card_button_;
    QPushButton* remove_card_button_;
    QPushButton* study_button_;

    // study page
    StudyWidget* study_widget_;

    // bottom bar
    QPushButton* exit_button_;
};

#endif // MAINWINDOW_HH