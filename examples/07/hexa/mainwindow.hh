#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "hexspinbox.hh"
#include <QMainWindow>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // Initialize hexSpinBox and conversionLabel_
    void init();

public slots:
    // Convert hexa decimal value to decimal value
    void convert(int value);

private:
    Ui::MainWindow *ui;

    // Spinbox for the hexadecimal value
    HexSpinBox* hexSpinBox_;

    // Label for the decimal value
    QLabel* conversionLabel_;
};
#endif // MAINWINDOW_HH
