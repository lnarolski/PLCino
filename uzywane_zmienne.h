#ifndef UZYWANE_ZMIENNE_H
#define UZYWANE_ZMIENNE_H

#include <QDialog>
#include "dodawanie_zmiennej.h"
#include "model_uzywane_zmienne.h"
#include "zmienna_w_arduino.h"

namespace Ui {
class uzywane_zmienne;
}

class uzywane_zmienne : public QDialog
{
    Q_OBJECT

public:
    explicit uzywane_zmienne(QMap<QString, zmienna_w_arduino> *lista, QWidget *parent = 0);
    ~uzywane_zmienne();

private slots:

    void on_nowa_clicked();

    void on_usun_clicked();

    void edycja_zmiennej(const QModelIndex ModelIndex);

private:
    Ui::uzywane_zmienne *ui;
    dodawanie_zmiennej* dialog; //okno odpowiedzialne za dodawanie nowych zmiennych
    QMap<QString, zmienna_w_arduino> *lista_uzywanych_zmiennych; //adres do listy używanych zmiennych
    model_uzywane_zmienne model; //model danych używany przez listę używanych zmiennych(zrobiony tylko po to, żeby móc ustawić nagłówki kolumn)
    dodawanie_zmiennej* okno_edycji_zmiennej;
};

#endif // UZYWANE_ZMIENNE_H
