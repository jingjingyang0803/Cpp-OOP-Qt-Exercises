#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), timer_(new QTimer(this)), seconds_(0),
      minutes_(0)
{
    ui->setupUi(this);

    connect(timer_, &QTimer::timeout, this, &MainWindow::update_timer);

    ui->lcdNumberMin->display(0);
    ui->lcdNumberSec->display(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startButton_clicked()
{
    timer_->start(1000);
}

void MainWindow::on_stopButton_clicked()
{
    timer_->stop();
}

void MainWindow::on_resetButton_clicked()
{
    timer_->stop();
    seconds_ = 0;
    minutes_ = 0;
    ui->lcdNumberMin->display("0");
    ui->lcdNumberSec->display("0");
}

void MainWindow::update_timer()
{
    seconds_++;
    if (seconds_ == 60)
    {
        minutes_++;
        seconds_ = 0;
    }
    ui->lcdNumberSec->display(seconds_);
    ui->lcdNumberMin->display(minutes_);
}
