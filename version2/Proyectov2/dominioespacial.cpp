#include "dominioespacial.h"
#include "ui_dominioespacial.h"

dominioEspacial::dominioEspacial(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dominioEspacial)
{
    ui->setupUi(this);
}

dominioEspacial::~dominioEspacial()
{
    delete ui;
}



void dominioEspacial::on_pbtnCargar_clicked()
{
    buscarImagen();//Este metodo buscarImagen, hace una
    //exploracion para buscar la imagen.

}
void dominioEspacial::buscarImagen(){
    //Explora el disco duro, en busca de la imagen digital.

    QString url="C://Users//FernandoAlexis//Desktop//Repositorio de imagenes//";
    this->nombreArchivo=QFileDialog::getOpenFileName(this,tr("Open File"),
                                                  url,
                                               "Todos los archivos(*.*);;Imagenes JPG(*.jpg)");
    int altura=ui->lblImagen->height();
    int ancho=ui->lblImagen->width();
    QPixmap pix(this->nombreArchivo);
    ui->lblImagen->setPixmap(pix.scaled(ancho,altura,Qt::KeepAspectRatio));
    this->objImagen=new imagen(this->nombreArchivo);//Inicializa la clase imagen y paasa como parametro
    //al contructor la ubicacion de la imagen a cargar.
    QString descripcion;
    descripcion.append("Ancho: "+QString::number(this->objImagen->getAncho()));
    descripcion.append("\n");
    descripcion.append("Alto: "+QString::number(this->objImagen->getAlto()));
    descripcion.append("\n");
    descripcion.append("Ruta: "+this->nombreArchivo);
    ui->ptxtDescripcion->setPlainText(descripcion);//Muestra las caracteristicas de la imagen.
}

Mat dominioEspacial::alterarPixel3C(Mat img,QList<QList<int> >listaRGBALterada)
{
    //Aqui reemplazamos los pixeles originales de la imagen,
    //por los pixeles alterados de forma secuencial, en sus tres canales que la componen.

    int k=0;
    double por;
    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.cols; j++) {
            img.data[img.channels()*(img.cols*i+j)+0]
                    =listaRGBALterada.value(k).value(0);
           img.data[img.channels()*(img.cols*i+j)+1]
                    =listaRGBALterada.value(k).value(1);
            img.data[img.channels()*(img.cols*i+j)+2]
                    =listaRGBALterada.value(k).value(2);
            k++;
        }
        por=(double)i/(double)(img.rows-1);
        ui->pBarra->setValue(round(por*100));
        cout<<"load "<<por<<endl;
    }
    return img;
}

Mat dominioEspacial::alterarPixel1C(Mat img, QList<int> listaRGBALterada)
{
    //Aqui reemplazamos los pixeles originales de la imagen,
    //por los pixeles alterados de forma secuencial, en un canal que la compone.
    int k=0;
    double por;
    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.cols; j++) {
            img.at<uchar>(i,j)
                    =listaRGBALterada.value(k);
          img.at<uchar>(i,j)
                    =listaRGBALterada.value(k);
            img.at<uchar>(i,j)
                    =listaRGBALterada.value(k);
            k++;
        }
        por=(double)i/(double)(img.rows-1);
        ui->pBarra->setValue(round(por*100));
        cout<<"load "<<por<<endl;

    }
    return img;

}

void dominioEspacial::on_pbtnProcesar_clicked()
{
    //Valida si se cargo la imagen.
    if (!ui->lblImagen->pixmap()) {
        QMessageBox::warning(this,tr("Advertencia"),tr("Cargue una imagen."));
        return;
    }
    //Valida, si se a elegido algún espacio de color.
    if(!ui->rbtnRGB->isChecked() && !ui->rbtnGray->isChecked() && !ui->rbtnYCrCb->isChecked() && !ui->rbtnYUV->isChecked()){
        QMessageBox::warning(this,tr("Advertencia"),tr("Seleccione un Espacio de color."));
        return;
    }    
    //Valida, si se a elegido algún proceso.
    if(!ui->rbtnIncrustar->isChecked() && !ui->rbtnExtraer->isChecked()){
        QMessageBox::warning(this,tr("Advertencia"),tr("Seleccione un proceso."));
        return;
    }
    //Comprueba que tipo de proceso a realizar sea inscrustar o extraer.
    if (ui->rbtnIncrustar->isChecked()) {//Comprueba si se selecciono el proceso de incrustar.
        if( ui->ptxtMensaje->toPlainText().length()<1){
            QMessageBox::warning(this,tr("Advertencia"),tr("Introduzca un mensaje."));
            return;
        }
        procesoIncrustarDE();//Este método inscrusta el mensaje en la imagen digital.
    }
    if (ui->rbtnExtraer->isChecked()) {//Comprueba si se selecciono el proceso de extraer o recuperar.
        procesoExtraerDE();//Este método extrae o recupera el mensahe de la imagen digital.
    }
}
void dominioEspacial::procesoIncrustarDE()
{
    //En este método, se procede a realizar
    //todos los procesos para la incrustacion del mensaje en la
    //imagen digital.

    //Varibales para procesar texto.
    QString texto;
    QList<QList<int> > listaBitText;
    texto=ui->ptxtMensaje->toPlainText();//se almacena en una variable de tipo QString el mensaje.
    this->objMensaje=new mensaje(texto);//Inicializa de la clase mensaje para poder pasar el parametro al constructor
    //que viene hacer el mensaje a ocultar para su posterior procesamiento.
    listaBitText=this->objMensaje->getListaByte();//Este método pide una lista de byte de los caracteres
    //del mensaje procesados.

    //Variables para procesar imagen.
    QList<QList<int> >listaPixelRGBIO;
    QList<int>listaPixelGray;
    int ancho=this->objImagen->getAncho();//Obtiene el ancho de la imagen digital.
    int alto=this->objImagen->getAlto();//obtiene el alto de la imagen digital.
    //Variables para alterar pixeles.
    QList<QList<int> > listaRGBALterada;
    QList<int > listaGrayALterada;

    Mat imgNueva;
    //Comprueba que tipo de espacio de color se selecciono para le ocultamiento del mensaje.
    if (ui->rbtnRGB->isChecked()) {
        this->objImagen->agregarPixelIO();//Este metodo realiza la funcion de agregar los pixeles
        //de la imagen original en una lista.
        listaPixelRGBIO=this->objImagen->getListaPixelRGBIO();//Obtiene la lista de pixeles de la imagen original.
        this->objLsb=new lsb();//inicializacion de la clase lsb
        listaRGBALterada=this->objLsb->alterarPixel(listaPixelRGBIO,listaBitText);//Obtiene la lista de pixeles
        //alterados aplicando el metodo Least Significan Bit.
        imgNueva=objImagen->getImgOriginal().clone();//Obtenemos la clonacion de la imagen original.
        imgNueva=alterarPixel3C(imgNueva,listaRGBALterada);//Aqui se reemplaza de manera secuencial los pixeles de la
        //imagen clonada.

    }
      //Comprueba que tipo de espacio de color se selecciono para le ocultamiento del mensaje.
    if (ui->rbtnGray->isChecked()) {
        Mat img=objImagen->getImgOriginal().clone();//Obtenemos la clonacion de la imagen original.
        img=objEspColor->convertirRGBGray(img);//Obtiene la conversion de la imagen segun su espacio de color.
        objImagen->setImgOriginal(img);//Reemplaza la imagen.
//        imshow("gris",objImagen->getImgOriginal());
        listaPixelGray=this->objImagen->agregarPixel();//Obtiene la lista de pixeles de la imagen original.
        this->objLsb=new lsb();//inicializacion de la clase lsb
        listaGrayALterada=this->objLsb->alterarPixelGray(listaPixelGray,listaBitText);//Obtiene la lista de pixeles
        //alterados aplicando el metodo Least Significan Bit.
        imgNueva=Mat::zeros(Size(ancho,alto), CV_8UC1);//crear un imagen de un canal.
        imgNueva=alterarPixel1C(imgNueva,listaGrayALterada);//obtener la imagen alteara y reemplazarla.

    }
      //Comprueba que tipo de espacio de color se selecciono para le ocultamiento del mensaje.
    if (ui->rbtnYCrCb->isChecked()) {
        Mat img=objImagen->getImgOriginal().clone();//Obtenemos la clonacion de la imagen original.
        img=objEspColor->convertirRGBYCrCb(img);//Obtiene la conversion de la imagen segun su espacio de color.
//        imshow("YCrCb",img);
        objImagen->setImgOriginal(img);//Reemplaza la imagen.
        this->objImagen->agregarPixelIO();//Obtiene la lista de pixeles de la imagen original.
        listaPixelRGBIO=this->objImagen->getListaPixelRGBIO();//Obtiene la lista de pixeles de la imagen original.
        this->objLsb=new lsb();//inicializacion de la clase lsb
        listaRGBALterada=this->objLsb->alterarPixel(listaPixelRGBIO,listaBitText);//Obtiene la lista de pixeles
        //alterados aplicando el metodo Least Significan Bit.
        imgNueva=objImagen->getImgOriginal().clone();//
        imgNueva=Mat::zeros(Size(ancho,alto), CV_8UC3);//crear un imagen de 3 canales.
        imgNueva=alterarPixel3C(imgNueva,listaRGBALterada);//obtener la imagen alteara y reemplazarla.
//        imshow("YCrCb2",imgNueva);
        imgNueva=objEspColor->convertirYCrCbRGB(imgNueva);//Obtener la imagen a color segun su espacio de color.

    }
      //Comprueba que tipo de espacio de color se selecciono para le ocultamiento del mensaje.
    if (ui->rbtnYUV->isChecked()) {
        Mat img=objImagen->getImgOriginal().clone();//Obtenemos la clonacion de la imagen original.
        img=objEspColor->convertirRGBYUV(img);//Obtiene la conversion de la imagen segun su espacio de color.
//        imshow("YCrCb",img);
        objImagen->setImgOriginal(img);//Reemplaza la imagen.
        this->objImagen->agregarPixelIO();//Obtiene la lista de pixeles de la imagen original.
        listaPixelRGBIO=this->objImagen->getListaPixelRGBIO();//Obtiene la lista de pixeles de la imagen original.
        this->objLsb=new lsb();//inicializacion de la clase lsb
        listaRGBALterada=this->objLsb->alterarPixel(listaPixelRGBIO,listaBitText);//Obtiene la lista de pixeles
        //alterados aplicando el metodo Least Significan Bit.
        imgNueva=objImagen->getImgOriginal().clone();
        imgNueva=Mat::zeros(Size(ancho,alto), CV_8UC3);//crear un imagen de 3 canales.
        imgNueva=alterarPixel3C(imgNueva,listaRGBALterada);//obtener la imagen alteara y reemplazarla.
//        imshow("YCrCb2",imgNueva);
        imgNueva=objEspColor->convertirYUVRGB(imgNueva);//Obtener la imagen a color segun su espacio de color.

    }
    QMessageBox::information(this,tr("Información"),tr("El mensaje se incrusto con satisfacción."));
    ui->ptxtMensaje->setPlainText("");
    ui->pBarra->setValue(0);
    imshow("Estegoimagen",imgNueva);
}
void dominioEspacial::procesoExtraerDE()
{
    //En este método, se procede a realizar
    //todos los procesos para la extracción o recuperacion del mensaje de la
    //imagen digital.
     QString mensajeExtraido;
     objLsb=new lsb();
     Mat imgNueva;
     //Comprobamos en que espacio de color se selecciono para la recuperacion del mensaje.
    if (ui->rbtnRGB->isChecked()) {

        QList<QList<int> >listaPixelRGBEI;
        objImagen->agregarPixelIO();//Obtiene la lista de pixeles de la imagen alterada.
        listaPixelRGBEI=objImagen->getListaPixelRGBIO();//Obtiene la lista de los pixeles de la imagen alterada.
        mensajeExtraido=this->objLsb->extraerInformacion(listaPixelRGBEI);//Obtiene el mensaje extraido
        //de la imagen utilizando el metodo Least Significant Bit.
    }
    if (ui->rbtnGray->isChecked()) {
        QList<int >listaPixelGrayEI;
        imgNueva=objImagen->getImgOriginal().clone();//Obtiene una clonacion de la imagen original.
        imgNueva=objEspColor->convertirRGBGray(imgNueva);//Obtiene la conversion de la imagen segun sus espacio de color
        objImagen->setImgOriginal(imgNueva);//Se reempleza la imagen.
        listaPixelGrayEI=this->objImagen->agregarPixel();//Obtiene la lista de pixeles de la imagen alterada.
        mensajeExtraido=this->objLsb->extraerInformacionGray(listaPixelGrayEI);//Obtiene el mensaje extraido
        //de la imagen utilizando el metodo Least Significant Bit.
    }

    if (ui->rbtnYCrCb->isChecked()) {
        QList<QList<int> >listaPixelRGBEI;
        imgNueva=objImagen->getImgOriginal().clone();//Obtiene una clonacion de la imagen original.
        imgNueva=objEspColor->convertirRGBYCrCb(imgNueva);//Obtiene la conversion de la imagen segun sus espacio de color
//        imshow("eje",imgNueva);
        objImagen->setImgOriginal(imgNueva);//Se reempleza la imagen.
        objImagen->agregarPixelIO();//Obtiene la lista de pixeles de la imagen alterada.
        listaPixelRGBEI=objImagen->getListaPixelRGBIO();//Obtiene la lista de los pixeles de la imagen alterada.
        mensajeExtraido=this->objLsb->extraerInformacion(listaPixelRGBEI);//Obtiene el mensaje extraido
        //de la imagen utilizando el metodo Least Significant Bit.
    }
    if (ui->rbtnYUV->isChecked()) {
        QList<QList<int> >listaPixelRGBEI;
        imgNueva=objImagen->getImgOriginal().clone();//Obtiene una clonacion de la imagen original.
        imgNueva=objEspColor->convertirRGBYUV(imgNueva);//Obtiene la conversion de la imagen segun sus espacio de color
//        imshow("eje",imgNueva);
        objImagen->setImgOriginal(imgNueva);//Se reempleza la imagen.
        objImagen->agregarPixelIO();//Obtiene la lista de pixeles de la imagen alterada.
        listaPixelRGBEI=objImagen->getListaPixelRGBIO();//Obtiene la lista de los pixeles de la imagen alterada.
        mensajeExtraido=this->objLsb->extraerInformacion(listaPixelRGBEI);//Obtiene el mensaje extraido
        //de la imagen utilizando el metodo Least Significant Bit.
    }


    ui->pBarra->setValue(100);
    ui->ptxtMensaje->setPlainText(mensajeExtraido);//Muestra el texto recuperado
    QMessageBox::information(this,tr("Información"),tr("El mensaje se recupero con satisfacción"));
}
