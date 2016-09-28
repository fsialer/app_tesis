#include "resultado3.h"
#include "ui_resultado3.h"

resultado3::resultado3(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::resultado3)
{
    ui->setupUi(this);
}

resultado3::~resultado3()
{
    delete ui;
}

void resultado3::on_pbtnCargar_clicked()
{
    QString url="C://";
    QString fichero=QFileDialog::getOpenFileName(this,tr("Open File"),
                                                  url,
                                               "Todos los archivos(*.*);;Imagenes JPG(*.jpg)");
    objNpad=new notepad();
    msg=objNpad->readOnly(fichero);

}

void resultado3::on_pbtnCargar2_clicked()
{
    QString url="C://";
    QString fichero=QFileDialog::getOpenFileName(this,tr("Open File"),
                                                  url,
                                               "Todos los archivos(*.*);;Imagenes JPG(*.jpg)");
    objNpad=new notepad();
    msg2=objNpad->readOnly(fichero);

}

void resultado3::on_pbtnProcesar_clicked()
{
    int tamanio=msg2.length();

    double por=0;
    int cont=0;
    for (int i = 0; i < tamanio; ++i) {
        if (msg.at(i)!=msg2.at(i)) {
            cont+=1;
        }
        por=(double)i/(double)(tamanio-1);
        ui->pbarra->setValue(round(por*100));
    }
    ui->txtCaracterErroneo->setText(QString::number(cont));

}
