#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    // Add your slots here.

private:
    Ui::MainWindow *ui;
    QTimer* timer_;
    // Add other necessary members here.
};

#endif // MAINWINDOW_HH
