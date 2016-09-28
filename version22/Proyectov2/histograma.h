
#ifndef HISTOGRAMA_H
#define HISTOGRAMA_H
#include <QList>
#include <opencv2/opencv.hpp>
using namespace cv;
class histograma
{
private:
    QList<int> vc1;
    QList<int> vc2;
    QList<int> vc3;
public:
    histograma();
    void calcularHistograma(Mat img,int op);
    QList<int> getc1();
    QList<int> getc2();
    QList<int> getc3();

};

#endif // HISTOGRAMA_H
