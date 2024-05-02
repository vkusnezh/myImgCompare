#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QPushButton *pushButton;
    void on_pushButton_clicked();
    QLabel labelPicRoot;

    // min of red + green + blue for image segmentation to deside if pixel is a color one
    const double minRGBthreshold = 15;
    // min alpha with minRGBthreshold for image segmentation to decide if pixel is a background
    const double minAthreshold = 240;
};
#endif // MAINWINDOW_H
