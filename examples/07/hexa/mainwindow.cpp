#include "mainwindow.hh"
#include "ui_mainwindow.h"

// Y coordinate of the position of the conversionLabel_
const int CONV_POS_Y = 50;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
    connect(hexSpinBox_,
            static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this, &MainWindow::convert);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    hexSpinBox_ = new HexSpinBox(this);
    hexSpinBox_->setGeometry(0, 0, hexSpinBox_->width(),
                             hexSpinBox_->height());

    conversionLabel_ = new QLabel(this);
    conversionLabel_->setGeometry(0, CONV_POS_Y, conversionLabel_->width(),
                                  conversionLabel_->height());
}

void MainWindow::convert(int value)
{
    // Conversion happens "automatically", since the default base is 10
    conversionLabel_->setText(QString::number(value));
}

