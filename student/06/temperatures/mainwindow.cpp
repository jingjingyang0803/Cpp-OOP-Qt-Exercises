#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_lineEditScale_editingFinished()
{

}


void MainWindow::on_spinBoxDegrees_valueChanged(int arg1)
{

}


void MainWindow::on_pushButtonConvert_clicked()
{

}


void MainWindow::on_pushButtonClose_clicked()
{

}

