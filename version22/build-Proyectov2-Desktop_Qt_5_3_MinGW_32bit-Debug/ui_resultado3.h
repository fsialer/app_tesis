/********************************************************************************
** Form generated from reading UI file 'resultado3.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESULTADO3_H
#define UI_RESULTADO3_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_resultado3
{
public:
    QPushButton *pbtnCargar;
    QPushButton *pbtnCargar2;
    QPushButton *pbtnProcesar;
    QProgressBar *pbarra;
    QLabel *label;
    QLineEdit *txtCaracterErroneo;

    void setupUi(QDialog *resultado3)
    {
        if (resultado3->objectName().isEmpty())
            resultado3->setObjectName(QStringLiteral("resultado3"));
        resultado3->resize(313, 165);
        pbtnCargar = new QPushButton(resultado3);
        pbtnCargar->setObjectName(QStringLiteral("pbtnCargar"));
        pbtnCargar->setGeometry(QRect(20, 30, 75, 23));
        pbtnCargar2 = new QPushButton(resultado3);
        pbtnCargar2->setObjectName(QStringLiteral("pbtnCargar2"));
        pbtnCargar2->setGeometry(QRect(210, 30, 75, 23));
        pbtnProcesar = new QPushButton(resultado3);
        pbtnProcesar->setObjectName(QStringLiteral("pbtnProcesar"));
        pbtnProcesar->setGeometry(QRect(20, 90, 271, 23));
        pbarra = new QProgressBar(resultado3);
        pbarra->setObjectName(QStringLiteral("pbarra"));
        pbarra->setGeometry(QRect(20, 60, 271, 23));
        pbarra->setValue(0);
        label = new QLabel(resultado3);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 130, 151, 16));
        txtCaracterErroneo = new QLineEdit(resultado3);
        txtCaracterErroneo->setObjectName(QStringLiteral("txtCaracterErroneo"));
        txtCaracterErroneo->setGeometry(QRect(192, 130, 101, 20));

        retranslateUi(resultado3);

        QMetaObject::connectSlotsByName(resultado3);
    } // setupUi

    void retranslateUi(QDialog *resultado3)
    {
        resultado3->setWindowTitle(QApplication::translate("resultado3", "Caracteres erroneos", 0));
        pbtnCargar->setText(QApplication::translate("resultado3", "Cargar", 0));
        pbtnCargar2->setText(QApplication::translate("resultado3", "Cargar", 0));
        pbtnProcesar->setText(QApplication::translate("resultado3", "Procesar", 0));
        label->setText(QApplication::translate("resultado3", "Cantidad caracteres erroneos:", 0));
    } // retranslateUi

};

namespace Ui {
    class resultado3: public Ui_resultado3 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESULTADO3_H
