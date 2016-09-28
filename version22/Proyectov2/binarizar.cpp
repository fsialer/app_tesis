#include "binarizar.h"

binarizar::binarizar()
{
}

//Este metodo getByte devuelve una conversión de un decimal que recibe por parametro
//en un cadena de 8 bits, diviendo el decimal entre 2, guardando
//los residuos y luego diviendo cociente resultante entre 2 hasta que
//hasta que el cociente sea mayor igual divisor.
QString binarizar::getByte(int decimal)
{
    int cociente,residuo;
    cout<<"decimal del binario: "<<decimal<<endl;
    QString byte="";
    //comprueba si el decimal es menor a 2
    //para asi asignarle la cadena que le corresponde
    if (decimal<2) {
        if (decimal==0) {
            for (int i =0; i < 8; i++) {
                byte='0'+byte;
            }
        }else{
            byte="00000001";
        }

    }else{
     //Si el decimal es mayor, entonces procede
     //a entrar en un do while para poder obtener
     // la cadena de 8 bits del decimal
        do{
            cociente=decimal/2;
            residuo=decimal%2;
            byte=QString::number(residuo)+byte;
            if (cociente==1) {
                byte=QString::number(cociente)+byte;
            }
            decimal=cociente;
        }while(cociente!=1);
        //comprobamos si el tamaño de la cadena es
        // menor a 8, si lo es se procede a agregar
        //los bit faltantes.
        if (byte.length()<=8) {
            for (int i = byte.length(); i < 8; i++) {
                byte='0'+byte;
            }
        }
    }

    return byte;
}
