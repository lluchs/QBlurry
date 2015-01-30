#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "blurrer.h"

#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->selectImageButton, SIGNAL(clicked()), this, SLOT(selectImage()));
    connect(ui->sigmaSlider, SIGNAL(sliderMoved(int)), this, SLOT(updateBlur()));
    connect(ui->sizeSlider, SIGNAL(sliderMoved(int)), this, SLOT(updateBlur()));
}

MainWindow::~MainWindow()
{
    delete ui;
    if (image) delete image;
    if (result) delete result;
}

void MainWindow::selectImage()
{
    auto fileName = QFileDialog::getOpenFileName(this, "Open Image", "", "Image Files (*.png *.jpg *.bmp)");
    if (image) delete image;
    if (result) delete result;
    if (blurrer) delete blurrer;

    image = new QImage(fileName);
    if (image->isNull())
        QMessageBox::critical(this, "Loading Error", "Could not load image file.");
    else
        ui->statusBar->showMessage(fileName);
    ui->input->setPixmap(QPixmap::fromImage(*image));

    result = new QImage(image->size(), image->format());
    blurrer = new Blurrer(this, image, result);
    updateBlur();
}

void MainWindow::updateBlur()
{
    if (!blurrer) return;
    float sigma = ui->sigmaSlider->value() / 10.f;
    int size = ui->sizeSlider->value();
    blurrer->createKernel(sigma, size);
    blurrer->update();
    ui->result->setPixmap(QPixmap::fromImage(*result));
}
