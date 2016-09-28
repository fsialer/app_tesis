#include "espaciocolor.h"

espacioColor::espacioColor()
{
}
//El metodo convertirRGBGray convierte la imagen a color en imagen
//en escala de grises. Formula: Gray=(R+B+G)/3

Mat espacioColor::convertirRGBGray(Mat img)
{
    cvtColor(img,img,CV_RGB2GRAY);
    return img;

}

Mat espacioColor::convertirGrayRGB(Mat img)
{
    cvtColor(img,img,CV_GRAY2RGB);
    return img;
}
//El metodo convertirRGBYCrCb convierte la imagen a color en imagen
//en YCbCr. Formula: Y=wR*R+(1-wB-wR)*G+wB*B,
//Cb=((0.5)/1-wB)*(B-Y), Cr=((0.5)/1-wR)*(R-Y)
Mat espacioColor::convertirRGBYCrCb(Mat img)
{
    cvtColor(img,img,CV_RGB2YCrCb);
    return img;

}
//El metodo convertirYCbCrRGB convierte la imagen YCbCr a color.
Mat espacioColor::convertirYCrCbRGB(Mat img)
{
    cvtColor(img,img,CV_YCrCb2RGB);
    return img;

}
//El metodo convertirRGBYUV convierte la imagen a color en imagen
//en escala de grises. Formula: Y=0.299*R+0.587*G+0.114*B, U=0.492*(B-Y)
//V=0.877*(R-Y)
Mat espacioColor::convertirRGBYUV(Mat img)
{
    cvtColor(img,img,CV_RGB2YUV);
    return img;
}
//El metodo convertirYCbCrRGB convierte la imagen YUV a color.
Mat espacioColor::convertirYUVRGB(Mat img)
{
    cvtColor(img,img,CV_YUV2RGB);
    return img;
}

