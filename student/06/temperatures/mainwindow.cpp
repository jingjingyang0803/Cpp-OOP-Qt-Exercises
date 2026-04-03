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

void MainWindow::on_pushButtonConvert_clicked()
{
    QString scale = ui->lineEditScale->text();
    int degrees = ui->spinBoxDegrees->value();

    double converted = 0.0;

    if (scale == "Celsius")
    {
        converted = 1.8 * degrees + 32.0;
        ui->textBrowser->setText(QString::number(converted));
    }
    else if (scale == "Fahrenheit")
    {
        converted = (degrees - 32.0) / 1.8;
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
