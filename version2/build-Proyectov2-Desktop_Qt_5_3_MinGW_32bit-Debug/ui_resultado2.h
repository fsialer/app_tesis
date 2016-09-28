/********************************************************************************
** Form generated from reading UI file 'resultado2.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESULTADO2_H
#define UI_RESULTADO2_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_resultado2
{
public:
    QGroupBox *groupBox;
    QLabel *lblImagen;
    QPushButton *pbtnCargar1;
    QGroupBox *groupBox_2;
    QLabel *lblImagen2;
    QPushButton *pbtnCargar2;
    QLabel *label_3;
    QLineEdit *txtFidelidad;
    QProgressBar *pbarra;
    QPushButton *pbtnCalcular;
    QLabel *label;
    QLineEdit *txtCantENA;

    void setupUi(QDialog *resultado2)
    {
        if (resultado2->objectName().isEmpty())
            resultado2->setObjectName(QStringLiteral("resultado2"));
        resultado2->resize(284, 394);
        groupBox = new QGroupBox(resultado2);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 0, 131, 191));
        lblImagen = new QLabel(groupBox);
        lblImagen->setObjectName(QStringLiteral("lblImagen"));
        lblImagen->setGeometry(QRect(20, 30, 91, 121));
        pbtnCargar1 = new QPushButton(groupBox);
        pbtnCargar1->setObjectName(QStringLiteral("pbtnCargar1"));
        pbtnCargar1->setGeometry(QRect(10, 160, 101, 23));
        groupBox_2 = new QGroupBox(resultado2);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(150, 0, 120, 191));
        lblImagen2 = new QLabel(groupBox_2);
        lblImagen2->setObjectName(QStringLiteral("lblImagen2"));
        lblImagen2->setGeometry(QRect(20, 30, 81, 111));
        pbtnCargar2 = new QPushButton(groupBox_2);
        pbtnCargar2->setObjectName(QStringLiteral("pbtnCargar2"));
        pbtnCargar2->setGeometry(QRect(10, 160, 101, 23));
        label_3 = new QLabel(resultado2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 320, 151, 16));
        txtFidelidad = new QLineEdit(resultado2);
        txtFidelidad->setObjectName(QStringLiteral("txtFidelidad"));
        txtFidelidad->setGeometry(QRect(170, 320, 91, 20));
        pbarra = new QProgressBar(resultado2);
        pbarra->setObjectName(QStringLiteral("pbarra"));
        pbarra->setGeometry(QRect(10, 280, 261, 23));
        pbarra->setValue(0);
        pbtnCalcular = new QPushButton(resultado2);
        pbtnCalcular->setObjectName(QStringLiteral("pbtnCalcular"));
        pbtnCalcular->setGeometry(QRect(10, 240, 261, 23));
        label = new QLabel(resultado2);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 360, 181, 16));
        txtCantENA = new QLineEdit(resultado2);
        txtCantENA->setObjectName(QStringLiteral("txtCantENA"));
        txtCantENA->setGeometry(QRect(200, 360, 61, 20));

        retranslateUi(resultado2);

        QMetaObject::connectSlotsByName(resultado2);
    } // setupUi

    void retranslateUi(QDialog *resultado2)
    {
        resultado2->setWindowTitle(QApplication::translate("resultado2", "Fidelidad de la imagen", 0));
        groupBox->setTitle(QApplication::translate("resultado2", "Imagen original", 0));
        lblImagen->setText(QString());
        pbtnCargar1->setText(QApplication::translate("resultado2", "Cargar", 0));
        groupBox_2->setTitle(QApplication::translate("resultado2", "Imagen Alterada", 0));
        lblImagen2->setText(QString());
        pbtnCargar2->setText(QApplication::translate("resultado2", "Cargar", 0));
        label_3->setText(QApplication::translate("resultado2", "Fidelidad de la imagen alterada:", 0));
        pbtnCalcular->setText(QApplication::translate("resultado2", "Calcular", 0));
        label->setText(QApplication::translate("resultado2", "Cantidad de elementos no afectados:", 0));
    } // retranslateUi

};

namespace Ui {
    class resultado2: public Ui_resultado2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESULTADO2_H
