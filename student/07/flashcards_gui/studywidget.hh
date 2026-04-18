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
 * Displays one card at a time and allows the user to flip the card
 * and navigate through the deck.
 *
 * Author information:
 *   Name: Jingjing Yang
 *   Email: jingjing.yang@tuni.fi
 */

class StudyWidget : public QWidget
{
    Q_OBJECT

  public:
    explicit StudyWidget(QWidget* parent = nullptr);

    void setStudyDeck(std::shared_ptr<Deck> deck, const std::string& front_field,
                      const std::string& back_field);

  private slots:
    void showPreviousCard();
    void showNextCard();
    void flipCard();
    void chooseRandomColors();
    void applySideColors();
    void updateView();
    void updateSelectedFields();

  private:
    void setupUi();
    void setupConnections();

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

    QComboBox* front_field_box_;
    QComboBox* back_field_box_;
    Fields available_fields_;

    QColor front_color_;
    QColor back_color_;
};

#endif // STUDYWIDGET_HH