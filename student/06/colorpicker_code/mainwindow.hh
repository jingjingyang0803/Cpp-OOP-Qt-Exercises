#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QLabel>
#include <QMainWindow>
#include <QSlider>
#include <QSpinBox>

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

  private:
    void setup_ui();
    void setup_connections();

  private slots:
    void onColorChanged();

  private:
    const int RGB_VALUE_MAX = 255;

    QSlider* horizontalSliderRed_;
    QSlider* horizontalSliderGreen_;
    QSlider* horizontalSliderBlue_;

    QSpinBox* spinBoxRed_;
    QSpinBox* spinBoxGreen_;
    QSpinBox* spinBoxBlue_;

    QLabel* colorPreviewLabel_;
};
#endif // MAINWINDOW_HH