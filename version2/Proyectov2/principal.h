#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QMainWindow>
#include <dominioespacial.h>
#include <dominiofrecuencial.h>
#include <resultado.h>
#include <resultado2.h>
#include <resultado3.h>

namespace Ui {
class principal;
}

class principal : public QMainWindow
{
    Q_OBJECT

public:
    explicit principal(QWidget *parent = 0);
    ~principal();

private slots:
    void on_actionDominio_Espacial_triggered();

    void on_actionDominio_Frecuencial_triggered();

    void on_actionResultados_triggered();

    void on_actionFidelidad_triggered();

    void on_actionCaracter_erroneo_triggered();

private:
    Ui::principal *ui;
};

#endif // PRINCIPAL_H
