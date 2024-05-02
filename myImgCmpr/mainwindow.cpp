#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath(), tr("Images (*.png *.xpm *.jpg)"));

//    if (file_name.isEmpty())
//        qDebug() << "Selected file is empty";

    if (!file_name.isEmpty())
    {
        // Open prompt and display the image
        QMessageBox::information(this, "...", file_name);
        QImage img(file_name);
        QPixmap pix = QPixmap::fromImage(img);

        // Get label dimensions
        int w = ui->labelPicRoot->width();
        int h = ui->labelPicRoot->height();

        // Load the image into the UI
        ui->labelPicRoot->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));

        // Get image width and height, create an empty binary matrix
        int cols = img.width();
        int rows = img.height();
        int numBlackPixels = 0;
        QVector<QVector<int>> imgArray(rows, QVector<int>(cols, 0));

        // Get pixel data and update the matrix
        for (unsigned int i = 0; i < rows; i++)
        {
            for (unsigned int j = 0; j < cols; j++)
            {
                // img.pixel(x,y) where x = col, y = row (coordinates)
                QColor clrCurrent(img.pixel(j, i));
                int r = clrCurrent.red();
                int g = clrCurrent.green();
                int b = clrCurrent.blue();
                int a = clrCurrent.alpha();

                // If black, assign 1
                // Black r = 0, g = 0, b = 0, a = 255
                if (r + g + b < minRGBthreshold && a > minAthreshold)
                {
                    imgArray[i][j] = 1;
                    numBlackPixels += 1;
                }
            }
        }

        // Update UI with information
        ui->labelRootDims->setText(QString("W: %1  H: %2").arg(cols).arg(rows));
        float pD = (static_cast<float>(numBlackPixels) / (cols * rows)) * 100.0f;
        ui->labelPrcDark->setText(QString::number(pD));
    }
}
