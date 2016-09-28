#-------------------------------------------------
#
# Project created by QtCreator 2015-10-12T22:41:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Proyectov2
TEMPLATE = app


SOURCES += main.cpp\
        principal.cpp \
    dominioespacial.cpp \
    dominiofrecuencial.cpp \
    espaciocolor.cpp \
    notepad.cpp \
    imagen.cpp \
    mensaje.cpp \
    binarizar.cpp \
    lsb.cpp \
    cuantizacion.cpp \
    histograma.cpp \
    resultado.cpp \
    resultado2.cpp \
    resultado3.cpp

HEADERS  += principal.h \
    dominioespacial.h \
    dominiofrecuencial.h \
    espaciocolor.h \
    notepad.h \
    imagen.h \
    mensaje.h \
    binarizar.h \
    lsb.h \
    cuantizacion.h \
    histograma.h \
    resultado.h \
    resultado2.h \
    resultado3.h

FORMS    += principal.ui \
    dominioespacial.ui \
    dominiofrecuencial.ui \
    resultado.ui \
    resultado2.ui \
    resultado3.ui
INCLUDEPATH+=C:\opencv2.4.6.g\include
LIBS+=C:/opencv2.4.6.g/bin/*.dll
