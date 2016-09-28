#ifndef DOMINIOESPACIAL_H
#define DOMINIOESPACIAL_H

#include <QDialog>
#include <QString>
#include <opencv2/opencv.hpp>
#include <QFileDialog>
#include <iostream>
#include <stdio.h>
#include <QPixmap>
#include <QMessageBox>
#include "imagen.h"
#include "espaciocolor.h"
#include "mensaje.h"
#include "binarizar.h"
#include "lsb.h"
//#include "cuantizacion.h"
using namespace cv;
using namespace std;

namespace Ui {
class dominioEspacial;
}

class dominioEspacial : public QDialog
{
    Q_OBJECT

public:
    explicit dominioEspacial(QWidget *parent = 0);
    ~dominioEspacial();

private slots:

    void on_pbtnCargar_clicked();

    void on_pbtnProcesar_clicked();

private:
    Ui::dominioEspacial *ui;
    QString nombreArchivo;
    imagen *objImagen;
    espacioColor *objEspColor;
    mensaje *objMensaje;
    binarizar *objBin;
    lsb *objLsb;
//    cuantizacion *objCuant;
//    binarizar *objBin;
    void procesoIncrustarDE();
    void procesoExtraerDE();
    void buscarImagen();
    Mat alterarPixel3C(Mat img,QList<QList<int> > listaRGBALterada);
    Mat alterarPixel1C(Mat img,QList<int> listaRGBALterada);

};

#endif // DOMINIOESPACIAL_H
