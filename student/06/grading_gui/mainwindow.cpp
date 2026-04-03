#include "mainwindow.hh"
#include "ui_mainwindow.h"

#include "gradecalculator.hh"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->spinBoxN->setMaximum(MAX_N_POINTS);
    ui->spinBoxP1->setMaximum(MAX_P_POINTS_PER_PROJECT);
    ui->spinBoxP2->setMaximum(MAX_P_POINTS_PER_PROJECT);
    ui->spinBoxB->setMaximum(MAX_B_POINTS);
    ui->spinBoxE->setMaximum(5);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonCalculate_clicked()
{
    unsigned int pointsN = ui->spinBoxN->value();
    unsigned int pointsP1 = ui->spinBoxP1->value();
    unsigned int pointsP2 = ui->spinBoxP2->value();
    unsigned int pointsB = ui->spinBoxB->value();
    unsigned int pointsE = ui->spinBoxE->value();

    unsigned int scoreW = score_from_weekly_exercises(pointsN + pointsB);
    unsigned int scoreP = score_from_projects(pointsP1, pointsP2);
    unsigned int total = calculate_total_grade(pointsN + pointsB, pointsP1, pointsP2, pointsE);

    ui->textBrowser->setText("W-Score: " + QString::number(scoreW) + "\nP-Score: " +
                             QString::number(scoreP) + "\nTotal grade: " + QString::number(total));
}
