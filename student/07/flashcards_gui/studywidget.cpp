#include "studywidget.hh"

#include <QHBoxLayout>
#include <QRandomGenerator>
#include <QString>
#include <QVBoxLayout>
#include <QVector>

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

    available_fields_.clear();
    front_field_box_->clear();
    back_field_box_->clear();

    if (deck_)
    {
        auto fields_ptr = deck_->get_fields();
        if (fields_ptr)
        {
            available_fields_ = *fields_ptr;

            for (const std::string& field : available_fields_)
            {
                QString qfield = QString::fromStdString(field);
                front_field_box_->addItem(qfield);
                back_field_box_->addItem(qfield);
            }
        }
    }

    front_field_box_->setCurrentText(QString::fromStdString(front_field_));
    back_field_box_->setCurrentText(QString::fromStdString(back_field_));

    chooseRandomColors();
    updateView();
}

void StudyWidget::setupUi()
{
    QVBoxLayout* main_layout = new QVBoxLayout(this);

    QHBoxLayout* field_layout = new QHBoxLayout();

    QLabel* front_label = new QLabel("Front:", this);
    front_field_box_ = new QComboBox(this);

    QLabel* back_label = new QLabel("Back:", this);
    back_field_box_ = new QComboBox(this);

    field_layout->addWidget(front_label);
    field_layout->addWidget(front_field_box_);
    field_layout->addWidget(back_label);
    field_layout->addWidget(back_field_box_);
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

    last_button_ = new QPushButton("Previous", this);
    progress_label_ = new QLabel("0 / 0", this);
    progress_label_->setAlignment(Qt::AlignCenter);
    next_button_ = new QPushButton("Next", this);

    nav_layout->addWidget(last_button_);
    nav_layout->addWidget(progress_label_);
    nav_layout->addWidget(next_button_);

    flip_button_ = new QPushButton("Flip card", this);
    exit_button_ = new QPushButton("Exit study session", this);

    main_layout->addLayout(field_layout);
    main_layout->addWidget(card_label_);
    main_layout->addLayout(nav_layout);
    main_layout->addWidget(flip_button_);

    main_layout->addWidget(exit_button_);
}

void StudyWidget::setupConnections()
{
    connect(last_button_, &QPushButton::clicked, this, &StudyWidget::showPreviousCard);

    connect(next_button_, &QPushButton::clicked, this, &StudyWidget::showNextCard);

    connect(flip_button_, &QPushButton::clicked, this, &StudyWidget::flipCard);

    connect(exit_button_, &QPushButton::clicked, this, &StudyWidget::exitRequested);

    connect(front_field_box_, &QComboBox::currentTextChanged, this,
            &StudyWidget::updateSelectedFields);
    connect(back_field_box_, &QComboBox::currentTextChanged, this,
            &StudyWidget::updateSelectedFields);
}

void StudyWidget::updateSelectedFields()
{
    front_field_ = front_field_box_->currentText().toStdString();
    back_field_ = back_field_box_->currentText().toStdString();

    showing_front_ = true;
    updateView();
}

void StudyWidget::chooseRandomColors()
{
    QVector<QColor> palette = {
        QColor("#e74c3c"), // red
        QColor("#3498db"), // blue
        QColor("#2ecc71"), // green
        QColor("#f1c40f"), // yellow
        QColor("#9b59b6"), // purple
        QColor("#e67e22"), // orange
        QColor("#1abc9c")  // teal
    };

    int first_index = QRandomGenerator::global()->bounded(palette.size());
    int second_index = QRandomGenerator::global()->bounded(palette.size());

    while (second_index == first_index)
    {
        second_index = QRandomGenerator::global()->bounded(palette.size());
    }

    front_color_ = palette.at(first_index);
    back_color_ = palette.at(second_index);
}

void StudyWidget::applySideColors()
{
    QString front_color_name = front_color_.name();
    QString back_color_name = back_color_.name();

    // ComboBox + dropdown list
    front_field_box_->setStyleSheet("QComboBox {"
                                    "  border: 2px solid " +
                                    front_color_name +
                                    ";"
                                    "  border-radius: 4px;"
                                    "  padding: 4px;"
                                    "}"
                                    "QComboBox QAbstractItemView {"
                                    "  selection-background-color: " +
                                    front_color_name +
                                    ";"
                                    "}");

    back_field_box_->setStyleSheet("QComboBox {"
                                   "  border: 2px solid " +
                                   back_color_name +
                                   ";"
                                   "  border-radius: 4px;"
                                   "  padding: 4px;"
                                   "}"
                                   "QComboBox QAbstractItemView {"
                                   "  selection-background-color: " +
                                   back_color_name +
                                   ";"
                                   "}");

    // Card border color
    QColor active_color = showing_front_ ? front_color_ : back_color_;
    QString active_color_name = active_color.name();

    card_label_->setStyleSheet("QLabel {"
                               "  border: 3px solid " +
                               active_color_name +
                               ";"
                               "  border-radius: 8px;"
                               "  padding: 20px;"
                               "  font-size: 32px;"
                               "  font-weight: bold;"
                               "}");
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

    applySideColors();
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