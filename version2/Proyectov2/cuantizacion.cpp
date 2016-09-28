#include "cuantizacion.h"

cuantizacion::cuantizacion()
{
}
//El metodo ConvertirM2D_IMG devuelve una matriz según el
// estandar de compresión JPEG
Mat cuantizacion::convertirM2D_IMG()
{
    int matrizCuant[8][8]={
        {16, 11, 10, 16, 24, 40, 51, 61},
        {12, 12, 14, 19, 26, 58, 60, 55},
        {14, 13, 16, 24, 40, 57, 69, 56},
        {14, 17, 22, 29, 51, 87, 80, 62},
        {18, 22, 37, 56, 68, 109, 103, 77},
        {24, 35, 55, 64, 81, 104, 113, 92},
        {49, 64, 78, 87, 103, 121, 120, 101},
        {72, 92, 95, 98, 112, 100, 103, 99}
        };


    return Mat(8,8,CV_32SC1,&matrizCuant);
}
//El metodo convertirM2D_CrCb devuelve una matriz según el
// estandar de compresión JPEG a color
Mat cuantizacion::convertirM2D_CrCb()
{
    int matrizCuantQC[8][8]={
        {17,18,24,47,99,99,99,99},
        {18,21,26,66,99,99,99,99},
        {24,26,56,99,99,99,99,99},
        {47,66,99,99,99,99,99,99},
        {99,99,99,99,99,99,99,99},
        {99,99,99,99,99,99,99,99},
        {99,99,99,99,99,99,99,99},
        {99,99,99,99,99,99,99,99}
        };

    return Mat(8,8,CV_32SC1,&matrizCuantQC);
}
