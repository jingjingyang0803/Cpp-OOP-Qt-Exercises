/*
#############################################################################
# COMP.CS.115 Ohjelmointi 3: Rajapinnat / Programming 3: Interfaces         #
# Project: Opettelukorttien paluu / Return of Flashcards                    #
# File: studywidget.cpp                                                     #
# Description: Implements StudyWidget class.                                #
#                                                                           #
# Notes:                                                                    #
#                                                                           #
# Author information:                                                       #
#   Name: Jingjing Yang                                                     #
#   Email: jingjing.yang@tuni.fi                                            #
#############################################################################
*/

#include "studywidget.hh"

#include <QHBoxLayout>
#include <QRandomGenerator>
#include <QVBoxLayout>
#include <QVector>

StudyWidget::StudyWidget(QWidget* parent) : QWidget(parent)
{
    setupUi();
    setupConnections();
}

void StudyWidget::setStudyDeck(std::shared_ptr<Deck> deck)
{
    // initialize variables and UI elements
    deck_ = deck;

    current_index_ = 0;
    showing_front_ = true;

    // reset combo boxes
    available_fields_.clear();
    front_field_box_->clear();
    back_field_box_->clear();

    // load fields from deck
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

    // prevent signals while setting default values
    front_field_box_->blockSignals(true);
    back_field_box_->blockSignals(true);

    if (!available_fields_.empty())
    {
        front_field_box_->setCurrentIndex(0);

        // default back field to second field if exists, otherwise first field
        if (available_fields_.size() > 1)
            back_field_box_->setCurrentIndex(1);
        else
            back_field_box_->setCurrentIndex(0);
    }

    front_field_box_->blockSignals(false);
    back_field_box_->blockSignals(false);

    // sync selected values to variables
    front_field_ = front_field_box_->currentText().toStdString();
    back_field_ = back_field_box_->currentText().toStdString();

    chooseRandomColors();
    updateView();
}

void StudyWidget::setupUi()
{
    QVBoxLayout* main_layout = new QVBoxLayout(this);
    main_layout->setAlignment(Qt::AlignTop);

    // field selection row
    QHBoxLayout* field_layout = new QHBoxLayout();

    front_field_box_ = new QComboBox(this);
    back_field_box_ = new QComboBox(this);

    field_layout->addWidget(new QLabel("Front:", this));
    field_layout->addWidget(front_field_box_);
    field_layout->addWidget(new QLabel("Back:", this));
    field_layout->addWidget(back_field_box_);

    // card display
    card_label_ = new QLabel("No card", this);
    card_label_->setAlignment(Qt::AlignCenter);
    card_label_->setWordWrap(true);
    card_label_->setMinimumHeight(200);

    // navigation row
    QHBoxLayout* nav_layout = new QHBoxLayout();

    last_button_ = new QPushButton("Previous", this);
    next_button_ = new QPushButton("Next", this);
    progress_label_ = new QLabel("0 / 0", this);
    progress_label_->setAlignment(Qt::AlignCenter);

    nav_layout->addWidget(last_button_);
    nav_layout->addWidget(progress_label_);
    nav_layout->addWidget(next_button_);

    // actions
    QHBoxLayout* action_layout = new QHBoxLayout();

    add_button_ = new QPushButton("Add card", this);
    flip_button_ = new QPushButton("Flip", this);
    exit_button_ = new QPushButton("Exit", this);

    action_layout->addWidget(add_button_);
    action_layout->addWidget(flip_button_);
    action_layout->addWidget(exit_button_);

    main_layout->addLayout(field_layout);
    main_layout->addWidget(card_label_);
    main_layout->addLayout(nav_layout);
    main_layout->addLayout(action_layout);
}

void StudyWidget::setupConnections()
{
    // navigation buttons
    connect(last_button_, &QPushButton::clicked, this, &StudyWidget::showPreviousCard);
    connect(next_button_, &QPushButton::clicked, this, &StudyWidget::showNextCard);

    // other actions
    connect(add_button_, &QPushButton::clicked, this, &StudyWidget::addCardRequested);
    connect(flip_button_, &QPushButton::clicked, this, &StudyWidget::flipCard);
    connect(exit_button_, &QPushButton::clicked, this, &StudyWidget::exitRequested);

    // field selection changes
    connect(front_field_box_, &QComboBox::currentTextChanged, this,
            &StudyWidget::updateSelectedFields);
    connect(back_field_box_, &QComboBox::currentTextChanged, this,
            &StudyWidget::updateSelectedFields);
}

void StudyWidget::updateSelectedFields()
{
    front_field_ = front_field_box_->currentText().toStdString();
    back_field_ = back_field_box_->currentText().toStdString();

    // always show front when user changes fields
    showing_front_ = true;
    updateView();
}

void StudyWidget::updateView()
{
    if (!deck_ || deck_->get_cards().empty())
    {
        card_label_->setText("No cards");
        progress_label_->setText("0 / 0");
        return;
    }

    const auto& cards = deck_->get_cards();

    // wrap around if index is out of range
    if (current_index_ >= cards.size())
        current_index_ = 0;

    auto card = cards.at(current_index_);

    // request only the field we want to display
    Fields request;
    request.push_back(showing_front_ ? front_field_ : back_field_);

    auto defs = card->get_definitions(request);

    QString text = defs.empty() ? "" : QString::fromStdString(defs.at(0));

    applySideColors();

    card_label_->setText(text);
    progress_label_->setText(QString::number(current_index_ + 1) + " / " +
                             QString::number(cards.size()));
}

void StudyWidget::refreshStudyView()
{
    updateView();
}

void StudyWidget::showPreviousCard()
{
    if (!deck_)
        return;

    // move backward with wrap-around
    if (current_index_ == 0)
        current_index_ = deck_->get_cards().size() - 1;
    else
        --current_index_;

    showing_front_ = true;
    updateView();
}

void StudyWidget::showNextCard()
{
    if (!deck_)
        return;

    // move forward with wrap-around
    current_index_ = (current_index_ + 1) % deck_->get_cards().size();
    showing_front_ = true;

    updateView();
}

void StudyWidget::flipCard()
{
    // toggle front/back
    showing_front_ = !showing_front_;
    updateView();
}

void StudyWidget::chooseRandomColors()
{
    QVector<QColor> palette = {"#e74c3c", "#3498db", "#2ecc71", "#f1c40f",
                               "#9b59b6", "#e67e22", "#1abc9c"};

    int a = QRandomGenerator::global()->bounded(palette.size());
    int b = QRandomGenerator::global()->bounded(palette.size());

    // ensure two different colors
    while (a == b)
        b = QRandomGenerator::global()->bounded(palette.size());

    front_color_ = palette[a];
    back_color_ = palette[b];
}

void StudyWidget::applySideColors()
{
    QString f = front_color_.name();
    QString b = back_color_.name();

    // color hint for front/back selectors
    front_field_box_->setStyleSheet("border:2px solid " + f);
    back_field_box_->setStyleSheet("border:2px solid " + b);

    // highlight current side on the card
    QString active = (showing_front_ ? front_color_ : back_color_).name();

    card_label_->setStyleSheet("border:3px solid " + active +
                               "; border-radius:8px; padding:20px; font-size:28px;");
}
