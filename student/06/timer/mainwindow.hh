#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QTimer>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

  private slots:
    void on_startButton_clicked();

    void on_stopButton_clicked();

    void on_resetButton_clicked();

    void update_timer();

  private:
    Ui::MainWindow* ui;
    QTimer* timer_;
    // necessary members
    int seconds_;
    int minutes_;
};

#endif // MAINWINDOW_HH
