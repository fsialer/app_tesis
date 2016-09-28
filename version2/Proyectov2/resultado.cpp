#include "resultado.h"
#include "ui_resultado.h"

resultado::resultado(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::resultado)
{
    ui->setupUi(this);
}

resultado::~resultado()
{
    delete ui;
}

void resultado::on_pbtnProcesar_clicked()
{
    QString url="C://Users//FERNANDO//Desktop//Repositorio de imagenes//";
    this->nombreArchivo=QFileDialog::getOpenFileName(this,tr("Open File"),
                                                  url,
                                               "Todos los archivos(*.*);;Imagenes JPG(*.jpg)");
    int altura=ui->lblImagen->height();
    int ancho=ui->lblImagen->width();
    QPixmap pix(this->nombreArchivo);
    ui->lblImagen->setPixmap(pix.scaled(ancho,altura,Qt::KeepAspectRatio));
    if (!ui->lblImagen->pixmap()) {
        QMessageBox::warning(this,tr("Advertencia"),tr("Cargue una imagen."));
        return;
    }
    this->objImagen=new imagen(this->nombreArchivo);
    QString descripcion;
    descripcion.append("Ancho: "+QString::number(this->objImagen->getAncho()));
    descripcion.append("\n");
    descripcion.append("Alto: "+QString::number(this->objImagen->getAlto()));
    descripcion.append("\n");
    descripcion.append("Ruta: "+this->nombreArchivo);
    ui->ptxtDescripcion->setPlainText(descripcion);

    cout<<this->objImagen->getImgOriginal().channels()<<endl;
    objHist=new histograma();
    if (ui->rbtnGray->isChecked()) {
        QStringList titulos;
        ui->tblWHistigrama->setColumnCount(1);
        titulos<<"Gray";
        ui->tblWHistigrama->setHorizontalHeaderLabels(titulos);

        objHist->calcularHistograma(this->objImagen->getImgOriginal(),1);
        for (int i = 0; i < 256; ++i) {
    //        fila=ui->tblwRGBO->rowCount()-1;
            ui->tblWHistigrama->insertRow(ui->tblWHistigrama->rowCount());
            QString strR;
            strR=QString::number(objHist->getc1().value(i));

            ui->tblWHistigrama->setItem(i,0,new QTableWidgetItem(strR));
        }

    }
    if (ui->rbtnColor->isChecked()) {
        QStringList titulos;
        ui->tblWHistigrama->setColumnCount(3);
        titulos<<"Rojo"<<"Verde"<<"Azul";
        ui->tblWHistigrama->setHorizontalHeaderLabels(titulos);
        objHist->calcularHistograma(this->objImagen->getImgOriginal(),2);
        for (int i = 0; i < 256; ++i) {
    //        fila=ui->tblwRGBO->rowCount()-1;
            ui->tblWHistigrama->insertRow(ui->tblWHistigrama->rowCount());
            QString strR;
            strR=QString::number(objHist->getc1().value(i));
            QString strG;
            strG=QString::number(objHist->getc2().value(i));
            QString strB;
            strB=QString::number(objHist->getc3().value(i));
            ui->tblWHistigrama->setItem(i,0,new QTableWidgetItem(strR));
             ui->tblWHistigrama->setItem(i,1,new QTableWidgetItem(strG));
              ui->tblWHistigrama->setItem(i,2,new QTableWidgetItem(strB));
        }
    }
}
