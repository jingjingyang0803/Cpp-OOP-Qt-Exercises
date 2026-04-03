#include "mainwindow.hh"

#include <QApplication>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSlider>
#include <QSpinBox>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    auto* central_widget = new QWidget(this);
    setCentralWidget(central_widget);

    // Create the horizontal layout and grid layout, and add the grid layout to the horizontal
    // layout
    auto* horizontal_layout = new QHBoxLayout(central_widget);
    auto* grid_layout = new QGridLayout(central_widget);
    horizontal_layout->addLayout(grid_layout);

    // Create the labels, sliders and spin boxes for red, green and blue
    auto* red_label = new QLabel("Red", this);
    auto* green_label = new QLabel("Green", this);
    auto* blue_label = new QLabel("Blue", this);

    auto* red_slider = new QSlider(Qt::Horizontal, this);
    auto* green_slider = new QSlider(Qt::Horizontal, this);
    auto* blue_slider = new QSlider(Qt::Horizontal, this);

    auto* red_spin = new QSpinBox(this);
    auto* green_spin = new QSpinBox(this);
    auto* blue_spin = new QSpinBox(this);

    // Set the range of the sliders to be between 0 and 255
    red_slider->setRange(0, 255);
    green_slider->setRange(0, 255);
    blue_slider->setRange(0, 255);

    // Set the range of the spin boxes to be between 0 and 255
    red_spin->setRange(0, 255);
    green_spin->setRange(0, 255);
    blue_spin->setRange(0, 255);

    // Add the labels, sliders and spin boxes to the grid layout
    grid_layout->addWidget(red_label, 0, 0);
    grid_layout->addWidget(red_slider, 0, 1);
    grid_layout->addWidget(red_spin, 0, 2);
    grid_layout->addWidget(green_label, 1, 0);
    grid_layout->addWidget(green_slider, 1, 1);
    grid_layout->addWidget(green_spin, 1, 2);
    grid_layout->addWidget(blue_label, 2, 0);
    grid_layout->addWidget(blue_slider, 2, 1);
    grid_layout->addWidget(blue_spin, 2, 2);

    // Add a label for the color preview to the horizontal layout
    auto* color_preview_label = new QLabel("Color Preview", this);
    horizontal_layout->addWidget(color_preview_label);
}

MainWindow::~MainWindow()
{
}
