#include "imagen.h"

//Este contructor carga como parametro el ruta de la imagen para ser cargada
imagen::imagen(QString nombreArhivo): imgOriginal(imread(nombreArhivo.toStdString()))
{
}

imagen::imagen()
{

}
//Este metodo getImgOriginal devuleve la imagen original
Mat imagen::getImgOriginal()
{
    return imgOriginal;
}
//Este metodo setImgOriginal reemplaza la imagen original

void imagen::setImgOriginal(Mat img)
{
    this->imgOriginal=img;
}

//Este metodo agregarPixelIO agrega una lista de pixeles de la imagenes
//de 3 canales.
void imagen::agregarPixelIO()
{
    for (int i = 0; i < getAlto(); i++) {
        for (int j = 0; j < getAncho(); j++) {
            this->listaPixelRGBIO.push_back(agregarRGB(i,j));//Agrega los pixeles de la imagen en una lista.
        }
    }
}

//Este metodo agregarPixel agrega en una lista los pixeles de la imagen de un canal
QList<int> imagen::agregarPixel()
{
    QList<int> pixeles;
    for (int i = 0; i < getAlto(); i++) {
        for (int j = 0; j < getAncho(); j++) {
            pixeles.push_back((int)this->imgOriginal.at<uchar>(i,j));//Agrega los pixeles en una lista

        }
    }
    return pixeles;
}

//Este metodo getListaPixelRGBIO devuelve la lista de los pixeles de las imagenes de 3 canales
QList<QList<int> > imagen::getListaPixelRGBIO()
{
    return this->listaPixelRGBIO;
}
//Este metodo getAncho devuelve el ancho de la imagen
int imagen::getAncho()
{
    return imgOriginal.cols;
}

//Este metodo getAlto devuelve el alto de la imagen
int imagen::getAlto()
{
    return imgOriginal.rows;
}

//Este metodo agregarRGB agrega todos los pixeles en una lista de las imagenes de 3 canales
QList<int> imagen::agregarRGB(int fila, int columna)
{
    QList<int> RGB;
    RGB.clear();
    int b=this->imgOriginal.data[this->imgOriginal.channels()*(this->imgOriginal.cols*fila+columna)+0];
    RGB.push_back(b);
    int g=this->imgOriginal.data[this->imgOriginal.channels()*(this->imgOriginal.cols*fila+columna)+1];
    RGB.push_back(g);
    int r=this->imgOriginal.data[this->imgOriginal.channels()*(this->imgOriginal.cols*fila+columna)+2];
    RGB.push_back(r);
    return RGB;
}

//Este metodo bloques8x8, devuelve una lista de bloque o subimagenes de 8x8, se hace con el
//fin de evitar la pérdida de la calidad durante el procesamiento de la imagen.
QList<Mat> imagen::bloques8x8(Mat gray)
{
    int width=(gray.cols)/8;
    int height=(gray.rows)/8;
    int n=8;
    int w=width*n;
    int h=height*n;
    QList<Mat> bloques;
        for (int i = 0; i < h; i+=n) {
            for (int j = 0; j < w; j+=n) {
                Rect  r (j,  i,  8,  8);//formar bloque 8x8--Coge la coordenada de la esquina y se le asigna la longitud que ocupara en la imagen
                Mat bloque=gray(r);//bloque 8x8
                bloque.convertTo(bloque,CV_32FC1);
//                cout<<bloque<<endl;
                subtract(bloque,128.0,bloque);
//                cout<<bloque<<endl;
               bloques.push_back(bloque);
            }
        }
        return bloques;

}

//Este metodo reconstuirImgC1, devuelve la imagen reconstruida de un solo canal
Mat imagen::reconstuirImgC1(QList<Mat> bloqueSumar, int col, int row)
{
    int width=col/8;
    int height=row/8;
    int n=8;
    int w=width*n;
    int h=height*n;
    Mat imgNueva=Mat::zeros(Size(w,h), CV_8UC1);

    int cont=0;
    for (int j = 0; j <h; j+=n) {
        for (int k = 0; k < w; k+=n) {
            Mat bloque=bloqueSumar.at(cont);
            cout<<bloque<<endl;
            for (int p = 0; p < n; p++) {
                 for (int l = 0; l < n; l++) {
                      imgNueva.at<uchar>(j+p,k+l)=round(bloque.at<float>(p,l));
//                         cout<<(int) imgNueva5.at<uchar>(j+p,k+l)<<" -- "<<(int)bloque.at<float>(p,l)<<endl;
                  }
              }
            cont++;
          }
    }
    return imgNueva;
}

//Este metodo reconstuirImgC3, devuelve la imagen reconstruida de 3 canales.
Mat imagen::reconstuirImgC3(Mat c1, Mat c2, Mat c3, int col, int row)
{

    Mat imgNueva=Mat::zeros(Size(col,row), CV_8UC3);
    for (int i = 0; i < imgNueva.rows; ++i) {
        for (int j = 0; j < imgNueva.cols; ++j) {
            int Y=(int)c1.at<uchar>(i,j);
            int cR=(int)c2.at<uchar>(i,j);
            int cB=(int)c3.at<uchar>(i,j);
            imgNueva.data[imgNueva.channels()*(imgNueva.cols*i+j)+0]=Y;
            imgNueva.data[imgNueva.channels()*(imgNueva.cols*i+j)+1]=cR;
            imgNueva.data[imgNueva.channels()*(imgNueva.cols*i+j)+2]=cB;
        }

    }
    return imgNueva;
}
