#ifndef LSB_H
#define LSB_H
#include <opencv2/opencv.hpp>
#include <QString>
#include <QList>
#include "binarizar.h"
#include <iostream>
#include <stdio.h>
using namespace std;
using namespace cv;
class lsb
{
private:
    Mat EstegoImagen;
    int cantidadMultiplo(int cantidad, int multiplo);
    binarizar *objBinariar;

    QString byteCoef;



public:
    lsb();
    QList<QList<int> > alterarPixel(QList<QList<int> > listaPixelRGBIO,QList<QList<int> > listaByteTexto);
    int alterarAC(int decimalCoe, int bit);
    QString extraerInformacion(QList<QList<int> > listaPixelRGBEI);
    QString extraerInformacionGray(QList<int > listaPixelGrayEI);
    QString extraerAC(QList<Mat> bloqueCuan);
    int convertirBinarioDecimal(QString byte);
    Mat getEstegoImagem();
    Mat modificarCoeficientesAC(Mat coefAC,QList<int> byteCaracter);
    QList<int> alterarPixelGray(QList<int> listaGrayALterada,QList<QList<int> > listaByteTexto);
};

#endif // LSB_H
