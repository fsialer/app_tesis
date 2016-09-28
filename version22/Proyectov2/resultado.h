#ifndef RESULTADO_H
#define RESULTADO_H

#include <QDialog>
#include <opencv2/opencv.hpp>
#include "imagen.h"
#include <QFileDialog>
#include <QString>
#include <iostream>
#include <stdio.h>
#include <QPixmap>
#include <QMessageBox>
#include <QDir>
#include <QDebug>
#include <histograma.h>
#include <QListView>

using namespace cv;
using namespace std;
namespace Ui {
class resultado;
}

class resultado : public QDialog
{
    Q_OBJECT

public:
    explicit resultado(QWidget *parent = 0);
    ~resultado();

private slots:
    void on_pbtnProcesar_clicked();

private:
    Ui::resultado *ui;
    QString nombreArchivo;
    imagen *objImagen;
    histograma *objHist;
};

#endif // RESULTADO_H
