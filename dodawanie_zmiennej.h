#ifndef DODAWANIE_ZMIENNEJ_H
#define DODAWANIE_ZMIENNEJ_H

#include <QDialog>
#include <QMap>
#include <QString>
#include "model_uzywane_zmienne.h"
#include <zmienna_w_arduino.h>

namespace Ui {
class dodawanie_zmiennej;
}

class dodawanie_zmiennej : public QDialog
{
    Q_OBJECT

public:
    explicit dodawanie_zmiennej(QMap<QString, zmienna_w_arduino> *lista, model_uzywane_zmienne *model, QString nazwa_zmiennej = "", QString *adres_nazwy_zmiennej_z_modelu_drabinki = NULL, QString numer_pinu = "", quint32 rodzaj_zmiennej = 0, quint32 typ_pinu = 0, QWidget *parent = 0);
    ~dodawanie_zmiennej();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

public:
    Ui::dodawanie_zmiennej *ui;
private:
    QMap<QString, zmienna_w_arduino> *lista_uzywanych_zmiennych; //adres do listy używanych zmiennych w głównej klasie
    model_uzywane_zmienne *model_temp; //adres do modelu danych używanego przez listę używanych zmiennych
    QString* nazwa_wybranej_zmiennej;
};

#endif // DODAWANIE_ZMIENNEJ_H
