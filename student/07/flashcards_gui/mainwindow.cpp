#include "mainwindow.hh"

#include <string>
#include <vector>

#include <QDebug>
#include <QDialog>
#include <QDialogButtonBox>
#include <QDir>
#include <QFormLayout>
#include <QListWidget>
#include <QMessageBox>
#include <QSplitter>
#include <QStackedWidget>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    setup_ui();
    setup_connections();
}

void MainWindow::setup_ui()
{
    app_stack_ = new QStackedWidget(this);
    setCentralWidget(app_stack_);

    // -------------------------
    // Main page
    // -------------------------
    main_page_ = new QWidget(this);
    QVBoxLayout* main_layout = new QVBoxLayout(main_page_);

    main_layout->addLayout(create_top_bar());

    QSplitter* splitter = new QSplitter(Qt::Horizontal, this);
    splitter->addWidget(create_left_panel());
    splitter->addWidget(create_right_panel());
    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 2);
    splitter->setChildrenCollapsible(true);
    splitter->setHandleWidth(6);

    main_layout->addWidget(splitter);
    main_layout->addLayout(create_bottom_bar());

    // -------------------------
    // Study page
    // -------------------------
    study_page_ = new QWidget(this);
    QVBoxLayout* study_layout = new QVBoxLayout(study_page_);

    study_widget_ = new StudyWidget(this);
    study_layout->addWidget(study_widget_);

    // -------------------------
    // Add pages to stack
    // -------------------------
    app_stack_->addWidget(main_page_);
    app_stack_->addWidget(study_page_);
    app_stack_->setCurrentWidget(main_page_);

    setup_main_window();
}

QHBoxLayout* MainWindow::create_top_bar()
{
    QHBoxLayout* top_layout = new QHBoxLayout();

    file_edit_ = new QLineEdit(this);
    file_edit_->setPlaceholderText("Enter file name, and press ENTER to load");

    top_layout->addWidget(file_edit_);

    return top_layout;
}

QWidget* MainWindow::create_left_panel()
{
    QWidget* left_panel = new QWidget(this);
    QVBoxLayout* left_layout = new QVBoxLayout(left_panel);

    QLabel* decks_label = new QLabel("Decks", this);
    deck_list_ = new QListWidget(this);

    QHBoxLayout* deck_button_row = new QHBoxLayout();
    add_deck_button_ = new QPushButton("Add", this);
    remove_deck_button_ = new QPushButton("Remove", this);

    deck_button_row->addWidget(add_deck_button_);
    deck_button_row->addWidget(remove_deck_button_);

    left_panel->setMinimumWidth(0);

    left_layout->addWidget(decks_label);
    left_layout->addWidget(deck_list_);
    left_layout->addLayout(deck_button_row);

    return left_panel;
}

QWidget* MainWindow::create_right_panel()
{
    QWidget* right_panel = new QWidget(this);
    QVBoxLayout* right_layout = new QVBoxLayout(right_panel);

    selected_deck_label_ = new QLabel("", this);
    card_list_ = new QListWidget(this);

    QHBoxLayout* card_button_layout = new QHBoxLayout();
    new_card_button_ = new QPushButton("New", this);
    edit_card_button_ = new QPushButton("Edit", this);
    remove_card_button_ = new QPushButton("Remove", this);
    study_button_ = new QPushButton("Study", this);

    card_button_layout->addWidget(new_card_button_);
    card_button_layout->addWidget(edit_card_button_);
    card_button_layout->addWidget(remove_card_button_);
    card_button_layout->addWidget(study_button_);

    right_panel->setMinimumWidth(0);

    right_layout->addWidget(selected_deck_label_);
    right_layout->addWidget(card_list_);
    right_layout->addLayout(card_button_layout);

    return right_panel;
}

QHBoxLayout* MainWindow::create_bottom_bar()
{
    QHBoxLayout* bottom_layout = new QHBoxLayout();

    exit_button_ = new QPushButton("Exit", this);

    bottom_layout->addStretch();
    bottom_layout->addWidget(exit_button_);

    return bottom_layout;
}

void MainWindow::setup_main_window()
{
    setWindowTitle("Flashcards");
    resize(600, 400);
}

void MainWindow::setup_connections()
{
    connect(file_edit_, &QLineEdit::returnPressed, this, &MainWindow::loadFile);

    connect(add_deck_button_, &QPushButton::clicked, this, &MainWindow::addDeck);
    connect(remove_deck_button_, &QPushButton::clicked, this, &MainWindow::removeDeck);

    connect(deck_list_, &QListWidget::currentTextChanged, this, &MainWindow::showDeckCards);

    connect(new_card_button_, &QPushButton::clicked, this, &MainWindow::addCard);
    connect(remove_card_button_, &QPushButton::clicked, this, &MainWindow::removeCard);
    connect(edit_card_button_, &QPushButton::clicked, this, &MainWindow::editCard);

    connect(study_button_, &QPushButton::clicked, this, &MainWindow::startStudy);
    connect(study_widget_, &StudyWidget::exitRequested, this, &MainWindow::exitStudyMode);

    connect(exit_button_, &QPushButton::clicked, this, &MainWindow::close);
}

void MainWindow::loadFile()
{
    qDebug() << "loadFile called";
    qDebug() << "current path =" << QDir::currentPath();

    QString file_name_qt = file_edit_->text().trimmed();
    std::string file_name = file_name_qt.toStdString();

    if (file_name.empty())
    {
        QMessageBox::warning(this, "Input Error", "Please enter a file name.");
        return;
    }

    if (deck_manager_.read_file(file_name))
    {
        deck_list_->clear();
        card_list_->clear();

        std::vector<std::string> deck_names = deck_manager_.get_deck_names();
        for (const std::string& deck_name : deck_names)
        {
            deck_list_->addItem(QString::fromStdString(deck_name));
        }

        selected_deck_label_->setText("Ready to learn? Select a deck to start!");
        file_edit_->clear();
    }
    else
    {
        QMessageBox::critical(this, "Error", "Failed to load the file: " + file_name_qt);
    }
}

void MainWindow::addDeck()
{
    QDialog dialog(this);
    dialog.setWindowTitle("Add Deck");

    QFormLayout* form_layout = new QFormLayout(&dialog);

    QLineEdit* deck_name_input = new QLineEdit(&dialog);
    QLineEdit* fields_input = new QLineEdit(&dialog);

    deck_name_input->setPlaceholderText("Enter deck name");
    fields_input->setPlaceholderText("Example: English;Finnish");

    form_layout->addRow("Deck name:", deck_name_input);
    form_layout->addRow("Fields:", fields_input);

    QDialogButtonBox* button_box =
        new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);

    form_layout->addWidget(button_box);

    connect(button_box, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(button_box, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() != QDialog::Accepted)
    {
        return;
    }

    QString deck_name_qt = deck_name_input->text().trimmed();
    QString fields_qt = fields_input->text().trimmed();

    std::string deck_name = deck_name_qt.toStdString();

    if (deck_name.empty())
    {
        QMessageBox::warning(this, "Input Error", "Deck name cannot be empty.");
        return;
    }

    std::vector<std::string> fields;
    QStringList parts = fields_qt.split(';', Qt::SkipEmptyParts);
    for (const QString& part : parts)
    {
        QString trimmed = part.trimmed();
        if (!trimmed.isEmpty())
        {
            fields.push_back(trimmed.toStdString());
        }
    }

    if (fields.empty())
    {
        QMessageBox::warning(this, "Input Error", "Fields cannot be empty.");
        return;
    }

    if (deck_manager_.add_deck(deck_name, fields))
    {
        deck_list_->addItem(QString::fromStdString(deck_name));
    }
    else
    {
        QMessageBox::critical(this, "Error", "Failed to add the deck. It may already exist.");
    }
}

void MainWindow::removeDeck()
{
    QListWidgetItem* selected_item = deck_list_->currentItem();
    if (!selected_item)
    {
        QMessageBox::warning(this, "Selection Error", "No deck selected.");
        return;
    }

    int removed_row = deck_list_->row(selected_item);
    std::string deck_name = selected_item->text().toStdString();

    if (deck_manager_.remove_deck(deck_name))
    {
        delete selected_item;

        // select a new deck if available, otherwise clear the right panel
        if (deck_list_->count() > 0)
        {
            int new_row = removed_row;
            if (new_row >= deck_list_->count())
            {
                new_row = deck_list_->count() - 1;
            }

            deck_list_->setCurrentRow(new_row);
        }
        else
        {
            selected_deck_label_->setText("Ready to learn? Select a deck to start!");
            card_list_->clear();
        }
    }
    else
    {
        QMessageBox::critical(this, "Error", "Failed to remove the deck.");
    }
}

QString MainWindow::formatCardText(const std::shared_ptr<Card>& card) const
{
    if (!card)
    {
        return "";
    }

    QString card_text;

    const auto& card_fields = card->get_fields();
    const auto& card_definitions = card->get_definitions(card_fields);

    for (size_t i = 0; i < card_fields.size(); ++i)
    {
        card_text += QString::fromStdString(card_fields.at(i));
        card_text += ": ";
        card_text += QString::fromStdString(card_definitions.at(i));

        if (i + 1 < card_definitions.size() && i + 1 < card_fields.size())
        {
            card_text += " | ";
        }
    }

    return card_text;
}

void MainWindow::showDeckCards(const QString& deck_name_qt)
{
    if (deck_name_qt.isEmpty())
    {
        selected_deck_label_->setText("Ready to learn? Select a deck to start!");
        card_list_->clear();
        return;
    }

    std::string deck_name = deck_name_qt.toStdString();
    selected_deck_label_->setText("You're studying: " + deck_name_qt);
    card_list_->clear();

    auto deck = deck_manager_.get_deck(deck_name);
    if (!deck)
    {
        return;
    }

    for (const auto& card : deck->get_cards())
    {
        QString card_text = formatCardText(card);
        if (!card_text.isEmpty())
        {
            QListWidgetItem* item = new QListWidgetItem(card_text);
            item->setData(Qt::UserRole, static_cast<uint>(card->get_id()));
            card_list_->addItem(item);
        }
    }
}

void MainWindow::addCard()
{
    QListWidgetItem* selected_item = deck_list_->currentItem();
    if (!selected_item)
    {
        QMessageBox::warning(this, "Selection Error", "No deck selected.");
        return;
    }

    std::string deck_name = selected_item->text().toStdString();
    auto deck = deck_manager_.get_deck(deck_name);

    if (!deck)
    {
        QMessageBox::critical(this, "Error", "Selected deck not found.");
        return;
    }

    auto deck_fields_ptr = deck->get_fields();
    if (!deck_fields_ptr || deck_fields_ptr->empty())
    {
        QMessageBox::warning(this, "Error", "This deck has no fields.");
        return;
    }

    QDialog dialog(this);
    dialog.setWindowTitle("Add Card");

    QFormLayout* form_layout = new QFormLayout(&dialog);
    std::vector<QLineEdit*> input_boxes;

    for (const std::string& field_name : *deck_fields_ptr)
    {
        QLineEdit* input = new QLineEdit(&dialog);
        input->setPlaceholderText(QString::fromStdString(field_name));
        form_layout->addRow(QString::fromStdString(field_name) + ":", input);
        input_boxes.push_back(input);
    }

    QDialogButtonBox* button_box =
        new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);

    form_layout->addWidget(button_box);

    connect(button_box, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(button_box, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() != QDialog::Accepted)
    {
        return;
    }

    Fields definitions;
    for (QLineEdit* input : input_boxes)
    {
        definitions.push_back(input->text().toStdString());
    }

    if (deck->add_card(*deck_fields_ptr, definitions))
    {
        showDeckCards(QString::fromStdString(deck_name));
    }
    else
    {
        QMessageBox::critical(this, "Error", "Failed to add card.");
    }
}

void MainWindow::removeCard()
{
    QListWidgetItem* selected_deck_item = deck_list_->currentItem();
    if (!selected_deck_item)
    {
        QMessageBox::warning(this, "Selection Error", "No deck selected.");
        return;
    }

    std::string deck_name = selected_deck_item->text().toStdString();
    auto deck = deck_manager_.get_deck(deck_name);

    if (!deck)
    {
        QMessageBox::critical(this, "Error", "Selected deck not found.");
        return;
    }

    QListWidgetItem* selected_card_item = card_list_->currentItem();
    if (!selected_card_item)
    {
        QMessageBox::warning(this, "Selection Error", "No card selected.");
        return;
    }

    unsigned int card_id = selected_card_item->data(Qt::UserRole).toUInt();

    if (deck->remove_card(card_id))
    {
        showDeckCards(QString::fromStdString(deck_name));
    }
    else
    {
        QMessageBox::critical(this, "Error", "Failed to remove card.");
    }
}

void MainWindow::editCard()
{
    QListWidgetItem* selected_deck_item = deck_list_->currentItem();
    if (!selected_deck_item)
    {
        QMessageBox::warning(this, "Selection Error", "No deck selected.");
        return;
    }

    std::string deck_name = selected_deck_item->text().toStdString();
    auto deck = deck_manager_.get_deck(deck_name);
    if (!deck)
    {
        QMessageBox::critical(this, "Error", "Selected deck not found.");
        return;
    }

    QListWidgetItem* selected_card_item = card_list_->currentItem();
    if (!selected_card_item)
    {
        QMessageBox::warning(this, "Selection Error", "No card selected.");
        return;
    }

    unsigned int card_id = selected_card_item->data(Qt::UserRole).toUInt();
    auto card = deck->get_card(card_id);
    if (!card)
    {
        QMessageBox::critical(this, "Error", "Selected card not found.");
        return;
    }

    auto deck_fields_ptr = deck->get_fields();
    if (!deck_fields_ptr || deck_fields_ptr->empty())
    {
        QMessageBox::warning(this, "Error", "This deck has no fields.");
        return;
    }

    Fields current_definitions = card->get_definitions(*deck_fields_ptr);

    QDialog dialog(this);
    dialog.setWindowTitle("Edit Card");

    QFormLayout* form_layout = new QFormLayout(&dialog);
    std::vector<QLineEdit*> input_boxes;

    for (size_t i = 0; i < deck_fields_ptr->size(); ++i)
    {
        const std::string& field_name = deck_fields_ptr->at(i);

        QLineEdit* input = new QLineEdit(&dialog);
        input->setText(QString::fromStdString(current_definitions.at(i)));
        form_layout->addRow(QString::fromStdString(field_name) + ":", input);
        input_boxes.push_back(input);
    }

    QDialogButtonBox* button_box =
        new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);

    form_layout->addWidget(button_box);

    connect(button_box, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(button_box, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() != QDialog::Accepted)
    {
        return;
    }

    Fields new_definitions;
    for (QLineEdit* input : input_boxes)
    {
        std::string text = input->text().toStdString();
        if (text.empty())
        {
            QMessageBox::warning(this, "Input Error", "All fields must be filled.");
            return;
        }
        new_definitions.push_back(text);
    }

    if (!card->update_definitions(*deck_fields_ptr, new_definitions))
    {
        QMessageBox::critical(this, "Error", "Failed to update card.");
        return;
    }

    showDeckCards(QString::fromStdString(deck_name));
}

void MainWindow::startStudy()
{
    QListWidgetItem* selected_item = deck_list_->currentItem();
    if (!selected_item)
    {
        QMessageBox::warning(this, "Selection Error", "No deck selected.");
        return;
    }

    std::string deck_name = selected_item->text().toStdString();
    auto deck = deck_manager_.get_deck(deck_name);
    if (!deck)
    {
        QMessageBox::critical(this, "Error", "Selected deck not found.");
        return;
    }

    auto fields_ptr = deck->get_fields();
    if (!fields_ptr || fields_ptr->size() < 2)
    {
        QMessageBox::warning(this, "Study Error", "Study mode requires at least two fields.");
        return;
    }

    std::string front_field = fields_ptr->at(0);
    std::string back_field = fields_ptr->at(1);

    study_widget_->setStudyDeck(deck, front_field, back_field);
    enterStudyMode();
}

void MainWindow::enterStudyMode()
{
    app_stack_->setCurrentWidget(study_page_);
}

void MainWindow::exitStudyMode()
{
    app_stack_->setCurrentWidget(main_page_);
}