#ifndef IMAGEN_H
#define IMAGEN_H
#include <QString>
#include <opencv2/opencv.hpp>
#include <QList>
#include <iostream>
#include <stdio.h>
using namespace std;
using namespace cv;
class imagen
{
private:
    Mat imgOriginal;
    QList<QList<int> > listaPixelRGBIO;
    QList<QList<int> > listaPixelGray;
public:
    imagen(QString nombreArhivo);
    imagen();
    Mat getImgOriginal();
    void setImgOriginal(Mat img);
    void agregarPixelIO();
    QList<int> agregarPixel();
    QList<QList<int> > getListaPixelRGBIO();
    int getAncho();
    int getAlto();
    QList<int> agregarRGB(int fila,int columna);
    QList<Mat> bloques8x8(Mat gray);
    Mat reconstuirImgC1(QList<Mat> bloqueSumar,int col,int row);
    Mat reconstuirImgC3(Mat c1,Mat c2,Mat c3,int col,int row);

};

#endif // IMAGEN_H
