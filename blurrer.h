#ifndef BLURRER_H
#define BLURRER_H

#include <QObject>
#include <QImage>

class Blurrer : public QObject
{
    Q_OBJECT
public:
    Blurrer(QObject *parent, QImage *input, QImage *output);
    ~Blurrer();
    void createKernel(float sigma, int size);

signals:

public slots:
    void update();

private:
    QImage *input, *output;
    QVector<float> kernel;

};

#endif // BLURRER_H
