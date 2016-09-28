#ifndef RESULTADO2_H
#define RESULTADO2_H

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
#include "math.h"
//#include "cuantizacion.h"
using namespace cv;
using namespace std;
namespace Ui {
class resultado2;
}

class resultado2 : public QDialog
{
    Q_OBJECT

public:
    explicit resultado2(QWidget *parent = 0);
    ~resultado2();

private slots:
    void on_pbtnCargar1_clicked();

    void on_pbtnCalcular_clicked();

    void on_pbtnCargar2_clicked();

private:
    Ui::resultado2 *ui;
    QString nombreArchivo;
    imagen *objImagen;
    espacioColor *objEspColor;
    mensaje *objMensaje;
    binarizar *objBin;
    lsb *objLsb;
    Mat img;
    Mat imgAlterada;
    void buscarImagen();
};

#endif // RESULTADO2_H
