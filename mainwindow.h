#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>

class Blurrer;

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
    void selectImage();
    void updateBlur();

private:
    Ui::MainWindow *ui;
    QImage *image = 0, *result = 0;
    Blurrer *blurrer = 0;
};

#endif // MAINWINDOW_H
