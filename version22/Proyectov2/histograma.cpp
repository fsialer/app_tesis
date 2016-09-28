#include "histograma.h"

histograma::histograma()
{
}

void histograma::calcularHistograma(Mat img, int op)
{
    int c1[256];
    int c2[256];
    int c3[256];
    int cont=1;
    if (op==1) {
        for (int i = 0; i < img.rows; ++i) {
            for (int j = 0; j < img.cols; ++j) {
                c1[(int)img.at<uchar>(i,j)]+=cont;
            }
        }
        for (int i = 0; i < 256; ++i) {
            this->vc1.push_back(c1[i]);
        }
    }else{
        for (int i = 0; i < img.rows; ++i) {
            for (int j = 0; j < img.cols; ++j) {
                int pixelAzul=(int)img.data[img.channels()*(img.cols*i+j)+0];
                int pixelVerde=(int)img.data[img.channels()*(img.cols*i+j)+1];
                int pixelRojo=(int)img.data[img.channels()*(img.cols*i+j)+2];
               c1[pixelRojo-1]+=1;
               c2[pixelVerde-1]+=1;
               c3[pixelAzul-1]+=1;
            }
        }
        for (int i = 0; i < 256; ++i) {
            this->vc1.push_back(c1[i]);
            this->vc2.push_back(c2[i]);
            this->vc3.push_back(c3[i]);
        }

    }

}

QList<int> histograma::getc1()
{
    return this->vc1;
}

QList<int> histograma::getc2()
{
    return this->vc2;
}

QList<int> histograma::getc3()
{
    return this->vc3;
}
