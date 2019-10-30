#ifndef PLCINO_H
#define PLCINO_H

#include <QDesktopWidget>
#include <QTableWidget>
#include <QStandardItemModel>
#include <QSizePolicy>
#include <QtDebug>
#include <QMessageBox>
#include <QInputDialog>
#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QList>
#include <QTableView>
#include <QStandardItemModel>
#include <QMap>
#include <QString>
#include <QFileDialog>
#include <QDir>
#include <QWizard>
#include <QLabel>
#include <QLineEdit>
#include <QProcess>
#include <QSerialPort>
#include <QThread>
#include <QSerialPortInfo>
#include <uzywane_zmienne.h>
#include <model_drabinka.h>
#include <wybor_portu.h>
#include <zmienna_w_arduino.h>
#include <edycja_specjalna.h>
#include "elementy_schematu.h"

enum rodzaje_obslugiwanych_plytek {
    leonardo,
    nano,
    mega,
    brak
};

namespace Ui {
class PLCino;
}

class PLCino : public QMainWindow //główna klasa programu
{
    Q_OBJECT

public:
    explicit PLCino(QWidget *parent = 0);
    ~PLCino();

private slots:
    void on_actionNowy_obwod_triggered();

    void on_actionUsun_obwod_triggered();

    void on_actionDodaj_kolumne_triggered();

    void on_actionUsun_kolumne_triggered();

    void on_actionDodaj_wiersz_triggered();

    void on_actionUsun_wiersz_triggered();

    void on_actionUzywane_zmienne_triggered();

    void on_actionPort_triggered();

    void edycja_wlasciwosci(const QModelIndex ModelIndex);

    void on_actionLeonadro_triggered();

    void on_actionMega_triggered();

    void on_actionNano_triggered();

    void on_actionNowy_triggered();

    void on_actionZamknij_triggered();

    void on_actionKompiluj_do_C_triggered();

    void on_actionKompiluj_i_wgraj_do_Arduino_triggered();

    void on_actionZapisz_triggered();

    void on_actionOtworz_triggered();

    void on_actionEdycja_wlasciwosci_triggered();

    void on_actionUsun_element_triggered();

    void on_actionWgraj_plik_C_do_Arduino_triggered();

public:
    Ui::PLCino *ui;
    QList<QTableView*> lista_obwodow; //lista graficznych obwodów(tabel)
    QList<model_drabinka*> lista_modeli; //lista modeli danych dla każdego graficznego obwodu
    QMap<QString, zmienna_w_arduino> lista_uzywanych_zmiennych; //lista używanych zmiennych z nazwami w środowisku graficznym oraz odpowiadającymi im nazwami w programie Arduino
    uzywane_zmienne* okno_edycji_zmiennych; //okno służące do edycji listy używanych zmiennych
    QDialog* okno_wyboru_portu; //okno używane do wyboru portu COM, do którego podłączona jest płytka Arduino
    dodawanie_zmiennej *okno_dodawanie_zmiennej; //okno pojawiające się, gdy użytkownik chce ustawić zmienną do elementu, która jeszcze nie istnieje
    edycja_specjalna *okno_edycji_specjalnej;

    struct {
        QString nazwa_wybranego_portu;
        rodzaje_obslugiwanych_plytek wybrana_plytka;
        QString sciezka_zapisu_projektu;
        QString sciezka_zapisu_kompilacja;
    } konfiguracja; //struktura z konfiguracją programu

private:
    int kompilator();
    int wybranie_sciezki_zapisu(int);

    //ELEMENTY WYKORZYSTYWANE NA POTRZEBY KOMPILACJI
    QString warunek;
    bool sprawdz_czy_jest_na_liscie(elementy_drabinki* a, QList<elementy_schematu*>* b);
    bool sprawdz_czy_jest_na_liscie(elementy_schematu* a, QList<elementy_schematu*> b);
    bool sprawdz_czy_jest_na_liscie(QString a, QList<elementy_schematu*> liczniki, QList<elementy_schematu *> timery);
    bool sprawdz_czy_jest_na_wejsciu_lub_wyjsciu(elementy_drabinki* a, elementy_schematu* b);
    elementy_schematu* znajdz_element_drabinki(QList <elementy_schematu*> lista, elementy_drabinki* a);
    bool czy_styk_nalezy_do_bloku_funkcyjnego(QString nazwa_zmiennej, QList<elementy_schematu*> liczniki, QList<elementy_schematu*> timery);
    void tworzenie_warunkow(QTextStream &out, elementy_schematu* element, QString string, QList<elementy_schematu*> liczniki, QList<elementy_schematu*> timery);
    QString poszukiwanie_portu_bootloadera(QList<QSerialPortInfo> *przed_resetem, QList<QSerialPortInfo> *po_resecie);
};

#endif // PLCINO_H
