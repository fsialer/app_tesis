#include "mensaje.h"
//Este contructor carga como parametro el texto que queremos binarizar.
mensaje::mensaje(QString texto):
    mTexto(texto)
{
    objBinarizar=new binarizar();//Inicializa la clase binarizar.
}

//Este metodo agregarBits, devuelve una lista bits de cada caracter del mensaje.
QList<int> mensaje::agregarBits(QString byte)
{
    QList<int> bits;
    bits.clear();
    for (int i = 0; i < byte.length(); i++) {
        bits.push_back((int)byte.at(i).digitValue());
        cout<<bits.value(i)<<endl;
    }
    return bits;

}

//Este metodo getListaByte, devuelve una lista de una lista de byte que lo conforma
//el mensaje.

QList<QList<int> > mensaje::getListaByte()
{
    QString byte;
    cout<<"lista de byte"<<endl;
    for (int i = 0; i < tamanioTexto(); i++) {
        cout<<"==================="<<endl;
        byte=this->objBinarizar->getByte(toascii(mTexto.at(i).toLatin1()));
        this->listaByte.push_back(agregarBits(byte));

    }
    return this->listaByte;
}
//Este metodo tamanioTexto, devuelve el tamaño del mensaje.
int mensaje::tamanioTexto()
{
    return mTexto.length();
}

