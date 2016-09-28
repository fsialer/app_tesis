#ifndef DOMINIOFRECUENCIAL_H
#define DOMINIOFRECUENCIAL_H

#include <QDialog>
#include <opencv2/opencv.hpp>
#include "imagen.h"
#include "mensaje.h"
#include "lsb.h"
#include "cuantizacion.h"
#include "notepad.h"
#include "espaciocolor.h"
#include <QFileDialog>
#include <QString>
#include <iostream>
#include <stdio.h>
#include <QPixmap>
#include <QMessageBox>
#include <QDir>
#include <QDebug>
#include <QByteArray>
#include <QTextStream>
#include <QIODevice>
#include <QStringList>
#include <QProcess>
using namespace cv;
using namespace std;
namespace Ui {
class dominioFrecuencial;
}

class dominioFrecuencial : public QDialog
{
    Q_OBJECT

public:
    explicit dominioFrecuencial(QWidget *parent = 0);
    ~dominioFrecuencial();

private slots:
    void on_pbtnCargarImg_clicked();

    void on_pbtnBinarizar_clicked();

    void on_pbtnProcesar_clicked();

    void on_pbtnMostrar_clicked();

private:
    Ui::dominioFrecuencial *ui;
    QString nombreArchivo;
    imagen *objImagen;
    mensaje *objMensaje;
    lsb *objLsb;
    espacioColor *objEspColor;
    cuantizacion *objCuant;
     binarizar *objBin;
     notepad *objNpad;
    void buscarImagen();
    void procesoIncrustarDF();
    void procesoExtraerDF();
    void leerCoefAC();
    QList<Mat> calcularDCT(QList<Mat> bloquesC1);
    QList<Mat> calcularCuantizacion(QList<Mat> bloqueDCTC1, int opcion);
    QList<Mat> calcularCuantizacionMult(QList<Mat> bloqueCuanC1, int opcion);
    QList<Mat> calcularIDCT(QList<Mat> bloqueMultC1);
    QList<Mat> aumentar(QList<Mat> bloqueIDCTC1);

    QList<Mat> bloqueCuanC1;
    void modificarCoefAC();
};

#endif // DOMINIOFRECUENCIAL_H
