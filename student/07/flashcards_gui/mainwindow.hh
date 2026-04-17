#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "deckmanager.hh"

#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QStackedWidget>
#include <QWidget>

class MainWindow : public QMainWindow
{
    Q_OBJECT
  public:
    explicit MainWindow(QWidget* parent = nullptr);

  private:
    void setup_ui();
    void setup_connections();

  private slots:
    void loadFile();
    void addDeck();
    void removeDeck();

  private:
    DeckManager deck_manager_;

    QLineEdit* file_edit_;
    QPushButton* load_button_;

    QListWidget* deck_list_;
    QLineEdit* deck_name_edit_;
    QLineEdit* deck_fields_edit_;
    QPushButton* add_deck_button_;
    QPushButton* remove_deck_button_;

    QLabel* selected_deck_label_;
    QListWidget* card_list_;
    QPushButton* new_card_button_;
    QPushButton* edit_card_button_;
    QPushButton* remove_card_button_;
    QStackedWidget* card_stack_;

    QPushButton* exit_button_;

  signals:
};

#endif // MAINWINDOW_HH
