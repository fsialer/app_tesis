#ifndef ESPACIOCOLOR_H
#define ESPACIOCOLOR_H
#include <opencv2/opencv.hpp>
using namespace cv;
class espacioColor
{
public:
    espacioColor();
    Mat convertirRGBGray(Mat img);
    Mat convertirGrayRGB(Mat img);
    Mat convertirRGBYCrCb(Mat img);
    Mat convertirYCrCbRGB(Mat img);
    Mat convertirRGBYUV(Mat img);
    Mat convertirYUVRGB(Mat img);
    Mat convertirRGBHSL(Mat img);
    Mat convertirHSLRGB(Mat img);


};

#endif // ESPACIOCOLOR_H
