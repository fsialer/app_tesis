#include "principal.h"
#include "ui_principal.h"

principal::principal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::principal)
{
    ui->setupUi(this);
}

principal::~principal()
{
    delete ui;
}

void principal::on_actionDominio_Espacial_triggered()
{
    dominioEspacial  *de=new dominioEspacial(this);
    de->setModal(true);
    de->show();
}

void principal::on_actionDominio_Frecuencial_triggered()
{
    dominioFrecuencial  *df=new dominioFrecuencial(this);
    df->setModal(true);
    df->show();
}

void principal::on_actionResultados_triggered()
{
    resultado *result=new resultado(this);
    result->setModal(true);
    result->show();

}

void principal::on_actionFidelidad_triggered()
{
    resultado2 *result=new resultado2(this);
    result->setModal(true);
    result->show();
}

void principal::on_actionCaracter_erroneo_triggered()
{
    resultado3 *result=new resultado3(this);
    result->setModal(true);
    result->show();
}
