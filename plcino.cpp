#define PROJEKT 0
#define KOMPILACJA 1
#define ROZMIAR_BUFORA 10240

#include "plcino.h"
#include "ui_plcino.h"
#include "elementy_drabinki.h"
#include <stdio.h>


PLCino::PLCino(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PLCino)
{
    ui->setupUi(this);
    okno_edycji_zmiennych = NULL;
    okno_wyboru_portu = NULL;
    okno_dodawanie_zmiennej = NULL;
    okno_edycji_specjalnej = NULL;
    //maksymalizacja okna aplikacji i blokada zmiany rozmiaru
    this->setWindowState(Qt::WindowMaximized); //maksymalizacja okna
    this->setFixedSize(QDesktopWidget().availableGeometry(this).size()); //ustawienie stałego rozmiaru okna programu
    this->konfiguracja.wybrana_plytka = brak;
}

PLCino::~PLCino()
{
    delete ui;
}

void PLCino::on_actionNowy_obwod_triggered()
{
    lista_obwodow.insert(lista_obwodow.size(), new QTableView(this));
    lista_modeli.insert(lista_modeli.size(), new model_drabinka(this));
    lista_obwodow[lista_obwodow.size() - 1]->setModel(lista_modeli[lista_modeli.size() - 1]);
    lista_obwodow[lista_obwodow.size() - 1]->setAcceptDrops(true);
    lista_obwodow[lista_obwodow.size() - 1]->setDropIndicatorShown(true);
    lista_obwodow[lista_obwodow.size() - 1]->setDragDropOverwriteMode(true);
    lista_obwodow[lista_obwodow.size() - 1]->setSelectionMode(QAbstractItemView::SingleSelection); //możliwość zaznaczenia tylko jednej komórki
    lista_obwodow[lista_obwodow.size() - 1]->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
    lista_obwodow[lista_obwodow.size() - 1]->setMinimumHeight(400);
    lista_obwodow[lista_obwodow.size() - 1]->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    lista_obwodow[lista_obwodow.size() - 1]->verticalHeader()->setDefaultSectionSize(100);
    lista_obwodow[lista_obwodow.size() - 1]->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    lista_obwodow[lista_obwodow.size() - 1]->horizontalHeader()->setDefaultSectionSize(100);
    ui->verticalLayout->addWidget(lista_obwodow[lista_obwodow.size() - 1],0);
    connect(lista_obwodow[lista_obwodow.size() - 1], SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(edycja_wlasciwosci(const QModelIndex &))); //podłączenie sygnału podwójnego kliknięcia do metody edycja_wlasciwosci
//    statusBar()->showMessage("Liczba linii: " + QString::number(lista_linii.size()) + " LayoutStretch: " + QString::number(ui->verticalLayout->stretch(lista_linii.size()-1))); //DEBUG
}

void PLCino::on_actionUsun_obwod_triggered()
{
    for (int i = 0; i < lista_obwodow.size(); i++) {
        if(lista_obwodow[i]->hasFocus()) {
            QLayoutItem *element_layout = ui->verticalLayout->takeAt(i); //OGARNĄĆ CO TU SIĘ DZIEJE
            delete element_layout->widget();
            delete element_layout;
            lista_obwodow.removeAt(i);
            lista_modeli.removeAt(i);
            break;
        }
    }
}

void PLCino::on_actionDodaj_kolumne_triggered()
{
    for (int i = 0; i < lista_obwodow.size(); i++) {
        if(lista_obwodow[i]->hasFocus()) {
            QModelIndexList zaznaczenie = lista_obwodow[i]->selectionModel()->selectedIndexes();
            if(zaznaczenie.length() != 0)
                lista_modeli[i]->insertColumn(zaznaczenie[0].column()+1);
            else
                lista_modeli[i]->insertColumn(0);
        }
    }
}

void PLCino::on_actionUsun_kolumne_triggered()
{
    for (int i = 0; i < lista_obwodow.size(); i++) {
        if(lista_obwodow[i]->hasFocus()) {
            QModelIndexList zaznaczenie = lista_obwodow[i]->selectionModel()->selectedIndexes();
            if(zaznaczenie.length() != 0)
                lista_modeli[i]->removeColumn(zaznaczenie[0].column());
        }
    }
}

void PLCino::on_actionDodaj_wiersz_triggered()
{
    for (int i = 0; i < lista_obwodow.size(); i++) {
        if(lista_obwodow[i]->hasFocus()) {
            QModelIndexList zaznaczenie = lista_obwodow[i]->selectionModel()->selectedIndexes();
            if(zaznaczenie.length() != 0)
                lista_modeli[i]->insertRow(zaznaczenie[0].row()+1);
            else
                lista_modeli[i]->insertRow(0);
        }
    }
}


void PLCino::on_actionUsun_wiersz_triggered()
{
    for (int i = 0; i < lista_obwodow.size(); i++) {
        if(lista_obwodow[i]->hasFocus()) {
            QModelIndexList zaznaczenie = lista_obwodow[i]->selectionModel()->selectedIndexes();
            if(zaznaczenie.length() != 0)
                lista_modeli[i]->removeRow(zaznaczenie[0].row());
        }
    }
}

void PLCino::on_actionUzywane_zmienne_triggered()
{
    if (okno_edycji_zmiennych == NULL) {
        okno_edycji_zmiennych = new uzywane_zmienne(&lista_uzywanych_zmiennych, this);
        okno_edycji_zmiennych->show();
    }
    else {
        delete okno_edycji_zmiennych;
        okno_edycji_zmiennych = new uzywane_zmienne(&lista_uzywanych_zmiennych, this);
        okno_edycji_zmiennych->show();
    }
}

void PLCino::on_actionPort_triggered()
{
    if(okno_wyboru_portu == NULL) {
        okno_wyboru_portu = new Wybor_portu(this, &konfiguracja.nazwa_wybranego_portu);
        okno_wyboru_portu->show();
    }
    else {
        okno_wyboru_portu->show();
    }
}

void PLCino::edycja_wlasciwosci(const QModelIndex ModelIndex)
{
    if(ModelIndex.isValid()) {
        for (int i = 0; i < lista_obwodow.size(); i++) {
            if(lista_obwodow[i]->hasFocus()) {
                if (lista_modeli[i]->model_dane.at(ModelIndex.row())->at(ModelIndex.column())->rodzaj != pusty && lista_modeli[i]->model_dane.at(ModelIndex.row())->at(ModelIndex.column())->rodzaj != lacznik) {
                    if (lista_modeli[i]->model_dane.at(ModelIndex.row())->at(ModelIndex.column())->rodzaj != cewka && lista_modeli[i]->model_dane.at(ModelIndex.row())->at(ModelIndex.column())->rodzaj != styk) {
                        if (okno_edycji_specjalnej == NULL) {
                            okno_edycji_specjalnej = new edycja_specjalna(lista_modeli[i]->model_dane.at(ModelIndex.row())->at(ModelIndex.column()));
                        }
                        else {
                            delete okno_edycji_specjalnej;
                            okno_edycji_specjalnej = new edycja_specjalna(lista_modeli[i]->model_dane.at(ModelIndex.row())->at(ModelIndex.column()));
                        }
                        okno_edycji_specjalnej->exec();
                    }
                    else {
                        bool ok; //wciśnięcie przycisku OK w oknie dialogowym
                        QString zmienna;
                        zmienna = QInputDialog::getText(this, tr("Wprowadzanie nazwy zmiennej"),
                                                        tr("Podaj nazwę zmiennej:"), QLineEdit::Normal, "", &ok);
                        if (ok) {
                            if (!lista_uzywanych_zmiennych.contains(zmienna)) {
                                bool zmienna_jest_liczba;
                                if (zmienna.toInt(&zmienna_jest_liczba)) {
                                    lista_modeli[i]->model_dane.at(ModelIndex.row())->at(ModelIndex.column())->zmienna = zmienna;
                                }
                                else {
                                    if (okno_dodawanie_zmiennej == NULL)
                                        okno_dodawanie_zmiennej = new dodawanie_zmiennej(&lista_uzywanych_zmiennych, NULL, zmienna, &lista_modeli[i]->model_dane.at(ModelIndex.row())->at(ModelIndex.column())->zmienna);
                                    else {
                                        delete okno_dodawanie_zmiennej;
                                        okno_dodawanie_zmiennej = new dodawanie_zmiennej(&lista_uzywanych_zmiennych, NULL, zmienna, &lista_modeli[i]->model_dane.at(ModelIndex.row())->at(ModelIndex.column())->zmienna);
                                    }
                                    //                                okno_dodawanie_zmiennej->show();
                                    okno_dodawanie_zmiennej->exec(); //aby nie było można kliknąć niczego poza obszarem okna
                                }
                            }
                            else {
                                lista_modeli[i]->model_dane.at(ModelIndex.row())->at(ModelIndex.column())->zmienna = zmienna;
                            }
                        }
                    }
                }
            }
        }
    }
}

void PLCino::on_actionLeonadro_triggered()
{
    konfiguracja.wybrana_plytka = leonardo;
    ui->actionMega->setChecked(false);
    ui->actionNano->setChecked(false);
    ui->actionLeonadro->setChecked(true);
}

void PLCino::on_actionMega_triggered()
{
    konfiguracja.wybrana_plytka = mega;
    ui->actionLeonadro->setChecked(false);
    ui->actionNano->setChecked(false);
    ui->actionMega->setChecked(true);
}

void PLCino::on_actionNano_triggered()
{
    konfiguracja.wybrana_plytka = nano;
    ui->actionMega->setChecked(false);
    ui->actionLeonadro->setChecked(false);
    ui->actionNano->setChecked(true);
}

void PLCino::on_actionNowy_triggered()
{
    QMessageBox msgBox;
    msgBox.setText("Czy na pewno zamknąć stary projekt?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int wybrany_przycisk = msgBox.exec();
    if (wybrany_przycisk == QMessageBox::Ok) {
        QLayoutItem *element_layout;
        while ((element_layout = ui->verticalLayout->takeAt(0)) != 0) { //OGARNĄĆ CO TU SIĘ DZIEJE
            delete element_layout->widget();
            delete element_layout;
        }
        lista_obwodow.clear();
        lista_modeli.clear();
        lista_uzywanych_zmiennych.clear();
        konfiguracja.wybrana_plytka = brak;
    }
}

void PLCino::on_actionZamknij_triggered()
{
    exit(0);
}

int PLCino::kompilator()
{
    QList<elementy_schematu*> liczniki;
    QList<elementy_schematu*> timery;
    QList<elementy_schematu*> cewki;
    QList<elementy_schematu*> rozdzielacze;
    QList<QList <elementy_schematu*>*> przetworzone_obwody;
    QList<QList <elementy_schematu*>*> poczatki;
    QList<QList <elementy_schematu*>*> konce;

    //ROZPOCZĘCIE ANALIZY KOLEJNYCH LINII(poszukiwanie elementów "wykonawczych" i rozdzielaczy)
    for (int i = 0; i < lista_modeli.count(); ++i) {
        przetworzone_obwody.append(new QList <elementy_schematu*>);
        poczatki.append(new QList <elementy_schematu*>);
        konce.append(new QList <elementy_schematu*>);
        for (int j = 0; j < lista_modeli[i]->model_dane.count(); ++j) {
            for (int k = 0; k < lista_modeli[i]->model_dane.at(j)->count(); ++k) {
                switch (lista_modeli[i]->model_dane.at(j)->at(k)->rodzaj) {
                case lacznik:
                    switch (lista_modeli[i]->model_dane.at(j)->at(k)->rodzaj2) {
                    case GORA_PRAWO_DOL:
                        rozdzielacze.append(new elementy_schematu(lista_modeli[i]->model_dane.at(j)->at(k), i, k, j));
                        break;
                    case GORA_LEWO_DOL:
                        rozdzielacze.append(new elementy_schematu(lista_modeli[i]->model_dane.at(j)->at(k), i, k, j));
                        break;
                    case LEWO_DOL_PRAWO:
                        rozdzielacze.append(new elementy_schematu(lista_modeli[i]->model_dane.at(j)->at(k), i, k, j));
                        break;
                    case LEWO_GORA_PRAWO:
                        rozdzielacze.append(new elementy_schematu(lista_modeli[i]->model_dane.at(j)->at(k), i, k, j));
                        break;
                    case GORA_DOL_LEWO_PRAWO:
                        rozdzielacze.append(new elementy_schematu(lista_modeli[i]->model_dane.at(j)->at(k), i, k, j));
                        break;
                    default:
                        break;
                    }
                    break;
                case blok_funkcyjny:
                    switch (lista_modeli[i]->model_dane.at(j)->at(k)->rodzaj2) {
                    case LICZNIK:
                        liczniki.append(new elementy_schematu(lista_modeli[i]->model_dane.at(j)->at(k), i, k, j));
                        przetworzone_obwody[i]->append(new elementy_schematu(lista_modeli[i]->model_dane.at(j)->at(k), i, k, j));
                        break;
                    case TIMER:
                        timery.append(new elementy_schematu(lista_modeli[i]->model_dane.at(j)->at(k), i, k, j));
                        przetworzone_obwody[i]->append(new elementy_schematu(lista_modeli[i]->model_dane.at(j)->at(k), i, k, j));
                    default:
                        break;
                    }
                    //przetworzone_linie[i]->append(new elementy_schematu(lista_modeli[i]->model_dane.at(j)->at(k), i, k, j));
                    konce[i]->append(new elementy_schematu(lista_modeli[i]->model_dane.at(j)->at(k), i, k, j));
                    break;
                case cewka:
                    cewki.append(new elementy_schematu(lista_modeli[i]->model_dane.at(j)->at(k), i, k, j));
                    przetworzone_obwody[i]->append(new elementy_schematu(lista_modeli[i]->model_dane.at(j)->at(k), i, k, j));
                    konce[i]->append(new elementy_schematu(lista_modeli[i]->model_dane.at(j)->at(k), i, k, j));
                    break;
                case styk:
                    przetworzone_obwody[i]->append(new elementy_schematu(lista_modeli[i]->model_dane.at(j)->at(k), i, k, j));
                    break;
                case operator_porownania:
                    przetworzone_obwody[i]->append(new elementy_schematu(lista_modeli[i]->model_dane.at(j)->at(k), i, k, j));
                    break;
                default:
                    break;
                }
            }
        }
    }
    //UPRASZCZENIE SCHEMATÓW
    for(int i = rozdzielacze.count() - 1; i >= 0; --i) { //wykrywanie do czego są podłączone rozdzielacze
        switch (rozdzielacze.at(i)->element->rodzaj2) {
        case GORA_PRAWO_DOL:
            for (int j = 0; j < 3; ++j) {
                int x = rozdzielacze.at(i)->numer_kolumny, y = rozdzielacze.at(i)->numer_wiersza, x_poprz = rozdzielacze.at(i)->numer_kolumny, y_poprz = rozdzielacze.at(i)->numer_wiersza;
                bool koniec = false;
                switch (j) {
                case 0: //GÓRA
                    --y;
                    while(!koniec) {
                        switch (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj) {
                        case lacznik:
                            if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_PRAWO_DOL || lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_LEWO_DOL || lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == LEWO_DOL_PRAWO || lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == LEWO_GORA_PRAWO || lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_DOL_LEWO_PRAWO) {
                                if (!sprawdz_czy_jest_na_wejsciu_lub_wyjsciu(lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x), rozdzielacze.at(i))) {
                                    rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(rozdzielacze, lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                    //znajdz_element_drabinki(rozdzielacze, rozdzielacze.at(i)->element)->wejscia_elementu.append(rozdzielacze[i]);
                                    koniec = true;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == LEWO_PRAWO) {
                                if (x_poprz > x) { //RUCH W LEWO
                                    if (x == 0) { //PIERWSZA KOLUMNA
                                        rozdzielacze[i]->wejscia_elementu.append(NULL);
                                        koniec = true;
                                    }
                                    else {
                                        --x;
                                        --x_poprz;
                                    }
                                }
                                else { //RUCH W PRAWO
                                    ++x;
                                    ++x_poprz;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_DOL) {
                                if (y_poprz > y) { //RUCH W GÓRĘ
                                    --y;
                                    --y_poprz;
                                }
                                else { //RUCH W DOŁ
                                    ++y;
                                    ++y_poprz;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == DOL_PRAWO) {
                                if (y_poprz > y) { //ZMIANA KIERUNKU W PRAWO
                                    ++x;
                                    ++y_poprz;
                                }
                                else { //ZMIANA KIERUNKU W DÓŁ
                                    --y;
                                    --x_poprz;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == DOL_LEWO) {
                                if (y_poprz > y) { //ZMIANA KIERUNKU W LEWO
                                    if (x == 0) {
                                        rozdzielacze[i]->wejscia_elementu.append(NULL);
                                        koniec = true;
                                    }
                                    else {
                                        --x;
                                        ++y_poprz;
                                    }
                                }
                                else { //ZMIANA KIERUNKU W DÓŁ
                                    ++y;
                                    ++x_poprz;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_PRAWO) {
                                if (y > y_poprz) { //ZMIANA KIERUNKU W PRAWO
                                    ++x;
                                    y_poprz++;
                                }
                                else { //ZMIANA KIERUNKU W GÓRĘ
                                    --y;
                                    --x_poprz;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_LEWO) {
                                if (y > y_poprz) { //ZMIANA KIERUNKU W LEWO
                                    if (x == 0) {
                                        rozdzielacze[i]->wejscia_elementu.append(NULL);
                                        koniec = true;
                                    }
                                    else {
                                        --x;
                                        ++y_poprz;
                                    }
                                } //ZMIANA KIERUNKU DO GÓRY
                                else {
                                    --y;
                                    ++x_poprz;
                                }
                            }
                            break;
                        case cewka:
                            rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                            znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wejscia_elementu.append(rozdzielacze[i]);
                            koniec = true;
                            break;
                        case styk:
                            if (x > x_poprz) {
                                rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wejscia_elementu.append(rozdzielacze[i]);
                            }
                            else {
                                rozdzielacze[i]->wejscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wyjscia_elementu.append(rozdzielacze[i]);
                            }
                            koniec = true;
                            break;
                        case operator_porownania:
                            if (x > x_poprz) {
                                rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wejscia_elementu.append(rozdzielacze[i]);
                            }
                            else {
                                rozdzielacze[i]->wejscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wyjscia_elementu.append(rozdzielacze[i]);
                            }
                            koniec = true;
                            break;
                        case blok_funkcyjny:
                            rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                            znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wejscia_elementu.append(rozdzielacze[i]);
                            koniec = true;
                            break;
                        default:
                            break;
                        }
                    }
                    break;
                case 1: //PRAWO
                    ++x;
                    while(!koniec) {
                        switch (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj) {
                        case lacznik:
                            if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_PRAWO_DOL || lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_LEWO_DOL || lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == LEWO_DOL_PRAWO || lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == LEWO_GORA_PRAWO || lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_DOL_LEWO_PRAWO) {
                                if (!sprawdz_czy_jest_na_wejsciu_lub_wyjsciu(lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x), rozdzielacze.at(i))) {
                                    rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(rozdzielacze, lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                    //znajdz_element_drabinki(rozdzielacze, rozdzielacze.at(i)->element)->wejscia_elementu.append(rozdzielacze[i]);
                                    koniec = true;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == LEWO_PRAWO) {
                                if (x_poprz > x) { //RUCH W LEWO
                                    if (x == 0) { //PIERWSZA KOLUMNA
                                        rozdzielacze[i]->wejscia_elementu.append(NULL);
                                        koniec = true;
                                    }
                                    else {
                                        --x;
                                        --x_poprz;
                                    }
                                }
                                else { //RUCH W PRAWO
                                    ++x;
                                    ++x_poprz;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_DOL) {
                                if (y_poprz > y) { //RUCH W GÓRĘ
                                    --y;
                                    --y_poprz;
                                }
                                else { //RUCH W DOŁ
                                    ++y;
                                    ++y_poprz;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == DOL_PRAWO) {
                                if (y_poprz > y) { //ZMIANA KIERUNKU W PRAWO
                                    ++x;
                                    ++y_poprz;
                                }
                                else { //ZMIANA KIERUNKU W DÓŁ
                                    --y;
                                    --x_poprz;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == DOL_LEWO) {
                                if (y_poprz > y) { //ZMIANA KIERUNKU W LEWO
                                    if (x == 0) {
                                        rozdzielacze[i]->wejscia_elementu.append(NULL);
                                        koniec = true;
                                    }
                                    else {
                                        --x;
                                        ++y_poprz;
                                    }
                                }
                                else { //ZMIANA KIERUNKU W DÓŁ
                                    ++y;
                                    ++x_poprz;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_PRAWO) {
                                if (y > y_poprz) { //ZMIANA KIERUNKU W PRAWO
                                    ++x;
                                    y_poprz++;
                                }
                                else { //ZMIANA KIERUNKU W GÓRĘ
                                    --y;
                                    --x_poprz;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_LEWO) {
                                if (y > y_poprz) { //ZMIANA KIERUNKU W LEWO
                                    if (x == 0) {
                                        rozdzielacze[i]->wejscia_elementu.append(NULL);
                                        koniec = true;
                                    }
                                    else {
                                        --x;
                                        ++y_poprz;
                                    }
                                } //ZMIANA KIERUNKU DO GÓRY
                                else {
                                    --y;
                                    ++x_poprz;
                                }
                            }
                            break;
                        case cewka:
                            rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                            znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wejscia_elementu.append(rozdzielacze[i]);
                            koniec = true;
                            break;
                        case styk:
                            if (x > x_poprz) {
                                rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wejscia_elementu.append(rozdzielacze[i]);
                            }
                            else {
                                rozdzielacze[i]->wejscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wyjscia_elementu.append(rozdzielacze[i]);
                            }
                            koniec = true;
                            break;
                        case operator_porownania:
                            if (x > x_poprz) {
                                rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wejscia_elementu.append(rozdzielacze[i]);
                            }
                            else {
                                rozdzielacze[i]->wejscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wyjscia_elementu.append(rozdzielacze[i]);
                            }
                            koniec = true;
                            break;
                        case blok_funkcyjny:
                            rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                            znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wejscia_elementu.append(rozdzielacze[i]);
                            koniec = true;
                            break;
                        default:
                            break;
                        }
                    }
                    break;
                case 2: //DÓŁ
                    ++y;
                    while(!koniec) {
                        switch (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj) {
                        case lacznik:
                            if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_PRAWO_DOL || lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_LEWO_DOL || lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == LEWO_DOL_PRAWO || lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == LEWO_GORA_PRAWO || lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_DOL_LEWO_PRAWO) {
                                if (!sprawdz_czy_jest_na_wejsciu_lub_wyjsciu(lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x), rozdzielacze.at(i))) {
                                    rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(rozdzielacze, lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                    //znajdz_element_drabinki(rozdzielacze, rozdzielacze.at(i)->element)->wejscia_elementu.append(rozdzielacze[i]);
                                    koniec = true;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == LEWO_PRAWO) {
                                if (x_poprz > x) { //RUCH W LEWO
                                    if (x == 0) { //PIERWSZA KOLUMNA
                                        rozdzielacze[i]->wejscia_elementu.append(NULL);
                                        koniec = true;
                                    }
                                    else {
                                        --x;
                                        --x_poprz;
                                    }
                                }
                                else { //RUCH W PRAWO
                                    ++x;
                                    ++x_poprz;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_DOL) {
                                if (y_poprz > y) { //RUCH W GÓRĘ
                                    --y;
                                    --y_poprz;
                                }
                                else { //RUCH W DOŁ
                                    ++y;
                                    ++y_poprz;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == DOL_PRAWO) {
                                if (y_poprz > y) { //ZMIANA KIERUNKU W PRAWO
                                    ++x;
                                    ++y_poprz;
                                }
                                else { //ZMIANA KIERUNKU W DÓŁ
                                    --y;
                                    --x_poprz;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == DOL_LEWO) {
                                if (y_poprz > y) { //ZMIANA KIERUNKU W LEWO
                                    if (x == 0) {
                                        rozdzielacze[i]->wejscia_elementu.append(NULL);
                                        koniec = true;
                                    }
                                    else {
                                        --x;
                                        ++y_poprz;
                                    }
                                }
                                else { //ZMIANA KIERUNKU W DÓŁ
                                    ++y;
                                    ++x_poprz;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_PRAWO) {
                                if (y > y_poprz) { //ZMIANA KIERUNKU W PRAWO
                                    ++x;
                                    y_poprz++;
                                }
                                else { //ZMIANA KIERUNKU W GÓRĘ
                                    --y;
                                    --x_poprz;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_LEWO) {
                                if (y > y_poprz) { //ZMIANA KIERUNKU W LEWO
                                    if (x == 0) {
                                        rozdzielacze[i]->wejscia_elementu.append(NULL);
                                        koniec = true;
                                    }
                                    else {
                                        --x;
                                        ++y_poprz;
                                    }
                                } //ZMIANA KIERUNKU DO GÓRY
                                else {
                                    --y;
                                    ++x_poprz;
                                }
                            }
                            break;
                        case cewka:
                            rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                            znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wejscia_elementu.append(rozdzielacze[i]);
                            koniec = true;
                            break;
                        case styk:
                            if (x > x_poprz) {
                                rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wejscia_elementu.append(rozdzielacze[i]);
                            }
                            else {
                                rozdzielacze[i]->wejscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wyjscia_elementu.append(rozdzielacze[i]);
                            }
                            koniec = true;
                            break;
                        case operator_porownania:
                            if (x > x_poprz) {
                                rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wejscia_elementu.append(rozdzielacze[i]);
                            }
                            else {
                                rozdzielacze[i]->wejscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wyjscia_elementu.append(rozdzielacze[i]);
                            }
                            koniec = true;
                            break;
                        case blok_funkcyjny:
                            rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                            znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wejscia_elementu.append(rozdzielacze[i]);
                            koniec = true;
                            break;
                        default:
                            break;
                        }
                    }
                    break;
                default:
                    break;
                }
            }
            break;
        case GORA_LEWO_DOL:
            for (int j = 0; j < 3; ++j) {
                int x = rozdzielacze.at(i)->numer_kolumny, y = rozdzielacze.at(i)->numer_wiersza, x_poprz = rozdzielacze.at(i)->numer_kolumny, y_poprz = rozdzielacze.at(i)->numer_wiersza;
                bool koniec = false;
                switch (j) {
                case 0: //GÓRA
                    --y;
                    while(!koniec) {
                        switch (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj) {
                        case lacznik:
                            if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_PRAWO_DOL || lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_LEWO_DOL || lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == LEWO_DOL_PRAWO || lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == LEWO_GORA_PRAWO || lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_DOL_LEWO_PRAWO) {
                                if (!sprawdz_czy_jest_na_wejsciu_lub_wyjsciu(lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x), rozdzielacze.at(i))) {
                                    rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(rozdzielacze, lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                    //znajdz_element_drabinki(rozdzielacze, rozdzielacze.at(i)->element)->wejscia_elementu.append(rozdzielacze[i]);
                                    koniec = true;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == LEWO_PRAWO) {
                                if (x_poprz > x) { //RUCH W LEWO
                                    if (x == 0) { //PIERWSZA KOLUMNA
                                        rozdzielacze[i]->wejscia_elementu.append(NULL);
                                        koniec = true;
                                    }
                                    else {
                                        --x;
                                        --x_poprz;
                                    }
                                }
                                else { //RUCH W PRAWO
                                    ++x;
                                    ++x_poprz;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_DOL) {
                                if (y_poprz > y) { //RUCH W GÓRĘ
                                    --y;
                                    --y_poprz;
                                }
                                else { //RUCH W DOŁ
                                    ++y;
                                    ++y_poprz;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == DOL_PRAWO) {
                                if (y_poprz > y) { //ZMIANA KIERUNKU W PRAWO
                                    ++x;
                                    ++y_poprz;
                                }
                                else { //ZMIANA KIERUNKU W DÓŁ
                                    --y;
                                    --x_poprz;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == DOL_LEWO) {
                                if (y_poprz > y) { //ZMIANA KIERUNKU W LEWO
                                    if (x == 0) {
                                        rozdzielacze[i]->wejscia_elementu.append(NULL);
                                        koniec = true;
                                    }
                                    else {
                                        --x;
                                        ++y_poprz;
                                    }
                                }
                                else { //ZMIANA KIERUNKU W DÓŁ
                                    ++y;
                                    ++x_poprz;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_PRAWO) {
                                if (y > y_poprz) { //ZMIANA KIERUNKU W PRAWO
                                    ++x;
                                    y_poprz++;
                                }
                                else { //ZMIANA KIERUNKU W GÓRĘ
                                    --y;
                                    --x_poprz;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_LEWO) {
                                if (y > y_poprz) { //ZMIANA KIERUNKU W LEWO
                                    if (x == 0) {
                                        rozdzielacze[i]->wejscia_elementu.append(NULL);
                                        koniec = true;
                                    }
                                    else {
                                        --x;
                                        ++y_poprz;
                                    }
                                } //ZMIANA KIERUNKU DO GÓRY
                                else {
                                    --y;
                                    ++x_poprz;
                                }
                            }
                            break;
                        case cewka:
                            rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                            znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wejscia_elementu.append(rozdzielacze[i]);
                            koniec = true;
                            break;
                        case styk:
                            if (x > x_poprz) {
                                rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wejscia_elementu.append(rozdzielacze[i]);
                            }
                            else {
                                rozdzielacze[i]->wejscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wyjscia_elementu.append(rozdzielacze[i]);
                            }
                            koniec = true;
                            break;
                        case operator_porownania:
                            if (x > x_poprz) {
                                rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wejscia_elementu.append(rozdzielacze[i]);
                            }
                            else {
                                rozdzielacze[i]->wejscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wyjscia_elementu.append(rozdzielacze[i]);
                            }
                            koniec = true;
                            break;
                        case blok_funkcyjny:
                            rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                            znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wejscia_elementu.append(rozdzielacze[i]);
                            koniec = true;
                            break;
                        default:
                            break;
                        }
                    }
                    break;
                case 1: //LEWO (SPRAWDZIĆ CZY X == 0)
                    if (x == 0) {

                    }
                    else {
                        --x;
                        while(!koniec) {
                            switch (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj) {
                            case lacznik:
                                if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_PRAWO_DOL || lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_LEWO_DOL || lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == LEWO_DOL_PRAWO || lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == LEWO_GORA_PRAWO || lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_DOL_LEWO_PRAWO) {
                                    if (!sprawdz_czy_jest_na_wejsciu_lub_wyjsciu(lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x), rozdzielacze.at(i))) {
                                        rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(rozdzielacze, lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                        //znajdz_element_drabinki(rozdzielacze, rozdzielacze.at(i)->element)->wejscia_elementu.append(rozdzielacze[i]);
                                        koniec = true;
                                    }
                                }
                                else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == LEWO_PRAWO) {
                                    if (x_poprz > x) { //RUCH W LEWO
                                        if (x == 0) { //PIERWSZA KOLUMNA
                                            rozdzielacze[i]->wejscia_elementu.append(NULL);
                                            koniec = true;
                                        }
                                        else {
                                            --x;
                                            --x_poprz;
                                        }
                                    }
                                    else { //RUCH W PRAWO
                                        ++x;
                                        ++x_poprz;
                                    }
                                }
                                else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_DOL) {
                                    if (y_poprz > y) { //RUCH W GÓRĘ
                                        --y;
                                        --y_poprz;
                                    }
                                    else { //RUCH W DOŁ
                                        ++y;
                                        ++y_poprz;
                                    }
                                }
                                else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == DOL_PRAWO) {
                                    if (y_poprz > y) { //ZMIANA KIERUNKU W PRAWO
                                        ++x;
                                        ++y_poprz;
                                    }
                                    else { //ZMIANA KIERUNKU W DÓŁ
                                        --y;
                                        --x_poprz;
                                    }
                                }
                                else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == DOL_LEWO) {
                                    if (y_poprz > y) { //ZMIANA KIERUNKU W LEWO
                                        if (x == 0) {
                                            rozdzielacze[i]->wejscia_elementu.append(NULL);
                                            koniec = true;
                                        }
                                        else {
                                            --x;
                                            ++y_poprz;
                                        }
                                    }
                                    else { //ZMIANA KIERUNKU W DÓŁ
                                        ++y;
                                        ++x_poprz;
                                    }
                                }
                                else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_PRAWO) {
                                    if (y > y_poprz) { //ZMIANA KIERUNKU W PRAWO
                                        ++x;
                                        y_poprz++;
                                    }
                                    else { //ZMIANA KIERUNKU W GÓRĘ
                                        --y;
                                        --x_poprz;
                                    }
                                }
                                else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_LEWO) {
                                    if (y > y_poprz) { //ZMIANA KIERUNKU W LEWO
                                        if (x == 0) {
                                            rozdzielacze[i]->wejscia_elementu.append(NULL);
                                            koniec = true;
                                        }
                                        else {
                                            --x;
                                            ++y_poprz;
                                        }
                                    } //ZMIANA KIERUNKU DO GÓRY
                                    else {
                                        --y;
                                        ++x_poprz;
                                    }
                                }
                                break;
                            case cewka:
                                rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wejscia_elementu.append(rozdzielacze[i]);
                                koniec = true;
                                break;
                            case styk:
                                if (x > x_poprz) {
                                    rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                    znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wejscia_elementu.append(rozdzielacze[i]);
                                }
                                else {
                                    rozdzielacze[i]->wejscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                    znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wyjscia_elementu.append(rozdzielacze[i]);
                                }
                                koniec = true;
                                break;
                            case operator_porownania:
                                if (x > x_poprz) {
                                    rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                    znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wejscia_elementu.append(rozdzielacze[i]);
                                }
                                else {
                                    rozdzielacze[i]->wejscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                    znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wyjscia_elementu.append(rozdzielacze[i]);
                                }
                                koniec = true;
                                break;
                            case blok_funkcyjny:
                                rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wejscia_elementu.append(rozdzielacze[i]);
                                koniec = true;
                                break;
                            default:
                                break;
                            }
                        }
                    }
                    break;
                case 2: //DÓŁ
                    ++y;
                    while(!koniec) {
                        switch (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj) {
                        case lacznik:
                            if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_PRAWO_DOL || lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_LEWO_DOL || lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == LEWO_DOL_PRAWO || lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == LEWO_GORA_PRAWO || lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_DOL_LEWO_PRAWO) {
                                if (!sprawdz_czy_jest_na_wejsciu_lub_wyjsciu(lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x), rozdzielacze.at(i))) {
                                    rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(rozdzielacze, lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                    //znajdz_element_drabinki(rozdzielacze, rozdzielacze.at(i)->element)->wejscia_elementu.append(rozdzielacze[i]);
                                    koniec = true;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == LEWO_PRAWO) {
                                if (x_poprz > x) { //RUCH W LEWO
                                    if (x == 0) { //PIERWSZA KOLUMNA
                                        rozdzielacze[i]->wejscia_elementu.append(NULL);
                                        koniec = true;
                                    }
                                    else {
                                        --x;
                                        --x_poprz;
                                    }
                                }
                                else { //RUCH W PRAWO
                                    ++x;
                                    ++x_poprz;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_DOL) {
                                if (y_poprz > y) { //RUCH W GÓRĘ
                                    --y;
                                    --y_poprz;
                                }
                                else { //RUCH W DOŁ
                                    ++y;
                                    ++y_poprz;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == DOL_PRAWO) {
                                if (y_poprz > y) { //ZMIANA KIERUNKU W PRAWO
                                    ++x;
                                    ++y_poprz;
                                }
                                else { //ZMIANA KIERUNKU W DÓŁ
                                    --y;
                                    --x_poprz;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == DOL_LEWO) {
                                if (y_poprz > y) { //ZMIANA KIERUNKU W LEWO
                                    if (x == 0) {
                                        rozdzielacze[i]->wejscia_elementu.append(NULL);
                                        koniec = true;
                                    }
                                    else {
                                        --x;
                                        ++y_poprz;
                                    }
                                }
                                else { //ZMIANA KIERUNKU W DÓŁ
                                    ++y;
                                    ++x_poprz;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_PRAWO) {
                                if (y > y_poprz) { //ZMIANA KIERUNKU W PRAWO
                                    ++x;
                                    y_poprz++;
                                }
                                else { //ZMIANA KIERUNKU W GÓRĘ
                                    --y;
                                    --x_poprz;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_LEWO) {
                                if (y > y_poprz) { //ZMIANA KIERUNKU W LEWO
                                    if (x == 0) {
                                        rozdzielacze[i]->wejscia_elementu.append(NULL);
                                        koniec = true;
                                    }
                                    else {
                                        --x;
                                        ++y_poprz;
                                    }
                                } //ZMIANA KIERUNKU DO GÓRY
                                else {
                                    --y;
                                    ++x_poprz;
                                }
                            }
                            break;
                        case cewka:
                            rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                            znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wejscia_elementu.append(rozdzielacze[i]);
                            koniec = true;
                            break;
                        case styk:
                            if (x > x_poprz) {
                                rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wejscia_elementu.append(rozdzielacze[i]);
                            }
                            else {
                                rozdzielacze[i]->wejscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wyjscia_elementu.append(rozdzielacze[i]);
                            }
                            koniec = true;
                            break;
                        case operator_porownania:
                            if (x > x_poprz) {
                                rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wejscia_elementu.append(rozdzielacze[i]);
                            }
                            else {
                                rozdzielacze[i]->wejscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wyjscia_elementu.append(rozdzielacze[i]);
                            }
                            koniec = true;
                            break;
                        case blok_funkcyjny:
                            rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                            znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wejscia_elementu.append(rozdzielacze[i]);
                            koniec = true;
                            break;
                        default:
                            break;
                        }
                    }
                    break;
                default:
                    break;
                }
            }
            break;
        case LEWO_DOL_PRAWO:
            for (int j = 0; j < 3; ++j) {
                int x = rozdzielacze.at(i)->numer_kolumny, y = rozdzielacze.at(i)->numer_wiersza, x_poprz = rozdzielacze.at(i)->numer_kolumny, y_poprz = rozdzielacze.at(i)->numer_wiersza;
                bool koniec = false;
                switch (j) {
                case 0: //PRAWO
                    ++x;
                    while(!koniec) {
                        switch (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj) {
                        case lacznik:
                            if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_PRAWO_DOL || lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_LEWO_DOL || lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == LEWO_DOL_PRAWO || lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == LEWO_GORA_PRAWO || lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_DOL_LEWO_PRAWO) {
                                if (!sprawdz_czy_jest_na_wejsciu_lub_wyjsciu(lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x), rozdzielacze.at(i))) {
                                    rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(rozdzielacze, lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                    //znajdz_element_drabinki(rozdzielacze, rozdzielacze.at(i)->element)->wejscia_elementu.append(rozdzielacze[i]);
                                    koniec = true;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == LEWO_PRAWO) {
                                if (x_poprz > x) { //RUCH W LEWO
                                    if (x == 0) { //PIERWSZA KOLUMNA
                                        rozdzielacze[i]->wejscia_elementu.append(NULL);
                                        koniec = true;
                                    }
                                    else {
                                        --x;
                                        --x_poprz;
                                    }
                                }
                                else { //RUCH W PRAWO
                                    ++x;
                                    ++x_poprz;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_DOL) {
                                if (y_poprz > y) { //RUCH W GÓRĘ
                                    --y;
                                    --y_poprz;
                                }
                                else { //RUCH W DOŁ
                                    ++y;
                                    ++y_poprz;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == DOL_PRAWO) {
                                if (y_poprz > y) { //ZMIANA KIERUNKU W PRAWO
                                    ++x;
                                    ++y_poprz;
                                }
                                else { //ZMIANA KIERUNKU W DÓŁ
                                    --y;
                                    --x_poprz;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == DOL_LEWO) {
                                if (y_poprz > y) { //ZMIANA KIERUNKU W LEWO
                                    if (x == 0) {
                                        rozdzielacze[i]->wejscia_elementu.append(NULL);
                                        koniec = true;
                                    }
                                    else {
                                        --x;
                                        ++y_poprz;
                                    }
                                }
                                else { //ZMIANA KIERUNKU W DÓŁ
                                    ++y;
                                    ++x_poprz;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_PRAWO) {
                                if (y > y_poprz) { //ZMIANA KIERUNKU W PRAWO
                                    ++x;
                                    y_poprz++;
                                }
                                else { //ZMIANA KIERUNKU W GÓRĘ
                                    --y;
                                    --x_poprz;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_LEWO) {
                                if (y > y_poprz) { //ZMIANA KIERUNKU W LEWO
                                    if (x == 0) {
                                        rozdzielacze[i]->wejscia_elementu.append(NULL);
                                        koniec = true;
                                    }
                                    else {
                                        --x;
                                        ++y_poprz;
                                    }
                                } //ZMIANA KIERUNKU DO GÓRY
                                else {
                                    --y;
                                    ++x_poprz;
                                }
                            }
                            break;
                        case cewka:
                            rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                            znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wejscia_elementu.append(rozdzielacze[i]);
                            koniec = true;
                            break;
                        case styk:
                            if (x > x_poprz) {
                                rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wejscia_elementu.append(rozdzielacze[i]);
                            }
                            else {
                                rozdzielacze[i]->wejscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wyjscia_elementu.append(rozdzielacze[i]);
                            }
                            koniec = true;
                            break;
                        case operator_porownania:
                            if (x > x_poprz) {
                                rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wejscia_elementu.append(rozdzielacze[i]);
                            }
                            else {
                                rozdzielacze[i]->wejscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wyjscia_elementu.append(rozdzielacze[i]);
                            }
                            koniec = true;
                            break;
                        case blok_funkcyjny:
                            rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                            znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wejscia_elementu.append(rozdzielacze[i]);
                            koniec = true;
                            break;
                        default:
                            break;
                        }
                    }
                    break;
                case 1: //LEWO
                    if (x == 0) {
                        rozdzielacze[i]->wejscia_elementu.append(NULL);
                        koniec = true;
                    }
                    else {
                        --x;
                        while(!koniec) {
                            switch (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj) {
                            case lacznik:
                                if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_PRAWO_DOL || lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_LEWO_DOL || lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == LEWO_DOL_PRAWO || lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == LEWO_GORA_PRAWO || lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_DOL_LEWO_PRAWO) {
                                    if (!sprawdz_czy_jest_na_wejsciu_lub_wyjsciu(lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x), rozdzielacze.at(i))) {
                                        rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(rozdzielacze, lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                        //znajdz_element_drabinki(rozdzielacze, rozdzielacze.at(i)->element)->wejscia_elementu.append(rozdzielacze[i]);
                                        koniec = true;
                                    }
                                }
                                else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == LEWO_PRAWO) {
                                    if (x_poprz > x) { //RUCH W LEWO
                                        if (x == 0) { //PIERWSZA KOLUMNA
                                            rozdzielacze[i]->wejscia_elementu.append(NULL);
                                            koniec = true;
                                        }
                                        else {
                                            --x;
                                            --x_poprz;
                                        }
                                    }
                                    else { //RUCH W PRAWO
                                        ++x;
                                        ++x_poprz;
                                    }
                                }
                                else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_DOL) {
                                    if (y_poprz > y) { //RUCH W GÓRĘ
                                        --y;
                                        --y_poprz;
                                    }
                                    else { //RUCH W DOŁ
                                        ++y;
                                        ++y_poprz;
                                    }
                                }
                                else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == DOL_PRAWO) {
                                    if (y_poprz > y) { //ZMIANA KIERUNKU W PRAWO
                                        ++x;
                                        ++y_poprz;
                                    }
                                    else { //ZMIANA KIERUNKU W DÓŁ
                                        --y;
                                        --x_poprz;
                                    }
                                }
                                else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == DOL_LEWO) {
                                    if (y_poprz > y) { //ZMIANA KIERUNKU W LEWO
                                        if (x == 0) {
                                            rozdzielacze[i]->wejscia_elementu.append(NULL);
                                            koniec = true;
                                        }
                                        else {
                                            --x;
                                            ++y_poprz;
                                        }
                                    }
                                    else { //ZMIANA KIERUNKU W DÓŁ
                                        ++y;
                                        ++x_poprz;
                                    }
                                }
                                else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_PRAWO) {
                                    if (y > y_poprz) { //ZMIANA KIERUNKU W PRAWO
                                        ++x;
                                        y_poprz++;
                                    }
                                    else { //ZMIANA KIERUNKU W GÓRĘ
                                        --y;
                                        --x_poprz;
                                    }
                                }
                                else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_LEWO) {
                                    if (y > y_poprz) { //ZMIANA KIERUNKU W LEWO
                                        if (x == 0) {
                                            rozdzielacze[i]->wejscia_elementu.append(NULL);
                                            koniec = true;
                                        }
                                        else {
                                            --x;
                                            ++y_poprz;
                                        }
                                    } //ZMIANA KIERUNKU DO GÓRY
                                    else {
                                        --y;
                                        ++x_poprz;
                                    }
                                }
                                break;
                            case cewka:
                                rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wejscia_elementu.append(rozdzielacze[i]);
                                koniec = true;
                                break;
                            case styk:
                                if (x > x_poprz) {
                                    rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                    znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wejscia_elementu.append(rozdzielacze[i]);
                                }
                                else {
                                    rozdzielacze[i]->wejscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                    znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wyjscia_elementu.append(rozdzielacze[i]);
                                }
                                koniec = true;
                                break;
                            case operator_porownania:
                                if (x > x_poprz) {
                                    rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                    znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wejscia_elementu.append(rozdzielacze[i]);
                                }
                                else {
                                    rozdzielacze[i]->wejscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                    znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wyjscia_elementu.append(rozdzielacze[i]);
                                }
                                koniec = true;
                                break;
                            case blok_funkcyjny:
                                rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wejscia_elementu.append(rozdzielacze[i]);
                                koniec = true;
                                break;
                            default:
                                break;
                            }
                        }
                    }
                    break;
                case 2: //DÓŁ
                    ++y;
                    while(!koniec) {
                        switch (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj) {
                        case lacznik:
                            if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_PRAWO_DOL || lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_LEWO_DOL || lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == LEWO_DOL_PRAWO || lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == LEWO_GORA_PRAWO || lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_DOL_LEWO_PRAWO) {
                                if (!sprawdz_czy_jest_na_wejsciu_lub_wyjsciu(lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x), rozdzielacze.at(i))) {
                                    rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(rozdzielacze, lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                    //znajdz_element_drabinki(rozdzielacze, rozdzielacze.at(i)->element)->wejscia_elementu.append(rozdzielacze[i]);
                                    koniec = true;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == LEWO_PRAWO) {
                                if (x_poprz > x) { //RUCH W LEWO
                                    if (x == 0) { //PIERWSZA KOLUMNA
                                        rozdzielacze[i]->wejscia_elementu.append(NULL);
                                        koniec = true;
                                    }
                                    else {
                                        --x;
                                        --x_poprz;
                                    }
                                }
                                else { //RUCH W PRAWO
                                    ++x;
                                    ++x_poprz;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_DOL) {
                                if (y_poprz > y) { //RUCH W GÓRĘ
                                    --y;
                                    --y_poprz;
                                }
                                else { //RUCH W DOŁ
                                    ++y;
                                    ++y_poprz;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == DOL_PRAWO) {
                                if (y_poprz > y) { //ZMIANA KIERUNKU W PRAWO
                                    ++x;
                                    ++y_poprz;
                                }
                                else { //ZMIANA KIERUNKU W DÓŁ
                                    --y;
                                    --x_poprz;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == DOL_LEWO) {
                                if (y_poprz > y) { //ZMIANA KIERUNKU W LEWO
                                    if (x == 0) {
                                        rozdzielacze[i]->wejscia_elementu.append(NULL);
                                        koniec = true;
                                    }
                                    else {
                                        --x;
                                        ++y_poprz;
                                    }
                                }
                                else { //ZMIANA KIERUNKU W DÓŁ
                                    ++y;
                                    ++x_poprz;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_PRAWO) {
                                if (y > y_poprz) { //ZMIANA KIERUNKU W PRAWO
                                    ++x;
                                    y_poprz++;
                                }
                                else { //ZMIANA KIERUNKU W GÓRĘ
                                    --y;
                                    --x_poprz;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_LEWO) {
                                if (y > y_poprz) { //ZMIANA KIERUNKU W LEWO
                                    if (x == 0) {
                                        rozdzielacze[i]->wejscia_elementu.append(NULL);
                                        koniec = true;
                                    }
                                    else {
                                        --x;
                                        ++y_poprz;
                                    }
                                } //ZMIANA KIERUNKU DO GÓRY
                                else {
                                    --y;
                                    ++x_poprz;
                                }
                            }
                            break;
                        case cewka:
                            rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                            znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wejscia_elementu.append(rozdzielacze[i]);
                            koniec = true;
                            break;
                        case styk:
                            if (x > x_poprz) {
                                rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wejscia_elementu.append(rozdzielacze[i]);
                            }
                            else {
                                rozdzielacze[i]->wejscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wyjscia_elementu.append(rozdzielacze[i]);
                            }
                            koniec = true;
                            break;
                        case operator_porownania:
                            if (x > x_poprz) {
                                rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wejscia_elementu.append(rozdzielacze[i]);
                            }
                            else {
                                rozdzielacze[i]->wejscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wyjscia_elementu.append(rozdzielacze[i]);
                            }
                            koniec = true;
                            break;
                        case blok_funkcyjny:
                            rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                            znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wejscia_elementu.append(rozdzielacze[i]);
                            koniec = true;
                            break;
                        default:
                            break;
                        }
                    }
                    break;
                default:
                    break;
                }
            }
            break;
        case LEWO_GORA_PRAWO:
            for (int j = 0; j < 3; ++j) {
                int x = rozdzielacze.at(i)->numer_kolumny, y = rozdzielacze.at(i)->numer_wiersza, x_poprz = rozdzielacze.at(i)->numer_kolumny, y_poprz = rozdzielacze.at(i)->numer_wiersza;
                bool koniec = false;
                switch (j) {
                case 0: //GÓRA
                    --y;
                    while(!koniec) {
                        switch (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj) {
                        case lacznik:
                            if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_PRAWO_DOL || lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_LEWO_DOL || lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == LEWO_DOL_PRAWO || lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == LEWO_GORA_PRAWO || lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_DOL_LEWO_PRAWO) {
                                if (!sprawdz_czy_jest_na_wejsciu_lub_wyjsciu(lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x), rozdzielacze.at(i))) {
                                    rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(rozdzielacze, lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                    //znajdz_element_drabinki(rozdzielacze, rozdzielacze.at(i)->element)->wejscia_elementu.append(rozdzielacze[i]);
                                    koniec = true;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == LEWO_PRAWO) {
                                if (x_poprz > x) { //RUCH W LEWO
                                    if (x == 0) { //PIERWSZA KOLUMNA
                                        rozdzielacze[i]->wejscia_elementu.append(NULL);
                                        koniec = true;
                                    }
                                    else {
                                        --x;
                                        --x_poprz;
                                    }
                                }
                                else { //RUCH W PRAWO
                                    ++x;
                                    ++x_poprz;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_DOL) {
                                if (y_poprz > y) { //RUCH W GÓRĘ
                                    --y;
                                    --y_poprz;
                                }
                                else { //RUCH W DOŁ
                                    ++y;
                                    ++y_poprz;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == DOL_PRAWO) {
                                if (y_poprz > y) { //ZMIANA KIERUNKU W PRAWO
                                    ++x;
                                    ++y_poprz;
                                }
                                else { //ZMIANA KIERUNKU W DÓŁ
                                    --y;
                                    --x_poprz;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == DOL_LEWO) {
                                if (y_poprz > y) { //ZMIANA KIERUNKU W LEWO
                                    if (x == 0) {
                                        rozdzielacze[i]->wejscia_elementu.append(NULL);
                                        koniec = true;
                                    }
                                    else {
                                        --x;
                                        ++y_poprz;
                                    }
                                }
                                else { //ZMIANA KIERUNKU W DÓŁ
                                    ++y;
                                    ++x_poprz;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_PRAWO) {
                                if (y > y_poprz) { //ZMIANA KIERUNKU W PRAWO
                                    ++x;
                                    y_poprz++;
                                }
                                else { //ZMIANA KIERUNKU W GÓRĘ
                                    --y;
                                    --x_poprz;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_LEWO) {
                                if (y > y_poprz) { //ZMIANA KIERUNKU W LEWO
                                    if (x == 0) {
                                        rozdzielacze[i]->wejscia_elementu.append(NULL);
                                        koniec = true;
                                    }
                                    else {
                                        --x;
                                        ++y_poprz;
                                    }
                                } //ZMIANA KIERUNKU DO GÓRY
                                else {
                                    --y;
                                    ++x_poprz;
                                }
                            }
                            break;
                        case cewka:
                            rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                            znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wejscia_elementu.append(rozdzielacze[i]);
                            koniec = true;
                            break;
                        case styk:
                            if (x > x_poprz) {
                                rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wejscia_elementu.append(rozdzielacze[i]);
                            }
                            else {
                                rozdzielacze[i]->wejscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wyjscia_elementu.append(rozdzielacze[i]);
                            }
                            koniec = true;
                            break;
                        case operator_porownania:
                            if (x > x_poprz) {
                                rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wejscia_elementu.append(rozdzielacze[i]);
                            }
                            else {
                                rozdzielacze[i]->wejscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wyjscia_elementu.append(rozdzielacze[i]);
                            }
                            koniec = true;
                            break;
                        case blok_funkcyjny:
                            rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                            znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wejscia_elementu.append(rozdzielacze[i]);
                            koniec = true;
                            break;
                        default:
                            break;
                        }
                    }
                    break;
                case 1: //LEWO
                    if (x == 0) {
                        rozdzielacze[i]->wejscia_elementu.append(NULL);
                        koniec = true;
                    }
                    else {
                        --x;
                        while(!koniec) {
                            switch (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj) {
                            case lacznik:
                                if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_PRAWO_DOL || lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_LEWO_DOL || lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == LEWO_DOL_PRAWO || lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == LEWO_GORA_PRAWO || lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_DOL_LEWO_PRAWO) {
                                    if (!sprawdz_czy_jest_na_wejsciu_lub_wyjsciu(lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x), rozdzielacze.at(i))) {
                                        rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(rozdzielacze, lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                        //znajdz_element_drabinki(rozdzielacze, rozdzielacze.at(i)->element)->wejscia_elementu.append(rozdzielacze[i]);
                                        koniec = true;
                                    }
                                }
                                else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == LEWO_PRAWO) {
                                    if (x_poprz > x) { //RUCH W LEWO
                                        if (x == 0) { //PIERWSZA KOLUMNA
                                            rozdzielacze[i]->wejscia_elementu.append(NULL);
                                            koniec = true;
                                        }
                                        else {
                                            --x;
                                            --x_poprz;
                                        }
                                    }
                                    else { //RUCH W PRAWO
                                        ++x;
                                        ++x_poprz;
                                    }
                                }
                                else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_DOL) {
                                    if (y_poprz > y) { //RUCH W GÓRĘ
                                        --y;
                                        --y_poprz;
                                    }
                                    else { //RUCH W DOŁ
                                        ++y;
                                        ++y_poprz;
                                    }
                                }
                                else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == DOL_PRAWO) {
                                    if (y_poprz > y) { //ZMIANA KIERUNKU W PRAWO
                                        ++x;
                                        ++y_poprz;
                                    }
                                    else { //ZMIANA KIERUNKU W DÓŁ
                                        --y;
                                        --x_poprz;
                                    }
                                }
                                else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == DOL_LEWO) {
                                    if (y_poprz > y) { //ZMIANA KIERUNKU W LEWO
                                        if (x == 0) {
                                            rozdzielacze[i]->wejscia_elementu.append(NULL);
                                            koniec = true;
                                        }
                                        else {
                                            --x;
                                            ++y_poprz;
                                        }
                                    }
                                    else { //ZMIANA KIERUNKU W DÓŁ
                                        ++y;
                                        ++x_poprz;
                                    }
                                }
                                else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_PRAWO) {
                                    if (y > y_poprz) { //ZMIANA KIERUNKU W PRAWO
                                        ++x;
                                        y_poprz++;
                                    }
                                    else { //ZMIANA KIERUNKU W GÓRĘ
                                        --y;
                                        --x_poprz;
                                    }
                                }
                                else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_LEWO) {
                                    if (y > y_poprz) { //ZMIANA KIERUNKU W LEWO
                                        if (x == 0) {
                                            rozdzielacze[i]->wejscia_elementu.append(NULL);
                                            koniec = true;
                                        }
                                        else {
                                            --x;
                                            ++y_poprz;
                                        }
                                    } //ZMIANA KIERUNKU DO GÓRY
                                    else {
                                        --y;
                                        ++x_poprz;
                                    }
                                }
                                break;
                            case cewka:
                                rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wejscia_elementu.append(rozdzielacze[i]);
                                koniec = true;
                                break;
                            case styk:
                                if (x > x_poprz) {
                                    rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                    znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wejscia_elementu.append(rozdzielacze[i]);
                                }
                                else {
                                    rozdzielacze[i]->wejscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                    znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wyjscia_elementu.append(rozdzielacze[i]);
                                }
                                koniec = true;
                                break;
                            case operator_porownania:
                                if (x > x_poprz) {
                                    rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                    znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wejscia_elementu.append(rozdzielacze[i]);
                                }
                                else {
                                    rozdzielacze[i]->wejscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                    znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wyjscia_elementu.append(rozdzielacze[i]);
                                }
                                koniec = true;
                                break;
                            case blok_funkcyjny:
                                rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wejscia_elementu.append(rozdzielacze[i]);
                                koniec = true;
                                break;
                            default:
                                break;
                            }
                        }
                    }
                    break;
                case 2: //PRAWO
                    ++x;
                    while(!koniec) {
                        switch (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj) {
                        case lacznik:
                            if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_PRAWO_DOL || lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_LEWO_DOL || lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == LEWO_DOL_PRAWO || lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == LEWO_GORA_PRAWO || lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_DOL_LEWO_PRAWO) {
                                if (!sprawdz_czy_jest_na_wejsciu_lub_wyjsciu(lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x), rozdzielacze.at(i))) {
                                    rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(rozdzielacze, lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                    //znajdz_element_drabinki(rozdzielacze, rozdzielacze.at(i)->element)->wejscia_elementu.append(rozdzielacze[i]);
                                    koniec = true;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == LEWO_PRAWO) {
                                if (x_poprz > x) { //RUCH W LEWO
                                    if (x == 0) { //PIERWSZA KOLUMNA
                                        rozdzielacze[i]->wejscia_elementu.append(NULL);
                                        koniec = true;
                                    }
                                    else {
                                        --x;
                                        --x_poprz;
                                    }
                                }
                                else { //RUCH W PRAWO
                                    ++x;
                                    ++x_poprz;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_DOL) {
                                if (y_poprz > y) { //RUCH W GÓRĘ
                                    --y;
                                    --y_poprz;
                                }
                                else { //RUCH W DOŁ
                                    ++y;
                                    ++y_poprz;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == DOL_PRAWO) {
                                if (y_poprz > y) { //ZMIANA KIERUNKU W PRAWO
                                    ++x;
                                    ++y_poprz;
                                }
                                else { //ZMIANA KIERUNKU W DÓŁ
                                    --y;
                                    --x_poprz;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == DOL_LEWO) {
                                if (y_poprz > y) { //ZMIANA KIERUNKU W LEWO
                                    if (x == 0) {
                                        rozdzielacze[i]->wejscia_elementu.append(NULL);
                                        koniec = true;
                                    }
                                    else {
                                        --x;
                                        ++y_poprz;
                                    }
                                }
                                else { //ZMIANA KIERUNKU W DÓŁ
                                    ++y;
                                    ++x_poprz;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_PRAWO) {
                                if (y > y_poprz) { //ZMIANA KIERUNKU W PRAWO
                                    ++x;
                                    y_poprz++;
                                }
                                else { //ZMIANA KIERUNKU W GÓRĘ
                                    --y;
                                    --x_poprz;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_LEWO) {
                                if (y > y_poprz) { //ZMIANA KIERUNKU W LEWO
                                    if (x == 0) {
                                        rozdzielacze[i]->wejscia_elementu.append(NULL);
                                        koniec = true;
                                    }
                                    else {
                                        --x;
                                        ++y_poprz;
                                    }
                                } //ZMIANA KIERUNKU DO GÓRY
                                else {
                                    --y;
                                    ++x_poprz;
                                }
                            }
                            break;
                        case cewka:
                            rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                            znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wejscia_elementu.append(rozdzielacze[i]);
                            koniec = true;
                            break;
                        case styk:
                            if (x > x_poprz) {
                                rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wejscia_elementu.append(rozdzielacze[i]);
                            }
                            else {
                                rozdzielacze[i]->wejscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wyjscia_elementu.append(rozdzielacze[i]);
                            }
                            koniec = true;
                            break;
                        case operator_porownania:
                            if (x > x_poprz) {
                                rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wejscia_elementu.append(rozdzielacze[i]);
                            }
                            else {
                                rozdzielacze[i]->wejscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wyjscia_elementu.append(rozdzielacze[i]);
                            }
                            koniec = true;
                            break;
                        case blok_funkcyjny:
                            rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                            znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wejscia_elementu.append(rozdzielacze[i]);
                            koniec = true;
                            break;
                        default:
                            break;
                        }
                    }
                    break;
                default:
                    break;
                }
            }
            break;
        case GORA_DOL_LEWO_PRAWO:
            for (int j = 0; j < 4; ++j) {
                int x = rozdzielacze.at(i)->numer_kolumny, y = rozdzielacze.at(i)->numer_wiersza, x_poprz = rozdzielacze.at(i)->numer_kolumny, y_poprz = rozdzielacze.at(i)->numer_wiersza;
                bool koniec = false;
                switch (j) {
                case 0: //GÓRA
                    --y;
                    while(!koniec) {
                        switch (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj) {
                        case lacznik:
                            if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_PRAWO_DOL || lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_LEWO_DOL || lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == LEWO_DOL_PRAWO || lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == LEWO_GORA_PRAWO || lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_DOL_LEWO_PRAWO) {
                                if (!sprawdz_czy_jest_na_wejsciu_lub_wyjsciu(lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x), rozdzielacze.at(i))) {
                                    rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(rozdzielacze, lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                    //znajdz_element_drabinki(rozdzielacze, rozdzielacze.at(i)->element)->wejscia_elementu.append(rozdzielacze[i]);
                                    koniec = true;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == LEWO_PRAWO) {
                                if (x_poprz > x) { //RUCH W LEWO
                                    if (x == 0) { //PIERWSZA KOLUMNA
                                        rozdzielacze[i]->wejscia_elementu.append(NULL);
                                        koniec = true;
                                    }
                                    else {
                                        --x;
                                        --x_poprz;
                                    }
                                }
                                else { //RUCH W PRAWO
                                    ++x;
                                    ++x_poprz;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_DOL) {
                                if (y_poprz > y) { //RUCH W GÓRĘ
                                    --y;
                                    --y_poprz;
                                }
                                else { //RUCH W DOŁ
                                    ++y;
                                    ++y_poprz;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == DOL_PRAWO) {
                                if (y_poprz > y) { //ZMIANA KIERUNKU W PRAWO
                                    ++x;
                                    ++y_poprz;
                                }
                                else { //ZMIANA KIERUNKU W DÓŁ
                                    --y;
                                    --x_poprz;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == DOL_LEWO) {
                                if (y_poprz > y) { //ZMIANA KIERUNKU W LEWO
                                    if (x == 0) {
                                        rozdzielacze[i]->wejscia_elementu.append(NULL);
                                        koniec = true;
                                    }
                                    else {
                                        --x;
                                        ++y_poprz;
                                    }
                                }
                                else { //ZMIANA KIERUNKU W DÓŁ
                                    ++y;
                                    ++x_poprz;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_PRAWO) {
                                if (y > y_poprz) { //ZMIANA KIERUNKU W PRAWO
                                    ++x;
                                    y_poprz++;
                                }
                                else { //ZMIANA KIERUNKU W GÓRĘ
                                    --y;
                                    --x_poprz;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_LEWO) {
                                if (y > y_poprz) { //ZMIANA KIERUNKU W LEWO
                                    if (x == 0) {
                                        rozdzielacze[i]->wejscia_elementu.append(NULL);
                                        koniec = true;
                                    }
                                    else {
                                        --x;
                                        ++y_poprz;
                                    }
                                } //ZMIANA KIERUNKU DO GÓRY
                                else {
                                    --y;
                                    ++x_poprz;
                                }
                            }
                            break;
                        case cewka:
                            rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                            znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wejscia_elementu.append(rozdzielacze[i]);
                            koniec = true;
                            break;
                        case styk:
                            if (x > x_poprz) {
                                rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wejscia_elementu.append(rozdzielacze[i]);
                            }
                            else {
                                rozdzielacze[i]->wejscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wyjscia_elementu.append(rozdzielacze[i]);
                            }
                            koniec = true;
                            break;
                        case operator_porownania:
                            if (x > x_poprz) {
                                rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wejscia_elementu.append(rozdzielacze[i]);
                            }
                            else {
                                rozdzielacze[i]->wejscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wyjscia_elementu.append(rozdzielacze[i]);
                            }
                            koniec = true;
                            break;
                        case blok_funkcyjny:
                            rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                            znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wejscia_elementu.append(rozdzielacze[i]);
                            koniec = true;
                            break;
                        default:
                            break;
                        }
                    }
                    break;
                case 1: //LEWO
                    if (x == 0) {
                        rozdzielacze[i]->wejscia_elementu.append(NULL);
                        koniec = true;
                    }
                    else {
                        --x;
                        while(!koniec) {
                            switch (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj) {
                            case lacznik:
                                if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_PRAWO_DOL || lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_LEWO_DOL || lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == LEWO_DOL_PRAWO || lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == LEWO_GORA_PRAWO || lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_DOL_LEWO_PRAWO) {
                                    if (!sprawdz_czy_jest_na_wejsciu_lub_wyjsciu(lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x), rozdzielacze.at(i))) {
                                        rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(rozdzielacze, lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                        //znajdz_element_drabinki(rozdzielacze, rozdzielacze.at(i)->element)->wejscia_elementu.append(rozdzielacze[i]);
                                        koniec = true;
                                    }
                                }
                                else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == LEWO_PRAWO) {
                                    if (x_poprz > x) { //RUCH W LEWO
                                        if (x == 0) { //PIERWSZA KOLUMNA
                                            rozdzielacze[i]->wejscia_elementu.append(NULL);
                                            koniec = true;
                                        }
                                        else {
                                            --x;
                                            --x_poprz;
                                        }
                                    }
                                    else { //RUCH W PRAWO
                                        ++x;
                                        ++x_poprz;
                                    }
                                }
                                else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_DOL) {
                                    if (y_poprz > y) { //RUCH W GÓRĘ
                                        --y;
                                        --y_poprz;
                                    }
                                    else { //RUCH W DOŁ
                                        ++y;
                                        ++y_poprz;
                                    }
                                }
                                else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == DOL_PRAWO) {
                                    if (y_poprz > y) { //ZMIANA KIERUNKU W PRAWO
                                        ++x;
                                        ++y_poprz;
                                    }
                                    else { //ZMIANA KIERUNKU W DÓŁ
                                        --y;
                                        --x_poprz;
                                    }
                                }
                                else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == DOL_LEWO) {
                                    if (y_poprz > y) { //ZMIANA KIERUNKU W LEWO
                                        if (x == 0) {
                                            rozdzielacze[i]->wejscia_elementu.append(NULL);
                                            koniec = true;
                                        }
                                        else {
                                            --x;
                                            ++y_poprz;
                                        }
                                    }
                                    else { //ZMIANA KIERUNKU W DÓŁ
                                        ++y;
                                        ++x_poprz;
                                    }
                                }
                                else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_PRAWO) {
                                    if (y > y_poprz) { //ZMIANA KIERUNKU W PRAWO
                                        ++x;
                                        y_poprz++;
                                    }
                                    else { //ZMIANA KIERUNKU W GÓRĘ
                                        --y;
                                        --x_poprz;
                                    }
                                }
                                else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_LEWO) {
                                    if (y > y_poprz) { //ZMIANA KIERUNKU W LEWO
                                        if (x == 0) {
                                            rozdzielacze[i]->wejscia_elementu.append(NULL);
                                            koniec = true;
                                        }
                                        else {
                                            --x;
                                            ++y_poprz;
                                        }
                                    } //ZMIANA KIERUNKU DO GÓRY
                                    else {
                                        --y;
                                        ++x_poprz;
                                    }
                                }
                                break;
                            case cewka:
                                rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wejscia_elementu.append(rozdzielacze[i]);
                                koniec = true;
                                break;
                            case styk:
                                if (x > x_poprz) {
                                    rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                    znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wejscia_elementu.append(rozdzielacze[i]);
                                }
                                else {
                                    rozdzielacze[i]->wejscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                    znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wyjscia_elementu.append(rozdzielacze[i]);
                                }
                                koniec = true;
                                break;
                            case operator_porownania:
                                if (x > x_poprz) {
                                    rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                    znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wejscia_elementu.append(rozdzielacze[i]);
                                }
                                else {
                                    rozdzielacze[i]->wejscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                    znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wyjscia_elementu.append(rozdzielacze[i]);
                                }
                                koniec = true;
                                break;
                            case blok_funkcyjny:
                                rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wejscia_elementu.append(rozdzielacze[i]);
                                koniec = true;
                                break;
                            default:
                                break;
                            }
                        }
                    }
                    break;
                case 2: //DÓŁ
                    ++y;
                    while(!koniec) {
                        switch (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj) {
                        case lacznik:
                            if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_PRAWO_DOL || lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_LEWO_DOL || lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == LEWO_DOL_PRAWO || lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == LEWO_GORA_PRAWO || lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_DOL_LEWO_PRAWO) {
                                if (!sprawdz_czy_jest_na_wejsciu_lub_wyjsciu(lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x), rozdzielacze.at(i))) {
                                    rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(rozdzielacze, lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                    //znajdz_element_drabinki(rozdzielacze, rozdzielacze.at(i)->element)->wejscia_elementu.append(rozdzielacze[i]);
                                    koniec = true;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == LEWO_PRAWO) {
                                if (x_poprz > x) { //RUCH W LEWO
                                    if (x == 0) { //PIERWSZA KOLUMNA
                                        rozdzielacze[i]->wejscia_elementu.append(NULL);
                                        koniec = true;
                                    }
                                    else {
                                        --x;
                                        --x_poprz;
                                    }
                                }
                                else { //RUCH W PRAWO
                                    ++x;
                                    ++x_poprz;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_DOL) {
                                if (y_poprz > y) { //RUCH W GÓRĘ
                                    --y;
                                    --y_poprz;
                                }
                                else { //RUCH W DOŁ
                                    ++y;
                                    ++y_poprz;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == DOL_PRAWO) {
                                if (y_poprz > y) { //ZMIANA KIERUNKU W PRAWO
                                    ++x;
                                    ++y_poprz;
                                }
                                else { //ZMIANA KIERUNKU W DÓŁ
                                    --y;
                                    --x_poprz;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == DOL_LEWO) {
                                if (y_poprz > y) { //ZMIANA KIERUNKU W LEWO
                                    if (x == 0) {
                                        rozdzielacze[i]->wejscia_elementu.append(NULL);
                                        koniec = true;
                                    }
                                    else {
                                        --x;
                                        ++y_poprz;
                                    }
                                }
                                else { //ZMIANA KIERUNKU W DÓŁ
                                    ++y;
                                    ++x_poprz;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_PRAWO) {
                                if (y > y_poprz) { //ZMIANA KIERUNKU W PRAWO
                                    ++x;
                                    y_poprz++;
                                }
                                else { //ZMIANA KIERUNKU W GÓRĘ
                                    --y;
                                    --x_poprz;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_LEWO) {
                                if (y > y_poprz) { //ZMIANA KIERUNKU W LEWO
                                    if (x == 0) {
                                        rozdzielacze[i]->wejscia_elementu.append(NULL);
                                        koniec = true;
                                    }
                                    else {
                                        --x;
                                        ++y_poprz;
                                    }
                                } //ZMIANA KIERUNKU DO GÓRY
                                else {
                                    --y;
                                    ++x_poprz;
                                }
                            }
                            break;
                        case cewka:
                            rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                            znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wejscia_elementu.append(rozdzielacze[i]);
                            koniec = true;
                            break;
                        case styk:
                            if (x > x_poprz) {
                                rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wejscia_elementu.append(rozdzielacze[i]);
                            }
                            else {
                                rozdzielacze[i]->wejscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wyjscia_elementu.append(rozdzielacze[i]);
                            }
                            koniec = true;
                            break;
                        case operator_porownania:
                            if (x > x_poprz) {
                                rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wejscia_elementu.append(rozdzielacze[i]);
                            }
                            else {
                                rozdzielacze[i]->wejscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wyjscia_elementu.append(rozdzielacze[i]);
                            }
                            koniec = true;
                            break;
                        case blok_funkcyjny:
                            rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                            znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wejscia_elementu.append(rozdzielacze[i]);
                            koniec = true;
                            break;
                        default:
                            break;
                        }
                    }
                    break;
                case 3: //PRAWO
                    ++x;
                    while(!koniec) {
                        switch (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj) {
                        case lacznik:
                            if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_PRAWO_DOL || lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_LEWO_DOL || lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == LEWO_DOL_PRAWO || lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == LEWO_GORA_PRAWO || lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_DOL_LEWO_PRAWO) {
                                if (!sprawdz_czy_jest_na_wejsciu_lub_wyjsciu(lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x), rozdzielacze.at(i))) {
                                    rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(rozdzielacze, lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                    //znajdz_element_drabinki(rozdzielacze, rozdzielacze.at(i)->element)->wejscia_elementu.append(rozdzielacze[i]);
                                    koniec = true;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == LEWO_PRAWO) {
                                if (x_poprz > x) { //RUCH W LEWO
                                    if (x == 0) { //PIERWSZA KOLUMNA
                                        rozdzielacze[i]->wejscia_elementu.append(NULL);
                                        koniec = true;
                                    }
                                    else {
                                        --x;
                                        --x_poprz;
                                    }
                                }
                                else { //RUCH W PRAWO
                                    ++x;
                                    ++x_poprz;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_DOL) {
                                if (y_poprz > y) { //RUCH W GÓRĘ
                                    --y;
                                    --y_poprz;
                                }
                                else { //RUCH W DOŁ
                                    ++y;
                                    ++y_poprz;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == DOL_PRAWO) {
                                if (y_poprz > y) { //ZMIANA KIERUNKU W PRAWO
                                    ++x;
                                    ++y_poprz;
                                }
                                else { //ZMIANA KIERUNKU W DÓŁ
                                    --y;
                                    --x_poprz;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == DOL_LEWO) {
                                if (y_poprz > y) { //ZMIANA KIERUNKU W LEWO
                                    if (x == 0) {
                                        rozdzielacze[i]->wejscia_elementu.append(NULL);
                                        koniec = true;
                                    }
                                    else {
                                        --x;
                                        ++y_poprz;
                                    }
                                }
                                else { //ZMIANA KIERUNKU W DÓŁ
                                    ++y;
                                    ++x_poprz;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_PRAWO) {
                                if (y > y_poprz) { //ZMIANA KIERUNKU W PRAWO
                                    ++x;
                                    y_poprz++;
                                }
                                else { //ZMIANA KIERUNKU W GÓRĘ
                                    --y;
                                    --x_poprz;
                                }
                            }
                            else if (lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)->rodzaj2 == GORA_LEWO) {
                                if (y > y_poprz) { //ZMIANA KIERUNKU W LEWO
                                    if (x == 0) {
                                        rozdzielacze[i]->wejscia_elementu.append(NULL);
                                        koniec = true;
                                    }
                                    else {
                                        --x;
                                        ++y_poprz;
                                    }
                                } //ZMIANA KIERUNKU DO GÓRY
                                else {
                                    --y;
                                    ++x_poprz;
                                }
                            }
                            break;
                        case cewka:
                            rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                            znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wejscia_elementu.append(rozdzielacze[i]);
                            koniec = true;
                            break;
                        case styk:
                            if (x > x_poprz) {
                                rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wejscia_elementu.append(rozdzielacze[i]);
                            }
                            else {
                                rozdzielacze[i]->wejscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wyjscia_elementu.append(rozdzielacze[i]);
                            }
                            koniec = true;
                            break;
                        case operator_porownania:
                            if (x > x_poprz) {
                                rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wejscia_elementu.append(rozdzielacze[i]);
                            }
                            else {
                                rozdzielacze[i]->wejscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                                znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wyjscia_elementu.append(rozdzielacze[i]);
                            }
                            koniec = true;
                            break;
                        case blok_funkcyjny:
                            rozdzielacze[i]->wyjscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x)));
                            znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], lista_modeli[rozdzielacze.at(i)->numer_linii]->model_dane.at(y)->at(x))->wejscia_elementu.append(rozdzielacze[i]);
                            koniec = true;
                            break;
                        default:
                            break;
                        }
                    }
                    break;
                default:
                    break;
                }
            }
            break;
        default:
            break;

        }
    }
    for (int i = 0; i < przetworzone_obwody.count(); ++i) { //analiza "nierozdzielaczy"
        for (int j = 0; j < przetworzone_obwody[i]->count(); ++j) {
            if (przetworzone_obwody[i]->at(j)->wejscia_elementu.count() == 0) { //WEJŚCIA ELEMENTÓW
                if (przetworzone_obwody[i]->at(j)->numer_kolumny == 0) {
                    przetworzone_obwody[i]->at(j)->wejscia_elementu.append(NULL);
                }
                else {
                    bool koniec = false;
                    int x = przetworzone_obwody[i]->at(j)->numer_kolumny, y = przetworzone_obwody[i]->at(j)->numer_wiersza, y_poprz = przetworzone_obwody[i]->at(j)->numer_wiersza, x_poprz = przetworzone_obwody[i]->at(j)->numer_kolumny;
                    while(!koniec) {
                        --x;
                        switch (lista_modeli[i]->model_dane.at(y)->at(x)->rodzaj) {
                        case lacznik:
                            if (lista_modeli[i]->model_dane.at(y)->at(x)->rodzaj2 == LEWO_PRAWO) {
                                if (x_poprz > x) { //RUCH W LEWO
                                    if (x == 0) { //PIERWSZA KOLUMNA
                                        przetworzone_obwody[i]->at(j)->wejscia_elementu.append(NULL);
                                        koniec = true;
                                    }
                                    else {
                                        --x;
                                        --x_poprz;
                                    }
                                }
                                else { //RUCH W PRAWO
                                    ++x;
                                    ++x_poprz;
                                }
                            }
                            else if (lista_modeli[i]->model_dane.at(y)->at(x)->rodzaj2 == GORA_DOL) {
                                if (y_poprz > y) { //RUCH W GÓRĘ
                                    --y;
                                    --y_poprz;
                                }
                                else { //RUCH W DOŁ
                                    ++y;
                                    ++y_poprz;
                                }
                            }
                            else if (lista_modeli[i]->model_dane.at(y)->at(x)->rodzaj2 == DOL_PRAWO) {
                                if (y_poprz > y) { //ZMIANA KIERUNKU W PRAWO
                                    ++x;
                                    ++y_poprz;
                                }
                                else { //ZMIANA KIERUNKU W DÓŁ
                                    --y;
                                    --x_poprz;
                                }
                            }
                            else if (lista_modeli[i]->model_dane.at(y)->at(x)->rodzaj2 == DOL_LEWO) {
                                if (y_poprz > y) { //ZMIANA KIERUNKU W LEWO
                                    if (x == 0) {
                                        przetworzone_obwody[i]->at(j)->wejscia_elementu.append(NULL);
                                        koniec = true;
                                    }
                                    else {
                                        --x;
                                        ++y_poprz;
                                    }
                                }
                                else { //ZMIANA KIERUNKU W DÓŁ
                                    ++y;
                                    ++x_poprz;
                                }
                            }
                            else if (lista_modeli[i]->model_dane.at(y)->at(x)->rodzaj2 == GORA_PRAWO) {
                                if (y > y_poprz) { //ZMIANA KIERUNKU W PRAWO
                                    ++x;
                                    y_poprz++;
                                }
                                else { //ZMIANA KIERUNKU W GÓRĘ
                                    --y;
                                    --x_poprz;
                                }
                            }
                            else if (lista_modeli[i]->model_dane.at(y)->at(x)->rodzaj2 == GORA_LEWO) {
                                if (y > y_poprz) { //ZMIANA KIERUNKU W LEWO
                                    if (x == 0) {
                                        przetworzone_obwody[i]->at(j)->wejscia_elementu.append(NULL);
                                        koniec = true;
                                    }
                                    else {
                                        --x;
                                        ++y_poprz;
                                    }
                                } //ZMIANA KIERUNKU DO GÓRY
                                else {
                                    --y;
                                    ++x_poprz;
                                }
                            }
                            break;
                        case styk:
                            przetworzone_obwody[i]->at(j)->wejscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[i], lista_modeli[i]->model_dane.at(y)->at(x)));
                            znajdz_element_drabinki(*przetworzone_obwody[i], lista_modeli[i]->model_dane.at(y)->at(x))->wyjscia_elementu.append(przetworzone_obwody[i]->at(j));
                            koniec = true;
                            break;
                        case operator_porownania:
                            przetworzone_obwody[i]->at(j)->wejscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[i], lista_modeli[i]->model_dane.at(y)->at(x)));
                            znajdz_element_drabinki(*przetworzone_obwody[i], lista_modeli[i]->model_dane.at(y)->at(x))->wyjscia_elementu.append(przetworzone_obwody[i]->at(j));
                            koniec = true;
                            break;
                        default:
                            break;
                        }
                    }
                }
            }
            if (przetworzone_obwody[i]->at(j)->wyjscia_elementu.count() == 0) { //WYJŚCIA ELEMENTÓW
                if (przetworzone_obwody[i]->at(j)->element->rodzaj != cewka && przetworzone_obwody[i]->at(j)->element->rodzaj != blok_funkcyjny) {
                    bool koniec = false;
                    int x = przetworzone_obwody[i]->at(j)->numer_kolumny, y = przetworzone_obwody[i]->at(j)->numer_wiersza, y_poprz = przetworzone_obwody[i]->at(j)->numer_wiersza, x_poprz = przetworzone_obwody[i]->at(j)->numer_kolumny;
                    while(!koniec) {
                        ++x;
                        switch (lista_modeli[i]->model_dane.at(y)->at(x)->rodzaj) {
                        case lacznik:
                            if (lista_modeli[i]->model_dane.at(y)->at(x)->rodzaj2 == LEWO_PRAWO) {
                                if (x_poprz > x) { //RUCH W LEWO
                                    --x;
                                    --x_poprz;
                                }
                                else { //RUCH W PRAWO
                                    ++x;
                                    ++x_poprz;
                                }
                            }
                            else if (lista_modeli[i]->model_dane.at(y)->at(x)->rodzaj2 == GORA_DOL) {
                                if (y_poprz > y) { //RUCH W GÓRĘ
                                    --y;
                                    --y_poprz;
                                }
                                else { //RUCH W DOŁ
                                    ++y;
                                    ++y_poprz;
                                }
                            }
                            else if (lista_modeli[i]->model_dane.at(y)->at(x)->rodzaj2 == DOL_PRAWO) {
                                if (y_poprz > y) { //ZMIANA KIERUNKU W PRAWO
                                    ++x;
                                    ++y_poprz;
                                }
                                else { //ZMIANA KIERUNKU W DÓŁ
                                    --y;
                                    --x_poprz;
                                }
                            }
                            else if (lista_modeli[i]->model_dane.at(y)->at(x)->rodzaj2 == DOL_LEWO) {
                                if (y_poprz > y) { //ZMIANA KIERUNKU W LEWO
                                    --x;
                                    ++y_poprz;
                                }
                                else { //ZMIANA KIERUNKU W DÓŁ
                                    ++y;
                                    ++x_poprz;
                                }
                            }
                            else if (lista_modeli[i]->model_dane.at(y)->at(x)->rodzaj2 == GORA_PRAWO) {
                                if (y > y_poprz) { //ZMIANA KIERUNKU W PRAWO
                                    ++x;
                                    y_poprz++;
                                }
                                else { //ZMIANA KIERUNKU W GÓRĘ
                                    --y;
                                    --x_poprz;
                                }
                            }
                            else if (lista_modeli[i]->model_dane.at(y)->at(x)->rodzaj2 == GORA_LEWO) {
                                if (y > y_poprz) { //ZMIANA KIERUNKU W LEWO
                                    --x;
                                    ++y_poprz;
                                } //ZMIANA KIERUNKU DO GÓRY
                                else {
                                    --y;
                                    ++x_poprz;
                                }
                            }
                            break;
                        case cewka:
                            przetworzone_obwody[i]->at(j)->wyjscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[i], lista_modeli[i]->model_dane.at(y)->at(x)));
                            znajdz_element_drabinki(*przetworzone_obwody[i], lista_modeli[i]->model_dane.at(y)->at(x))->wejscia_elementu.append(przetworzone_obwody[i]->at(j));
                            koniec = true;
                            break;
                        case blok_funkcyjny:
                            przetworzone_obwody[i]->at(j)->wyjscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[i], lista_modeli[i]->model_dane.at(y)->at(x)));
                            znajdz_element_drabinki(*przetworzone_obwody[i], lista_modeli[i]->model_dane.at(y)->at(x))->wejscia_elementu.append(przetworzone_obwody[i]->at(j));
                            koniec = true;
                            break;
                        case styk:
                            przetworzone_obwody[i]->at(j)->wyjscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[i], lista_modeli[i]->model_dane.at(y)->at(x)));
                            znajdz_element_drabinki(*przetworzone_obwody[i], lista_modeli[i]->model_dane.at(y)->at(x))->wejscia_elementu.append(przetworzone_obwody[i]->at(j));
                            koniec = true;
                            break;
                        case operator_porownania:
                            przetworzone_obwody[i]->at(j)->wyjscia_elementu.append(znajdz_element_drabinki(*przetworzone_obwody[i], lista_modeli[i]->model_dane.at(y)->at(x)));
                            znajdz_element_drabinki(*przetworzone_obwody[i], lista_modeli[i]->model_dane.at(y)->at(x))->wejscia_elementu.append(przetworzone_obwody[i]->at(j));
                            koniec = true;
                            break;
                        default:
                            break;
                        }
                    }
                }
            }
        }
    }
    while(rozdzielacze.count() != 0) { //redukcja kilku połączonych ze sobą rozdzielaczy do jednego
        for(int i = rozdzielacze.count() - 1; i >= 0; --i) {
            bool zakoncz = false;
            for (int j = 0; !zakoncz && j < rozdzielacze[i]->wyjscia_elementu.count(); ++j) {
                if (rozdzielacze[i]->wyjscia_elementu[j]->element->rodzaj == lacznik) {
                    for (int k = 0; k < rozdzielacze[i]->wejscia_elementu.count(); ++k) {
                        rozdzielacze[i]->wyjscia_elementu[j]->wejscia_elementu.append(rozdzielacze[i]->wejscia_elementu[k]);
                        rozdzielacze[i]->wejscia_elementu[k]->wyjscia_elementu.replace(rozdzielacze[i]->wejscia_elementu[k]->wyjscia_elementu.indexOf(rozdzielacze[i]), rozdzielacze[i]->wyjscia_elementu[j]);
                    }
                    for (int k = 0; k < rozdzielacze[i]->wyjscia_elementu.count(); ++k) {
                        if (rozdzielacze[i]->wyjscia_elementu[k] == rozdzielacze[i]->wyjscia_elementu[j])
                            continue;
                        rozdzielacze[i]->wyjscia_elementu[j]->wyjscia_elementu.append(rozdzielacze[i]->wyjscia_elementu[k]);
                        if (rozdzielacze[i]->wyjscia_elementu[k]->element->rodzaj != lacznik)
                            rozdzielacze[i]->wyjscia_elementu[k]->wejscia_elementu.replace(rozdzielacze[i]->wyjscia_elementu[k]->wejscia_elementu.indexOf(rozdzielacze[i]), rozdzielacze[i]->wyjscia_elementu[j]);
                        else
                            rozdzielacze[i]->wyjscia_elementu[k]->wyjscia_elementu.replace(rozdzielacze[i]->wyjscia_elementu[k]->wyjscia_elementu.indexOf(rozdzielacze[i]), rozdzielacze[i]->wyjscia_elementu[j]);
                    }
                    rozdzielacze[i]->wyjscia_elementu[j]->wyjscia_elementu.removeAll(rozdzielacze[i]);
                    delete rozdzielacze[i];
                    rozdzielacze.removeAt(i);
                    zakoncz = true;
                }
            }
            if (!zakoncz) {
                for (int j = 0; j < rozdzielacze[i]->wejscia_elementu.count(); ++j) {
                    if (rozdzielacze[i]->wejscia_elementu[j] != NULL) {
                        for (int k = 0; k < rozdzielacze[i]->wyjscia_elementu.count(); ++k) {
                            znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], rozdzielacze[i]->wejscia_elementu[j]->element)->wyjscia_elementu.append(rozdzielacze[i]->wyjscia_elementu[k]);
                        }
                        rozdzielacze[i]->wejscia_elementu[j]->wyjscia_elementu.removeAll(rozdzielacze[i]);
                    }
                }
                for (int j = 0; j < rozdzielacze[i]->wyjscia_elementu.count(); ++j) {
                    for (int k = 0; k < rozdzielacze[i]->wejscia_elementu.count(); ++k) {
                        znajdz_element_drabinki(*przetworzone_obwody[rozdzielacze[i]->numer_linii], rozdzielacze[i]->wyjscia_elementu[j]->element)->wejscia_elementu.append(rozdzielacze[i]->wejscia_elementu[k]);
                    }
                    rozdzielacze[i]->wyjscia_elementu[j]->wejscia_elementu.removeAll(rozdzielacze[i]);
                }
                delete rozdzielacze[i];
                rozdzielacze.removeAt(i);
            }
        }
    }
    for (int i = 0; i < przetworzone_obwody.count(); ++i) { //znajdowanie początkowych elementów
        for (int j = 0; j < przetworzone_obwody[i]->count(); ++j) {
            if (sprawdz_czy_jest_na_liscie(NULL, przetworzone_obwody[i]->at(j)->wejscia_elementu)) {
                poczatki[i]->append(przetworzone_obwody[i]->at(j));
            }
        }
    }
    //ROZPOCZĘCIE KOMPILACJI
    QFile plik_z_projektem(konfiguracja.sciezka_zapisu_kompilacja);
    if (!plik_z_projektem.open(QIODevice::WriteOnly)){
        QMessageBox msgBox;
        msgBox.setText("Nie udało się zapisać pliku!");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
        return -1;
    }
    QTextStream out(&plik_z_projektem);
    if (timery.count() > 0) {
        out<<"class timer {\n"
             "public:\n"
             "timer(unsigned long a) {\n"
             "czas = 0;\n"
             "prog_zalaczenia = a;\n"
             "stan = false;\n"
             "}\n\n"

             "void wykonanie() {\n"
             "if (czas == 0)\n"
             "czas = millis();\n"
             "if (!stan && millis() - czas >= prog_zalaczenia)\n"
             "stan = true;\n"
             "}\n"
             "void reset() {\n"
             "stan = false;\n"
             "czas = 0;\n"
             "}\n\n"

             "unsigned long czas;\n"
             "unsigned long prog_zalaczenia;\n"
             "bool stan;\n"
             "};\n\n"; }
    if (liczniki.count() > 0) {
        out<<"class licznik {\n"
             "public:\n"
             "licznik(unsigned long a) {\n"
             "prog_zalaczenia = a;\n"
             "aktualna_liczba = 0;\n"
             "poprzednie_wejscie = false;\n"
             "}\n"

             "void wykonanie() {\n"
             "if (aktualna_liczba != prog_zalaczenia && poprzednie_wejscie == false) {\n"
             "aktualna_liczba += 1;\n"
             "poprzednie_wejscie = true;\n"
             "}\n"
             "if (aktualna_liczba == prog_zalaczenia) {\n"
             "stan = true;\n"
             "}\n"
             "}\n"

             "void zmiana_wejscia() {\n"
             "poprzednie_wejscie = false;\n"
             "}\n"

             "void reset() {\n"
             "aktualna_liczba = 0;\n"
             "stan = false;\n"
             "}\n"

             "unsigned long prog_zalaczenia;\n"
             "unsigned long aktualna_liczba;\n"
             "bool poprzednie_wejscie;\n"
             "bool stan;\n"
             "};\n"; }
    QMapIterator<QString, zmienna_w_arduino> i(lista_uzywanych_zmiennych);
    while (i.hasNext()) {
        i.next();
        if (i.value().typ_zmiennej != NIE_DOTYCZY) {
            if (i.value().rodzaj_pinu != NIE_DOTYCZY) {
                out<<"int "<<i.key()<<"_pin";
                out<<" = "<<i.value().numer_pinu<<";\n";
                out<<"int "<<i.key()<<";\n";
            }
            else {
                out<<"int "<<i.key();
                out<<" = false;\n";
            }
        }
    }
    for (int i = 0; i < timery.count(); ++i) {
        out<<"timer "<<timery[i]->element->zmienna<<"("<<timery[i]->element->parametry.value(PV)<<");\n";
    }
    for (int i = 0; i < liczniki.count(); ++i) {
        out<<"licznik "<<liczniki[i]->element->zmienna<<"("<<liczniki[i]->element->parametry.value(PV)<<");\n";
    }
    out<<"\nvoid setup() {\n";
    i.toFront();
    while (i.hasNext()) {
        i.next();
        if (i.value().typ_zmiennej == DYSKRETNA && i.value().rodzaj_pinu != NIE_DOTYCZY) {
            out<<"pinMode("<<i.key()<<"_pin"<<",";
            if (i.value().rodzaj_pinu == WEJSCIE)
                out<<"INPUT);\n";
            else
                out<<"OUTPUT);\n";
        }
    }
    out<<"}\n"
         "\n"
         "void loop() {\n";
    i.toFront();
    while (i.hasNext()) { //odczyty wartości z pinów na początku wykonania pętli(jak w przyszłości będzie potrzeba sterowania analogowymi wyjściami to tutaj dodać potrzebne definicje)
        i.next();
        if (i.value().rodzaj_pinu == WEJSCIE) {
            if (i.value().typ_zmiennej == DYSKRETNA) {
                out<<i.key()<<" = digitalRead("<<i.key()<<"_pin);\n";
            }
            else {
                out<<i.key()<<" = analogRead("<<i.key()<<"_pin);\n";
            }
        }
    }
    for (int j = 0; j < poczatki.count(); ++j) {
        for (int k = 0; k < poczatki[j]->count(); ++k) {
            if (k == 0)
                out<<"if (";
            warunek.clear();
            tworzenie_warunkow(out, poczatki[j]->at(k), warunek, liczniki, timery);
            warunek.chop(4);
            if (k == 0 && poczatki[j]->count() > 1)
                warunek += " || ";
            out<<warunek;
            if (k == poczatki[j]->count() - 1)
                out<<") {\n";

        }
        for (int k = 0; k < konce[j]->count(); k++) {
            switch (konce[j]->at(k)->element->rodzaj) {
            case cewka:
                switch (konce[j]->at(k)->element->rodzaj2) {
                case ZWYKLA:
                    out<<konce[j]->at(k)->element->zmienna<<" = true;\n";
                    break;
                case ZANEGOWANA:
                    out<<konce[j]->at(k)->element->zmienna<<" = false;\n";
                    break;
                default:
                    break;
                }
                break;
            case blok_funkcyjny:
                out<<konce[j]->at(k)->element->zmienna<<".wykonanie();\n";
            default:
                break;
            }
        }
        for (int k = 0; k < konce[j]->count(); k++) {
            if (k == 0)
                out<<"}\n"
                     "else {\n";
            switch (konce[j]->at(k)->element->rodzaj) {
            case cewka:
                switch (konce[j]->at(k)->element->rodzaj2) {
                case ZWYKLA:
                    out<<konce[j]->at(k)->element->zmienna<<" = false;\n";
                    break;
                case ZANEGOWANA:
                    out<<konce[j]->at(k)->element->zmienna<<" = true;\n";
                    break;
                default:
                    break;
                }
                break;
            case blok_funkcyjny:
                switch (konce[j]->at(k)->element->rodzaj2) {
                case TIMER:
                    out<<konce[j]->at(k)->element->zmienna<<".reset();\n";
                    break;
                case LICZNIK:
                    out<<konce[j]->at(k)->element->zmienna<<".zmiana_wejscia();\n";
                    break;
                default:
                    break;
                }
            default:
                break;
            }
            if (k == konce[j]->count() - 1)
                out<<"}\n";
        }
    }
    for (int j = 0; j < liczniki.count(); j++) {
        if (sprawdz_czy_jest_na_liscie(liczniki[j]->element->parametry.value(ZMIENNA_RESETUJACA), liczniki, timery)) {
            out<<"if ("<<liczniki[j]->element->parametry.value(ZMIENNA_RESETUJACA)<<".stan) {";
            out<<liczniki[j]->element->zmienna<<".reset();\n"
                                                "}\n";
        }
        else {
            out<<"if ("<<liczniki[j]->element->parametry.value(ZMIENNA_RESETUJACA)<<") {";
            out<<liczniki[j]->element->zmienna<<".reset();\n"
                                                "}\n";
        }
    }
    i.toFront();
    while (i.hasNext()) { //zapis wartości do pinów na końcu działania pętli(jak w przyszłości będzie potrzeba sterowania analogowymi wyjściami to tutaj dodać potrzebne definicje)
        i.next();
        if (i.value().rodzaj_pinu == WYJSCIE) {
            if (i.value().typ_zmiennej == DYSKRETNA) {
                out<<"digitalWrite("<<i.key()<<"_pin, "<<i.key()<<");\n";
            }
        }
    }
    out<<"}";
    plik_z_projektem.close();
    //CZYSZCZENIE PAMIĘCI
    for (int j = 0; j < przetworzone_obwody.count(); ++j) {
        for (int k = 0; k < przetworzone_obwody[j]->count(); ++k) {
            delete przetworzone_obwody[j]->at(k);
        }
        delete przetworzone_obwody[j];
        delete poczatki[j];
        delete konce[j];
    }
    for (int j = 0; j < liczniki.count(); ++j) {
        delete liczniki[j];
    }
    for (int j = 0; j < timery.count(); ++j) {
        delete timery[j];
    }
    return 0;
}

int PLCino::wybranie_sciezki_zapisu(int rodzaj_zapisu)
{
    QString sciezka_pliku;
    if (rodzaj_zapisu == PROJEKT)
        sciezka_pliku = QFileDialog::getSaveFileName(this, tr("Zapisz"),
                                                     QDir::currentPath(),
                                                     tr("Projekty (*.plc)"));
    else
        sciezka_pliku = QFileDialog::getSaveFileName(this, tr("Zapisz"),
                                                     QDir::currentPath(),
                                                     tr("Kod źródłowy Arduino (*.ino)"));
    if(sciezka_pliku.isEmpty())
        return -1;
    if (rodzaj_zapisu == PROJEKT)
        konfiguracja.sciezka_zapisu_projektu = sciezka_pliku;
    else
        konfiguracja.sciezka_zapisu_kompilacja = sciezka_pliku;
    return 0;
}

bool PLCino::sprawdz_czy_jest_na_liscie(elementy_drabinki *a, QList<elementy_schematu *> *b)
{
    for (int i = 0; i < b->count(); ++i) {
        if (b->at(i)->element == a)
            return true;
    }
    return false;
}

bool PLCino::sprawdz_czy_jest_na_liscie(elementy_schematu *a, QList<elementy_schematu *> b)
{
    for (int i = 0; i < b.count(); ++i) {
        if (b.at(i) == a)
            return true;
    }
    return false;
}

bool PLCino::sprawdz_czy_jest_na_liscie(QString a, QList<elementy_schematu *> liczniki, QList<elementy_schematu *> timery)
{
    for (int i = 0; i < liczniki.count(); ++i) {
        if (QString::compare(liczniki[i]->element->zmienna, a, Qt::CaseInsensitive) == 0) {
            return true;
        }
    }
    for (int i = 0; i < timery.count(); ++i) {
        if (QString::compare(timery[i]->element->zmienna, a, Qt::CaseInsensitive) == 0) {
            return true;
        }
    }
    return false;
}

bool PLCino::sprawdz_czy_jest_na_wejsciu_lub_wyjsciu(elementy_drabinki *a, elementy_schematu *b)
{
    for (int i = 0; i < b->wejscia_elementu.count(); ++i) {
        if (b->wejscia_elementu.at(i)->element == a)
            return true;
    }
    for (int i = 0; i < b->wyjscia_elementu.count(); ++i) {
        if (b->wyjscia_elementu.at(i)->element == a)
            return true;
    }
    return false;
}

elementy_schematu *PLCino::znajdz_element_drabinki(QList<elementy_schematu *> lista, elementy_drabinki *a)
{
    for(int i = 0; i < lista.count(); ++i) {
        if(lista[i]->element == a)
            return lista[i];
    }
    return NULL;
}

bool PLCino::czy_styk_nalezy_do_bloku_funkcyjnego(QString nazwa_zmiennej, QList<elementy_schematu *> liczniki, QList<elementy_schematu *> timery)
{
    for (int i = 0; i < liczniki.count(); ++i) {
        if (QString::compare(liczniki[i]->element->zmienna, nazwa_zmiennej) == 0)
            return true;
    }
    for (int i = 0; i < timery.count(); ++i) {
        if (QString::compare(timery[i]->element->zmienna, nazwa_zmiennej) == 0)
            return true;
    }
    return false;
}

void PLCino::tworzenie_warunkow(QTextStream &out, elementy_schematu *element, QString string, QList<elementy_schematu *> liczniki, QList<elementy_schematu *> timery)
{
    QString warunek_kopia = string;
    if (element->element->rodzaj == cewka || element->element->rodzaj == blok_funkcyjny) { //warunek, gdy w obwodzie znajduje się tylko cewka lub blok funkcyjny, który się zawsze wykonuje
        warunek += " true     ";
        return;
    }
    switch (element->element->rodzaj) {
    case styk:
        switch (element->element->rodzaj2) {
        case ZWYKLY:
            if (czy_styk_nalezy_do_bloku_funkcyjnego(element->element->zmienna, liczniki, timery)) {
                warunek_kopia += " " + element->element->zmienna + ".stan ";
            }
            else {
                warunek_kopia += " " + element->element->zmienna + " ";
            }
            break;
        case ZANEGOWANY:
            if (czy_styk_nalezy_do_bloku_funkcyjnego(element->element->zmienna, liczniki, timery)) {
                warunek_kopia += " !" + element->element->zmienna + ".stan ";
            }
            else {
                warunek_kopia += " !" + element->element->zmienna + " ";
            }
            break;
        default:
            break;
        }
        break;
    case operator_porownania:
        switch (element->element->rodzaj2) {
        case WIEKSZY_BADZ_ROWNY:
            warunek_kopia += " " + element->element->parametry.value(ELEMENT1) + " >= " + element->element->parametry.value(ELEMENT2) + " ";
            break;
        case WIEKSZY:
            warunek_kopia += " " + element->element->parametry.value(ELEMENT1) + " > " + element->element->parametry.value(ELEMENT2) + " ";
            break;
        case MNIEJSZY_BADZ_ROWNY:
            warunek_kopia += " " + element->element->parametry.value(ELEMENT1) + " <= " + element->element->parametry.value(ELEMENT2) + " ";
            break;
        case MNIEJSZY:
            warunek_kopia += " " + element->element->parametry.value(ELEMENT1) + " < " + element->element->parametry.value(ELEMENT2) + " ";
            break;
        case ROWNY:
            warunek_kopia += " " + element->element->parametry.value(ELEMENT1) + " == " + element->element->parametry.value(ELEMENT2) + " ";
            break;
        case ROZNY:
            warunek_kopia += " " + element->element->parametry.value(ELEMENT1) + " != " + element->element->parametry.value(ELEMENT2) + " ";
            break;
        default:
            break;
        }
    default:
        break;
    }
    if (element->wyjscia_elementu[0]->element->rodzaj != cewka && element->wyjscia_elementu[0]->element->rodzaj != blok_funkcyjny) {
        warunek_kopia += "&&";
    }
    for (int i = 0; i < element->wyjscia_elementu.count(); ++i) {
        if (element->wyjscia_elementu[i]->element->rodzaj == cewka || element->wyjscia_elementu[i]->element->rodzaj == blok_funkcyjny) {
            if (element->wyjscia_elementu.count() == 1)
                warunek += warunek_kopia + " || ";
            else
                warunek += warunek_kopia;
        }
        else {
            tworzenie_warunkow(out, element->wyjscia_elementu[i], warunek_kopia, liczniki, timery);
        }
    }
}

QString PLCino::poszukiwanie_portu_bootloadera(QList<QSerialPortInfo> *przed_resetem, QList<QSerialPortInfo> *po_resecie)
{
    for (int i = 0; i < po_resecie->count(); i++) {
        bool znaleziono = false;
        for (int j = 0; j < przed_resetem->count(); j++) {
            if (po_resecie->at(i).portName() == przed_resetem->at(j).portName()) {
                znaleziono = true;
                break;
            }
        }
        if (!znaleziono)
            return po_resecie->at(i).portName();
    }
    return "";
}

void PLCino::on_actionKompiluj_do_C_triggered()
{
    if (wybranie_sciezki_zapisu(KOMPILACJA) < 0)
        return;
    kompilator();
    statusBar()->showMessage("Kompilacja zakończona", 5000);
    QMessageBox msgBox;
    msgBox.setText("Kompilacja zakończona");
    msgBox.setIcon(QMessageBox::Information);
    msgBox.exec();
}

void PLCino::on_actionKompiluj_i_wgraj_do_Arduino_triggered()
{
    QMessageBox msgBox;
    if (konfiguracja.wybrana_plytka == brak || konfiguracja.nazwa_wybranego_portu.isEmpty()) {
        msgBox.setText("Nie skonfigurowano ustawień układu Arduino!");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
        return;
    }
    if (wybranie_sciezki_zapisu(KOMPILACJA) < 0)
        return;
    statusBar()->showMessage("Kompilacja do języka Arduino...");
    kompilator();
    QDir dir = QDir::root();
    dir.rmpath("temp/");
    dir.mkpath("temp/");
    dir.cd("temp/");

    QFile log(dir.path() + "/log.txt");
    if (!log.open(QIODevice::WriteOnly)){
        QMessageBox msgBox;
        msgBox.setText("Nie udało utworzyć pliku log!");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
        return;
    }
    QTextStream out_log(&log);
    QProcess proces_arduino_builder;
    QProcess proces_avrdude;
    QSerialPort odblokowanie_mikrokontrolera;
    QList<QSerialPortInfo> porty_przed_resetem;
    QList<QSerialPortInfo> porty_po_resecie;
    QString COM_bootloadera;
    statusBar()->showMessage("Kompilacja do formatu Intel HEX...");
    switch (konfiguracja.wybrana_plytka) {
    case nano:
        proces_arduino_builder.setProcessChannelMode(QProcess::MergedChannels);
        proces_arduino_builder.start(("arduino-builder.exe -hardware hardware -tools har"
                      "dware\\tools -tools tools-builder -fqbn arduino:avr:nano:cpu=atmega328 -build-pat"
                      "h " + dir.absolutePath() + " -compile " + konfiguracja.sciezka_zapisu_kompilacja).toStdString().c_str());
        proces_arduino_builder.waitForFinished(-1);
        out_log<<proces_arduino_builder.readAll();
        proces_avrdude.setProcessChannelMode(QProcess::MergedChannels);
        statusBar()->showMessage("Wgrywanie programu do Arduino...");
        proces_avrdude.start(("avrdude.exe -v -C\"avrdude.conf\" -pm328p -carduino -P " + konfiguracja.nazwa_wybranego_portu +
                              " -b57600 -D -Uflash:w:" + dir.absolutePath() + "/" + konfiguracja.sciezka_zapisu_kompilacja.section('/', -1) + ".hex:i").toStdString().c_str());
        proces_avrdude.waitForFinished(10000);
        out_log<<proces_avrdude.readAll();
        break;
    case leonardo:
        proces_arduino_builder.setProcessChannelMode(QProcess::MergedChannels);
        proces_arduino_builder.start(("arduino-builder.exe -hardware hardware -tools har"
                      "dware\\tools -tools tools-builder -fqbn arduino:avr:leonardo:cpu=atmega32u4 -build-pat"
                      "h " + dir.absolutePath() + " -compile " + konfiguracja.sciezka_zapisu_kompilacja).toStdString().c_str());
        proces_arduino_builder.waitForFinished(-1);
        out_log<<proces_arduino_builder.readAll();
        proces_avrdude.setProcessChannelMode(QProcess::MergedChannels);
        odblokowanie_mikrokontrolera.setPortName(konfiguracja.nazwa_wybranego_portu);
        odblokowanie_mikrokontrolera.setBaudRate(1200);
        porty_przed_resetem = QSerialPortInfo::availablePorts();
        statusBar()->showMessage("Uruchamianie bootloadera...");
        odblokowanie_mikrokontrolera.open(QIODevice::ReadWrite);
        QThread::msleep(2000);
        porty_po_resecie = QSerialPortInfo::availablePorts();
        COM_bootloadera = poszukiwanie_portu_bootloadera(&porty_przed_resetem, &porty_po_resecie);
        odblokowanie_mikrokontrolera.close();
        statusBar()->showMessage("Wgrywanie programu do Arduino...");
        proces_avrdude.start(("avrdude.exe -v -C\"avrdude.conf\" -p atmega32u4 -c avr109 -P " + COM_bootloadera +
                              " -b 57600 -D -Uflash:w:" + dir.absolutePath() + "/" + konfiguracja.sciezka_zapisu_kompilacja.section('/', -1) + ".hex:i").toStdString().c_str());
        proces_avrdude.waitForFinished(10000);
        out_log<<proces_avrdude.readAll();
        break;
    case mega:
        proces_arduino_builder.setProcessChannelMode(QProcess::MergedChannels);
        proces_arduino_builder.start(("arduino-builder.exe -hardware hardware -tools har"
                      "dware\\tools -tools tools-builder -fqbn arduino:avr:mega:cpu=atmega2560 -build-pat"
                      "h " + dir.absolutePath() + " -compile " + konfiguracja.sciezka_zapisu_kompilacja).toStdString().c_str());
        proces_arduino_builder.waitForFinished(-1);
        out_log<<proces_arduino_builder.readAll();
        proces_avrdude.setProcessChannelMode(QProcess::MergedChannels);
        statusBar()->showMessage("Wgrywanie programu do Arduino...");
        proces_avrdude.start(("avrdude.exe -v -C\"avrdude.conf\" -pm2560 -c wiring -P " + konfiguracja.nazwa_wybranego_portu +
                              " -b 115200 -D -Uflash:w:" + dir.absolutePath() + "/" + konfiguracja.sciezka_zapisu_kompilacja.section('/', -1) + ".hex:i").toStdString().c_str());
        proces_avrdude.waitForFinished(10000);
        out_log<<proces_avrdude.readAll();
        break;
    default:
        break;
    }
    log.close();
    statusBar()->showMessage("Kompilacja zakończona", 5000);
    msgBox.setText("Kompilacja i wgrywanie zakończone.\nSzczegóły w pliku " + dir.path() + "/log.txt");
    msgBox.setIcon(QMessageBox::Information);
    msgBox.exec();
}

void PLCino::on_actionZapisz_triggered()
{
    if (wybranie_sciezki_zapisu(PROJEKT) >= 0) {
        QFile plik_z_projektem(konfiguracja.sciezka_zapisu_projektu);
        if (!plik_z_projektem.open(QIODevice::WriteOnly)){
            QMessageBox msgBox;
            msgBox.setText("Nie udało się zapisać pliku!");
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.exec();
            return;
        }
        QDataStream zapis(&plik_z_projektem);
        zapis<<(quint32)lista_modeli.count(); //liczba modeli
        for (int i = 0; i < lista_modeli.count(); ++i) {
            zapis<<(quint32)lista_modeli[i]->kolumny_temp;
            if (lista_modeli[i]->model_dane.count() != 0) {
                zapis<<(quint32)lista_modeli[i]->model_dane.count(); //liczba wierszy
                if (lista_modeli[i]->model_dane.count() != 0)
                    zapis<<(quint32)lista_modeli[i]->model_dane.at(0)->count(); //liczba kolumn
            }
            for (int j = 0; j < lista_modeli[i]->model_dane.count(); ++j) {
                for (int k = 0; k < lista_modeli[i]->model_dane.at(j)->count(); ++k) {
                    zapis<<(quint32)lista_modeli[i]->model_dane.at(j)->at(k)->rodzaj<<(quint32)lista_modeli[i]->model_dane.at(j)->at(k)->rodzaj2<<lista_modeli[i]->model_dane.at(j)->at(k)->nazwa<<lista_modeli[i]->model_dane.at(j)->at(k)->zmienna<<lista_modeli[i]->model_dane.at(j)->at(k)->parametry;
                }
            }
        }
        zapis<<(quint32)lista_uzywanych_zmiennych.count();
        for (QMap<QString, zmienna_w_arduino>::iterator i = lista_uzywanych_zmiennych.begin(); i != lista_uzywanych_zmiennych.end(); ++i) {
            zapis<<i.key();
            zapis<<i.value().numer_pinu;
            zapis<<i.value().rodzaj_pinu;
            zapis<<i.value().typ_zmiennej;
        }
        zapis<<konfiguracja.nazwa_wybranego_portu<<konfiguracja.sciezka_zapisu_projektu<<(quint32)konfiguracja.wybrana_plytka;
        plik_z_projektem.flush();
        plik_z_projektem.close();
        QMessageBox msgBox;
        msgBox.setText("Plik został zapisany");
        msgBox.setIcon(QMessageBox::Information);
        msgBox.exec();
    }
}

void PLCino::on_actionOtworz_triggered()
{
    QString sciezka_pliku = QFileDialog::getOpenFileName(this, tr("Otwórz"),
                                                         QDir::currentPath(),
                                                         tr("Projekty (*.plc)"));
    if(sciezka_pliku.isEmpty())
        return;
    QFile plik_z_projektem(sciezka_pliku);
    if (!plik_z_projektem.open(QIODevice::ReadOnly)){
        QMessageBox msgBox;
        msgBox.setText("Nie udało się otworzyć pliku!");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
        return;
    }
    on_actionNowy_triggered();
    QDataStream odczyt(&plik_z_projektem);
    quint32 liczba_zapisanych_modeli;
    odczyt>>liczba_zapisanych_modeli;
    for (quint32 i = 0; i < liczba_zapisanych_modeli; ++i) {
        quint32 kolumny_temp, liczba_wierszy_w_modelu;
        odczyt>>kolumny_temp;
        odczyt>>liczba_wierszy_w_modelu;
        quint32 liczba_kolumn_w_modelu;
        if (liczba_wierszy_w_modelu != 0) {
            odczyt>>liczba_kolumn_w_modelu;
        }
        else {
            liczba_kolumn_w_modelu = 0;
        }
        lista_modeli.insert(i, new model_drabinka(this, liczba_kolumn_w_modelu, liczba_wierszy_w_modelu));
        lista_modeli[i]->kolumny_temp=kolumny_temp;
        for (quint32 j = 0; j < liczba_wierszy_w_modelu; ++j) {
            for (quint32 k = 0; k < liczba_kolumn_w_modelu; ++k) {
                elementy rodzaj_temp;
                quint32 rodzaj2_temp;
                QString nazwa_temp, zmienna_temp;
                odczyt>>(quint32&)rodzaj_temp>>(quint32&)rodzaj2_temp>>nazwa_temp>>zmienna_temp>>lista_modeli[i]->model_dane.at(j)->at(k)->parametry;
                lista_modeli[i]->model_dane.at(j)->at(k)->rodzaj = rodzaj_temp;
                lista_modeli[i]->model_dane.at(j)->at(k)->rodzaj2 = rodzaj2_temp;
                lista_modeli[i]->model_dane.at(j)->at(k)->nazwa = nazwa_temp;
                lista_modeli[i]->model_dane.at(j)->at(k)->zmienna = zmienna_temp;
            }
        }
    }
    quint32 liczba_zapisanych_uzywanych_zmiennych;
    odczyt>>liczba_zapisanych_uzywanych_zmiennych;
    for (quint32 i = 0; i < liczba_zapisanych_uzywanych_zmiennych; ++i) {
        QString klucz_temp, numer_pinu_temp;
        quint32 typ_zmiennej_temp, rodzaj_pinu_temp;
        odczyt>>klucz_temp>>numer_pinu_temp>>typ_zmiennej_temp>>rodzaj_pinu_temp;
        lista_uzywanych_zmiennych.insert(klucz_temp, {numer_pinu_temp, rodzaj_pinu_temp, typ_zmiennej_temp});
    }
    odczyt>>konfiguracja.nazwa_wybranego_portu>>konfiguracja.sciezka_zapisu_projektu>>(quint32&)konfiguracja.wybrana_plytka;
    switch (konfiguracja.wybrana_plytka) {
    case nano:
        ui->actionNano->setChecked(true);
        ui->actionMega->setChecked(false);
        ui->actionLeonadro->setChecked(false);
        break;
    case leonardo:
        ui->actionNano->setChecked(false);
        ui->actionMega->setChecked(false);
        ui->actionLeonadro->setChecked(true);
        break;
    case mega:
        ui->actionNano->setChecked(false);
        ui->actionMega->setChecked(true);
        ui->actionLeonadro->setChecked(false);
        break;
    default:
        break;
    }
    for (int i = 0; i < lista_modeli.count(); ++i) {
        lista_obwodow.insert(i, new QTableView(this));
        lista_obwodow[i]->setModel(lista_modeli[i]);
        lista_obwodow[i]->setAcceptDrops(true);
        lista_obwodow[i]->setDropIndicatorShown(true);
        lista_obwodow[i]->setDragDropOverwriteMode(true);
        lista_obwodow[i]->setSelectionMode(QAbstractItemView::SingleSelection); //możliwość zaznaczenia tylko jednej komórki
        lista_obwodow[i]->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
        lista_obwodow[i]->setMinimumHeight(400);
        lista_obwodow[i]->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
        lista_obwodow[i]->verticalHeader()->setDefaultSectionSize(100);
        lista_obwodow[i]->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
        lista_obwodow[i]->horizontalHeader()->setDefaultSectionSize(100);
        lista_obwodow[i]->adjustSize();
        ui->verticalLayout->addWidget(lista_obwodow[i],0);
        connect(lista_obwodow[i], SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(edycja_wlasciwosci(const QModelIndex &))); //podłączenie sygnału podwójnego kliknięcia do metody edycja_wlasciwosci
    }
    plik_z_projektem.flush();
    plik_z_projektem.close();
}

void PLCino::on_actionEdycja_wlasciwosci_triggered()
{
    for (int i = 0; i < lista_obwodow.size(); i++) {
        if(lista_obwodow[i]->hasFocus()) {
            QModelIndexList zaznaczony_element = lista_obwodow[i]->selectionModel()->selectedIndexes(); //zawsze będzie tylko jeden element, bo wyłączone jest zaznaczanie wielu elementów w QTableView
            if(zaznaczony_element.length() != 0) {
                edycja_wlasciwosci(zaznaczony_element[0]);
                break;
            }
        }
    }
}

void PLCino::on_actionUsun_element_triggered()
{
    for (int i = 0; i < lista_obwodow.size(); i++) {
        if(lista_obwodow[i]->hasFocus()) {
            QModelIndexList zaznaczony_element = lista_obwodow[i]->selectionModel()->selectedIndexes(); //zawsze będzie tylko jeden element, bo wyłączone jest zaznaczanie wielu elementów w QTableView
            if(zaznaczony_element.length() != 0) {
                lista_modeli[i]->model_dane.at(zaznaczony_element[0].row())->replace(zaznaczony_element[0].column(), new elementy_drabinki());
                break;
            }
        }
    }
}

void PLCino::on_actionWgraj_plik_C_do_Arduino_triggered()
{
    QMessageBox msgBox;
    if (konfiguracja.wybrana_plytka == brak || konfiguracja.nazwa_wybranego_portu.isEmpty()) {
        msgBox.setText("Nie skonfigurowano ustawień układu Arduino!");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
        return;
    }
    QString sciezka_pliku = QFileDialog::getOpenFileName(this, tr("Otwórz"),
                                                         QDir::currentPath(),
                                                         tr("Kod źródłowy Arduino (*.ino)"));
    if (sciezka_pliku.isEmpty())
        return;
    QDir dir = QDir::root();
    dir.rmpath("temp/");
    dir.mkpath("temp/");
    dir.cd("temp/");

    QFile log(dir.path() + "/log.txt");
    if (!log.open(QIODevice::WriteOnly)){
        QMessageBox msgBox;
        msgBox.setText("Nie udało utworzyć pliku log!");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
        return;
    }
    QTextStream out_log(&log);
    QProcess proces_arduino_builder;
    QProcess proces_avrdude;
    QSerialPort odblokowanie_mikrokontrolera;
    QList<QSerialPortInfo> porty_przed_resetem;
    QList<QSerialPortInfo> porty_po_resecie;
    QString COM_bootloadera;
    statusBar()->showMessage("Kompilacja do formatu Intel HEX...");
    switch (konfiguracja.wybrana_plytka) {
    case nano:
        proces_arduino_builder.setProcessChannelMode(QProcess::MergedChannels);
        proces_arduino_builder.start(("arduino-builder.exe -hardware hardware -tools har"
                      "dware\\tools -tools tools-builder -fqbn arduino:avr:nano:cpu=atmega328 -build-pat"
                      "h " + dir.absolutePath() + " -compile " + sciezka_pliku).toStdString().c_str());
        proces_arduino_builder.waitForFinished(-1);
        out_log<<proces_arduino_builder.readAll();
        proces_avrdude.setProcessChannelMode(QProcess::MergedChannels);
        statusBar()->showMessage("Wgrywanie programu do Arduino...");
        proces_avrdude.start(("avrdude.exe -v -C\"avrdude.conf\" -pm328p -carduino -P " + konfiguracja.nazwa_wybranego_portu +
                              " -b57600 -D -Uflash:w:" + dir.absolutePath() + "/" + sciezka_pliku.section('/', -1) + ".hex:i").toStdString().c_str());
        proces_avrdude.waitForFinished(10000);
        out_log<<proces_avrdude.readAll();
        break;
    case leonardo:
        proces_arduino_builder.setProcessChannelMode(QProcess::MergedChannels);
        proces_arduino_builder.start(("arduino-builder.exe -hardware hardware -tools har"
                      "dware\\tools -tools tools-builder -fqbn arduino:avr:leonardo:cpu=atmega32u4 -build-pat"
                      "h " + dir.absolutePath() + " -compile " + sciezka_pliku).toStdString().c_str());
        proces_arduino_builder.waitForFinished(-1);
        out_log<<proces_arduino_builder.readAll();
        proces_avrdude.setProcessChannelMode(QProcess::MergedChannels);
        odblokowanie_mikrokontrolera.setPortName(konfiguracja.nazwa_wybranego_portu);
        odblokowanie_mikrokontrolera.setBaudRate(1200);
        porty_przed_resetem = QSerialPortInfo::availablePorts();
        statusBar()->showMessage("Uruchamianie bootloadera...");
        odblokowanie_mikrokontrolera.open(QIODevice::ReadWrite);
        QThread::msleep(2000);
        porty_po_resecie = QSerialPortInfo::availablePorts();
        COM_bootloadera = poszukiwanie_portu_bootloadera(&porty_przed_resetem, &porty_po_resecie);
        odblokowanie_mikrokontrolera.close();
        statusBar()->showMessage("Wgrywanie programu do Arduino...");
        proces_avrdude.start(("avrdude.exe -v -C\"avrdude.conf\" -p atmega32u4 -c avr109 -P " + COM_bootloadera +
                              " -b 57600 -D -Uflash:w:" + dir.absolutePath() + "/" + sciezka_pliku.section('/', -1) + ".hex:i").toStdString().c_str());
        proces_avrdude.waitForFinished(10000);
        out_log<<proces_avrdude.readAll();
        break;
    case mega:
        proces_arduino_builder.setProcessChannelMode(QProcess::MergedChannels);
        proces_arduino_builder.start(("arduino-builder.exe -hardware hardware -tools har"
                      "dware\\tools -tools tools-builder -fqbn arduino:avr:mega:cpu=atmega2560 -build-pat"
                      "h " + dir.absolutePath() + " -compile " + sciezka_pliku).toStdString().c_str());
        proces_arduino_builder.waitForFinished(-1);
        out_log<<proces_arduino_builder.readAll();
        proces_avrdude.setProcessChannelMode(QProcess::MergedChannels);
        statusBar()->showMessage("Wgrywanie programu do Arduino...");
        proces_avrdude.start(("avrdude.exe -v -C\"avrdude.conf\" -pm2560 -c wiring -P " + konfiguracja.nazwa_wybranego_portu +
                              " -b 115200 -D -Uflash:w:" + dir.absolutePath() + "/" + sciezka_pliku.section('/', -1) + ".hex:i").toStdString().c_str());
        proces_avrdude.waitForFinished(10000);
        out_log<<proces_avrdude.readAll();
        break;
    default:
        break;
    }
    log.close();
    statusBar()->showMessage("Wgrywanie zakończone", 5000);
    msgBox.setText("Wgrywanie zakończone.\nSzczegóły w pliku " + dir.path() + "/log.txt");
    msgBox.setIcon(QMessageBox::Information);
    msgBox.exec();

}
