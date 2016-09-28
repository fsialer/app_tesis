#ifndef NOTEPAD_H
#define NOTEPAD_H
#include <QString>
#include <QDir>
#include <QDebug>
#include <QTextStream>
#include <iostream>
#include <stdio.h>
using namespace std;
class notepad
{
public:
    notepad();
    void writeOnly(QString in,QString fichero);
    QString readOnly(QString fichero);

};

#endif // NOTEPAD_H
