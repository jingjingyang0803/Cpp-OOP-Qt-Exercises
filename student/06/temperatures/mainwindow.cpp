#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Set the range of the spin box for degrees
    ui->spinBoxDegrees->setMinimum(-273);
    ui->spinBoxDegrees->setMaximum(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_lineEditScale_editingFinished()
{
    scale_ = ui->lineEditScale->text();
}

void MainWindow::on_spinBoxDegrees_valueChanged(int arg1)
{
    degrees_ = arg1;
}

void MainWindow::on_pushButtonConvert_clicked()
{
    double converted = 0.0;

    if (scale_ == "Celsius")
    {
        converted = 1.8 * degrees_ + 32.0;
        ui->textBrowser->setText(QString::number(converted));
    }
    else if (scale_ == "Fahrenheit")
    {
        converted = (degrees_ - 32.0) * 1.8;
        ui->textBrowser->setText(QString::number(converted));
    }
    else
    {
        ui->textBrowser->setText("Unknown scale");
    }
}

void MainWindow::on_pushButtonClose_clicked()
{
}
