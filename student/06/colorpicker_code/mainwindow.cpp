#include "mainwindow.hh"

#include <QApplication>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    setup_ui();
    setup_connections();
}

MainWindow::~MainWindow()
{
}

void MainWindow::setup_ui()
{
    auto* central_widget = new QWidget(this);
    setCentralWidget(central_widget);

    // Create the horizontal layout and grid layout, and add the grid layout to the horizontal
    // layout
    auto* horizontal_layout = new QHBoxLayout(central_widget);
    auto* grid_layout = new QGridLayout();
    horizontal_layout->addLayout(grid_layout);

    // Create the labels, sliders and spin boxes for red, green and blue
    auto* red_label = new QLabel("Red", this);
    auto* green_label = new QLabel("Green", this);
    auto* blue_label = new QLabel("Blue", this);

    horizontalSliderRed_ = new QSlider(Qt::Horizontal, this);
    horizontalSliderGreen_ = new QSlider(Qt::Horizontal, this);
    horizontalSliderBlue_ = new QSlider(Qt::Horizontal, this);

    spinBoxRed_ = new QSpinBox(this);
    spinBoxGreen_ = new QSpinBox(this);
    spinBoxBlue_ = new QSpinBox(this);

    // Set the object names for the sliders and spin boxes so that they can be accessed in the tests
    spinBoxRed_->setObjectName("spinBoxRed");
    spinBoxGreen_->setObjectName("spinBoxGreen");
    spinBoxBlue_->setObjectName("spinBoxBlue");

    horizontalSliderRed_->setObjectName("horizontalSliderRed");
    horizontalSliderGreen_->setObjectName("horizontalSliderGreen");
    horizontalSliderBlue_->setObjectName("horizontalSliderBlue");

    // Set the range of the sliders to be between 0 and 255
    horizontalSliderRed_->setRange(0, RGB_VALUE_MAX);
    horizontalSliderGreen_->setRange(0, RGB_VALUE_MAX);
    horizontalSliderBlue_->setRange(0, RGB_VALUE_MAX);

    // Set the range of the spin boxes to be between 0 and 255
    spinBoxRed_->setRange(0, RGB_VALUE_MAX);
    spinBoxGreen_->setRange(0, RGB_VALUE_MAX);
    spinBoxBlue_->setRange(0, RGB_VALUE_MAX);

    // Add the labels, sliders and spin boxes to the grid layout
    grid_layout->addWidget(red_label, 0, 0);
    grid_layout->addWidget(horizontalSliderRed_, 0, 1);
    grid_layout->addWidget(spinBoxRed_, 0, 2);
    grid_layout->addWidget(green_label, 1, 0);
    grid_layout->addWidget(horizontalSliderGreen_, 1, 1);
    grid_layout->addWidget(spinBoxGreen_, 1, 2);
    grid_layout->addWidget(blue_label, 2, 0);
    grid_layout->addWidget(horizontalSliderBlue_, 2, 1);
    grid_layout->addWidget(spinBoxBlue_, 2, 2);

    // Add a label for the color preview to the horizontal layout
    colorPreviewLabel_ = new QLabel(this);
    colorPreviewLabel_->setFixedSize(60, 60);
    colorPreviewLabel_->setStyleSheet("background-color: rgb(0,0,0); border: 1px solid black;");

    horizontal_layout->addWidget(colorPreviewLabel_);
}

void MainWindow::setup_connections()
{
    // Connect the sliders to the spin boxes so that when the slider value changes, the
    // corresponding spin box value also changes
    connect(horizontalSliderRed_, &QSlider::valueChanged, spinBoxRed_, &QSpinBox::setValue);
    connect(horizontalSliderGreen_, &QSlider::valueChanged, spinBoxGreen_, &QSpinBox::setValue);
    connect(horizontalSliderBlue_, &QSlider::valueChanged, spinBoxBlue_, &QSpinBox::setValue);

    // Connect the spin boxes to the sliders so that when the spin box value changes, the
    // corresponding slider value also changes
    connect(spinBoxRed_, QOverload<int>::of(&QSpinBox::valueChanged), horizontalSliderRed_,
            &QSlider::setValue);
    connect(spinBoxGreen_, QOverload<int>::of(&QSpinBox::valueChanged), horizontalSliderGreen_,
            &QSlider::setValue);
    connect(spinBoxBlue_, QOverload<int>::of(&QSpinBox::valueChanged), horizontalSliderBlue_,
            &QSlider::setValue);

    // Connect the sliders and spin boxes to the onColorChanged slot so that when any of the values
    // change, the color preview is updated
    connect(horizontalSliderRed_, &QSlider::valueChanged, this, &MainWindow::onColorChanged);
    connect(horizontalSliderGreen_, &QSlider::valueChanged, this, &MainWindow::onColorChanged);
    connect(horizontalSliderBlue_, &QSlider::valueChanged, this, &MainWindow::onColorChanged);
    connect(spinBoxRed_, QOverload<int>::of(&QSpinBox::valueChanged), this,
            &MainWindow::onColorChanged);
    connect(spinBoxGreen_, QOverload<int>::of(&QSpinBox::valueChanged), this,
            &MainWindow::onColorChanged);
    connect(spinBoxBlue_, QOverload<int>::of(&QSpinBox::valueChanged), this,
            &MainWindow::onColorChanged);
}

void MainWindow::onColorChanged()
{
    // Get the current values of the sliders and spin boxes
    int red_value = horizontalSliderRed_->value();
    int green_value = horizontalSliderGreen_->value();
    int blue_value = horizontalSliderBlue_->value();

    // Update the color preview label with the new color
    QString color_style = QString("background-color: rgb(%1, %2, %3);")
                              .arg(red_value)
                              .arg(green_value)
                              .arg(blue_value);
    colorPreviewLabel_->setStyleSheet(color_style);
}