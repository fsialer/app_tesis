#ifndef MENSAJE_H
#define MENSAJE_H
#include <QString>
#include <QList>
#include "binarizar.h"
#include <iostream>
#include <stdio.h>
using namespace std;
class mensaje
{
private:
    QString mTexto;
    QList<QList<int> > listaByte;
    int tamanioTexto();
    binarizar *objBinarizar;
public:
    mensaje(QString texto);

    QList<QList<int> > getListaByte();
    QList<int> agregarBits(QString byte);
};

#endif // MENSAJE_H
