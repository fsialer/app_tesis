/********************************************************************************
** Form generated from reading UI file 'dominiofrecuencial.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOMINIOFRECUENCIAL_H
#define UI_DOMINIOFRECUENCIAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>

QT_BEGIN_NAMESPACE

class Ui_dominioFrecuencial
{
public:
    QGroupBox *groupBox;
    QPlainTextEdit *ptxtMensaje;
    QPushButton *pbtnBinarizar;
    QPushButton *pbtnMostrar;
    QGroupBox *groupBox_2;
    QLabel *lblImagen;
    QPushButton *pbtnCargarImg;
    QGroupBox *groupBox_3;
    QRadioButton *rbtnIncrustar;
    QRadioButton *rbtnExtraer;
    QGroupBox *groupBox_5;
    QPlainTextEdit *ptxtDescripcion;
    QGroupBox *groupBox_4;
    QRadioButton *rbtnGray;
    QRadioButton *rbtnYCrCb;
    QRadioButton *rbtnYUV;
    QGroupBox *groupBox_6;
    QPushButton *pbtnProcesar;
    QPushButton *pbtnSalir;
    QPushButton *pbtnGolay;
    QProgressBar *pBarra;
    QLabel *lblProceso;

    void setupUi(QDialog *dominioFrecuencial)
    {
        if (dominioFrecuencial->objectName().isEmpty())
            dominioFrecuencial->setObjectName(QStringLiteral("dominioFrecuencial"));
        dominioFrecuencial->resize(924, 383);
        groupBox = new QGroupBox(dominioFrecuencial);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 381, 301));
        ptxtMensaje = new QPlainTextEdit(groupBox);
        ptxtMensaje->setObjectName(QStringLiteral("ptxtMensaje"));
        ptxtMensaje->setGeometry(QRect(10, 30, 361, 211));
        pbtnBinarizar = new QPushButton(groupBox);
        pbtnBinarizar->setObjectName(QStringLiteral("pbtnBinarizar"));
        pbtnBinarizar->setGeometry(QRect(20, 250, 75, 23));
        pbtnMostrar = new QPushButton(groupBox);
        pbtnMostrar->setObjectName(QStringLiteral("pbtnMostrar"));
        pbtnMostrar->setGeometry(QRect(230, 250, 121, 23));
        groupBox_2 = new QGroupBox(dominioFrecuencial);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(410, 20, 151, 211));
        lblImagen = new QLabel(groupBox_2);
        lblImagen->setObjectName(QStringLiteral("lblImagen"));
        lblImagen->setGeometry(QRect(20, 30, 111, 121));
        lblImagen->setStyleSheet(QStringLiteral(""));
        pbtnCargarImg = new QPushButton(groupBox_2);
        pbtnCargarImg->setObjectName(QStringLiteral("pbtnCargarImg"));
        pbtnCargarImg->setGeometry(QRect(20, 170, 111, 23));
        groupBox_3 = new QGroupBox(dominioFrecuencial);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(570, 160, 181, 71));
        rbtnIncrustar = new QRadioButton(groupBox_3);
        rbtnIncrustar->setObjectName(QStringLiteral("rbtnIncrustar"));
        rbtnIncrustar->setGeometry(QRect(20, 30, 82, 17));
        rbtnExtraer = new QRadioButton(groupBox_3);
        rbtnExtraer->setObjectName(QStringLiteral("rbtnExtraer"));
        rbtnExtraer->setGeometry(QRect(100, 30, 82, 20));
        groupBox_5 = new QGroupBox(dominioFrecuencial);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setGeometry(QRect(570, 20, 181, 131));
        ptxtDescripcion = new QPlainTextEdit(groupBox_5);
        ptxtDescripcion->setObjectName(QStringLiteral("ptxtDescripcion"));
        ptxtDescripcion->setGeometry(QRect(10, 20, 161, 101));
        groupBox_4 = new QGroupBox(dominioFrecuencial);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(760, 20, 151, 211));
        rbtnGray = new QRadioButton(groupBox_4);
        rbtnGray->setObjectName(QStringLiteral("rbtnGray"));
        rbtnGray->setGeometry(QRect(30, 20, 101, 17));
        rbtnYCrCb = new QRadioButton(groupBox_4);
        rbtnYCrCb->setObjectName(QStringLiteral("rbtnYCrCb"));
        rbtnYCrCb->setGeometry(QRect(30, 60, 82, 17));
        rbtnYUV = new QRadioButton(groupBox_4);
        rbtnYUV->setObjectName(QStringLiteral("rbtnYUV"));
        rbtnYUV->setGeometry(QRect(30, 100, 82, 17));
        groupBox_6 = new QGroupBox(dominioFrecuencial);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        groupBox_6->setGeometry(QRect(410, 250, 501, 61));
        pbtnProcesar = new QPushButton(groupBox_6);
        pbtnProcesar->setObjectName(QStringLiteral("pbtnProcesar"));
        pbtnProcesar->setGeometry(QRect(20, 30, 121, 23));
        pbtnSalir = new QPushButton(groupBox_6);
        pbtnSalir->setObjectName(QStringLiteral("pbtnSalir"));
        pbtnSalir->setGeometry(QRect(410, 30, 75, 23));
        pbtnGolay = new QPushButton(groupBox_6);
        pbtnGolay->setObjectName(QStringLiteral("pbtnGolay"));
        pbtnGolay->setGeometry(QRect(160, 30, 75, 23));
        pBarra = new QProgressBar(dominioFrecuencial);
        pBarra->setObjectName(QStringLiteral("pBarra"));
        pBarra->setGeometry(QRect(10, 340, 391, 23));
        pBarra->setValue(0);
        lblProceso = new QLabel(dominioFrecuencial);
        lblProceso->setObjectName(QStringLiteral("lblProceso"));
        lblProceso->setGeometry(QRect(420, 340, 301, 16));

        retranslateUi(dominioFrecuencial);
        QObject::connect(pbtnSalir, SIGNAL(clicked()), dominioFrecuencial, SLOT(close()));

        QMetaObject::connectSlotsByName(dominioFrecuencial);
    } // setupUi

    void retranslateUi(QDialog *dominioFrecuencial)
    {
        dominioFrecuencial->setWindowTitle(QApplication::translate("dominioFrecuencial", "Dominio Frecuencial", 0));
        groupBox->setTitle(QApplication::translate("dominioFrecuencial", "Mensaje", 0));
        pbtnBinarizar->setText(QApplication::translate("dominioFrecuencial", "Binarizar", 0));
        pbtnMostrar->setText(QApplication::translate("dominioFrecuencial", "Mostrar mensaje", 0));
        groupBox_2->setTitle(QApplication::translate("dominioFrecuencial", "Imagen", 0));
        lblImagen->setText(QString());
        pbtnCargarImg->setText(QApplication::translate("dominioFrecuencial", "Cargar Imagen", 0));
        groupBox_3->setTitle(QApplication::translate("dominioFrecuencial", "Proceso", 0));
        rbtnIncrustar->setText(QApplication::translate("dominioFrecuencial", "Incrustar", 0));
        rbtnExtraer->setText(QApplication::translate("dominioFrecuencial", "Extraer", 0));
        groupBox_5->setTitle(QApplication::translate("dominioFrecuencial", "Descripcion", 0));
        groupBox_4->setTitle(QApplication::translate("dominioFrecuencial", "Espacio de Color", 0));
        rbtnGray->setText(QApplication::translate("dominioFrecuencial", "Escala de grises", 0));
        rbtnYCrCb->setText(QApplication::translate("dominioFrecuencial", "YCrCb", 0));
        rbtnYUV->setText(QApplication::translate("dominioFrecuencial", "YUV", 0));
        groupBox_6->setTitle(QApplication::translate("dominioFrecuencial", "Accion", 0));
        pbtnProcesar->setText(QApplication::translate("dominioFrecuencial", "Procesar", 0));
        pbtnSalir->setText(QApplication::translate("dominioFrecuencial", "Salir", 0));
        pbtnGolay->setText(QApplication::translate("dominioFrecuencial", "Golay", 0));
        lblProceso->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class dominioFrecuencial: public Ui_dominioFrecuencial {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOMINIOFRECUENCIAL_H
