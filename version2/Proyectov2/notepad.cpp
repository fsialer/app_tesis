#include "notepad.h"

notepad::notepad()
{
}
//Este metodo writeOnly, ubica el archivo .txt, y escribe dentro de el.
void notepad::writeOnly(QString in,QString fichero)
{
    QString ruta;
    ruta.append("C:\\Users\\FernandoAlexis\\Documents\\MATLAB\\golay\\golay\\for_testing\\"); //Si usas Windows debes utilizar "\"
    ruta.append(fichero);
    QFile file(ruta);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
      qDebug()<<"No se encuentra el archivo de texto!";
    }else{
        qDebug()<<"Exito.!";
        file.write(in.toUtf8());
        file.close();
    }
}

//Este metodo readOnly, ubica el archivo .txt, y lo lee.
QString notepad::readOnly(QString fichero)
{
    QString ruta;
    //Si usas Windows debes utilizar "\"
    ruta.append(fichero);
    QFile file(ruta);
    QString data;
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
      qDebug()<<"No se encuentra el archivo de texto2!";
    }else{qDebug()<<"Exito!";
        QTextStream in(&file);
        while (!in.atEnd()) {
           data.append(in.readLine());
        }
        cout<<data.length()<<endl;
      }
    return data;
}
