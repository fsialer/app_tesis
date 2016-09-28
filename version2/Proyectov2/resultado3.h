#ifndef RESULTADO3_H
#define RESULTADO3_H

#include <QDialog>
#include <QString>
#include <notepad.h>
#include <QFileDialog>
#include <iostream>
#include <stdio.h>
#include <QMessageBox>
#include "math.h"
using namespace std;
namespace Ui {
class resultado3;
}

class resultado3 : public QDialog
{
    Q_OBJECT

public:
    explicit resultado3(QWidget *parent = 0);
    ~resultado3();

private slots:
    void on_pbtnCargar_clicked();

    void on_pbtnCargar2_clicked();

    void on_pbtnProcesar_clicked();

private:
    Ui::resultado3 *ui;
    notepad *objNpad;
    QString msg;
    QString msg2;
};

#endif // RESULTADO3_H
