#include "studywidget.hh"

#include <QHBoxLayout>
#include <QString>
#include <QVBoxLayout>

StudyWidget::StudyWidget(QWidget* parent) : QWidget(parent)
{
    setupUi();
    setupConnections();
}

void StudyWidget::setStudyDeck(std::shared_ptr<Deck> deck, const std::string& front_field,
                               const std::string& back_field)
{
    deck_ = deck;
    front_field_ = front_field;
    back_field_ = back_field;
    current_index_ = 0;
    showing_front_ = true;

    updateView();
}

void StudyWidget::setupUi()
{
    QVBoxLayout* main_layout = new QVBoxLayout(this);

    card_label_ = new QLabel("No card", this);
    card_label_->setAlignment(Qt::AlignCenter);
    card_label_->setWordWrap(true);
    card_label_->setMinimumHeight(200);
    card_label_->setStyleSheet("QLabel {"
                               "  border: 1px solid gray;"
                               "  border-radius: 8px;"
                               "  padding: 20px;"
                               "  font-size: 20px;"
                               "}");

    QHBoxLayout* nav_layout = new QHBoxLayout();

    last_button_ = new QPushButton("Last", this);
    progress_label_ = new QLabel("0 / 0", this);
    progress_label_->setAlignment(Qt::AlignCenter);
    next_button_ = new QPushButton("Next", this);

    nav_layout->addWidget(last_button_);
    nav_layout->addWidget(progress_label_);
    nav_layout->addWidget(next_button_);

    flip_button_ = new QPushButton("Flip", this);

    main_layout->addWidget(card_label_);
    main_layout->addLayout(nav_layout);
    main_layout->addWidget(flip_button_);
}

void StudyWidget::setupConnections()
{
    connect(last_button_, &QPushButton::clicked, this, &StudyWidget::showPreviousCard);

    connect(next_button_, &QPushButton::clicked, this, &StudyWidget::showNextCard);

    connect(flip_button_, &QPushButton::clicked, this, &StudyWidget::flipCard);
}

void StudyWidget::updateView()
{
    if (!deck_ || deck_->get_cards().empty())
    {
        card_label_->setText("No cards to study.");
        progress_label_->setText("0 / 0");
        return;
    }

    const auto& cards = deck_->get_cards();

    if (current_index_ >= cards.size())
    {
        current_index_ = 0;
    }

    std::shared_ptr<Card> card = cards.at(current_index_);
    if (!card)
    {
        card_label_->setText("Invalid card.");
        progress_label_->setText(QString::number(current_index_ + 1) + " / " +
                                 QString::number(cards.size()));
        return;
    }

    Fields requested_fields;
    if (showing_front_)
    {
        requested_fields.push_back(front_field_);
    }
    else
    {
        requested_fields.push_back(back_field_);
    }

    Fields definitions = card->get_definitions(requested_fields);

    QString shown_text;
    if (!definitions.empty())
    {
        shown_text = QString::fromStdString(definitions.at(0));
    }
    else
    {
        shown_text = "";
    }

    card_label_->setText(shown_text);
    progress_label_->setText(QString::number(current_index_ + 1) + " / " +
                             QString::number(cards.size()));
}

void StudyWidget::showPreviousCard()
{
    if (!deck_ || deck_->get_cards().empty())
    {
        return;
    }

    if (current_index_ == 0)
    {
        current_index_ = deck_->get_cards().size() - 1;
    }
    else
    {
        --current_index_;
    }

    showing_front_ = true;
    updateView();
}

void StudyWidget::showNextCard()
{
    if (!deck_ || deck_->get_cards().empty())
    {
        return;
    }

    current_index_ = (current_index_ + 1) % deck_->get_cards().size();
    showing_front_ = true;
    updateView();
}

void StudyWidget::flipCard()
{
    if (!deck_ || deck_->get_cards().empty())
    {
        return;
    }

    showing_front_ = !showing_front_;
    updateView();
}