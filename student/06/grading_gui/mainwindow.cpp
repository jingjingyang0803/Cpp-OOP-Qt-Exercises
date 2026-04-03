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
    ui->spinBoxE->setMaximum(100);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonCalculate_clicked()
{
    double pointsN = ui->spinBoxN->value();
    double pointsP1 = ui->spinBoxP1->value();
    double pointsP2 = ui->spinBoxP2->value();
    double pointsE = ui->spinBoxE->value();

    unsigned int scoreW = score_from_weekly_exercises(pointsN);
    unsigned int scoreP = score_from_projects(pointsP1, pointsP2);
    unsigned int total = calculate_total_grade(pointsN, pointsP1, pointsP2, pointsE);

    ui->textBrowser->setText("W-Score: " + QString::number(scoreW) + "\nP-Score: " +
                             QString::number(scoreP) + "\nTotal grade: " + QString::number(total));
}
