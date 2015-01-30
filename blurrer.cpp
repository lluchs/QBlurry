#include "blurrer.h"

#define M_PI           3.14159265358979323846
#include <memory>

Blurrer::Blurrer(QObject *parent, QImage *input, QImage *output) :
    QObject(parent), input(input), output(output)
{
    createKernel(1, 3);
}

Blurrer::~Blurrer()
{
}

void Blurrer::createKernel(float sigma, int kernel_size)
{
    if (kernel_size % 2 == 0) kernel_size--;
    kernel.resize(kernel_size);

    const double sigma2 = 2 * sigma * sigma;
    double sum = 0;
    const int mid = kernel_size / 2;
    for (int i = 0; i < kernel_size; ++i) {
        int x = i - mid;
        kernel[i] = 1.f / (M_PI * sigma2) * std::exp(-x*x / sigma2);
        sum += kernel[i];
    }
    // Normalize kernel.
    for (int i = 0; i < kernel_size; ++i) {
        kernel[i] /= sum;
    }
}

static QRgb rgbmul(QRgb a, float t)
{
    return qRgb(qRed(a) * t, qGreen(a) * t, qBlue(a) * t);
}

void Blurrer::update()
{
    std::unique_ptr<QImage> tmp(new QImage(input->size(), input->format()));

    const int mid = kernel.size() / 2;
    // horizontal
    for (int y = 0; y < input->height(); ++y) {
        for (int x = 0; x < input->width(); ++x) {
            QRgb res = qRgb(0, 0, 0);
            for (int dx = -mid; dx <= mid; ++dx)
                res += rgbmul(input->pixel(qBound(0, x + dx, input->width() - 1), y), kernel[dx + mid]);
            tmp->setPixel(x, y, res);
        }
    }
    // vertical
    for (int x = 0; x < input->width(); ++x) {
        for (int y = 0; y < input->height(); ++y) {
            QRgb res = qRgb(0, 0, 0);
            for (int dy = -mid; dy <= mid; ++dy)
                res += rgbmul(tmp->pixel(x, qBound(0, y + dy, input->height() - 1)), kernel[dy + mid]);
            output->setPixel(x, y, res);
        }
    }
}
