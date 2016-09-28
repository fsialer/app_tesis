/********************************************************************************
** Form generated from reading UI file 'principal.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRINCIPAL_H
#define UI_PRINCIPAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_principal
{
public:
    QAction *actionExit;
    QAction *actionAbout;
    QAction *actionExit_2;
    QAction *actionDominio_Espacial;
    QAction *actionDominio_Frecuencial;
    QAction *actionResultados;
    QAction *actionFidelidad;
    QAction *actionCaracter_erroneo;
    QWidget *centralWidget;
    QLabel *label;
    QLabel *label_2;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEsteganografia;
    QMenu *menuAnalisi;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *principal)
    {
        if (principal->objectName().isEmpty())
            principal->setObjectName(QStringLiteral("principal"));
        principal->resize(714, 405);
        actionExit = new QAction(principal);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionAbout = new QAction(principal);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionExit_2 = new QAction(principal);
        actionExit_2->setObjectName(QStringLiteral("actionExit_2"));
        actionDominio_Espacial = new QAction(principal);
        actionDominio_Espacial->setObjectName(QStringLiteral("actionDominio_Espacial"));
        actionDominio_Frecuencial = new QAction(principal);
        actionDominio_Frecuencial->setObjectName(QStringLiteral("actionDominio_Frecuencial"));
        actionResultados = new QAction(principal);
        actionResultados->setObjectName(QStringLiteral("actionResultados"));
        actionFidelidad = new QAction(principal);
        actionFidelidad->setObjectName(QStringLiteral("actionFidelidad"));
        actionCaracter_erroneo = new QAction(principal);
        actionCaracter_erroneo->setObjectName(QStringLiteral("actionCaracter_erroneo"));
        centralWidget = new QWidget(principal);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 20, 281, 201));
        label->setPixmap(QPixmap(QString::fromUtf8("../../../../Pictures/esteganografia.jpg")));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(280, 240, 421, 91));
        QFont font;
        font.setPointSize(48);
        label_2->setFont(font);
        principal->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(principal);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 714, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuEsteganografia = new QMenu(menuBar);
        menuEsteganografia->setObjectName(QStringLiteral("menuEsteganografia"));
        menuAnalisi = new QMenu(menuBar);
        menuAnalisi->setObjectName(QStringLiteral("menuAnalisi"));
        principal->setMenuBar(menuBar);
        mainToolBar = new QToolBar(principal);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        principal->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(principal);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        principal->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEsteganografia->menuAction());
        menuBar->addAction(menuAnalisi->menuAction());
        menuFile->addAction(actionAbout);
        menuFile->addAction(actionExit_2);
        menuEsteganografia->addAction(actionDominio_Espacial);
        menuEsteganografia->addAction(actionDominio_Frecuencial);
        menuAnalisi->addAction(actionFidelidad);
        menuAnalisi->addAction(actionCaracter_erroneo);

        retranslateUi(principal);

        QMetaObject::connectSlotsByName(principal);
    } // setupUi

    void retranslateUi(QMainWindow *principal)
    {
        principal->setWindowTitle(QApplication::translate("principal", "principal", 0));
        actionExit->setText(QApplication::translate("principal", "Exit", 0));
        actionAbout->setText(QApplication::translate("principal", "About", 0));
        actionExit_2->setText(QApplication::translate("principal", "Exit", 0));
        actionDominio_Espacial->setText(QApplication::translate("principal", "Dominio Espacial", 0));
        actionDominio_Frecuencial->setText(QApplication::translate("principal", "Dominio Frecuencial", 0));
        actionResultados->setText(QApplication::translate("principal", "Histograma", 0));
        actionFidelidad->setText(QApplication::translate("principal", "Fidelidad", 0));
        actionCaracter_erroneo->setText(QApplication::translate("principal", "caracter erroneo", 0));
        label->setText(QString());
        label_2->setText(QApplication::translate("principal", "Esteganograf\303\255a", 0));
        menuFile->setTitle(QApplication::translate("principal", "File", 0));
        menuEsteganografia->setTitle(QApplication::translate("principal", "Esteganografia", 0));
        menuAnalisi->setTitle(QApplication::translate("principal", "Analisis", 0));
    } // retranslateUi

};

namespace Ui {
    class principal: public Ui_principal {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRINCIPAL_H
