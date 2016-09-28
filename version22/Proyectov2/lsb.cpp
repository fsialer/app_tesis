#include "lsb.h"
//El método cantidadMultiplo, devuelve la cantidad de la lista
//de los pixeles de la imagen hasta que sean multiplo de 3.
int lsb::cantidadMultiplo(int cantidad,int multiplo)
{
    do{
//        cout<<"por aqui "<<cantidadPixel<<endl;
        if (cantidad%multiplo==0) {
            cout<<"es multiplo de "<<multiplo<<":"<<cantidad<<endl;
        }else{
            cantidad=cantidad-1;
        }
    }while(cantidad%multiplo!=0);
    return cantidad;
}

//Este método convertirBinarioDecimal, devuelve un decimal que
//anteriormente era un byte (8 bits).
int lsb::convertirBinarioDecimal(QString byte)
{
    int sum=0;
    int num=7;
    cout<<"Aqui "<<byte.toStdString()<<endl;
    for (int i = 0; i < 8; i++) {
        if (byte.at(i).toLatin1()=='1') {//Comprueba si en la cadena de 8 bits existe algún '1'.

            cout<<sum<<"+"<<pow(2,num)<<"=";
            sum=sum+pow(2,num);//Calcula el decimal, teniendo en cuenta el exponente de base 2, según su
            //posición.
            cout<<sum<<endl;
        }
        num--;
    }
    return sum;

}



lsb::lsb()
{
    this->objBinariar=new binarizar();//inicializacion de la clase binarizar
}
int lsb::alterarAC(int decimalCoe, int bit)
{
    cout<<"===: "<<decimalCoe<<endl;
    cout<<"===: "<<bit<<endl;

 QString d=this->objBinariar->getByte(decimalCoe);
 cout<<"Byet original: "<<d.toStdString()<<endl;

    QString bit2;
    int decimal=0;

    bit2=QString::number(bit);
    QByteArray ba=bit2.toLatin1();
    const char *c=ba.data();
    d.replace(7,1,c);
    cout<<"Byte alterado: "<<d.toStdString()<<endl;
    decimal=convertirBinarioDecimal(d);
    return decimal;

}
//Este método alterarPixel, devuelve una lista con los pixeles alterados aplicando
//el metodo del Least Significant Bit.
QList<QList<int> > lsb::alterarPixel(QList<QList<int> > listaPixelRGBIO, QList<QList<int> > listaByteTexto)
{
    QString byte;
    QString bit;

    char caractSustituto;
    int k=0,p=0,l=1;
    int cantidadPixel=cantidadMultiplo(listaPixelRGBIO.size(),3);//Obtiene la cantidad de la lista de los pixeles
    //que sean multiplos de 3.
    int cantidadCaracteres=listaByteTexto.size()+1;//Se aumenta uno para el caracter especial para marcar el fin del texto oculto.
    int cantidadPixelEditar=cantidadCaracteres*3;//Se multiplica por 3 al cantidad de caracteres porque se usan 3 pixeles para
    //ocultar un caracter.
    int resta=cantidadPixelEditar-3;//Se resta uno por el caracter especial.
    if (cantidadPixelEditar<=cantidadPixel) {//Comprueba si la cantidadpixeles a editar es menor igual que la cantidad de pixeles.
        for (int i = 0; i < resta; i++) {//Este bucle recorre la cantidad de pixeles a editar.
            cout<<"============"<<endl;
            for (int j = 0; j < listaPixelRGBIO.value(i).size(); j++) {//Este bucle recorre los 3 canales por cada pixel.
                byte=objBinariar->getByte(listaPixelRGBIO.value(i).value(j));//Binariza el pixel
                cout<<"original: "<<listaPixelRGBIO.value(i).value(j)<<endl;
                cout<<byte.toStdString()<<endl;
                if (l==3) {//Comprueba si se utilizaron 3 pixeles para el ocultamiento del caracter.
                    if (j<2) {//Comprueba si se encuentra posicion 1 .
                        bit=QString::number(listaByteTexto.value(k).value(p));//Almacena el bit.
                        caractSustituto=bit.at(0).toLatin1();//Convierte el int en un char.
                        cout<<caractSustituto<<endl;
                        byte.replace(7,1,caractSustituto);//El byte binarizado se sustituye en la ultima posición
                        //del byte utilizando Least Significant Bit.
                        cout<<"sustituto:"<<byte.toStdString()<<endl;
                        listaPixelRGBIO[i][j]=convertirBinarioDecimal(byte);//Convierte el byte modificado en un decimal, y es sustituido
                        //por el nuevo decimal en la lista de los pixeles de la imagen.
                        cout<<"Modificado:"<<listaPixelRGBIO.value(i).value(j)<<endl;
                        p++;
                    }else{
                            k++;//Controla la posicion de los bytes.
                            p=0;//Controla la posicion de los bit de la lista de bytes.
                            l=0;//controla la cantidad de pixeles.
                    }
                }else{
                    bit=QString::number(listaByteTexto.value(k).value(p));//Almacena el bit.
                    caractSustituto=bit.at(0).toLatin1();//Convierte el int en un char.
                    cout<<caractSustituto<<endl;
                    byte.replace(7,1,caractSustituto);//El byte binarizado se sustituye en la ultima posición
                    //del byte utilizando Least Significant Bit.
                    cout<<"sustituto:"<<byte.toStdString()<<endl;
                     listaPixelRGBIO[i][j]=convertirBinarioDecimal(byte);//Convierte el byte modificado en un decimal, y es sustituido
                     //por el nuevo decimal en la lista de los pixeles de la imagen.
                    cout<<"Modificado:"<<listaPixelRGBIO.value(i).value(j)<<endl;
                    p++;
                }
            }
            l++;
        }
        l=1;
        cout<<"nuevo caracter"<<endl;
        int d=toascii('|');//Obtiene el decimal del caracter especial.
        QString byteCaracterfin;
        byteCaracterfin=objBinariar->getByte(d);//Binariza el decimal del caracter especial.
        QList<int> nuevo;
        nuevo.clear();
        for (int i = 0; i < byteCaracterfin.length(); i++) {
            nuevo.push_back((int)byteCaracterfin.at(i).digitValue());
            cout<<nuevo.value(i)<<endl;
        }
        cout<<d<<endl;
        for (int i = resta; i < cantidadPixelEditar; i++) {
            cout<<"========="<<endl;
            for (int j = 0; j < listaPixelRGBIO.value(i).size(); j++) {//Este bucle recorre los 3 canales por cada pixel.
                if (l==3) {//Comprueba si se utilizaron 3 pixeles para el ocultamiento del caracter.
                    byte=objBinariar->getByte(listaPixelRGBIO.value(i).value(j));//Binariza el pixel
                    cout<<"original: "<<listaPixelRGBIO.value(i).value(j)<<endl;
                    cout<<byte.toStdString()<<endl;
                    if (j<2) {//Comprueba si se encuentra posicion 1 .
                        bit=QString::number(nuevo.value(p));
                        caractSustituto=bit.at(0).toLatin1();
                        cout<<caractSustituto<<endl;
                        byte.replace(7,1,caractSustituto);//El byte binarizado se sustituye en la ultima posición
                        //del byte utilizando Least Significant Bit.
                        cout<<"sustituto:"<<byte.toStdString()<<endl;
                        listaPixelRGBIO[i][j]=convertirBinarioDecimal(byte);//Convierte el byte modificado en un decimal, y es sustituido
                        //por el nuevo decimal en la lista de los pixeles de la imagen.
                        cout<<"Modificado:"<<listaPixelRGBIO.value(i).value(j)<<endl;
                        p++;
                    }
                }else{
                    byte=objBinariar->getByte(listaPixelRGBIO.value(i).value(j));//Binariza el pixel
                    cout<<"original: "<<listaPixelRGBIO.value(i).value(j)<<endl;
                    cout<<byte.toStdString()<<endl;
                    bit=QString::number(nuevo.value(p));//Almacena el bit.
                    caractSustituto=bit.at(0).toLatin1();//Convierte el int en un char.
                    cout<<caractSustituto<<endl;
                    byte.replace(7,1,caractSustituto);//El byte binarizado se sustituye en la ultima posición
                    //del byte utilizando Least Significant Bit.
                    cout<<"sustituto:"<<byte.toStdString()<<endl;
                    listaPixelRGBIO[i][j]=convertirBinarioDecimal(byte);//Convierte el byte modificado en un decimal, y es sustituido
                            //por el nuevo decimal en la lista de los pixeles de la imagen.
                    cout<<"Modificado:"<<listaPixelRGBIO.value(i).value(j)<<endl;
                    p++;
                }
                }
            l++;
        }

    }
    return listaPixelRGBIO;

}

//Este método extraerInformacion, devuelve una String con el mensaje recuperado aplicando
//el metodo del Least Significant Bit para su extración.
QString lsb::extraerInformacion(QList<QList<int> > listaPixelRGBEI)
{
    QString texto="";
    QString byte;
    QString cadenaBit="";
    char caracter;
    bool parar=false;
    int decimal=0;
    int limitador=0;
    for (int i = 0; i < listaPixelRGBEI.size(); i++) {//bucle para recorrer los pixeles aletrados.
        for (int j = 0; j < listaPixelRGBEI.value(i).size(); j++) {//Recorrer los tres canales pixel.
            if (limitador<=7) {//Limitador para recuperar el bit de los pixeles alterados, y formar el byte.
                cout<<"decimal del byte: "<<listaPixelRGBEI.value(i).value(j)<<endl;
                byte=this->objBinariar->getByte(listaPixelRGBEI.value(i).value(j));//Envia el pixel, para posteriormente
                //convertir en un byte y almacenarlo.
                cout<<byte.toStdString()<<endl;
                cadenaBit=cadenaBit+byte.at(7).toLatin1();//Aplicamos least Significant Bit, para la recuperación del bit.
                cout<<"String nuevo: "<<cadenaBit.toStdString()<<endl;
                limitador++;
            }else{
                 decimal=convertirBinarioDecimal(cadenaBit);//Convertir el byte a un decimal.
                if (decimal==124) {//Comprobar si el decimal es igual decimal del caracter especial.
                    parar=true;
                }else{
                    limitador=0;
                    caracter=decimal;//Convertir el decimal en caracter.
                    texto=texto+caracter;//Concadenar el caracter.
                    cout<<"decimal final:"<<decimal<<endl;
                    cout<<"caracter final:"<<caracter<<endl;
                    cout<<"texto:"<<texto.toStdString()<<endl;

                    cadenaBit="";
                }
            }

//            if (limitador<=7) {
//                cout<<"cumple"<<endl;
//                cout<<"decimal del byte: "<<listaPixelRGBEI.value(i).value(j)<<endl;
//                byte=this->objBinariar->getByte(listaPixelRGBEI.value(i).value(j));
//                cadenaBit=cadenaBit+byte.at(7).toLatin1();
//               cout<<"String nuevo: "<<cadenaBit.toStdString()<<endl;
//                limitador++;
//            }else{
//              cout<<"Paso"<<endl;
//                limitador=0;
//                decimal=convertirBinarioDecimal(cadenaBit);
//                cadenaBit="";
//                if (decimal==124) {
//                   break;
//                  parar=true;
//              }else{
//                    caracter=decimal;

//                    cout<<"decimal:"<<decimal<<endl;
//                }
//            }
        }
        if (parar==true) {//Comprobar si es true, para poder detener la recuperación del mensaje.
            break;
        }
//        if (i==14) {
//            break;
//        }

    }
    return texto;
}

//Este método extraerInformacionGray, devuelve una String con el mensaje recuperado aplicando
//el metodo del Least Significant Bit para su extración.
QString lsb::extraerInformacionGray(QList<int> listaPixelGrayEI)
{
    QString texto="";
    QString byte;
    QString cadenaBit="";
    char caracter;
    bool parar=false;
    int decimal=0;
    int limitador=0;
    for (int i = 0; i < listaPixelGrayEI.size(); i++) {//bucle para recorrer los pixeles aletrados
        if (limitador<=7) {
            cout<<"decimal del byte: ["<<i<<"]"<<listaPixelGrayEI.value(i)<<endl;
            byte=this->objBinariar->getByte(listaPixelGrayEI.value(i));//Envia el pixel, para posteriormente
            //convertir en un byte y almacenarlo.
            cout<<byte.toStdString()<<endl;
            cadenaBit=cadenaBit+byte.at(7).toLatin1();//Aplicamos least Significant Bit, para la recuperación del bit.
            cout<<"String nuevo: "<<cadenaBit.toStdString()<<endl;
            limitador++;
        }else{
            decimal=convertirBinarioDecimal(cadenaBit);//Convertir el byte a un decimal.
            if (decimal==124) {//Comprobar si el decimal es igual decimal del caracter especial.
                parar=true;
            }else{
                limitador=0;
                caracter=decimal;//Convertir el decimal en caracter.
                texto=texto+caracter;//Concadenar el caracter.
                cout<<"decimal final:"<<decimal<<endl;
                cout<<"caracter final:"<<caracter<<endl;
                cout<<"texto:"<<texto.toStdString()<<endl;

                cadenaBit="";
                i--;
            }
        }
        if (parar==true) {//Comprobar si es true, para poder detener la recuperación del mensaje.
            break;
        }
    }
    return texto;
}

QString lsb::extraerAC(QList<Mat> bloqueCuan)
{
    QString texto;
    char caracter;
    QString cadenaByte;
    cout<<"=================================================0"<<endl;
    for (int i = 0; i < 3; i++) {
        Mat bloque=bloqueCuan.at(i);
        cout<<bloque<<endl;
        int coef=bloque.at<float>(0,1);
        if (coef<0) {
            coef=coef*-1;
            QString byte=objBinariar->getByte(coef);
            cout<<byte.toStdString()<<endl;
            cadenaByte=byte.at(7).toLatin1();

        }else{

            QString byte=objBinariar->getByte(coef);
            cout<<byte.toStdString()<<endl;
            cadenaByte=byte.at(7).toLatin1();

        }
        coef=bloque.at<float>(1,0);

        if (coef<0) {
            coef=coef*-1;
            QString byte=objBinariar->getByte(coef);
            cout<<byte.toStdString()<<endl;
            cadenaByte=cadenaByte+byte.at(7).toLatin1();

        }else{
            QString byte=objBinariar->getByte(coef);
            cout<<byte.toStdString()<<endl;
            cadenaByte=cadenaByte+byte.at(7).toLatin1();

        }
        coef=bloque.at<float>(2,0);

        if (coef<0) {
            coef=coef*-1;
            QString byte=objBinariar->getByte(coef);
            cout<<byte.toStdString()<<endl;
            cadenaByte=cadenaByte+byte.at(7).toLatin1();

        }else{
            QString byte=objBinariar->getByte(coef);
            cout<<byte.toStdString()<<endl;
            cadenaByte=cadenaByte+byte.at(7).toLatin1();

        }
        coef=bloque.at<float>(1,1);

        if (coef<0) {
            coef=coef*-1;
            QString byte=objBinariar->getByte(coef);
            cout<<byte.toStdString()<<endl;
            cadenaByte=cadenaByte+byte.at(7).toLatin1();

        }else{
            QString byte=objBinariar->getByte(coef);
            cout<<byte.toStdString()<<endl;
            cadenaByte=cadenaByte+byte.at(7).toLatin1();

        }
        coef=bloque.at<float>(0,2);

        if (coef<0) {
            coef=coef*-1;
            QString byte=objBinariar->getByte(coef);
            cout<<byte.toStdString()<<endl;
            cadenaByte=cadenaByte+byte.at(7).toLatin1();

        }else{
            QString byte=objBinariar->getByte(coef);
            cout<<byte.toStdString()<<endl;
            cadenaByte=cadenaByte+byte.at(7).toLatin1();

        }
        coef=bloque.at<float>(0,3);

        if (coef<0) {
            coef=coef*-1;
            QString byte=objBinariar->getByte(coef);
            cout<<byte.toStdString()<<endl;
            cadenaByte=cadenaByte+byte.at(7).toLatin1();

        }else{
            QString byte=objBinariar->getByte(coef);
            cout<<byte.toStdString()<<endl;
            cadenaByte=cadenaByte+byte.at(7).toLatin1();

        }
        coef=bloque.at<float>(1,2);

        if (coef<0) {
            coef=coef*-1;
            QString byte=objBinariar->getByte(coef);
            cout<<byte.toStdString()<<endl;
            cadenaByte=cadenaByte+byte.at(7).toLatin1();

        }else{
            QString byte=objBinariar->getByte(coef);
            cout<<byte.toStdString()<<endl;
            cadenaByte=cadenaByte+byte.at(7).toLatin1();

        }
        coef=bloque.at<float>(2,1);

        if (coef<0) {
            coef=coef*-1;
            QString byte=objBinariar->getByte(coef);
            cout<<byte.toStdString()<<endl;
            cadenaByte=cadenaByte+byte.at(7).toLatin1();

        }else{
            QString byte=objBinariar->getByte(coef);
            cout<<byte.toStdString()<<endl;
            cadenaByte=cadenaByte+byte.at(7).toLatin1();

        }


        int decimal=convertirBinarioDecimal(cadenaByte);
        char letra=decimal;
        texto=texto+letra;
        cadenaByte="";

}
    return texto;

}

Mat lsb::getEstegoImagem()
{
    return this->EstegoImagen;
}

Mat lsb::modificarCoeficientesAC(Mat coefAC, QList<int> byteCaracter)
{



    for (int i = 0; i < byteCaracter.size(); i++) {
        if (i==0) {
            int coef=(int)coefAC.at<float>(0,1);
            if (coef<0) {
                 int abs=coef*-1;
//                int bit=byteCaracter.at(i);
                int bit=1;
                int decimal;
                decimal=alterarAC(abs,bit);
                 decimal=decimal*-1;
                 cout<<decimal<<endl;
                 cout<<"negativo"<<endl;
                coefAC.at<float>(0,1)=decimal;
            }else{
//                int bit=byteCaracter.at(i);
                int bit=1;
                cout<<bit<<endl;
                int decimal=0;
                decimal=alterarAC(coef,bit);
                cout<<decimal<<endl;
                coefAC.at<float>(0,1)=decimal;
            }

        }
        if (i==1) {
            int coef=(int)coefAC.at<float>(1,0);
             if (coef<0) {
                 int abs=coef*-1;
//                 int bit=byteCaracter.at(i);
                 int bit=1;
                 int decimal;
                  decimal=alterarAC(abs,bit);
                  decimal=decimal*-1;
                  cout<<decimal<<endl;
                  coefAC.at<float>(1,0)=decimal;
             }else{
//                int bit=byteCaracter.at(i);
                 int bit=1;
                 cout<<bit<<endl;
                int decimal=0;
                decimal=alterarAC(coef,bit);
                cout<<decimal<<endl;
                coefAC.at<float>(1,0)=decimal;
             }
        }
        if (i==2) {
            int coef=(int)coefAC.at<float>(2,0);
            if (coef<0) {
                 int abs=coef*-1;
//                int bit=byteCaracter.at(i);
                 int bit=1;
                int decimal;
                decimal=alterarAC(abs,bit);
                decimal=decimal*-1;
                cout<<decimal<<endl;
                coefAC.at<float>(2,0)=decimal;
            }else{
//                int bit=byteCaracter.at(i);
                int bit=1;
                cout<<bit<<endl;
                int decimal=0;
                decimal=alterarAC(coef,bit);
                cout<<decimal<<endl;
                coefAC.at<float>(2,0)=decimal;
            }
        }
        if (i==3) {
            int coef=(int)coefAC.at<float>(1,1);
            if (coef<0) {
                 int abs=coef*-1;
//                int bit=byteCaracter.at(i);
                int bit=0;
                int decimal;
                decimal=alterarAC(abs,bit);
                decimal=decimal*-1;
                cout<<decimal<<endl;
                coefAC.at<float>(1,1)=decimal;
            }else{
                int bit=byteCaracter.at(i);
                cout<<bit<<endl;
                int decimal=0;
                decimal=alterarAC(coef,bit);
                cout<<decimal<<endl;
                coefAC.at<float>(1,1)=decimal;
            }
        }
        if (i==4) {
            int coef=(int)coefAC.at<float>(0,2);
            if (coef<0) {
                 int abs=coef*-1;
                int bit=byteCaracter.at(i);
                int decimal;
                decimal=alterarAC(abs,bit);
                decimal=decimal*-1;
                cout<<decimal<<endl;
                coefAC.at<float>(0,2)=decimal;
            }else{
                int bit=byteCaracter.at(i);
                cout<<bit<<endl;
                int decimal=0;
                decimal=alterarAC(coef,bit);
                cout<<decimal<<endl;
                coefAC.at<float>(0,2)=decimal;
            }
        }
        if (i==5) {
            int coef=(int)coefAC.at<float>(0,3);
            if (coef<0) {
                 int abs=coef*-1;
                int bit=byteCaracter.at(i);
                int decimal;
                decimal=alterarAC(abs,bit);
                decimal=decimal*-1;
                cout<<decimal<<endl;
                coefAC.at<float>(0,3)=decimal;
            }else{
                int bit=byteCaracter.at(i);
                cout<<bit<<endl;
                int decimal=0;
                decimal=alterarAC(coef,bit);
                cout<<decimal<<endl;
                coefAC.at<float>(0,3)=decimal;
            }
        }
        if (i==6) {
            int coef=(int)coefAC.at<float>(1,2);
            if (coef<0) {
                 int abs=coef*-1;
                int bit=byteCaracter.at(i);
                int decimal;
                decimal=alterarAC(abs,bit);
                decimal=decimal*-1;
                cout<<decimal<<endl;
                coefAC.at<float>(1,2)=decimal;
            }else{
                int bit=byteCaracter.at(i);
                cout<<bit<<endl;
                int decimal=0;
                decimal=alterarAC(coef,bit);
                cout<<decimal<<endl;
                coefAC.at<float>(1,2)=decimal;
            }
        }
        if (i==7) {
            int coef=(int)coefAC.at<float>(2,1);
            if (coef<0) {
                 int abs=coef*-1;
                int bit=byteCaracter.at(i);
                int decimal;
                decimal=alterarAC(abs,bit);
                decimal=decimal*-1;
                cout<<decimal<<endl;
                coefAC.at<float>(2,1)=decimal;
            }else{
                int bit=byteCaracter.at(i);
                cout<<bit<<endl;
                int decimal=0;
                decimal=alterarAC(coef,bit);

                cout<<decimal<<endl;
                coefAC.at<float>(2,1)=decimal;
            }
        }
    }
    return coefAC;

}

//Este método alterarPixelGray, devuelve una lista con los pixeles alterados aplicando
//el metodo del Least Significant Bit.
QList<int> lsb::alterarPixelGray(QList<int > listaPixelGray, QList<QList<int> > listaByteTexto)
{
    QString byte;
    QString bit;

    char caractSustituto;
    int k=0,p=0,l=1,cont=0;
    int cantidadPixel=cantidadMultiplo(listaPixelGray.size(),8);//Obtiene la cantidad de la lista de los pixeles
    int cantidadCaracteres=listaByteTexto.size()+1;//Se aumenta uno para el caracter especial para marcar el fin del texto oculto.
    int resta=cantidadCaracteres-1;//Se resta uno por el caracter especial.
    if (cantidadCaracteres<=cantidadPixel) {
        for (int i = 0; i < resta; ++i) {//Este bucle recorre la cantidad de pixeles a editar.
            for (int j = 0; j < 8; ++j) {//Este bucle recorre los 8 pixeles.
                byte=objBinariar->getByte(listaPixelGray.value(cont));//Binariza el pixel
                bit=QString::number(listaByteTexto.value(i).value(j));//Almacena el bit.
                cout<<"byte original: "<<byte.toStdString()<<endl;
                cout<<"bit extraido: "<<bit.toStdString()<<endl;
                caractSustituto=bit.at(0).toLatin1();//Convierte el int en un char.
                byte.replace(7,1,caractSustituto);//El byte binarizado se sustituye en la ultima posición
                //del byte utilizando Least Significant Bit.
                listaPixelGray[cont]=convertirBinarioDecimal(byte);//Convierte el byte modificado en un decimal, y es sustituido
                //por el nuevo decimal en la lista de los pixeles de la imagen.
                cont++;//Contador de la posicion del pixel a modificar.
                cout<<"================================="<<endl;
            }
        }
        cout<<"nuevo caracter"<<endl;
        int d=toascii('|');//Obtiene el decimal del caracter especial.
        QString byteCaracterfin;
        byteCaracterfin=objBinariar->getByte(d);//Binariza el decimal del caracter especial.
        QList<int> nuevo;
        nuevo.clear();
        for (int i = 0; i < byteCaracterfin.length(); i++) {
            nuevo.push_back((int)byteCaracterfin.at(i).digitValue());
            cout<<nuevo.value(i)<<endl;
        }
        for (int j = resta; j < cantidadCaracteres; ++j) {//Este bucle recorre la cantidad de pixeles a editar.
            for (int k = 0; k < 8; ++k) {//Este bucle recorre los 8 pixeles.
                 byte=objBinariar->getByte(listaPixelGray.value(cont));
                 bit=QString::number(nuevo.value(k));//Almacena el bit.
                 caractSustituto=bit.at(0).toLatin1();//Convierte el int en un char.
                 cout<<caractSustituto<<endl;
                 byte.replace(7,1,caractSustituto);//El byte binarizado se sustituye en la ultima posición
                 //del byte utilizando Least Significant Bit.
                 cout<<"sustituto:"<<byte.toStdString()<<endl;
                 listaPixelGray[cont]=convertirBinarioDecimal(byte);//Convierte el byte modificado en un decimal, y es sustituido
                 //por el nuevo decimal en la lista de los pixeles de la imagen.
                 cout<<"Modificado:"<<listaPixelGray.value(cont)<<endl;
                 cont++;
            }

        }


    }
    return listaPixelGray;
}
