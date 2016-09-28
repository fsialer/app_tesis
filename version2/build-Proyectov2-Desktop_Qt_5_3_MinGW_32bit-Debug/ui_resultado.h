/********************************************************************************
** Form generated from reading UI file 'resultado.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESULTADO_H
#define UI_RESULTADO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_resultado
{
public:
    QGroupBox *groupBox;
    QLabel *lblImagen;
    QTableWidget *tblWHistigrama;
    QPushButton *pbtnProcesar;
    QPlainTextEdit *ptxtDescripcion;
    QRadioButton *rbtnGray;
    QRadioButton *rbtnColor;

    void setupUi(QDialog *resultado)
    {
        if (resultado->objectName().isEmpty())
            resultado->setObjectName(QStringLiteral("resultado"));
        resultado->resize(665, 300);
        groupBox = new QGroupBox(resultado);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 631, 231));
        lblImagen = new QLabel(groupBox);
        lblImagen->setObjectName(QStringLiteral("lblImagen"));
        lblImagen->setGeometry(QRect(20, 20, 111, 111));
        tblWHistigrama = new QTableWidget(groupBox);
        tblWHistigrama->setObjectName(QStringLiteral("tblWHistigrama"));
        tblWHistigrama->setGeometry(QRect(350, 20, 261, 161));
        pbtnProcesar = new QPushButton(groupBox);
        pbtnProcesar->setObjectName(QStringLiteral("pbtnProcesar"));
        pbtnProcesar->setGeometry(QRect(20, 160, 131, 23));
        ptxtDescripcion = new QPlainTextEdit(groupBox);
        ptxtDescripcion->setObjectName(QStringLiteral("ptxtDescripcion"));
        ptxtDescripcion->setGeometry(QRect(190, 20, 101, 161));
        rbtnGray = new QRadioButton(resultado);
        rbtnGray->setObjectName(QStringLiteral("rbtnGray"));
        rbtnGray->setGeometry(QRect(20, 260, 82, 17));
        rbtnColor = new QRadioButton(resultado);
        rbtnColor->setObjectName(QStringLiteral("rbtnColor"));
        rbtnColor->setGeometry(QRect(150, 260, 82, 17));

        retranslateUi(resultado);

        QMetaObject::connectSlotsByName(resultado);
    } // setupUi

    void retranslateUi(QDialog *resultado)
    {
        resultado->setWindowTitle(QApplication::translate("resultado", "Dialog", 0));
        groupBox->setTitle(QApplication::translate("resultado", "GroupBox", 0));
        lblImagen->setText(QString());
        pbtnProcesar->setText(QApplication::translate("resultado", "Procesar", 0));
        rbtnGray->setText(QApplication::translate("resultado", "Escala de grises", 0));
        rbtnColor->setText(QApplication::translate("resultado", "Color", 0));
    } // retranslateUi

};

namespace Ui {
    class resultado: public Ui_resultado {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESULTADO_H
