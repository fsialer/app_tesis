#ifndef CUANTIZACION_H
#define CUANTIZACION_H
#include <opencv2/opencv.hpp>
using namespace cv;
class cuantizacion
{
public:
    cuantizacion();
    Mat convertirM2D_IMG();//convertir la matriz de cuantificacion 2D en una matriz de imagen Y
    Mat convertirM2D_CrCb();//convertir la matriz de cuantificacion 2D Cr y Cb
};

#endif // CUANTIZACION_H
