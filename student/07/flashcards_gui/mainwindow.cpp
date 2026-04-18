#include "mainwindow.hh"

#include <string>
#include <vector>

#include <QDebug>
#include <QDialog>
#include <QDialogButtonBox>
#include <QDir>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QMessageBox>
#include <QPushButton>
#include <QSplitter>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QWidget>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    setup_ui();
    setup_connections();
}

void MainWindow::setup_ui()
{
    // Create the central widget for the main window.
    QWidget* central_widget = new QWidget(this);
    setCentralWidget(central_widget);

    // Create the main vertical layout:
    // top bar -> middle area -> bottom bar.
    QVBoxLayout* main_layout = new QVBoxLayout(central_widget);

    // -------------------------------------------------
    // Top bar: file loading controls
    // -------------------------------------------------
    QHBoxLayout* top_layout = new QHBoxLayout();

    QLabel* file_label = new QLabel("File:", this);
    file_edit_ = new QLineEdit(this);
    load_button_ = new QPushButton("Load", this);

    file_edit_->setPlaceholderText("Enter file name");

    top_layout->addWidget(file_label);
    top_layout->addWidget(file_edit_);
    top_layout->addWidget(load_button_);

    main_layout->addLayout(top_layout);

    // -------------------------------------------------
    // Middle area: left and right panels
    // QSplitter allows the user to resize the panels.
    // -------------------------------------------------
    QSplitter* splitter = new QSplitter(Qt::Horizontal, this);

    // =========================
    // Left panel: deck controls
    // =========================
    QWidget* left_panel = new QWidget(this);
    QVBoxLayout* left_layout = new QVBoxLayout(left_panel);

    QLabel* decks_label = new QLabel("Decks", this);
    deck_list_ = new QListWidget(this);

    QHBoxLayout* deck_button_row = new QHBoxLayout();
    add_deck_button_ = new QPushButton("Add", this);
    remove_deck_button_ = new QPushButton("Remove", this);

    deck_button_row->addWidget(add_deck_button_);
    deck_button_row->addWidget(remove_deck_button_);

    left_layout->addWidget(decks_label);
    left_layout->addWidget(deck_list_);
    left_layout->addLayout(deck_button_row);

    // =========================
    // Right panel: cards and card tools
    // =========================
    QWidget* right_panel = new QWidget(this);
    QVBoxLayout* right_layout = new QVBoxLayout(right_panel);

    selected_deck_label_ = new QLabel("Selected deck: None", this);

    QLabel* cards_label = new QLabel("Cards", this);
    card_list_ = new QListWidget(this);

    // Create a horizontal layout for card action buttons.
    QHBoxLayout* card_button_layout = new QHBoxLayout();

    new_card_button_ = new QPushButton("New", this);
    edit_card_button_ = new QPushButton("Edit", this);
    remove_card_button_ = new QPushButton("Remove", this);

    card_button_layout->addWidget(new_card_button_);
    card_button_layout->addWidget(edit_card_button_);
    card_button_layout->addWidget(remove_card_button_);

    // Create a stacked widget for future card pages:
    // for example Add Card, Edit Card, or Study Card.
    card_stack_ = new QStackedWidget(this);

    // Add a simple placeholder page for now.
    QWidget* placeholder_page = new QWidget(this);
    QVBoxLayout* placeholder_layout = new QVBoxLayout(placeholder_page);
    QLabel* placeholder_label = new QLabel("Card editor area", this);

    placeholder_layout->addWidget(placeholder_label);
    card_stack_->addWidget(placeholder_page);

    right_layout->addWidget(selected_deck_label_);
    right_layout->addWidget(cards_label);
    right_layout->addWidget(card_list_);
    right_layout->addLayout(card_button_layout);
    right_layout->addWidget(card_stack_);

    // Add both panels into the splitter.
    splitter->addWidget(left_panel);
    splitter->addWidget(right_panel);

    // Make the right side a bit wider than the left side.
    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 2);

    main_layout->addWidget(splitter);

    // -------------------------------------------------
    // Bottom bar: exit button
    // -------------------------------------------------
    QHBoxLayout* bottom_layout = new QHBoxLayout();

    exit_button_ = new QPushButton("Exit", this);

    // Push the exit button to the right.
    bottom_layout->addStretch();
    bottom_layout->addWidget(exit_button_);

    main_layout->addLayout(bottom_layout);

    // -------------------------------------------------
    // Main window settings
    // -------------------------------------------------
    setWindowTitle("Flashcards");
    resize(1100, 700);
}

void MainWindow::setup_connections()
{
    // Load the file when the Load button is clicked.
    connect(load_button_, &QPushButton::clicked, this, &MainWindow::loadFile);

    // Add a new deck when the Add Deck button is clicked.
    connect(add_deck_button_, &QPushButton::clicked, this, &MainWindow::addDeck);

    // Remove the selected deck when the Remove Deck button is clicked.
    connect(remove_deck_button_, &QPushButton::clicked, this, &MainWindow::removeDeck);

    // Show the cards of the selected deck when the selection changes.
    connect(deck_list_, &QListWidget::currentTextChanged, this, &MainWindow::showDeckCards);

    // Add new card when the New Card button is clicked.
    connect(new_card_button_, &QPushButton::clicked, this, &MainWindow::addCard);

    // Close the program when the Exit button is clicked.
    connect(exit_button_, &QPushButton::clicked, this, &MainWindow::close);
}

void MainWindow::loadFile()
{
    qDebug() << "loadFile called";
    qDebug() << "current path =" << QDir::currentPath();
    // Read file name from the input field.
    std::string file_name = file_edit_->text().toStdString();

    qDebug() << "file name =" << QString::fromStdString(file_name);
    qDebug() << "deck count =" << static_cast<int>(deck_manager_.get_deck_names().size());
    if (deck_manager_.read_file(file_name))
    {
        deck_list_->clear();

        std::vector<std::string> deck_names = deck_manager_.get_deck_names();
        for (const std::string& deck_name : deck_names)
        {
            deck_list_->addItem(QString::fromStdString(deck_name));
        }

        selected_deck_label_->setText("Selected deck: None");
        card_list_->clear();
    }
    else
    {
        QMessageBox::critical(this, "Error", "Failed to load the file.");
    }
}

void MainWindow::addDeck()
{
    qDebug() << "addDeck called";

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

    std::string deck_name = deck_name_input->text().toStdString();
    std::string fields_str = fields_input->text().toStdString();

    if (deck_name.empty())
    {
        QMessageBox::warning(this, "Input Error", "Deck name cannot be empty.");
        return;
    }

    std::vector<std::string> fields;
    size_t start = 0;
    size_t end = fields_str.find(';');
    while (end != std::string::npos)
    {
        fields.push_back(fields_str.substr(start, end - start));
        start = end + 1;
        end = fields_str.find(';', start);
    }
    if (start < fields_str.size())
    {
        fields.push_back(fields_str.substr(start));
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
    qDebug() << "removeDeck called";

    QListWidgetItem* selected_item = deck_list_->currentItem();
    if (!selected_item)
    {
        QMessageBox::warning(this, "Selection Error", "No deck selected.");
        return;
    }

    std::string deck_name = selected_item->text().toStdString();
    if (deck_manager_.remove_deck(deck_name))
    {
        delete selected_item;
        selected_deck_label_->setText("Selected deck: None");
        card_list_->clear();
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
        selected_deck_label_->setText("Selected deck: None");
        card_list_->clear();
        return;
    }

    std::string deck_name = deck_name_qt.toStdString();
    selected_deck_label_->setText("Selected deck: " + deck_name_qt);
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
            card_list_->addItem(card_text);
        }
    }
}

void MainWindow::addCard()
{
    qDebug() << "addCard called";

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
        std::string text = input->text().toStdString();
        definitions.push_back(text);
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
