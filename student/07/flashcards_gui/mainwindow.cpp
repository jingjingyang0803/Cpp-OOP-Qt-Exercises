#include "mainwindow.hh"

#include <string>
#include <vector>

#include <QDebug>
#include <QDir>
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

    QLabel* deck_name_label = new QLabel("Deck name:", this);
    deck_name_edit_ = new QLineEdit(this);

    QLabel* deck_fields_label = new QLabel("Fields:", this);
    deck_fields_edit_ = new QLineEdit(this);

    add_deck_button_ = new QPushButton("Add Deck", this);
    remove_deck_button_ = new QPushButton("Remove Deck", this);

    deck_name_edit_->setPlaceholderText("Enter deck name");
    deck_fields_edit_->setPlaceholderText("Example: English;Finnish");
    left_layout->addWidget(decks_label);
    left_layout->addWidget(deck_list_);
    left_layout->addWidget(deck_name_label);
    left_layout->addWidget(deck_name_edit_);
    left_layout->addWidget(deck_fields_label);
    left_layout->addWidget(deck_fields_edit_);
    left_layout->addWidget(add_deck_button_);
    left_layout->addWidget(remove_deck_button_);

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
