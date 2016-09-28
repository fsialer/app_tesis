#include "resultado2.h"
#include "ui_resultado2.h"

resultado2::resultado2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::resultado2)
{
    ui->setupUi(this);
}

resultado2::~resultado2()
{
    delete ui;
}

void resultado2::on_pbtnCargar1_clicked()
{
    buscarImagen();
}

void resultado2::buscarImagen()
{
    QString url="C://Users//FERNANDO//Desktop//Repositorio de imagenes//imagenes originales//";
    this->nombreArchivo=QFileDialog::getOpenFileName(this,tr("Open File"),
                                                  url,
                                               "Todos los archivos(*.*);;Imagenes JPG(*.jpg)");
    int altura=ui->lblImagen->height();
    int ancho=ui->lblImagen->width();
    QPixmap pix(this->nombreArchivo);
    ui->lblImagen->setPixmap(pix.scaled(ancho,altura,Qt::KeepAspectRatio));
    this->objImagen=new imagen(this->nombreArchivo);
    img=this->objImagen->getImgOriginal().clone();
//    QString descripcion;
//    descripcion.append("Ancho: "+QString::number(this->objImagen->getAncho()));
//    descripcion.append("\n");
//    descripcion.append("Alto: "+QString::number(this->objImagen->getAlto()));
//    descripcion.append("\n");
//    descripcion.append("Ruta: "+this->nombreArchivo);
//    ui->ptxtDescripcion->setPlainText(descripcion);
}

void resultado2::on_pbtnCalcular_clicked()
{
    int width=imgAlterada.cols;
    int height=imgAlterada.rows;
    Rect  r (0,  0,  width,  height);
    Mat imgn=img(r);

    double sum=0,sum2=0;
    double fidelidad=0;
    double por=0;
    int cont=0;
    for (int i = 0; i < imgAlterada.rows; ++i) {
        for (int j = 0; j < imgAlterada.cols; ++j) {
            int pixel=imgn.at<uchar>(i,j);
            int pixel2=imgAlterada.at<uchar>(i,j);

            sum+=pow(pixel-pixel2,2);
            sum2+=pow(pixel,2);
            if (pixel!=pixel2) {
                cont+=1;
            }
        }
        por=(double)i/(double)(imgAlterada.rows-1);
        ui->pbarra->setValue(round(por*100));
    }
//    cout<<"suma: "<<sum<<endl<<" Suma2:"<<sum2<<endl;
    fidelidad=(1-(sum/sum2))*100;
//    cout<<"fidelidad: "<<fidelidad<<endl;
    ui->txtFidelidad->setText(QString::number(fidelidad));
    ui->txtCantENA->setText(QString::number(cont));
    QMessageBox::information(this,tr("Información"),tr("Calculo terminado."));
}

void resultado2::on_pbtnCargar2_clicked()
{
    QString url="C://Users//FERNANDO//Desktop//Repositorio de imagenes//";
    this->nombreArchivo=QFileDialog::getOpenFileName(this,tr("Open File"),
                                                  url,
                                               "Todos los archivos(*.*);;Imagenes JPG(*.jpg)");
    int altura=ui->lblImagen2->height();
    int ancho=ui->lblImagen2->width();
    QPixmap pix(this->nombreArchivo);
    ui->lblImagen2->setPixmap(pix.scaled(ancho,altura,Qt::KeepAspectRatio));
    this->objImagen=new imagen(this->nombreArchivo);
    imgAlterada=this->objImagen->getImgOriginal().clone();
}
