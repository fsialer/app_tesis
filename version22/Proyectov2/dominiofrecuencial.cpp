#include "dominiofrecuencial.h"
#include "ui_dominiofrecuencial.h"

dominioFrecuencial::dominioFrecuencial(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dominioFrecuencial)
{
    ui->setupUi(this);
}

dominioFrecuencial::~dominioFrecuencial()
{
    delete ui;
}

//
void dominioFrecuencial::buscarImagen()
{
    //Explora el disco duro, en busca de la imagen digital.
    QString url="C://Users//FERNANDO//Desktop//Repositorio de imagenes//";
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
    ui->ptxtDescripcion->setPlainText(descripcion);
}
void dominioFrecuencial::on_pbtnCargarImg_clicked()
{
    buscarImagen();//Este metodo buscarImagen, hace una
    //exploracion para buscar la imagen.
}
//Este método binariza el mensaje y lo codifica.
void dominioFrecuencial::on_pbtnBinarizar_clicked()
{
    //Procesar texto
    if( ui->ptxtMensaje->toPlainText().length()<1){
        QMessageBox::warning(this,tr("Advertencia"),tr("Introduzca un mensaje."));
        return;
    }
    QString texto;
    QList<QList<int> > listaByteText;
    QList<int> listaByte;
    texto=ui->ptxtMensaje->toPlainText();//se almacena en una variable de tipo QString el mensaje.
    this->objMensaje=new mensaje(texto);//Inicializa de la clase mensaje para poder pasar el parametro al constructor
    //que viene hacer el mensaje a ocultar para su posterior procesamiento.
    listaByteText=this->objMensaje->getListaByte();//Este método pide una lista de byte de los caracteres
    //del mensaje procesados.
    for (int i = 0; i < listaByteText.size(); i++) {//Bucle para recorrer todos los byte del texto.
        for (int j = 0; j < listaByteText.value(i).size(); j++) {//Bucle para recorrer los bt de cada byte.
            int bit=listaByteText.value(i).value(j);
            listaByte.push_back(bit);
        }
    }
    int decimal=124;//Decimal que indica el fin del mensaje.
    QString byte;
    objBin=new binarizar();//Inicialización de la clase binarizar.
    byte=objBin->getByte(decimal);//Devuelve el decimal en byte.
    for (int i = 0; i < 8; i++) {//Este bucle recorre los bit para el decimal convertidor en byte
        listaByte.push_back(byte.at(i).digitValue());//Descompone el byte en bits.
    }

    while(listaByte.size()%12!=0){//Este bucle lleva lso bit restantes.
        for (int i = 0; i < 4; ++i) {
            int bit=0;
            listaByte.push_back(bit);
        }
    }
    cout<<listaByte.size()<<endl;
    QString matriz;
    int cont=0;
    double por;
    for (int i = 0; i < listaByte.size(); i++) {//Este bucle recorre los byte, y los guarda
        //en block note en una matriz de bits.
        cont++;
        cout<<listaByte.value(i)<<" ";
        matriz.append(QString::number(listaByte.value(i)));
        if (cont<12) {//Comprobar si el bit es de longitud 12.
            matriz.append(" ");
        }
        if (cont==12) {//Comprobar si la longitud es igual a 12, para dar un salto de linea.
            matriz.append("\n");
            cont=0;
            cout<<""<<endl;
        }
        por=(double)i/(double)(listaByte.size()-1);
        ui->pBarra->setValue(round(por*100));
    }

    cout<<"Fin de codigo"<<endl;
    cout<<matriz.toStdString()<<endl;
    ui->lblProceso->setText("Binarizar.....");
    QString fichero="binario.txt";
    objNpad=new notepad();//Inicializar la clase notepad.
    objNpad->writeOnly(matriz,fichero);//Escribe la matriz en el block de notas.
    QMessageBox::information(this,tr("Información"),tr("Mensaje binarizado guardado correctamente."));
    ui->lblProceso->setText("");
    ui->pBarra->setValue(0);
}

void dominioFrecuencial::on_pbtnProcesar_clicked()
{
    //Valida si se cargo la imagen.
    if (!ui->lblImagen->pixmap()) {
        QMessageBox::warning(this,tr("Advertencia"),tr("Cargue una imagen."));
        return;
    }
      //Valida, si se a elegido algún proceso.
    if(!ui->rbtnIncrustar->isChecked() && !ui->rbtnExtraer->isChecked()){
        QMessageBox::warning(this,tr("Advertencia"),tr("Seleccione un proceso."));
        return;
    }
    //Valida, si se a elegido algún espacio de color.
    if(!ui->rbtnGray->isChecked()  && !ui->rbtnYCrCb->isChecked() && !ui->rbtnYUV->isChecked()){
        QMessageBox::warning(this,tr("Advertencia"),tr("Seleccione un Espacio de color."));

        return;
    }
     //Comprueba que tipo de proceso a realizar sea inscrustar o extraer.
    if (ui->rbtnIncrustar->isChecked()) {//Comprueba si se selecciono el proceso de incrustar.
        procesoIncrustarDF();//Este método inscrusta el mensaje en la imagen digital.
    }
    if (ui->rbtnExtraer->isChecked()) {//Comprueba si se selecciono el proceso de extraer o recuperar.
        procesoExtraerDF();//Este método extrae o recupera el mensahe de la imagen digital.
    }
}
//Este Método procesoIncrustarDF, incrusta el mensaje en la imagen digital.
void dominioFrecuencial::procesoIncrustarDF()
{
    //Variable para almacenar imagen
    Mat img=objImagen->getImgOriginal();
    Mat imgClon=img.clone();
    //variables para los bloques8x8
    QList<Mat> bloquesC1;
    QList<Mat> bloquesC2;
    QList<Mat> bloquesC3;
    //variables para la transformada DCT
    QList<Mat> bloqueDCTC1;
    QList<Mat> bloqueDCTC2;
    QList<Mat> bloqueDCTC3;
    QList<Mat> bloqueMultC1;
    QList<Mat> bloqueMultC2;
    QList<Mat> bloqueMultC3;
    //Cuantizacion
//    QList<Mat> bloqueCuanC1;
    QList<Mat> bloqueCuanC2;
    QList<Mat> bloqueCuanC3;
    QList<Mat> bloqueIDCTC1;
    QList<Mat> bloqueIDCTC2;
    QList<Mat> bloqueIDCTC3;
    QList<Mat> bloqueSumarC1;
    QList<Mat> bloqueSumarC2;
    QList<Mat> bloqueSumarC3;
    Mat imgContruirC1;
    Mat imgContruirC2;
    Mat imgContruirC3;
    Mat imgNueva;
    objEspColor=new espacioColor();//Inicializar la clase espacio de color.

     //Comprueba que tipo de espacio de color se selecciono para le ocultamiento del mensaje.
    if (ui->rbtnGray->isChecked()) {
        imgClon=objEspColor->convertirRGBGray(imgClon);//Devuelve la imagen convertida en el espacio de color  escala de grises.
//        imshow("gris",imgClon);
        bloquesC1=this->objImagen->bloques8x8(imgClon);//recibe bloques 8x8
        bloqueDCTC1=calcularDCT(bloquesC1);//Calcula la Discrete Cosine Transform DCT
        this->bloqueCuanC1=calcularCuantizacion(bloqueDCTC1,1);//Devuelve la matriz cuantificada
        modificarCoefAC();//Modifica los coeficientes AC de cada bloque 8x8 aplicando el metodo least Significant Bit
        bloqueMultC1=calcularCuantizacionMult(bloqueCuanC1,1);//Se multiplica las matrices de la cuantizacion para restaurar sus valores.
        bloqueIDCTC1=calcularIDCT(bloqueMultC1);//Calcula la Inverse Discrete Cosine Transform IDCT.
        bloqueSumarC1=aumentar(bloqueIDCTC1);//Se aumenta 128 a todos los coeficienes.
        objImagen=new imagen();//Inicializar la clase imagen
        imgContruirC1=objImagen->reconstuirImgC1(bloqueSumarC1,imgClon.cols,imgClon.rows).clone();//Devuelve la imagen reconstruida.
        imgNueva=imgContruirC1.clone();//Se clona la imagen.

    }
      //Comprueba que tipo de espacio de color se selecciono para le ocultamiento del mensaje.
    if (ui->rbtnYCrCb->isChecked()) {
        imgClon=objEspColor->convertirRGBYCrCb(imgClon);//Devuelve la imagen convertida en el espacio de color YCbCr.
//        imshow("YCrCb",imgClon);
        Mat gris(imgClon.rows,imgClon.cols,CV_8UC1);//Se almacenara la imagen en escala de grises.
        Mat Cr(imgClon.rows,imgClon.cols,CV_8UC1);//Se almacena la imagen en crominancia en Rojo.
        Mat Cb(imgClon.rows,imgClon.cols,CV_8UC1);//Se almacena la imagen en crominancia en Blue.

        double por;
          for (int i = 0; i < imgClon.rows; i++) {//El bucle recorre las filas de la imagen.
               for (int j = 0; j < imgClon.cols; j++) {//El bucle recorre las clumnas de la imagen.
                    gris.at<uchar>(i,j)=(int)imgClon.data[imgClon.channels()*(imgClon.cols*i+j)+0];//Guarda el pixel en escala de grises
                    Cr.at<uchar>(i,j)=(int)imgClon.data[imgClon.channels()*(imgClon.cols*i+j)+1];//guarda el pixel de crominancia en rojo
                    Cb.at<uchar>(i,j)=(int)imgClon.data[imgClon.channels()*(imgClon.cols*i+j)+2];//guarda el pixel de crominancia en azul
               }
               por=(double)i/(double)(imgClon.rows-1);
               ui->pBarra->setValue(round(por*100));
               ui->lblProceso->setText("Diviendo canales .....");

         }
          bloquesC1=this->objImagen->bloques8x8(gris);//recibe bloques 8x8 en escala de grises.
          bloquesC2=this->objImagen->bloques8x8(Cr);//recibe bloques 8x8 en crominancia d red.
          bloquesC3=this->objImagen->bloques8x8(Cb);//recibe bloques 8x8 en crominancia en blue.
          bloqueDCTC1=calcularDCT(bloquesC1);//Calcula la Discrete Cosine Transform DCT en escala de grises.
          bloqueDCTC2=calcularDCT(bloquesC2);//Calcula la Discrete Cosine Transform DCT en crominancia en Red.
          bloqueDCTC3=calcularDCT(bloquesC3);//Calcula la Discrete Cosine Transform DCT en crominancia en blue.
          this->bloqueCuanC1=calcularCuantizacion(bloqueDCTC1,1);//Devuelve la matriz cuantificada de la escala de grises.
          bloqueCuanC2=calcularCuantizacion(bloqueDCTC2,2);//Devuelve la matriz cuantificada de crominancia en red.
          bloqueCuanC3=calcularCuantizacion(bloqueDCTC3,2);//Devuelve la matriz cuantificada de crominancia en blue.
          modificarCoefAC();//Modifica los coeficientes AC de cada bloque 8x8 aplicando el metodo least Significant Bit
          bloqueMultC1=calcularCuantizacionMult(bloqueCuanC1,1);//Se multiplica las matrices de la cuantizacion para restaurar sus valores en escala de grises.
          bloqueMultC2=calcularCuantizacionMult(bloqueCuanC2,2);//Se multiplica las matrices de la cuantizacion para restaurar sus valores en crominancia red.
          bloqueMultC3=calcularCuantizacionMult(bloqueCuanC3,2);//Se multiplica las matrices de la cuantizacion para restaurar sus valores en crominancia blue.
          bloqueIDCTC1=calcularIDCT(bloqueMultC1);//Calcula la Inverse Discrete Cosine Transform DCT en escala de grises.
          bloqueIDCTC2=calcularIDCT(bloqueMultC2);//Calcula la Inverse Discrete Cosine Transform DCT en crominancia en Red.
          bloqueIDCTC3=calcularIDCT(bloqueMultC3);//Calcula la Inverse Discrete Cosine Transform DCT en crominancia en blue.
          bloqueSumarC1=aumentar(bloqueIDCTC1);//Se aumenta 128 a todos los coeficienes.
          bloqueSumarC2=aumentar(bloqueIDCTC2);//Se aumenta 128 a todos los coeficienes.
          bloqueSumarC3=aumentar(bloqueIDCTC3);//Se aumenta 128 a todos los coeficienes.
          objImagen=new imagen();//Inicializar la clase imagen
          imgContruirC1=objImagen->reconstuirImgC1(bloqueSumarC1,imgClon.cols,imgClon.rows).clone();//Devuelve la imagen reconstruida.
          imgContruirC2=objImagen->reconstuirImgC1(bloqueSumarC2,imgClon.cols,imgClon.rows).clone();//Devuelve la imagen reconstruida.
          imgContruirC3=objImagen->reconstuirImgC1(bloqueSumarC3,imgClon.cols,imgClon.rows).clone();//Devuelve la imagen reconstruida.
          imgNueva=objImagen->reconstuirImgC3(imgContruirC1,imgContruirC2,imgContruirC3,imgContruirC1.cols,imgContruirC1.rows);//Devuelve la imagen reconstruida.
          imgNueva=objEspColor->convertirYCrCbRGB(imgNueva);//Devuelve la imagen convertida a color segun su espacio de color.
//          imshow("Imagen Restaurada",imgNueva);
    }
      //Comprueba que tipo de espacio de color se selecciono para le ocultamiento del mensaje.
    if (ui->rbtnYUV->isChecked()) {
        imgClon=objEspColor->convertirRGBYUV(imgClon);//Devuelve la imagen convertida en el espacio de color YUV.
//        imshow("YUV",imgClon);
        Mat gris(imgClon.rows,imgClon.cols,CV_8UC1);//Se almacenara la imagen en escala de grises.
        Mat U(imgClon.rows,imgClon.cols,CV_8UC1);//Se almacena la imagen en crominancia en Rojo.
        Mat V(imgClon.rows,imgClon.cols,CV_8UC1);//Se almacena la imagen en crominancia en Blue.
        ui->pBarra->setValue(0);
        double por;
          for (int i = 0; i < imgClon.rows; i++) {//El bucle recorre las filas de la imagen.
               for (int j = 0; j < imgClon.cols; j++) {//El bucle recorre las clumnas de la imagen.
                    gris.at<uchar>(i,j)=(int)imgClon.data[imgClon.channels()*(imgClon.cols*i+j)+0];//Guarda el pixel en escala de grises
                    U.at<uchar>(i,j)=(int)imgClon.data[imgClon.channels()*(imgClon.cols*i+j)+1];//guarda el pixel de crominancia en rojo
                    V.at<uchar>(i,j)=(int)imgClon.data[imgClon.channels()*(imgClon.cols*i+j)+2];//guarda el pixel de crominancia en azul
               }
               por=(double)i/(double)(imgClon.rows-1);
               ui->pBarra->setValue(round(por*100));
               ui->lblProceso->setText("Diviendo canales .....");

         }
//          imshow("Y",gris);
//          imshow("U",U);
//          imshow("V",V);
          bloquesC1=this->objImagen->bloques8x8(gris);//recibe bloques 8x8 en escala de grises.
          bloquesC2=this->objImagen->bloques8x8(U);//recibe bloques 8x8 en crominancia d red.
          bloquesC3=this->objImagen->bloques8x8(V);//recibe bloques 8x8 en crominancia en blue.
          bloqueDCTC1=calcularDCT(bloquesC1);//Calcula la Discrete Cosine Transform DCT en escala de grises.
          bloqueDCTC2=calcularDCT(bloquesC2);//Calcula la Discrete Cosine Transform DCT en crominancia en Red.
          bloqueDCTC3=calcularDCT(bloquesC3);//Calcula la Discrete Cosine Transform DCT en crominancia en blue.
          this->bloqueCuanC1=calcularCuantizacion(bloqueDCTC1,1);//Devuelve la matriz cuantificada de la escala de grises.
          bloqueCuanC2=calcularCuantizacion(bloqueDCTC2,2);//Devuelve la matriz cuantificada de crominancia en red.
          bloqueCuanC3=calcularCuantizacion(bloqueDCTC3,2);//Devuelve la matriz cuantificada de crominancia en blue.
          modificarCoefAC();//Modifica los coeficientes AC de cada bloque 8x8 aplicando el metodo least Significant Bit
          bloqueMultC1=calcularCuantizacionMult(bloqueCuanC1,1);//Se multiplica las matrices de la cuantizacion para restaurar sus valores en escala de grises.
          bloqueMultC2=calcularCuantizacionMult(bloqueCuanC2,2);//Se multiplica las matrices de la cuantizacion para restaurar sus valores en crominancia red.
          bloqueMultC3=calcularCuantizacionMult(bloqueCuanC3,2);//Se multiplica las matrices de la cuantizacion para restaurar sus valores en crominancia blue
          bloqueIDCTC1=calcularIDCT(bloqueMultC1);//Calcula la Inverse Discrete Cosine Transform DCT en escala de grises.
          bloqueIDCTC2=calcularIDCT(bloqueMultC2);//Calcula la Inverse Discrete Cosine Transform DCT en crominancia en Red.
          bloqueIDCTC3=calcularIDCT(bloqueMultC3);//Calcula la Inverse Discrete Cosine Transform DCT en crominancia en blue.
          bloqueSumarC1=aumentar(bloqueIDCTC1);//Se aumenta 128 a todos los coeficienes.
          bloqueSumarC2=aumentar(bloqueIDCTC2);//Se aumenta 128 a todos los coeficienes.
          bloqueSumarC3=aumentar(bloqueIDCTC3);//Se aumenta 128 a todos los coeficienes.
          objImagen=new imagen();//Inicializar la clase imagen
          imgContruirC1=objImagen->reconstuirImgC1(bloqueSumarC1,imgClon.cols,imgClon.rows).clone();//Devuelve la imagen reconstruida.
          imgContruirC2=objImagen->reconstuirImgC1(bloqueSumarC2,imgClon.cols,imgClon.rows).clone();//Devuelve la imagen reconstruida.
          imgContruirC3=objImagen->reconstuirImgC1(bloqueSumarC3,imgClon.cols,imgClon.rows).clone();//Devuelve la imagen reconstruida.
          imgNueva=objImagen->reconstuirImgC3(imgContruirC1,imgContruirC2,imgContruirC3,imgContruirC1.cols,imgContruirC1.rows);//Devuelve la imagen reconstruida.
          imgNueva=objEspColor->convertirYUVRGB(imgNueva);//Devuelve la imagen convertida a color segun su espacio de color.



}
    QMessageBox::information(this,tr("Información"),tr("El mensaje se incrusto con satisfacción."));
     imshow("StegoimagenSG",imgNueva);
}
//Este método procesoExtraerDF, extrae o recupera el mensaje secreto de la imagen digital.
void dominioFrecuencial::procesoExtraerDF()
{
    Mat img=objImagen->getImgOriginal();
    Mat imgClon=img.clone();
    //variables para los bloques8x8
    QList<Mat> bloquesC1;
    QList<Mat> bloquesC2;
    QList<Mat> bloquesC3;
    //variables para la transformada DCT
    QList<Mat> bloqueDCTC1;
    QList<Mat> bloqueDCTC2;
    QList<Mat> bloqueDCTC3;
    QList<Mat> bloqueMultC1;
    QList<Mat> bloqueMultC2;
    QList<Mat> bloqueMultC3;
    //Cuantizacion
//    QList<Mat> bloqueCuanC1;
    QList<Mat> bloqueCuanC2;
    QList<Mat> bloqueCuanC3;
    QList<Mat> bloqueIDCTC1;
    QList<Mat> bloqueIDCTC2;
    QList<Mat> bloqueIDCTC3;
    QList<Mat> bloqueSumar;
    Mat imgContruir;
    objEspColor=new espacioColor();//Inicializar la clase espaciocolor
     //Comprueba que tipo de espacio de color se selecciono para la recuoeracion del mensaje.
    if (ui->rbtnGray->isChecked()) {
        imgClon=objEspColor->convertirRGBGray(imgClon);//Devuelve la imagen convertida en el espacio de color escala de grises.
//        imshow("gris",imgClon);
        bloquesC1=this->objImagen->bloques8x8(imgClon);//resive bloques 8x8.
        bloqueDCTC1=calcularDCT(bloquesC1);//Calcula la Discrete Cosine Transform DCT en escala de grises.
        this->bloqueCuanC1=calcularCuantizacion(bloqueDCTC1,1);//Se multiplica las matrices de la cuantizacion para restaurar sus valores en escala de grises.
        leerCoefAC();//Recupera los bits codificado de longitud 23 por fila, aplicando el metodo de Least Significant Bit.

    }
    //Comprueba que tipo de espacio de color se selecciono para la recuoeracion del mensaje.
    if (ui->rbtnYCrCb->isChecked()) {
        imgClon=objEspColor->convertirRGBYCrCb(imgClon);//Devuelve la imagen convertida en el espacio de color YCbCr.
//        imshow("YCrCb",imgClon);
        Mat gris(imgClon.rows,imgClon.cols,CV_8UC1);
        for (int i = 0; i < imgClon.rows; i++) {//El bucle recorre las filas de la imagen.
             for (int j = 0; j < imgClon.cols; j++) {//El bucle recorre las columnas de la imagen.
                  gris.at<uchar>(i,j)=(int)imgClon.data[imgClon.channels()*(imgClon.cols*i+j)+0];//Guarda el pixel en escala de grises
             }
       }
//        imshow("gris",gris);
        bloquesC1=this->objImagen->bloques8x8(gris);//resive bloques 8x8.
        bloqueDCTC1=calcularDCT(bloquesC1);//Calcula la Discrete Cosine Transform DCT en escala de grises.
        this->bloqueCuanC1=calcularCuantizacion(bloqueDCTC1,1);//Se multiplica las matrices de la cuantizacion para restaurar sus valores en escala de grises.
        leerCoefAC();//Recupera los bits codificado de longitud 23 por fila, aplicando el metodo de Least Significant Bit.
    }
    //Comprueba que tipo de espacio de color se selecciono para la recuoeracion del mensaje.
    if (ui->rbtnYUV->isChecked()) {
        imgClon=objEspColor->convertirRGBYUV(imgClon);//Devuelve la imagen convertida en el espacio de color YUV.
//        imshow("YCrCb",imgClon);
        Mat gris(imgClon.rows,imgClon.cols,CV_8UC1);
        for (int i = 0; i < imgClon.rows; i++) {//El bucle recorre las filas de la imagen.
             for (int j = 0; j < imgClon.cols; j++) {//El bucle recorre las columnas de la imagen.
                  gris.at<uchar>(i,j)=(int)imgClon.data[imgClon.channels()*(imgClon.cols*i+j)+0];//Guarda el pixel en escala de grises
             }
       }
//        imshow("gris",gris);
        bloquesC1=this->objImagen->bloques8x8(gris);//resive bloques 8x8.
        bloqueDCTC1=calcularDCT(bloquesC1);//Calcula la Discrete Cosine Transform DCT en escala de grises.
        this->bloqueCuanC1=calcularCuantizacion(bloqueDCTC1,1);//Se multiplica las matrices de la cuantizacion para restaurar sus valores en escala de grises.
        leerCoefAC();//Recupera los bits codificado de longitud 23 por fila, aplicando el metodo de Least Significant Bit.
    }


}

//Este metodo leerCoefAC, recupera los bits codificados aplicando Least Significant Bit de cada coeficiente
//recorriendo la matriz o bloque 8x8 en zig-zag.
void dominioFrecuencial::leerCoefAC()
{
    QString matriz;
    int cont=0;
    QString cadena;
    bool parar=false;
    objNpad=new notepad();//Inicializar la clase notepad.
    QString fichero="C:\\Users\\FERNANDO\\Documents\\MATLAB\\golay\\golay\\for_testing\\limite.txt";
    QString limite=objNpad->readOnly(fichero);//Carga la .txt los binarios codificados.
    objBin=new binarizar();
    for (int i = 0; i < this->bloqueCuanC1.size(); ++i) {//Este bucle recorre los bloques cuantificados.
        Mat bloque=this->bloqueCuanC1.at(i);//Carga los bloques por posicion.
        if (cadena!=limite) {//Verifica si la cadena limite es igual ala cadena.
            if (cadena.length()==45) {//Comprueba si es igual para dar un salto de linea.
                cout<<"cadena"<<cadena.toStdString()<<endl;
                matriz.append(cadena);//Concadena los bits.
                matriz.append("\n");//Concadena el salto de linea.
                cadena="";
            }
            int coef=bloque.at<float>(0,1);//Almacena el coeficiente.
            if (coef<0) {//Comprueba si el coeficiente es negativo.
                coef=coef*-1;//Convierte coeficiente negativo en positivo
                QString byte=objBin->getByte(coef);//Devuelve el byte del coeficiente.
                cout<<byte.toStdString()<<endl;
                cadena.append(byte.at(7).toLatin1());//Extrae el ultimo bit, aplicando least Significant Bit.
                if (cadena.length()<45) {//Comprueba si es menor para dar espacios.
                    cadena.append(" ");
                }
                cout<<"cadena"<<cadena.toStdString()<<endl;
            }else{
                QString byte=objBin->getByte(coef);//Devuelve el byte del coeficiente.
                cout<<byte.toStdString()<<endl;
                cadena.append(byte.at(7).toLatin1());//Extrae el ultimo bit, aplicando least Significant Bit.
                if (cadena.length()<45) {//Comprueba si es menor para dar espacios.
                    cadena.append(" ");
                }
                cout<<"cadena"<<cadena.toStdString()<<endl;

            }
        }else{
            break;
        }

        if (cadena!=limite) {//Verifica si la cadena limite es igual ala cadena.
            if (cadena.length()==45) {//Comprueba si es igual para dar un salto de linea.
                cout<<cadena.toStdString()<<endl;
                matriz.append(cadena);//Concadena los bits.
                matriz.append("\n");//Concadena el salto de linea.
                cadena="";
            }
            int coef=bloque.at<float>(1,0);//Almacena el coeficiente.
            if (coef<0) {//Comprueba si el coeficiente es negativo.
                coef=coef*-1;//Convierte coeficiente negativo en positivo
                QString byte=objBin->getByte(coef);//Devuelve el byte del coeficiente.
                cout<<byte.toStdString()<<endl;
                cadena.append(byte.at(7).toLatin1());//Extrae el ultimo bit, aplicando least Significant Bit.
                if (cadena.length()<45) {//Comprueba si es menor para dar espacios.
                    cadena.append(" ");
                }
                cout<<"cadena"<<cadena.toStdString()<<endl;
            }else{
                QString byte=objBin->getByte(coef);//Devuelve el byte del coeficiente.
                cout<<byte.toStdString()<<endl;
                cadena.append(byte.at(7).toLatin1());//Extrae el ultimo bit, aplicando least Significant Bit.
                if (cadena.length()<45) {//Comprueba si es menor para dar espacios.
                    cadena.append(" ");
                }
                cout<<"cadena"<<cadena.toStdString()<<endl;
            }
        }else{
            break;
        }
        if (cadena!=limite) {//Verifica si la cadena limite es igual ala cadena.
            if (cadena.length()==45) {//Comprueba si es igual para dar un salto de linea.
                cout<<cadena.toStdString()<<endl;
                matriz.append(cadena);//Concadena los bits.
                matriz.append("\n");//Concadena el salto de linea.
                cadena="";
            }
            int coef=bloque.at<float>(2,0);//Almacena el coeficiente.
            if (coef<0) {//Comprueba si el coeficiente es negativo.
                coef=coef*-1;//Convierte coeficiente negativo en positivo
                QString byte=objBin->getByte(coef);//Devuelve el byte del coeficiente.
                cout<<byte.toStdString()<<endl;
                cadena.append(byte.at(7).toLatin1());//Extrae el ultimo bit, aplicando least Significant Bit.
                if (cadena.length()<45) {//Comprueba si es menor para dar espacios.
                    cadena.append(" ");
                }
                cout<<"cadena"<<cadena.toStdString()<<endl;
            }else{
                QString byte=objBin->getByte(coef);//Devuelve el byte del coeficiente.
                cout<<byte.toStdString()<<endl;
                cadena.append(byte.at(7).toLatin1());//Extrae el ultimo bit, aplicando least Significant Bit.
                if (cadena.length()<45) {//Comprueba si es menor para dar espacios.
                    cadena.append(" ");
                }
                cout<<"cadena"<<cadena.toStdString()<<endl;

            }
        }else{
            break;
        }
        if (cadena!=limite) {//Verifica si la cadena limite es igual ala cadena.
            if (cadena.length()==45) {//Comprueba si es igual para dar un salto de linea.
                cout<<cadena.toStdString()<<endl;
                matriz.append(cadena);//Concadena los bits.
                matriz.append("\n");//Concadena el salto de linea.
                cadena="";
            }
            int coef=bloque.at<float>(1,1);//Almacena el coeficiente.
            if (coef<0) {//Comprueba si el coeficiente es negativo.
                coef=coef*-1;//Convierte coeficiente negativo en positivo
                QString byte=objBin->getByte(coef);//Devuelve el byte del coeficiente.
                cout<<byte.toStdString()<<endl;
                cadena.append(byte.at(7).toLatin1());//Extrae el ultimo bit, aplicando least Significant Bit.
                if (cadena.length()<45) {//Comprueba si es menor para dar espacios.
                    cadena.append(" ");
                }
                cout<<"cadena"<<cadena.toStdString()<<endl;
            }else{
                QString byte=objBin->getByte(coef);//Devuelve el byte del coeficiente.
                cout<<byte.toStdString()<<endl;
                cadena.append(byte.at(7).toLatin1());//Extrae el ultimo bit, aplicando least Significant Bit.
                if (cadena.length()<45) {//Comprueba si es menor para dar espacios.
                    cadena.append(" ");
                }
                cout<<"cadena"<<cadena.toStdString()<<endl;

            }
        }else{
            break;
        }
        if (cadena!=limite) {//Verifica si la cadena limite es igual ala cadena.
            if (cadena.length()==45) {//Comprueba si es igual para dar un salto de linea.
                cout<<cadena.toStdString()<<endl;
                matriz.append(cadena);//Concadena los bits.
                matriz.append("\n");//Concadena el salto de linea.
                cadena="";
            }
            int coef=bloque.at<float>(0,2);//Almacena el coeficiente.
            if (coef<0) {//Comprueba si el coeficiente es negativo.
                coef=coef*-1;//Convierte coeficiente negativo en positivo
                QString byte=objBin->getByte(coef);//Devuelve el byte del coeficiente.
                cout<<byte.toStdString()<<endl;
                cadena.append(byte.at(7).toLatin1());//Extrae el ultimo bit, aplicando least Significant Bit.
                if (cadena.length()<45) {//Comprueba si es menor para dar espacios.
                    cadena.append(" ");
                }
                cout<<"cadena"<<cadena.toStdString()<<endl;
            }else{
                QString byte=objBin->getByte(coef);//Devuelve el byte del coeficiente.
                cout<<byte.toStdString()<<endl;
                cadena.append(byte.at(7).toLatin1());//Extrae el ultimo bit, aplicando least Significant Bit.
                if (cadena.length()<45) {//Comprueba si es menor para dar espacios.
                    cadena.append(" ");
                }
                cout<<"cadena"<<cadena.toStdString()<<endl;

            }
        }else{
            break;
        }
        if (cadena!=limite) {//Verifica si la cadena limite es igual ala cadena.
            if (cadena.length()==45) {//Comprueba si es igual para dar un salto de linea.
                cout<<cadena.toStdString()<<endl;
                matriz.append(cadena);//Concadena los bits.
                matriz.append("\n");//Concadena el salto de linea.
                cadena="";
            }
            int coef=bloque.at<float>(0,3);//Almacena el coeficiente.
            if (coef<0) {//Comprueba si el coeficiente es negativo.
                coef=coef*-1;//Convierte coeficiente negativo en positivo
                QString byte=objBin->getByte(coef);//Devuelve el byte del coeficiente.
                cout<<byte.toStdString()<<endl;
                cadena.append(byte.at(7).toLatin1());//Extrae el ultimo bit, aplicando least Significant Bit.
                if (cadena.length()<45) {//Comprueba si es menor para dar espacios.
                    cadena.append(" ");
                }
                cout<<"cadena"<<cadena.toStdString()<<endl;
            }else{
                QString byte=objBin->getByte(coef);//Devuelve el byte del coeficiente.
                cout<<byte.toStdString()<<endl;
                cadena.append(byte.at(7).toLatin1());//Extrae el ultimo bit, aplicando least Significant Bit.
                if (cadena.length()<45) {//Comprueba si es menor para dar espacios.
                    cadena.append(" ");
                }
                cout<<"cadena"<<cadena.toStdString()<<endl;

            }
        }else{
            break;
        }
        if (cadena!=limite) {//Verifica si la cadena limite es igual ala cadena.
            if (cadena.length()==45) {//Comprueba si es igual para dar un salto de linea.
                cout<<cadena.toStdString()<<endl;
                matriz.append(cadena);//Concadena los bits.
                matriz.append("\n");
                cadena="";
            }
            int coef=bloque.at<float>(1,2);//Almacena el coeficiente.
            if (coef<0) {//Comprueba si el coeficiente es negativo.
                coef=coef*-1;//Convierte coeficiente negativo en positivo
                QString byte=objBin->getByte(coef);//Devuelve el byte del coeficiente.
                cout<<byte.toStdString()<<endl;
                cadena.append(byte.at(7).toLatin1());//Extrae el ultimo bit, aplicando least Significant Bit.
                if (cadena.length()<45) {//Comprueba si es menor para dar espacios.
                    cadena.append(" ");
                }
                cout<<"cadena"<<cadena.toStdString()<<endl;
            }else{
                QString byte=objBin->getByte(coef);//Devuelve el byte del coeficiente.
                cout<<byte.toStdString()<<endl;
                cadena.append(byte.at(7).toLatin1());//Extrae el ultimo bit, aplicando least Significant Bit.
                if (cadena.length()<45) {//Comprueba si es menor para dar espacios.
                    cadena.append(" ");
                }
                cout<<"cadena"<<cadena.toStdString()<<endl;

            }
        }else{
            break;
        }
        if (cadena!=limite) {//Verifica si la cadena limite es igual ala cadena.
            if (cadena.length()==45) {//Comprueba si es igual para dar un salto de linea.
                cout<<cadena.toStdString()<<endl;
                matriz.append(cadena);//Concadena los bits.
                matriz.append("\n");
                cadena="";
            }
            int coef=bloque.at<float>(2,1);//Almacena el coeficiente.
            if (coef<0) {//Comprueba si el coeficiente es negativo.
                coef=coef*-1;//Convierte coeficiente negativo en positivo.
                QString byte=objBin->getByte(coef);//Devuelve el byte del coeficiente.
                cout<<byte.toStdString()<<endl;
                cadena.append(byte.at(7).toLatin1());//Extrae el ultimo bit, aplicando least Significant Bit.
                if (cadena.length()<45) {//Comprueba si es menor para dar espacios.
                    cadena.append(" ");
                }
                cout<<"cadena"<<cadena.toStdString()<<endl;
            }else{
                QString byte=objBin->getByte(coef);//Devuelve el byte del coeficiente.
                cout<<byte.toStdString()<<endl;
                cadena.append(byte.at(7).toLatin1());//Extrae el ultimo bit, aplicando least Significant Bit.
                if (cadena.length()<45) {//Comprueba si es menor para dar espacios.
                    cadena.append(" ");
                }
                cout<<"cadena"<<cadena.toStdString()<<endl;
            }
        }else{
            break;
        }

    }
     cout<<"resultado:"<<matriz.toStdString()<<endl;
     fichero="codigo_extraido.txt";
     objNpad->writeOnly(matriz,fichero);//Escribe toda la matriz en un archivo .txt
     QMessageBox::information(this,tr("Información"),tr("El mensaje se recupero con satisfacción."));
}

//Este metodo calcularDCT, calcula la formula DCT por cada pixel, transformandolo en frecuencias.
QList<Mat> dominioFrecuencial::calcularDCT(QList<Mat> bloquesC1)
{

    QList<Mat> bloqueDCT;
    double por=0;
    for (int i = 0; i < bloquesC1.size(); i++) {//Este bucle recorrelos bloques 8x8
        Mat bloque=bloquesC1.at(i);//Guarda el bloque 8x8.
        Mat bloqueSalida;
        dct(bloque,bloqueSalida);//Calcula el DCT y lo almacena en el bloqueSalida.
        bloqueDCT.push_back(bloqueSalida);//Se guarda el coeficiente en una lista.
        por=(double)i/(double)(bloquesC1.size()-1);
        ui->pBarra->setValue(round(por*100));
        ui->lblProceso->setText("Calculando DCT .....");
    }


    return bloqueDCT;
}

//Este metodo calcularCuantizacion, se aplica con el fin de llenar de ceros las matriz 8x8
//para no tener perdida de datos.
QList<Mat> dominioFrecuencial::calcularCuantizacion(QList<Mat> bloqueDCTC1,int opcion)
{
    //dividir cuantificacion
   int div;
   double por=0;
   QList<Mat> bloqueCuanC12;
   for (int i = 0; i < bloqueDCTC1.size(); ++i) {//Este bucle recorre cada bloque 8x8.
       Mat bloque=bloqueDCTC1.at(i);
       for (int j = 0; j < bloque.rows; ++j) {//Este bucle recorre los coeficientes de cada bloque 8x8.
           for (int k = 0; k < bloque.cols; ++k) {
               if (opcion==1) {//Comprueba si de tipo 1 para escala de grises, sino es crominancia.
                   div=round(bloque.at<float>(j,k)/objCuant->convertirM2D_IMG().at<int>(j,k));//Se procede a dividir el coeficiente con el valor de la matriz Standar JPEG.
                   bloque.at<float>(j,k)=div;//Se reemplaza el coeficiente cuantificado.
               }else{
                   div=round(bloque.at<float>(j,k)/objCuant->convertirM2D_CrCb().at<int>(j,k));//Se procede a dividir el coeficiente con el valor de la matriz Standar JPEG a color.
                   bloque.at<float>(j,k)=div;//Se reemplaza el coeficiente cuantificado.
               }

           }
       }
       bloqueCuanC12.push_back(bloque);//Almacena el bloque 8x8 cuantificado
       por=(double)i/(double)(bloqueDCTC1.size()-1);
       ui->pBarra->setValue(round(por*100));
       ui->lblProceso->setText("Calculando Cuantización ....");
   }

   return bloqueCuanC12;

}

//Este metodo calcularCuantizacion, se aplica con el fin de restaurar los coeficientes.
QList<Mat> dominioFrecuencial::calcularCuantizacionMult(QList<Mat> bloqueCuanC1,int opcion)
{
    int mult;
    QList<Mat> bloqueMult;
    double por=0;
    for (int i = 0; i < bloqueCuanC1.size(); ++i) {//Este bucle recorre cada bloque 8x8.
        Mat bloque=bloqueCuanC1.at(i);
        for (int j = 0; j < bloque.rows; ++j) {//Este bucle recorre los coeficientes de cada bloque 8x8.
            for (int k = 0; k < bloque.cols; ++k) {
                if (opcion==1) {//Comprueba si de tipo 1 para escala de grises, sino es crominancia.
                    mult=bloque.at<float>(j,k)*objCuant->convertirM2D_IMG().at<int>(j,k);
                    bloque.at<float>(j,k)=mult;
                }else{
                    mult=bloque.at<float>(j,k)*objCuant->convertirM2D_CrCb().at<int>(j,k);
                    bloque.at<float>(j,k)=mult;
                }

            }
        }
        bloqueMult.push_back(bloque);//Almacena el bloque 8x8 cuantificado
        por=(double)i/(double)(bloqueCuanC1.size()-1);
        ui->pBarra->setValue(round(por*100));
        ui->lblProceso->setText("Multiplicar Cuantización....");
//                cout<<bloque<<endl;
    }

    return bloqueMult;


}

//Este metodo calcularIDCT, calcula la formula IDCT por cada coeficiente, transformandolo en pixel.
QList<Mat> dominioFrecuencial::calcularIDCT(QList<Mat> bloqueMultC1)
{
    QList<Mat> bloqueIDCT;
    double por=0;
    for (int i = 0; i < bloqueMultC1.size(); i++) {
        Mat bloque=bloqueMultC1.at(i);
        Mat bloqueSalida;
        idct(bloque,bloqueSalida);
        bloqueIDCT.push_back(bloqueSalida);
        por=(double)i/(double)(bloqueMultC1.size()-1);
        ui->pBarra->setValue(round(por*100));
        ui->lblProceso->setText("Calcular IDCT....");
//                cout<<bloqueSalida<<endl;
    }

    return bloqueIDCT;
}

//Este metodo aumentar, aumenta a todos los pixeles 128, para poder reconstruir la imagem.
QList<Mat> dominioFrecuencial::aumentar(QList<Mat> bloqueIDCTC1)
{
    QList<Mat> bloqueSumar;
     double por=0;
    for (int i = 0; i < bloqueIDCTC1.size(); i++) {
        Mat bloque=bloqueIDCTC1.at(i);
        add(bloque,128.0,bloque);
        bloqueSumar.push_back(bloque);
         por=(double)i/(double)(bloqueIDCTC1.size()-1);
        ui->pBarra->setValue(round(por*100));
        ui->lblProceso->setText("Aumentando 128....");
    }
    return bloqueSumar;

}


//Este metodo modificarCoefAC, modifica los los coeficientes binarizados aplicando Least Significant Bit
//recorriendo la matriz o bloque 8x8 en zig-zag.
void dominioFrecuencial::modificarCoefAC()
{
    QString fichero="C:\\Users\\FERNANDO\\Documents\\MATLAB\\golay\\golay\\for_testing\\codificado.txt";
    objNpad=new notepad();//Inicializar la clase notepad.
    QString codificado= objNpad->readOnly(fichero);//Lee el codigo codificado con ayuda del Codigo binario lineal golay(23,12)
    int cont=0;
    double por=0;
    int cant=this->bloqueCuanC1.size();
    for (int i = 0; i < this->bloqueCuanC1.size(); i++) {//Este bucle recorre los bloques cuantificados.
        Mat bloque=this->bloqueCuanC1.at(i);//Carga los bloques por posicion.
        cout<<bloque<<endl;
        objLsb=new lsb();//Inicializar la clase lsb.
        if (cont<codificado.length()) {//Comprueba que el contador sea menor ala longitud del mensaje codificado.
            int coef=(int)bloque.at<float>(0,1);//Almacena el coeficiente.
            if (coef<0) {//Comprueba si el coeficiente es negativo.
                int abs=coef*-1;//Convierte coeficiente negativo en positivo.
                QString strBit=codificado.at(cont);//Obtenemos el bit.
                int bit=strBit.toInt();//Se convierte en tipo integer.
                int decimal=objLsb->alterarAC(abs,bit);//Se modifica el ultimo bit del coeficiente aplicando least Significant Bit.
                decimal=decimal*-1;//Convierte el decimal positivo a negativo.
                bloque.at<float>(0,1)=decimal;//Se reemplaza el coeficiente.
                cont++;
                this->bloqueCuanC1.replace(i,bloque);//Se reemplaza el bloque 8x8 original por el modificado.

            }else{
                QString strBit=codificado.at(cont);//Obtenemos el bit.
                int bit=strBit.toInt();//Se convierte en tipo integer.
                int decimal=objLsb->alterarAC(coef,bit);//Se modifica el ultimo bit del coeficiente aplicando least Significant Bit.
                bloque.at<float>(0,1)=decimal;//Se reemplaza el coeficiente.
                cont++;
                this->bloqueCuanC1.replace(i,bloque);//Se reemplaza el bloque 8x8 original por el modificado.

            }
        }else{
            cout<<bloque<<endl;
            break;
        }
        if (cont<codificado.length()) {//Comprueba que el contador sea menor ala longitud del mensaje codificado.
            int coef=(int)bloque.at<float>(1,0);//Almacena el coeficiente.
            if (coef<0) {//Comprueba si el coeficiente es negativo.
                int abs=coef*-1;//Convierte coeficiente negativo en positivo.
                QString strBit=codificado.at(cont);//Obtenemos el bit.
                int bit=strBit.toInt();//Se convierte en tipo integer.
                int decimal=objLsb->alterarAC(abs,bit);//Se modifica el ultimo bit del coeficiente aplicando least Significant Bit.
                decimal=decimal*-1;//Convierte el decimal positivo a negativo.
                bloque.at<float>(1,0)=decimal;//Se reemplaza el coeficiente.
                cont++;
                this->bloqueCuanC1.replace(i,bloque);//Se reemplaza el bloque 8x8 original por el modificado.
            }else{
                QString strBit=codificado.at(cont);//Obtenemos el bit.
                int bit=strBit.toInt();//Se convierte en tipo integer.
                int decimal=objLsb->alterarAC(coef,bit);//Se modifica el ultimo bit del coeficiente aplicando least Significant Bit.
                bloque.at<float>(1,0)=decimal;//Se reemplaza el coeficiente.
                cont++;
                this->bloqueCuanC1.replace(i,bloque);//Se reemplaza el bloque 8x8 original por el modificado.
            }
        }else{
            cout<<bloque<<endl;
            break;
        }
        if (cont<codificado.length()) {//Comprueba que el contador sea menor ala longitud del mensaje codificado.
            int coef=(int)bloque.at<float>(2,0);//Almacena el coeficiente.
            if (coef<0) {//Comprueba si el coeficiente es negativo.
                int abs=coef*-1;//Convierte coeficiente negativo en positivo.
                QString strBit=codificado.at(cont);//Obtenemos el bit.
                int bit=strBit.toInt();//Se convierte en tipo integer.
                int decimal=objLsb->alterarAC(abs,bit);//Se modifica el ultimo bit del coeficiente aplicando least Significant Bit.
                decimal=decimal*-1;//Convierte el decimal positivo a negativo.
                bloque.at<float>(2,0)=decimal;//Se reemplaza el coeficiente.
                cont++;
                this->bloqueCuanC1.replace(i,bloque);//Se reemplaza el bloque 8x8 original por el modificado.
            }else{
                QString strBit=codificado.at(cont);//Obtenemos el bit.
                int bit=strBit.toInt();//Se convierte en tipo integer.
                int decimal=objLsb->alterarAC(coef,bit);//Se modifica el ultimo bit del coeficiente aplicando least Significant Bit.
                bloque.at<float>(2,0)=decimal;//Se reemplaza el coeficiente.
                cont++;
                this->bloqueCuanC1.replace(i,bloque);//Se reemplaza el bloque 8x8 original por el modificado.
            }
        }else{
            cout<<bloque<<endl;
            break;
        }
        if (cont<codificado.length()) {//Comprueba que el contador sea menor ala longitud del mensaje codificado.
            int coef=(int)bloque.at<float>(1,1);//Almacena el coeficiente.
            if (coef<0) {//Comprueba si el coeficiente es negativo.
                int abs=coef*-1;//Convierte coeficiente negativo en positivo.
                QString strBit=codificado.at(cont);//Obtenemos el bit.
                int bit=strBit.toInt();//Se convierte en tipo integer.
                int decimal=objLsb->alterarAC(abs,bit);//Se modifica el ultimo bit del coeficiente aplicando least Significant Bit.
                decimal=decimal*-1;//Convierte el decimal positivo a negativo.
                bloque.at<float>(1,1)=decimal;//Se reemplaza el coeficiente.
                cont++;
                this->bloqueCuanC1.replace(i,bloque);//Se reemplaza el bloque 8x8 original por el modificado.
            }else{
                QString strBit=codificado.at(cont);//Obtenemos el bit.
                int bit=strBit.toInt();//Se convierte en tipo integer.
                int decimal=objLsb->alterarAC(coef,bit);//Se modifica el ultimo bit del coeficiente aplicando least Significant Bit.
                bloque.at<float>(1,1)=decimal;//Se reemplaza el coeficiente.
                cont++;
                this->bloqueCuanC1.replace(i,bloque);//Se reemplaza el bloque 8x8 original por el modificado.
            }
        }else{
            cout<<bloque<<endl;
            break;
        }
        if (cont<codificado.length()) {//Comprueba que el contador sea menor ala longitud del mensaje codificado.
            int coef=(int)bloque.at<float>(0,2);//Almacena el coeficiente.
            if (coef<0) {//Comprueba si el coeficiente es negativo.
                int abs=coef*-1;//Convierte coeficiente negativo en positivo.
                QString strBit=codificado.at(cont);
                int bit=strBit.toInt();//Se convierte en tipo integer.
                int decimal=objLsb->alterarAC(abs,bit);//Se modifica el ultimo bit del coeficiente aplicando least Significant Bit.
                decimal=decimal*-1;//Convierte el decimal positivo a negativo.
                bloque.at<float>(0,2)=decimal;//Se reemplaza el coeficiente.
                cont++;
                this->bloqueCuanC1.replace(i,bloque);//Se modifica el ultimo bit del coeficiente aplicando least Significant Bit.
            }else{
                QString strBit=codificado.at(cont);
                int bit=strBit.toInt();//Se convierte en tipo integer.
                int decimal=objLsb->alterarAC(coef,bit);
                bloque.at<float>(0,2)=decimal;//Se reemplaza el coeficiente.
                cont++;
                this->bloqueCuanC1.replace(i,bloque);//Se reemplaza el bloque 8x8 original por el modificado.
            }
        }else{
            cout<<bloque<<endl;
            break;
        }
        if (cont<codificado.length()) {//Comprueba que el contador sea menor ala longitud del mensaje codificado.
            int coef=(int)bloque.at<float>(0,3);//Almacena el coeficiente.
            if (coef<0) {//Comprueba si el coeficiente es negativo.
                int abs=coef*-1;//Convierte coeficiente negativo en positivo.
                QString strBit=codificado.at(cont);//Obtenemos el bit.
                int bit=strBit.toInt();//Se convierte en tipo integer.
                int decimal=objLsb->alterarAC(abs,bit);//Se modifica el ultimo bit del coeficiente aplicando least Significant Bit.
                decimal=decimal*-1;//Convierte el decimal positivo a negativo.
                bloque.at<float>(0,3)=decimal;//Se reemplaza el coeficiente.
                cont++;
                this->bloqueCuanC1.replace(i,bloque);//Se reemplaza el bloque 8x8 original por el modificado.
            }else{
                QString strBit=codificado.at(cont);//Obtenemos el bit.
                int bit=strBit.toInt();//Se convierte en tipo integer.
                int decimal=objLsb->alterarAC(coef,bit);//Se modifica el ultimo bit del coeficiente aplicando least Significant Bit.
                bloque.at<float>(0,3)=decimal;//Se reemplaza el coeficiente.
                cont++;
                this->bloqueCuanC1.replace(i,bloque);//Se reemplaza el bloque 8x8 original por el modificado.
            }
        }else{
            cout<<bloque<<endl;
            break;
        }
        if (cont<codificado.length()) {//Comprueba que el contador sea menor ala longitud del mensaje codificado.
            int coef=(int)bloque.at<float>(1,2);//Almacena el coeficiente.
            if (coef<0) {//Comprueba si el coeficiente es negativo.
                int abs=coef*-1;//Convierte coeficiente negativo en positivo.
                QString strBit=codificado.at(cont);//Obtenemos el bit.
                int bit=strBit.toInt();//Se convierte en tipo integer.
                int decimal=objLsb->alterarAC(abs,bit);//Se modifica el ultimo bit del coeficiente aplicando least Significant Bit.
                decimal=decimal*-1;
                bloque.at<float>(1,2)=decimal;//Se reemplaza el coeficiente.
                cont++;
                this->bloqueCuanC1.replace(i,bloque);//Se reemplaza el bloque 8x8 original por el modificado.
            }else{
                QString strBit=codificado.at(cont);//Obtenemos el bit.
                int bit=strBit.toInt();//Se convierte en tipo integer.
                int decimal=objLsb->alterarAC(coef,bit);//Se modifica el ultimo bit del coeficiente aplicando least Significant Bit.
                bloque.at<float>(1,2)=decimal;//Se reemplaza el coeficiente.
                cont++;
                this->bloqueCuanC1.replace(i,bloque);//Se reemplaza el bloque 8x8 original por el modificado.
            }
        }else{
            cout<<bloque<<endl;
            break;
        }
        if (cont<codificado.length()) {//Comprueba que el contador sea menor ala longitud del mensaje codificado.
            int coef=(int)bloque.at<float>(2,1);//Almacena el coeficiente.
            if (coef<0) {//Comprueba si el coeficiente es negativo.
                int abs=coef*-1;//Convierte coeficiente negativo en positivo.
                QString strBit=codificado.at(cont);//Obtenemos el bit.
                int bit=strBit.toInt();//Se convierte en tipo integer.
                int decimal=objLsb->alterarAC(abs,bit);//Se modifica el ultimo bit del coeficiente aplicando least Significant Bit.
                decimal=decimal*-1;
                bloque.at<float>(2,1)=decimal;//Se reemplaza el coeficiente.
                cont++;
                this->bloqueCuanC1.replace(i,bloque);//Se reemplaza el bloque 8x8 original por el modificado.
            }else{
                QString strBit=codificado.at(cont);//Obtenemos el bit.
                int bit=strBit.toInt();//Se convierte en tipo integer.
                int decimal=objLsb->alterarAC(coef,bit);//Se modifica el ultimo bit del coeficiente aplicando least Significant Bit.
                bloque.at<float>(2,1)=decimal;//Se reemplaza el coeficiente.
                cont++;
                this->bloqueCuanC1.replace(i,bloque);//Se reemplaza el bloque 8x8 original por el modificado.
            }
        }else{
            cout<<bloque<<endl;
            break;
        }

          cout<<bloque<<endl;
          por=(double)i/(double)(cant-1);
          ui->pBarra->setValue(round(por*100));
          ui->lblProceso->setText("Modificando coefientes AC ....");
    }
    ui->pBarra->setValue(100);

    int resta=codificado.length()-23;//Le resto la longitud de 23 al codifico para el codigo limite.
    QString lim;
    for (int i = codificado.length(); i >resta; i--) {//Este bucle recorre el codigo limite.
        lim.prepend(codificado.at(i-1));
        if (i-1>resta) {
            lim.prepend(" ");
        }
    }
    fichero="limite.txt";
    objNpad->writeOnly(lim,fichero);//Lo ecribe en un archivo .txt y guarda el limite.

}

void dominioFrecuencial::on_pbtnMostrar_clicked()
{
    objNpad=new notepad();//Inicializar la clase notepad.
    QString fichero="C:\\Users\\FERNANDO\\Documents\\MATLAB\\golay\\golay\\for_testing\\decodificado.txt";
    QString decodificado=objNpad->readOnly(fichero);//Cargar el fichero decodificado
    objLsb=new lsb();//Inicializar la clase lsb.
    int cont=0;
    QString byte;
    QString mensaje;
    for (int i = 0; i < decodificado.length(); ++i) {//Este bucle recorre el mensaje binarizado decodificado.
        if (cont==8) {//Se comprueba si longitud su tamaño es de 8 bits.
            cout<<byte.toStdString()<<endl;
           int decimal=objLsb->convertirBinarioDecimal(byte);//Convierte el byte en decimal.
           char caracter=decimal;//El decimal se convierte en un caracter.
           mensaje.append(caracter);//Se concadena el caracter
           cont=0;
           byte="";
        }
        byte.append(decodificado.at(i));//Se concadena el bit del mensaje decodificado.
        cont++;
    }
    ui->ptxtMensaje->setPlainText(mensaje);//Se muestra el mensaje restaurado.
}
