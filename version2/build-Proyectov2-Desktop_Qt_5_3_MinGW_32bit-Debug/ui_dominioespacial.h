/********************************************************************************
** Form generated from reading UI file 'dominioespacial.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOMINIOESPACIAL_H
#define UI_DOMINIOESPACIAL_H

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

class Ui_dominioEspacial
{
public:
    QGroupBox *groupBox;
    QPushButton *pbtnCargar;
    QLabel *lblImagen;
    QGroupBox *groupBox_2;
    QRadioButton *rbtnRGB;
    QRadioButton *rbtnGray;
    QRadioButton *rbtnYCrCb;
    QRadioButton *rbtnYUV;
    QGroupBox *groupBox_3;
    QRadioButton *rbtnIncrustar;
    QRadioButton *rbtnExtraer;
    QGroupBox *groupBox_4;
    QPlainTextEdit *ptxtDescripcion;
    QGroupBox *groupBox_5;
    QPlainTextEdit *ptxtMensaje;
    QGroupBox *groupBox_6;
    QPushButton *pbtnProcesar;
    QPushButton *pbtnSalir;
    QProgressBar *pBarra;

    void setupUi(QDialog *dominioEspacial)
    {
        if (dominioEspacial->objectName().isEmpty())
            dominioEspacial->setObjectName(QStringLiteral("dominioEspacial"));
        dominioEspacial->resize(604, 452);
        groupBox = new QGroupBox(dominioEspacial);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 131, 181));
        pbtnCargar = new QPushButton(groupBox);
        pbtnCargar->setObjectName(QStringLiteral("pbtnCargar"));
        pbtnCargar->setGeometry(QRect(10, 150, 111, 23));
        lblImagen = new QLabel(groupBox);
        lblImagen->setObjectName(QStringLiteral("lblImagen"));
        lblImagen->setGeometry(QRect(15, 30, 101, 101));
        groupBox_2 = new QGroupBox(dominioEspacial);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(150, 10, 111, 181));
        rbtnRGB = new QRadioButton(groupBox_2);
        rbtnRGB->setObjectName(QStringLiteral("rbtnRGB"));
        rbtnRGB->setGeometry(QRect(10, 30, 82, 17));
        rbtnGray = new QRadioButton(groupBox_2);
        rbtnGray->setObjectName(QStringLiteral("rbtnGray"));
        rbtnGray->setGeometry(QRect(10, 60, 101, 17));
        rbtnYCrCb = new QRadioButton(groupBox_2);
        rbtnYCrCb->setObjectName(QStringLiteral("rbtnYCrCb"));
        rbtnYCrCb->setGeometry(QRect(10, 90, 82, 17));
        rbtnYUV = new QRadioButton(groupBox_2);
        rbtnYUV->setObjectName(QStringLiteral("rbtnYUV"));
        rbtnYUV->setGeometry(QRect(10, 120, 82, 17));
        groupBox_3 = new QGroupBox(dominioEspacial);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(270, 140, 181, 51));
        rbtnIncrustar = new QRadioButton(groupBox_3);
        rbtnIncrustar->setObjectName(QStringLiteral("rbtnIncrustar"));
        rbtnIncrustar->setGeometry(QRect(20, 20, 82, 17));
        rbtnExtraer = new QRadioButton(groupBox_3);
        rbtnExtraer->setObjectName(QStringLiteral("rbtnExtraer"));
        rbtnExtraer->setGeometry(QRect(100, 20, 82, 17));
        groupBox_4 = new QGroupBox(dominioEspacial);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(270, 10, 181, 131));
        ptxtDescripcion = new QPlainTextEdit(groupBox_4);
        ptxtDescripcion->setObjectName(QStringLiteral("ptxtDescripcion"));
        ptxtDescripcion->setGeometry(QRect(10, 20, 161, 101));
        groupBox_5 = new QGroupBox(dominioEspacial);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setGeometry(QRect(10, 210, 571, 181));
        ptxtMensaje = new QPlainTextEdit(groupBox_5);
        ptxtMensaje->setObjectName(QStringLiteral("ptxtMensaje"));
        ptxtMensaje->setGeometry(QRect(10, 20, 541, 141));
        groupBox_6 = new QGroupBox(dominioEspacial);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        groupBox_6->setGeometry(QRect(460, 10, 121, 181));
        pbtnProcesar = new QPushButton(groupBox_6);
        pbtnProcesar->setObjectName(QStringLiteral("pbtnProcesar"));
        pbtnProcesar->setGeometry(QRect(20, 30, 75, 23));
        pbtnSalir = new QPushButton(groupBox_6);
        pbtnSalir->setObjectName(QStringLiteral("pbtnSalir"));
        pbtnSalir->setGeometry(QRect(20, 110, 75, 23));
        pBarra = new QProgressBar(dominioEspacial);
        pBarra->setObjectName(QStringLiteral("pBarra"));
        pBarra->setGeometry(QRect(10, 420, 301, 23));
        pBarra->setValue(0);

        retranslateUi(dominioEspacial);
        QObject::connect(pbtnSalir, SIGNAL(clicked()), dominioEspacial, SLOT(close()));

        QMetaObject::connectSlotsByName(dominioEspacial);
    } // setupUi

    void retranslateUi(QDialog *dominioEspacial)
    {
        dominioEspacial->setWindowTitle(QApplication::translate("dominioEspacial", "Dominio Espacial", 0));
        groupBox->setTitle(QApplication::translate("dominioEspacial", "Imagen", 0));
        pbtnCargar->setText(QApplication::translate("dominioEspacial", "Cargar", 0));
        lblImagen->setText(QString());
        groupBox_2->setTitle(QApplication::translate("dominioEspacial", "Espacio de color", 0));
        rbtnRGB->setText(QApplication::translate("dominioEspacial", "solo RGB", 0));
        rbtnGray->setText(QApplication::translate("dominioEspacial", "Escala de grises", 0));
        rbtnYCrCb->setText(QApplication::translate("dominioEspacial", "YCrCb", 0));
        rbtnYUV->setText(QApplication::translate("dominioEspacial", "YUV", 0));
        groupBox_3->setTitle(QApplication::translate("dominioEspacial", "Proceso", 0));
        rbtnIncrustar->setText(QApplication::translate("dominioEspacial", "Incrustar", 0));
        rbtnExtraer->setText(QApplication::translate("dominioEspacial", "Extraer", 0));
        groupBox_4->setTitle(QApplication::translate("dominioEspacial", "Descripcion", 0));
        groupBox_5->setTitle(QApplication::translate("dominioEspacial", "Mensaje", 0));
        groupBox_6->setTitle(QApplication::translate("dominioEspacial", "Acci\303\263n", 0));
        pbtnProcesar->setText(QApplication::translate("dominioEspacial", "Procesar", 0));
        pbtnSalir->setText(QApplication::translate("dominioEspacial", "Salir", 0));
    } // retranslateUi

};

namespace Ui {
    class dominioEspacial: public Ui_dominioEspacial {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOMINIOESPACIAL_H
