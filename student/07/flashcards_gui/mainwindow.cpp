#include "mainwindow.hh"

#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QSplitter>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QWidget>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
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
    QLineEdit* file_edit = new QLineEdit(this);
    QPushButton* load_button = new QPushButton("Load", this);

    file_edit->setPlaceholderText("Enter file name");

    top_layout->addWidget(file_label);
    top_layout->addWidget(file_edit);
    top_layout->addWidget(load_button);

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
    QListWidget* deck_list = new QListWidget(this);

    QLabel* deck_name_label = new QLabel("Deck name:", this);
    QLineEdit* deck_name_edit = new QLineEdit(this);

    QLabel* deck_fields_label = new QLabel("Fields:", this);
    QLineEdit* deck_fields_edit = new QLineEdit(this);

    QPushButton* add_deck_button = new QPushButton("Add Deck", this);
    QPushButton* remove_deck_button = new QPushButton("Remove Deck", this);

    deck_name_edit->setPlaceholderText("Enter deck name");
    deck_fields_edit->setPlaceholderText("Example: English;Finnish");

    left_layout->addWidget(decks_label);
    left_layout->addWidget(deck_list);
    left_layout->addWidget(deck_name_label);
    left_layout->addWidget(deck_name_edit);
    left_layout->addWidget(deck_fields_label);
    left_layout->addWidget(deck_fields_edit);
    left_layout->addWidget(add_deck_button);
    left_layout->addWidget(remove_deck_button);

    // =========================
    // Right panel: cards and card tools
    // =========================
    QWidget* right_panel = new QWidget(this);
    QVBoxLayout* right_layout = new QVBoxLayout(right_panel);

    QLabel* selected_deck_label = new QLabel("Selected deck: None", this);

    QLabel* cards_label = new QLabel("Cards", this);
    QListWidget* card_list = new QListWidget(this);

    // Create a horizontal layout for card action buttons.
    QHBoxLayout* card_button_layout = new QHBoxLayout();

    QPushButton* new_card_button = new QPushButton("New", this);
    QPushButton* edit_card_button = new QPushButton("Edit", this);
    QPushButton* remove_card_button = new QPushButton("Remove", this);

    card_button_layout->addWidget(new_card_button);
    card_button_layout->addWidget(edit_card_button);
    card_button_layout->addWidget(remove_card_button);

    // Create a stacked widget for future card pages:
    // for example Add Card, Edit Card, or Study Card.
    QStackedWidget* card_stack = new QStackedWidget(this);

    // Add a simple placeholder page for now.
    QWidget* placeholder_page = new QWidget(this);
    QVBoxLayout* placeholder_layout = new QVBoxLayout(placeholder_page);
    QLabel* placeholder_label = new QLabel("Card editor area", this);

    placeholder_layout->addWidget(placeholder_label);
    card_stack->addWidget(placeholder_page);

    right_layout->addWidget(selected_deck_label);
    right_layout->addWidget(cards_label);
    right_layout->addWidget(card_list);
    right_layout->addLayout(card_button_layout);
    right_layout->addWidget(card_stack);

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

    QPushButton* exit_button = new QPushButton("Exit", this);

    // Push the exit button to the right.
    bottom_layout->addStretch();
    bottom_layout->addWidget(exit_button);

    main_layout->addLayout(bottom_layout);

    // -------------------------------------------------
    // Main window settings
    // -------------------------------------------------
    setWindowTitle("Flashcards");
    resize(1100, 700);

    // Close the program when the Exit button is clicked.
    connect(exit_button, &QPushButton::clicked, this, &MainWindow::close);
}
